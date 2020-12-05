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

int get_char() {
	return _getch();
}

void close() {

}

#else

#include <curses.h>

WINDOW* window;

void init_screen() {
	window = initscr();
	start_color();
	raw();
	keypad(stdscr, true);
}

int get_char() {
	return getch();
}

void close() {
	endwin();
}

void cursor_move(int x, int y) {
	move(y, x);
	refresh();
}

void set_cursor_color(int foreground, int background) {
	short curseFg = -1;
	short curseBg = -1;

	switch(foreground) {
		case attributes::BLACK:
			curseFg = COLOR_BLACK;
			break;
		case attributes::CYAN:
			curseFg = COLOR_CYAN;
			break;
		case attributes::BLUE:
			curseFg = COLOR_BLUE;
			break;
		case attributes::GREEN:
			curseFg = COLOR_GREEN;
			break;
		case attributes::MAGENTA:
			curseFg = COLOR_MAGENTA;
			break;
		case attributes::RED:
			curseFg = COLOR_RED;
			break;
		case attributes::WHITE:
			curseFg = COLOR_WHITE;
			break;
		case attributes::YELLOW:
			curseFg = COLOR_YELLOW;
			break;
		default: break;
	}

	switch(background) {
		case attributes::BACKGROUND_BLACK:
			curseBg = COLOR_BLACK;
			break;
		case attributes::BACKGROUND_CYAN:
			curseBg = COLOR_CYAN;
			break;
		case attributes::BACKGROUND_BLUE:
			curseBg = COLOR_BLUE;
			break;
		case attributes::BACKGROUND_GREEN:
			curseBg = COLOR_GREEN;
			break;
		case attributes::BACKGROUND_MAGENTA:
			curseBg = COLOR_MAGENTA;
			break;
		case attributes::BACKGROUND_RED:
			curseBg = COLOR_RED;
			break;
		case attributes::BACKGROUND_WHITE:
			curseBg = COLOR_WHITE;
			break;
		case attributes::BACKGROUND_YELLOW:
			curseBg = COLOR_YELLOW;
			break;
		default: break;
	}

	init_pair(1, curseFg, curseBg);
	attron(COLOR_PAIR(1));
	refresh();
}

void screen_print_text(const char* text) {
	printw(text);
}

arrow is_arrow_key(int c) {
	switch(c) {
		case KEY_UP: return arrow::UP;
		case KEY_DOWN: return arrow::DOWN;
		case KEY_LEFT: return arrow::LEFT;
		case KEY_RIGHT: return arrow::RIGHT;
		default: return arrow::NONE;
	}
}

#endif
