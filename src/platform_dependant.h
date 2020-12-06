#ifndef DSP_TEAM_PROJECT_PLATFORM_DEPENDANT_H
#define DSP_TEAM_PROJECT_PLATFORM_DEPENDANT_H

#if !defined(CONSOLE_OUTPUT_MODE_ANSI) && !defined(CONSOLE_OUTPUT_MODE_NCURSES)

#if defined WIN32
#define CONSOLE_OUTPUT_MODE_ANSI
#else
#define CONSOLE_OUTPUT_MODE_NCURSES
#endif // defined WIN32

#endif

#include <string>

void init_screen();

int get_char();

void close();

void cursor_move(int x, int y);

void set_cursor_color(int foreground, int background);

void screen_print_text(const std::string& text);

arrow is_arrow_key(int c);

void get_width_height(int& x, int& y);

#endif //DSP_TEAM_PROJECT_PLATFORM_DEPENDANT_H
