#include "button.h"
#include "canvas.h"
#include "attributes.h"
#include "fill_drawable.h"
#include "linear_layout.h"
#include "text_view.h"
#include "window.h"
#include "platform_dependant.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
	init_screen();

	ofstream os("log.txt");

	int width, height;
	get_width_height(width, height);
	width -= 1;
	height -= 1;

	auto* w = new window(width, height);

	auto* layout = new linear_layout(VERTICAL, width, height);
	layout->set_xy(0, 0);
	layout->set_background(new fill_drawable(attributes::BACKGROUND_BLUE));

	auto* title = new linear_layout(HORIZONTAL, width, 1);
	auto* title_text = new text_view("Frozen");
	title_text->set_width(width - 1);
	title_text->set_height(1);
	title->add_child(title_text);

	layout->add_child(title);

	for(int row = 0; row < 10; row++) {
		auto* margin_top = new linear_layout(VERTICAL, width, 1);
		layout->add_child(margin_top);

		auto* inner_layout = new linear_layout(HORIZONTAL, width, 1);
		inner_layout->set_background(new fill_drawable(attributes::BACKGROUND_MAGENTA));

		for(int column = 0; column < 10; column++) {
			std::stringstream str;
			str << '[' << row << ';' << column << ']';

			auto* seat = new text_view(str.str());
			seat->set_text_color(attributes::WHITE);
			seat->set_width(8);
			seat->set_height(1);
			inner_layout->add_child(seat);
		}

		layout->add_child(inner_layout);

		auto* margin_bottom = new linear_layout(VERTICAL, width, 1);
		layout->add_child(margin_bottom);
	}

	w->set_view(layout);
	w->render();

	w->start_input();

	delete w;

	os.close();

	return 0;
}
