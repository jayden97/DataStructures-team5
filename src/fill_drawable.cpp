#include "fill_drawable.h"

fill_drawable::fill_drawable(int color): drawable(0, 0), color(color) {
}

void fill_drawable::draw(canvas &c) {
	int width = c.get_width();
	int height = c.get_height();

	c.set_background_color(this->color);
	for(int y = 0; y < height; y++) {
		c.move_to(0, y);
		c.draw_text(std::string(width, ' '));
	}
}
