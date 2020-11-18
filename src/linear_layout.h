#ifndef DSP_TEAM_PROJECT_LINEAR_LAYOUT_H
#define DSP_TEAM_PROJECT_LINEAR_LAYOUT_H

#include "view_group.h"

enum orientation {
	HORIZONTAL,
	VERTICAL
};

class linear_layout: public view_group {
public:
	explicit linear_layout(orientation o = VERTICAL);

	void add_child(view* child) override;
	void destroy_child(int id) override;

	orientation get_orientation() const;

private:
	orientation orientation_value;

	int occupied_size;
};

#endif //DSP_TEAM_PROJECT_LINEAR_LAYOUT_H
