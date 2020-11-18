#include "canvas.h"
#include "fill_drawable.h"
#include "linear_layout.h"
#include "text_view.h"
#include "window.h"
#include "windows_thing.h"
#include <iostream>

using namespace std;

int main() {
	doWindowsStuff();

	auto* w = new window(10, 10);

	auto* layout = new linear_layout(VERTICAL, 10, 10);
	layout->set_xy(0, 0);
	layout->set_background(new fill_drawable(ansi::BACKGROUND_BLUE));
	layout->set_width(10);
	layout->set_height(10);

	auto* tv1 = new text_view("hello world\nasdf");
	tv1->set_width(12);
	tv1->set_height(3);
	tv1->set_text_color(ansi::CYAN);
	layout->add_child(tv1);

	auto* tv2 = new text_view("good");
	tv2->set_width(12);
	tv2->set_height(2);
	layout->add_child(tv2);

	w->set_view(layout);
	w->render();

	tv1->set_xy(5, 5);
	tv1->set_width(5);
	tv1->set_text_color(ansi::MAGENTA);

	tv2->set_text("great");
	layout->refresh_layout();

	delete w;

	return 0;
}
