#include "canvas.h"
#include "windows_thing.h"

using namespace std;

int main() {
	doWindowsStuff();

	canvas c(5, 5, 20, 10);
	c.draw_text("this is canvas\nwhich will help you\ndraw something on console.");
	return 0;
}
