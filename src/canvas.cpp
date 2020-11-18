#include "ansi.h"
#include "canvas.h"
#include <algorithm>
#include <iostream>
#include <string>

canvas::canvas(int translate_x, int translate_y, int width, int height)
	: translate_x(translate_x), translate_y(translate_y), width(width), height(height),
	is_background_bright(false), background_color(ansi::BACKGROUND_BLACK),
	x(0), y(0), color(ansi::WHITE) {
	// intentional empty code block
}

void canvas::move_to(int new_x, int new_y) {
	this->x = new_x;
	this->y = new_y;
}

void canvas::draw_text(std::string text) const {
	using std::max;

	int current_y = y;
	while(!text.empty()) {
		size_t max_width = max(0, this->width - this->x);
		std::string chunk = eat_chunk(text, max_width);

		ansi::move_cursor(this->translate_x + this->x + 1, this->translate_y + current_y + 1);
		ansi::set_colors(this->color, this->background_color, this->is_background_bright);
		std::cout << chunk;

		++current_y;
	}
}

std::string canvas::eat_chunk(std::string& text, size_t max_width) {
	using std::min;

	size_t index = text.find_first_of('\n');
	if(index == std::string::npos) {
		index = text.length();
	}

	size_t chunk_len = min(index, max_width);
	std::string chunk = text.substr(0, chunk_len);

	if(chunk_len <= index) {
		text = text.substr(min(text.length(), index + 1));
	}else{
		text = text.substr(chunk_len);
	}

	return chunk;
}

void canvas::set_color(int new_color) {
	if((new_color < 30 || 37 < new_color) && new_color != 0)
		throw std::invalid_argument("canvas: invalid color given");

	this->color = new_color;
}

void canvas::set_background_color(int value) {
	if((value < 40 || 47 < value) && value != 0)
		throw std::invalid_argument("canvas: invalid background color given");

	this->background_color = value;
}

void canvas::set_background_bright(bool value) {
	this->is_background_bright = value;
}

int canvas::get_translate_x() const {
	return this->translate_x;
}

int canvas::get_translate_y() const {
	return this->translate_y;
}

int canvas::get_width() const {
	return this->width;
}

int canvas::get_height() const {
	return this->height;
}

canvas canvas::sub_canvas(int sub_x, int sub_y, int max_width, int max_height) const {
	using std::min;

	return {translate_x + sub_x, translate_y + sub_y,
			   min(max_width, width - sub_x), min(max_height, height - sub_y)};
}
