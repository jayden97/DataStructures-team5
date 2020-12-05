#include "button.h"
#include "canvas.h"
#include "attributes.h"
#include "fill_drawable.h"
#include "linear_layout.h"
#include "text_view.h"
#include "window.h"
#include "platform_dependant.h"
#include <iostream>

using namespace std;

int main() {
	init_screen();

	auto* w = new window(10, 10);

	auto* layout = new linear_layout(VERTICAL, 10, 10);
	layout->set_xy(0, 0);
	layout->set_background(new fill_drawable(attributes::BACKGROUND_BLUE));
	layout->set_width(10);
	layout->set_height(10);

	auto* tv1 = new button("a");
	tv1->set_width(12);
	tv1->set_height(3);
	tv1->set_focused(true);
	tv1->set_text_color(attributes::CYAN);
	layout->add_child(tv1);

	auto* tv2 = new text_view("good");
	tv2->set_width(12);
	tv2->set_height(2);
	layout->add_child(tv2);

	w->set_view(layout);
	w->render();

	tv1->set_xy(5, 5);
	tv1->set_width(5);
	tv1->set_text_color(attributes::MAGENTA);

	tv2->set_text("great");
	//tv1->set_text("g");

	w->start_input();

	delete w;

	return 0;
}
