#include "windows_thing.h"
#include <iostream>

int main() {
	doWindowsStuff();

	std::cout << "\x1b[10;5H" << "HELLO!" << std::endl;
	std::cout << "World" << std::endl;

	return 0;
}
