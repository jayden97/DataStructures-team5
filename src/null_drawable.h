#ifndef DSP_TEAM_PROJECT_NULL_DRAWABLE_H
#define DSP_TEAM_PROJECT_NULL_DRAWABLE_H

#include "drawable.h"

class null_drawable: public drawable {
public:
	void draw(canvas& c) override;
};


#endif //DSP_TEAM_PROJECT_NULL_DRAWABLE_H
