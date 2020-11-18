#include "drawable.h"

drawable::drawable(): width(0), height(0) {
	// intentional empty block
}

drawable::drawable(int width, int height): width(width), height(height) {
	// intentional empty block
}

int drawable::get_width() const {
	return this->width;
}

int drawable::get_height() const {
	return this->height;
}

void drawable::set_width(int new_width) {
	this->width = new_width;
}

void drawable::set_height(int new_height) {
	this->height = new_height;
}
