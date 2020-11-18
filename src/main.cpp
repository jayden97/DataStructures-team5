#include "canvas.h"
#include "linear_layout.h"
#include "text_view.h"
#include "window.h"
#include "windows_thing.h"

using namespace std;

int main() {
	doWindowsStuff();

	window w;

	auto* layout = new linear_layout(VERTICAL);
	layout->set_xy(1, 1);
	layout->set_width(10);
	layout->set_height(10);

	auto* tv1 = new text_view("hello world\nasdf");
	tv1->set_width(12);
	tv1->set_height(3);
	layout->add_child(tv1);

	auto* tv2 = new text_view("good");
	tv2->set_width(12);
	tv2->set_height(2);
	layout->add_child(tv2);

	w.set_view(layout);
	w.render();

	return 0;
}
