#include "text_view.h"

text_view::text_view(std::string text_value) {
	this->text = std::move(text_value);
}

void text_view::draw(canvas &c) {
	c.draw_text(this->text);
}
