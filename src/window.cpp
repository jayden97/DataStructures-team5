#include "window.h"

window::window() {
	this->root = new root_layout();
}

window::~window() {
	delete this->root;
}

void window::set_view(view *v) {
	this->root->add_child(v);
}

void window::render() const {
	if(this->root != nullptr) {
		this->root->invalidate();
	}
}
