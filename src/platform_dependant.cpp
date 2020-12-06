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

#include <curses.h>
#include <unordered_map>
#include <string.h>

std::unordered_map<int, std::unordered_map<int, short>> table;

short current_fg = -1;
short current_bg = -1;

short pair_count = 0;

WINDOW* window;

template<typename MAP>
const typename MAP::mapped_type& get_with_default(const MAP& m,
                                                  const typename MAP::key_type& key,
                                                  const typename MAP::mapped_type& default_value) {
	auto it = m.find(key);
	if (it == m.end())
		return default_value;

	return it->second;
}

void init_pairs() {
	for(short fg = -1; fg <= 7; fg++) {
		for(short bg = -1; bg <= 7; bg++) {
			init_pair(++pair_count, fg, bg);
		}
	}
}

short find_initialized_pair(short fg, short bg) {
	for(short i = 1; i <= pair_count; i++) {
		short f, b;
		pair_content(i, &f, &b);

		if(fg == f && bg == b) return i;
	}

	return -1;
}

short find_background_color(short pair) {
	for(short i = 1; i <= pair_count; i++) {
		if(COLOR_PAIR(i) == pair) {
			short f, b;
			pair_content(i, &f, &b);
			return b;
		}
	}
	return -1;
}

void init_screen() {
	table.clear();

	window = initscr();
	start_color();

	init_pairs();

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

	use_default_colors();

	short pair = find_initialized_pair(curseFg, curseBg);
	attron(COLOR_PAIR(pair));

	current_fg = curseFg;
	current_bg = curseBg;
	refresh();
}

void screen_print_text(const std::string& text) {
	/*for(const char& pchar : text) {
		/*int x, y;
		getyx(curscr, y, x);

		short pair = mvinch(y, x) & A_COLOR;
		if(current_bg == -1) {
			short bg = get_with_default(table[x], y, -1);
			short new_pair = find_initialized_pair(current_fg, bg);
			attron(COLOR_PAIR(new_pair));
			refresh();
		}else{
			table[x][y] = find_background_color(pair);
		}*

		printw(&pchar);
		refresh();
	}*/

	printw(text.c_str());
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

void get_width_height(int& x, int& y) {
	getmaxyx(curscr, y, x);
}

#endif
