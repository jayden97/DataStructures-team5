#ifndef DSP_TEAM_PROJECT_CONSOLE_H
#define DSP_TEAM_PROJECT_CONSOLE_H

class console {
public:
	static void move_cursor(int x, int y);
	static void set_colors(int color, int background_color, bool brighten = false);
	static bool validate_color(int color);
	static bool validate_background_color(int background_color);
};

#endif //DSP_TEAM_PROJECT_CONSOLE_H
