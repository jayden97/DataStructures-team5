#ifndef DSP_TEAM_PROJECT_VIEW_H
#define DSP_TEAM_PROJECT_VIEW_H

#include <string>
#include "canvas.h"
#include "point.h"
#include "rect.h"

class view {
public:
	view();
	view(int x, int y, int width, int height);

	virtual void invalidate();
	virtual void invalidate(const rect& r);
	void invoke_redraw();

	point get_absolute_point() const;

	virtual void draw(const canvas& c) = 0;

	/** @internal */
	void _set_parent(view* parent);

private:
	view* parent;

	int x;
	int y;

	point last_drawn;

	int width;
	int height;

	bool must_redrawn = false;
};


#endif //DSP_TEAM_PROJECT_VIEW_H
