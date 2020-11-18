#include "view.h"

view::view(): last_drawn(vector2(-1, -1)) {
	this->id = view_id++;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

view::view(int x, int y, int width, int height): last_drawn(vector2(-1, -1)) {
	this->id = view_id++;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

view::~view() = default;

int view::get_id() const {
	return this->id;
}

void view::_set_parent(view *new_parent) {
	this->parent = new_parent;
}

bool view::has_parent() const {
	return this->parent != nullptr;
}

void view::invalidate() {
	this->must_redrawn = true;
}

bool is_middle(int target, int left, int right) {
	return (left - target) * (right - target) < 0;
}

void view::invalidate(const rect &r) {
	vector2 start_point = r.get_start();
	vector2 end_point = r.get_end();

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
				vector2(start_x + this->x, start_y + this->y),
				vector2(end_x + this->x, end_y + this->y)
				));
	}
}

bool view::must_redraw() const {
	return this->must_redrawn;
}

void view::invoke_redraw() {
	int last_x = this->last_drawn.get_x();
	int last_y = this->last_drawn.get_y();
	if(last_x == -1) {
		if(last_x != this->x || last_y != this->y) {
			// TODO forward invalidation to parent
		}
	}

	vector2 absolute = this->get_absolute_point();
	canvas c(absolute.get_x(), absolute.get_y(), this->width, this->height);
	draw(c);

	this->last_drawn = vector2(this->x, this->y);

	this->must_redrawn = false;
}

vector2 view::get_absolute_point() const {
	if(this->parent == nullptr)
		return {this->x, this->y};

	vector2 parent_point = this->parent->get_absolute_point();
	return {parent_point.get_x() + this->x, parent_point.get_y() + this->y};
}

void view::set_xy(int new_x, int new_y) {
	this->x = new_x;
	this->y = new_y;
}

int view::get_x() const {
	return this->x;
}

int view::get_y() const {
	return this->y;
}

int view::get_width() const {
	return this->width;
}

int view::get_height() const {
	return this->height;
}

int view::get_type() const {
	return TYPE;
}

void view::set_width(int new_width) {
	this->width = new_width;
}

void view::set_height(int new_height) {
	this->height = new_height;
}
