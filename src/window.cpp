#include "window.h"

window::window(int width, int height) {
	this->root = new root_layout(width, height);
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
