#ifndef DSP_TEAM_PROJECT_DRAWABLE_H
#define DSP_TEAM_PROJECT_DRAWABLE_H

#include "canvas.h"

class drawable {
public:
	drawable();
	drawable(int width, int height);
	virtual ~drawable() = default;

	virtual void draw(canvas& c) = 0;

	int get_width() const;
	int get_height() const;

	void set_width(int new_width);
	void set_height(int new_height);

private:
	int width;
	int height;
};

#endif //DSP_TEAM_PROJECT_DRAWABLE_H
