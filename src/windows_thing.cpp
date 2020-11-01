#include "windows_thing.h"

#if defined WIN32
#include <Windows.h>

void doWindowsStuff() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD dwMode = 0;
	GetConsoleMode(handle, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(handle, dwMode);
}
#else
void doWindowsStuff() {
	// empty code block
}
#endif
