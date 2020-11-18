#include "view.h"

view::view(view *parent): parent(parent) {
	this->width = parent->width;
	this->height = parent->height;
}

view::view(view* parent, int width, int height): parent(parent) {
	this->width = parent->width;
	this->height = parent->height;
}
