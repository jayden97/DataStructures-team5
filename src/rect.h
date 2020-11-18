#ifndef DSP_TEAM_PROJECT_RECT_H
#define DSP_TEAM_PROJECT_RECT_H

#include "point.h"

class rect {
public:
	rect(point start, point end);

	point get_start() const;
	point get_end() const;

private:
	point start;
	point end;
};


#endif //DSP_TEAM_PROJECT_RECT_H
