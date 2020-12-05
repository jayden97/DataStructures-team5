#include "text_view.h"

text_view::text_view(std::string text_value) {
	this->text = std::move(text_value);
}

void text_view::draw(canvas &c) {
	c.set_color(this->text_color);
	c.set_background_color(attributes::TRANSPARENT);
	c.draw_text(this->text);
}

void text_view::set_text_color(int color) {
	this->text_color = color;

	this->invalidate();
}

void text_view::set_text(std::string new_text) {
	this->text = std::move(new_text);

	this->invalidate();
}
