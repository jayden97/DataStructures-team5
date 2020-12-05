#include "attributes.h"
#include "platform_dependant.h"
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

void window::start_input() {
	if(this->wait_keyboard) return;

	this->wait_keyboard = true;

	while(this->wait_keyboard) {
		int c = get_char();
		arrow a = is_arrow_key(c);
		if(a == arrow::UP) {

		}
	}
}
