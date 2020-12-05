#include <iostream>
#include <sstream>
#include "attributes.h"
#include "console.h"
#include "platform_dependant.h"

void console::move_cursor(int x, int y) {
	cursor_move(x, y);
}

void console::set_colors(int color, int background_color, bool brighten) {
	/*if(!validate_color(color))
		throw std::invalid_argument("invalid color");

	if(!validate_background_color(background_color))
		throw std::invalid_argument("invalid background color");

	if(color == attributes::TRANSPARENT && background_color == attributes::TRANSPARENT)
		throw std::invalid_argument("at least one color must not be transparent");

	std::stringstream str;
	str << "\x1b[";
	if(color != attributes::TRANSPARENT) {
		str << color;
	}

	if(color != attributes::TRANSPARENT && background_color != attributes::TRANSPARENT) {
		str << ";";
	}

	if(background_color != attributes::TRANSPARENT) {
		str << background_color;
	}

	if(brighten)
		str << ";1";

	str << "m";*/

	set_cursor_color(color, background_color);
}

bool console::validate_color(int color) {
	return !((color < 30 || 37 < color) && color != 0 && color != -1);
}

bool console::validate_background_color(int background_color) {
	return !((background_color < 40 || 47 < background_color) && background_color != 0 && background_color != -1);
}
