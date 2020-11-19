#include <iostream>
#include "ansi.h"

void ansi::move_cursor(int x, int y) {
	std::cout << "\x1b[" << y << ";" << x << "H";
}

void ansi::set_colors(int color, int background_color, bool brighten) {
	if(!validate_color(color))
		throw std::invalid_argument("invalid color");

	if(!validate_background_color(background_color))
		throw std::invalid_argument("invalid background color");

	if(color == ansi::TRANSPARENT && background_color == ansi::TRANSPARENT)
		throw std::invalid_argument("at least one color must not be transparent");

	std::cout << "\x1b[";
	if(color != ansi::TRANSPARENT) {
		std::cout << color;
	}

	if(color != ansi::TRANSPARENT && background_color != ansi::TRANSPARENT) {
		std::cout << ";";
	}

	if(background_color != ansi::TRANSPARENT) {
		std::cout << background_color;
	}

	if(brighten)
		std::cout << ";1";
	std::cout << "m";
}

bool ansi::validate_color(int color) {
	return !((color < 30 || 37 < color) && color != 0 && color != -1);
}

bool ansi::validate_background_color(int background_color) {
	return !((background_color < 40 || 47 < background_color) && background_color != 0 && background_color != -1);
}
