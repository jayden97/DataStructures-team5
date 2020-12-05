#include "button.h"
#include "fill_drawable.h"

button::button(std::string text): text_view(std::move(text)) {
	this->idle_background = new fill_drawable(ansi::BACKGROUND_WHITE);
	this->hover_background = new fill_drawable(ansi::BACKGROUND_YELLOW);

	this->set_focusable(true);
}

button::~button() {
	delete this->idle_background;
	delete this->hover_background;
}

void button::draw(canvas &c) {
	if(this->is_focused()) {
		if(this->hover_background != nullptr) this->hover_background->draw(c);
	}else{
		if(this->idle_background != nullptr) this->idle_background->draw(c);
	}

	text_view::draw(c);
}
