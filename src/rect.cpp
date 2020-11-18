#include "rect.h"

rect::rect(vector2 start, vector2 end): start(start), end(end) {
	// intentional empty block
}

vector2 rect::get_start() const {
	return this->start;
}

vector2 rect::get_end() const {
	return this->end;
}
