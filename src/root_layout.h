#ifndef DSP_TEAM_PROJECT_ROOT_LAYOUT_H
#define DSP_TEAM_PROJECT_ROOT_LAYOUT_H

#include "view_group.h"

class root_layout: public view_group {
public:
	void add_child(view* child) override;

	void invalidate() override;
	void invalidate(const rect& r) override;

private:
	void redraw_all(view* target) const;
};


#endif //DSP_TEAM_PROJECT_ROOT_LAYOUT_H
