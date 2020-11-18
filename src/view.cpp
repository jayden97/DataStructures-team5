#include "view.h"

view::view(): last_drawn(point(-1, -1)) {
	this->x = 0;
	this->y = 0;
	this->width = parent->width;
	this->height = parent->height;
}

view::view(int x, int y, int width, int height): last_drawn(point(-1, -1)) {
	this->x = x;
	this->y = y;
	this->width = parent->width;
	this->height = parent->height;
}

void view::_set_parent(view *new_parent) {
	this->parent = new_parent;
}

void view::invalidate() {
	this->must_redrawn = true;
}

bool is_middle(int target, int left, int right) {
	return (left - target) * (right - target) < 0;
}

void view::invalidate(const rect &r) {
	point start_point = r.get_start();
	point end_point = r.get_end();

	int start_x = start_point.get_x();
	int start_y = start_point.get_y();
	int end_x = end_point.get_x();
	int end_y = end_point.get_y();

	if(is_middle(this->x, start_x, end_x) || is_middle(this->x + this->width, start_x, end_x)
		|| is_middle(this->y, start_y, end_y) || is_middle(this->y + this->height, start_y, end_y)) {
		this->invalidate();
	}

	if(this->parent != nullptr) {
		this->parent->invalidate(rect(
				point(start_x + this->x, start_y + this->y),
				point(end_x + this->x, end_y + this->y)
				));
	}
}

void view::invoke_redraw() {
	int last_x = this->last_drawn.get_x();
	int last_y = this->last_drawn.get_y();
	if(last_x == -1) {
		if(last_x != this->x || last_y != this->y) {
			// TODO forward invalidation to parent
		}
	}

	canvas c(this->x, this->y, this->width, this->height);
	draw(c);

	this->last_drawn = point(this->x, this->y);

	this->must_redrawn = false;
}

point view::get_absolute_point() const {
	if(this->parent == nullptr)
		return {this->x, this->y};

	point parent_point = this->parent->get_absolute_point();
	return {parent_point.get_x() + this->x, parent_point.get_y() + this->y};
}
