#ifndef DSP_TEAM_PROJECT_ANSI_H
#define DSP_TEAM_PROJECT_ANSI_H

class ansi {
public:
	static const int BLACK = 30;
	static const int RED = 31;
	static const int GREEN = 32;
	static const int YELLOW = 33;
	static const int BLUE = 34;
	static const int MAGENTA = 35;
	static const int CYAN = 36;
	static const int WHITE = 37;
	static const int RESET = 0;

	static const int BACKGROUND_BLACK = 40;
	static const int BACKGROUND_RED = 41;
	static const int BACKGROUND_GREEN = 42;
	static const int BACKGROUND_YELLOW = 43;
	static const int BACKGROUND_BLUE = 44;
	static const int BACKGROUND_MAGENTA = 45;
	static const int BACKGROUND_CYAN = 46;
	static const int BACKGROUND_WHITE = 47;

	static void move_cursor(int x, int y);
	static void set_colors(int color, int background_color, bool brighten = false);
};

#endif //DSP_TEAM_PROJECT_ANSI_H
