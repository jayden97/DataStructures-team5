#ifndef DSP_TEAM_PROJECT_CANVAS_H
#define DSP_TEAM_PROJECT_CANVAS_H

#include <string>

class canvas {
public:
	canvas(int translate_x, int translate_y, int width, int height);

	void move_to(int x, int y);
	void draw_text(std::string draw_text) const;

	void set_color(int color);
	void set_background_color(int color);
	void set_background_bright(bool value);

	int get_translate_x() const;
	int get_translate_y() const;
private:
	static std::string eat_chunk(std::string& text, size_t max_width);

	int translate_x;
	int translate_y;

	int x;
	int y;

	int width;
	int height;

	int color;
	int background_color;
	bool is_background_bright;
};


#endif //DSP_TEAM_PROJECT_CANVAS_H
