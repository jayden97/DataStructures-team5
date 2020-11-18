#include "rect.h"

rect::rect(point start, point end): start(start), end(end) {
	// intentional empty block
}

point rect::get_start() const {
	return this->start;
}

point rect::get_end() const {
	return this->end;
}
