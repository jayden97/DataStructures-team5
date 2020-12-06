#include "attributes.h"
#include "platform_dependant.h"

#if defined WIN32

#include <Windows.h>
#include <conio.h>

void init_screen() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD dwMode = 0;
	GetConsoleMode(handle, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(handle, dwMode);
}

void close() {

}

int get_char() {
	return _getch();
}

void close() {

}

void get_width_height(int& x, int& y) {
	CONSOLE_SCREEN_BUFFER_INFO GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

#else

#include <termios.h>
#include <curses.h>
#include <unordered_map>
#include "console.h"
#include <sstream>
#include <iostream>

void init_screen() {
	// set terminal in raw mode
	struct termios tty_attr{};

	tcgetattr(0,&tty_attr);

	tty_attr.c_lflag &= (~(ICANON|ECHO));
	tty_attr.c_cc[VTIME] = 0;
	tty_attr.c_cc[VMIN] = 1;

	tcsetattr(0,TCSANOW,&tty_attr);
}

int get_char() {
	return getchar();
}

void close() {
}

void cursor_move(int x, int y) {
	std::cout << "\x1b[" << y << ";" << x << "H";
}

void set_cursor_color(int foreground, int background) {
	if(!console::validate_color(foreground))
		throw std::invalid_argument("invalid color");

	if(!console::validate_background_color(background))
		throw std::invalid_argument("invalid background color");

	if(foreground == color::TRANSPARENT && background == color::TRANSPARENT)
		throw std::invalid_argument("at least one color must not be transparent");

	std::stringstream str;
	str << "\x1b[";
	if(foreground != color::TRANSPARENT) {
		str << foreground;
	}

	if(foreground != color::TRANSPARENT && background != color::TRANSPARENT) {
		str << ";";
	}

	if(foreground != color::TRANSPARENT) {
		str << background;
	}

	str << "m";

	std::cout << str.str();
}

void screen_print_text(const std::string& text) {
	std::cout << text;
}

arrow is_arrow_key(int c) {
	if(c == 0x1b) {
		if(getchar() == 0x5b) {
			switch(getchar()) {
				case 'A':
					return arrow::UP;
				case 'B':
					return arrow::DOWN;
				case 'D':
					return arrow::LEFT;
				case 'C':
					return arrow::RIGHT;
			}
		}
	}

	return arrow::NONE;
}

void get_width_height(int& x, int& y) {
	// TODO
	x = 80;
	y = 80;
}

#endif
