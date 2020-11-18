#include "point.h"

point::point(int x, int y): x(x), y(y) {
	// intentional empty block
}

int point::get_x() const {
	return this->x;
}

int point::get_y() const {
	return this->y;
}

void point::set_x(int new_x) {
	this->x = new_x;
}

void point::set_y(int new_y) {
	this->y = new_y;
}
