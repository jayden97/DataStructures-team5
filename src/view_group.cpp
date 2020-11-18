#include <iostream>
#include "view_group.h"

view_group::view_group(int width, int height): view(0, 0, width, height) {
	this->children = std::vector<view*>();
}

view_group::~view_group() {
	for(auto& itr : this->children) {
		delete itr;
		itr = nullptr;
	}
}

void view_group::add_child(view* child) {
	if(child->has_parent())
		throw std::invalid_argument("view_group: child already has a parent");

	child->_set_parent(this);
	this->children.push_back(child);
}

view* view_group::get_child(int id) {
	for(auto& itr : this->children) {
		if(itr->get_id() == id)
			return itr;
	}

	return nullptr;
}

void view_group::destroy_child(int id) {
	for(auto itr = this->children.begin(); itr != this->children.end(); ++itr) {
		if((*itr)->get_id() == id) {
			this->children.erase(itr);
			delete *itr;
			*itr = nullptr;
			break;
		}
	}
}

void view_group::invalidate() {
	for(auto& child : this->children) {
		child->invalidate(false);
	}

	view::invalidate();
}

bool is_in_middle(int target, int left, int right) {
	return (target - left) * (target - right) < 0;
}

bool is_stacked(view* v, const rect &r) {
	vector2 start = r.get_start();
	vector2 end = r.get_end();

	return (is_in_middle(start.get_x(), v->get_x(), v->get_x() + v->get_width())
		|| is_in_middle(end.get_x(), v->get_x(), v->get_x() + v->get_width()))
		&& (is_in_middle(start.get_y(), v->get_y(), v->get_y() + v->get_height())
		|| is_in_middle(end.get_y(), v->get_y(), v->get_y() + v->get_height()));
}

void view_group::invalidate(const rect &r) {
	bool must_request_layout = this->has_layout_requested_child();
	if(must_request_layout) {
		this->status_flag |= FLAG_REDRAW_BACKGROUND;
	}

	vector2 start = r.get_start();
	vector2 end = r.get_end();
	for(auto& child : this->children) {
		if(must_request_layout || is_stacked(child, r)) {
			// do not forward again to me
			child->invalidate(rect(
					vector2(start.get_x() - this->x, start.get_y() - this->y),
					vector2(end.get_x() - this->x, end.get_y() - this->y)
			), false);
		}
	}

	view::invalidate(r);
}

bool view_group::has_layout_requested_child() const {
	for(auto& itr : this->children) {
		if(itr->status_flag & FLAG_INVALIDATE_LAYOUT) return true;
	}

	return false;
}

void view_group::draw(canvas &c) {
	for(auto& child : this->children) {
		canvas sub = c.sub_canvas(child->get_x(), child->get_y(), child->get_width(), child->get_height());
		child->invoke_redraw(sub);
	}
}

std::vector<view*> view_group::get_children() const {
	// this will not copy children view itself, only copies vector
	return std::vector<view*>(this->children);
}

int view_group::get_type() const {
	return TYPE;
}
