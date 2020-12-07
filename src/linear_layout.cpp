#include "linear_layout.h"

linear_layout::linear_layout(orientation o, int width, int height):
	view_group(width, height), orientation_value(o), occupied_size(0) {
	// intentional empty block
}

void linear_layout::add_child(view *child) {
	view_group::add_child(child);

	if(this->orientation_value == HORIZONTAL) {
		child->set_xy(this->occupied_size, 0);
		this->occupied_size += child->get_width();
	}else{
		child->set_xy(0, this->occupied_size);
		this->occupied_size += child->get_height();
	}
}

void linear_layout::destroy_child(int id) {
	view* target = this->get_child(id);
	if(target == nullptr) return;

	if(this->orientation_value == HORIZONTAL) {
		int end = target->get_width() + target->get_x();

		for(auto& child : this->children) {
			if(end <= child->get_x()) {
				child->set_xy(child->get_x() - target->get_width(), child->get_y());
			}
		}
	}else{ // vertical
		int end = target->get_height() + target->get_y();
		for(auto& child : this->children) {
			if(end <= child->get_y()) {
				child->set_xy(child->get_x(), child->get_y() - target->get_height());
			}
		}
	}

	view_group::destroy_child(id);
}

orientation linear_layout::get_orientation() const {
	return this->orientation_value;
}
