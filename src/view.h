#ifndef DSP_TEAM_PROJECT_VIEW_H
#define DSP_TEAM_PROJECT_VIEW_H


#include <string>

class view {
public:
	explicit view(view* parent = nullptr);
	view(view* parent, int width, int height);

	void invalidate();

	virtual void draw() = 0;

private:
	view* parent;

	int width;
	int height;

	bool must_redrawn = false;
};


#endif //DSP_TEAM_PROJECT_VIEW_H
