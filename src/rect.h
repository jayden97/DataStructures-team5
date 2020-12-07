#ifndef DSP_TEAM_PROJECT_RECT_H
#define DSP_TEAM_PROJECT_RECT_H

#include "vector2.h"

class rect {
public:
	rect(vector2 start, vector2 end);

	vector2 get_start() const;
	vector2 get_end() const;

private:
	vector2 start;
	vector2 end;
};


#endif //DSP_TEAM_PROJECT_RECT_H
