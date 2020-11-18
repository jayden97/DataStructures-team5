#include <iostream>
#include "ansi.h"

void ansi::move_cursor(int x, int y) {
	std::cout << "\x1b[" << y << ";" << x << "H";
}

void ansi::set_colors(int color, int background_color, bool brighten) {
	if((color < 30 || 37 < color) && color != 0)
		throw std::invalid_argument("invalid color");

	if((background_color < 40 || 47 < background_color) && background_color != 0)
		throw std::invalid_argument("invalid background color");

	std::cout << "\x1b[" << color << ";" << background_color;
	if(brighten)
		std::cout << ";1";
	std::cout << "m";
}
