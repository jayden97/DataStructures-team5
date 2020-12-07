#include "console.h"
#include "canvas.h"
#include "attributes.h"
#include "platform_dependant.h"
#include <algorithm>
#include <iostream>
#include <string>

canvas::canvas(int translate_x, int translate_y, int width, int height, mask_filter mask)
	: translate_x(translate_x), translate_y(translate_y), width(width), height(height),
	  is_background_bright(false), background_color(color::BACKGROUND_BLACK),
	  x(0), y(0), color(color::WHITE), mask(mask) {
	// intentional empty code block
}

canvas::canvas(int translate_x, int translate_y, int width, int height,
			   int color, int background_color, bool is_background_bright, mask_filter mask)
		: translate_x(translate_x), translate_y(translate_y), width(width), height(height),
		  is_background_bright(is_background_bright), background_color(background_color),
		  x(0), y(0), color(color), mask(mask) {
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

		console::set_colors(this->color, this->background_color, this->is_background_bright);

		if(this->mask == nullptr) {
			console::move_cursor(this->translate_x + this->x + 1, this->translate_y + current_y + 1);
			//std::cout << chunk;
			screen_print_text(chunk);
		}else{
			int chunk_len = chunk.length();
			for(int i = 0; i < chunk_len; ++i) {
				if((*this->mask)(this->x + i, current_y)) {
					console::move_cursor(this->translate_x + this->x + i + 1, this->translate_y + current_y + 1);
					//std::cout << chunk[i];
					screen_print_text(std::string(1, chunk[i]));
				}
			}
		}

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
	if(!console::validate_color(new_color))
		throw std::invalid_argument("canvas: invalid color given");

	this->color = new_color;
}

void canvas::set_background_color(int value) {
	if(!console::validate_background_color(value))
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

canvas canvas::sub_canvas(int sub_x, int sub_y, int max_width, int max_height, mask_filter filter) const {
	using std::min;

	return {translate_x + sub_x, translate_y + sub_y,
			   min(max_width, width - sub_x), min(max_height, height - sub_y),
			   this->color, this->background_color, this->is_background_bright, filter};
}
