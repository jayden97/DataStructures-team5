#include "button.h"
#include "fill_drawable.h"

button::button(std::string text): text_view(std::move(text)) {
	this->idle_background = new fill_drawable(attributes::BACKGROUND_WHITE);
	this->hover_background = new fill_drawable(attributes::BACKGROUND_YELLOW);

	this->set_focusable(true);
}

button::~button() {
	delete this->idle_background;
	delete this->hover_background;
}

void button::draw(canvas &c) {
	canvas sub_canvas = c.sub_canvas(0, 0, c.get_width(), c.get_height());

	if(this->is_focused()) {
		if(this->hover_background != nullptr) this->hover_background->draw(sub_canvas);
	}else{
		if(this->idle_background != nullptr) {
			this->idle_background->draw(sub_canvas);
		}
	}

	c.set_color(this->is_focused() ? attributes::YELLOW : attributes::WHITE);
	c.set_background_color(attributes::TRANSPARENT);
	c.draw_text(text_view::get_text());
}
