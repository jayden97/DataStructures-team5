#include "vector2.h"

vector2::vector2(int x, int y): x(x), y(y) {
	// intentional empty block
}

int vector2::get_x() const {
	return this->x;
}

int vector2::get_y() const {
	return this->y;
}

void vector2::set_x(int new_x) {
	this->x = new_x;
}

void vector2::set_y(int new_y) {
	this->y = new_y;
}
