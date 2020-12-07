#ifndef DSP_TEAM_PROJECT_FILL_DRAWABLE_H
#define DSP_TEAM_PROJECT_FILL_DRAWABLE_H

#include "attributes.h"
#include "console.h"
#include "drawable.h"

class fill_drawable: public drawable {
public:
	fill_drawable(int color = color::BACKGROUND_BLACK);

	void draw(canvas& c) override;

private:
	int color;
};


#endif //DSP_TEAM_PROJECT_FILL_DRAWABLE_H
