#ifndef DSP_TEAM_PROJECT_VIEW_GROUP_H
#define DSP_TEAM_PROJECT_VIEW_GROUP_H

#include <vector>
#include "view.h"

class view_group: public view {
public:
	static const int TYPE = 1;

	view_group(int width, int height);
	~view_group() override;

	virtual void add_child(view* child) override;
	view* get_child(int id);
	virtual void destroy_child(int id);

	void invalidate(bool forward_parent) override;
	void invalidate(const rect& r, bool forward_parent) override;

	void draw(canvas& c) override;

	std::vector<view*> get_children() override;

	int get_type() const override;

protected:
	std::vector<view*> children;

private:
	bool has_layout_requested_child() const;
	drawable* get_top_background() const;
};

#endif //DSP_TEAM_PROJECT_VIEW_GROUP_H
