#include <iostream>
#include "root_layout.h"

root_layout::root_layout(int width, int height): view_group(width, height) {
	// intentional empty block
}

void root_layout::add_child(view *child) {
	if(!this->children.empty()) {
		throw std::out_of_range("root_layout: root may have only one child view");
	}

	view_group::add_child(child);
}

void root_layout::invalidate() {
	if(!this->children.empty()) {
		view* child = this->children[0];
		canvas root = canvas(child->get_x(), child->get_y(), child->get_width(), child->get_height());
		this->children[0]->invoke_redraw(root);
	}
}

void root_layout::invalidate(const rect &r) {
	this->invalidate();
}

void root_layout::request_layout() {
	// this->invalidate();
}

view* root_layout::get_view() const {
	if(!this->children.empty()) {
		return this->children[0];
	}

	return nullptr;
}
