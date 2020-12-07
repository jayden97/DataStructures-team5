#include "fill_drawable.h"
#include "view.h"

view::view():
	last_drawn(vector2(-1, -1)), last_size(vector2(-1, -1)) {
	this->id = view_id++;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->background = nullptr;
}

view::view(int x, int y, int width, int height):
	last_drawn(vector2(-1, -1)), last_size(vector2(-1, -1)) {
	this->id = view_id++;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->background = nullptr;
}

view::~view() {
	delete this->background;
}

int view::get_id() const {
	return this->id;
}

void view::_set_parent(view *new_parent) {
	this->parent = new_parent;
}

bool view::has_parent() const {
	return this->parent != nullptr;
}

view* view::get_parent() const {
	return this->parent;
}

void view::invalidate() {
	this->invalidate(true);
}

void view::invalidate(const rect &r) {
	this->invalidate(r, true);
}

void view::invalidate(bool forward_parent) {
	if(this->status_flag & FLAG_INVALIDATED) return;

	this->status_flag |= FLAG_INVALIDATED;

	if(forward_parent && this->parent != nullptr) {
		this->parent->invalidate(rect(
				vector2(this->x, this->y),
				vector2(this->x + this->width, this->y + this->height)
		));
	}
}

void view::invalidate(const rect &r, bool forward_parent) {
	if(this->status_flag & FLAG_INVALIDATED) return;
	this->status_flag |= FLAG_INVALIDATED;

	vector2 start_point = r.get_start();
	vector2 end_point = r.get_end();

	int start_x = start_point.get_x();
	int start_y = start_point.get_y();
	int end_x = end_point.get_x();
	int end_y = end_point.get_y();

	if(forward_parent && this->parent != nullptr) {
		this->parent->invalidate(rect(
				vector2(start_x + this->x, start_y + this->y),
				vector2(end_x + this->x, end_y + this->y)
		));
	}
}

void view::refresh_layout() {
	this->refresh_layout(true);
}

void view::refresh_layout(bool forward_parent) {
	this->status_flag |= FLAG_INVALIDATE_LAYOUT;

	this->invalidate(rect(
			vector2(this->x, this->x + this->width),
			vector2(this->y, this->y + this->height)
	), forward_parent);
}

bool view::must_redraw() const {
	return this->status_flag & FLAG_INVALIDATED;
}

void view::invoke_redraw(canvas& root_canvas) {
	if(this->status_flag & FLAG_REDRAW_BACKGROUND) {
		if(this->background != nullptr) {
			this->background->draw(root_canvas);
		}
	}

	canvas sub_canvas = root_canvas.sub_canvas(0, 0, this->width, this->height);
	this->draw(sub_canvas);

	this->last_drawn = vector2(this->x, this->y);
	this->last_size = vector2(this->width, this->height);

	this->status_flag = 0;
}

vector2 view::get_absolute_point() const {
	if(this->parent == nullptr)
		return {this->x, this->y};

	vector2 parent_point = this->parent->get_absolute_point();
	return {parent_point.get_x() + this->x, parent_point.get_y() + this->y};
}

void view::set_background(drawable* new_background) {
	this->background = new_background;
}

drawable* view::get_background() const {
	return this->background;
}

void view::set_click_listener(const view::click_listener_t&& listener) {
	this->click_listener = std::move(listener);
}

const view::click_listener_t& view::get_click_listener() const {
	return this->click_listener;
}

void view::click() {
	if(this->click_listener != nullptr) {
		(this->click_listener)(this);
	}
}

void view::add_child(view *v) {
	throw std::invalid_argument("view cannot have child");
}

std::vector<view*> view::get_children() {
	return std::vector<view*>();
}

void view::set_xy(int new_x, int new_y) {
	this->x = new_x;
	this->y = new_y;

	this->refresh_layout();
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

	this->refresh_layout();
}

void view::set_height(int new_height) {
	this->height = new_height;

	this->refresh_layout();
}

void view::set_focusable(bool value) {
	this->focusable = value;
}

bool view::is_focusable() const {
	return this->focusable;
}

void view::set_focused(bool value) {
	if(this->focused != value) {
		this->focused = value;

		this->invalidate();
	}
}

bool view::is_focused() const {
	return this->focusable && this->focused;
}
