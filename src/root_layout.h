#ifndef DSP_TEAM_PROJECT_ROOT_LAYOUT_H
#define DSP_TEAM_PROJECT_ROOT_LAYOUT_H

#include "view_group.h"

class root_layout: public view_group {
public:
	root_layout(int width, int height);

	void add_child(view* child) override;

	void invalidate() override;
	void invalidate(const rect& r) override;
};


#endif //DSP_TEAM_PROJECT_ROOT_LAYOUT_H
