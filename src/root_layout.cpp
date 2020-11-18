#include <iostream>
#include "root_layout.h"

void root_layout::add_child(view *child) {
	if(!this->children.empty()) {
		throw std::out_of_range("root_layout: root may have only one child view");
	}

	view_group::add_child(child);
}

void root_layout::invalidate() {
	redraw_all(this);
}

void root_layout::invalidate(const rect &r) {
	this->invalidate();
}

void root_layout::redraw_all(view* target) const {
	if(target->must_redraw()) {
		target->invoke_redraw();
	}

	if(target->get_type() == view_group::TYPE) {
		auto* group = dynamic_cast<view_group*>(target);
		auto children = group->get_children();
		for(auto& itr : children) {
			redraw_all(itr);
		}
	}
}
