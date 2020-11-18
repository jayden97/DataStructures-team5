#ifndef DSP_TEAM_PROJECT_VIEW_H
#define DSP_TEAM_PROJECT_VIEW_H

#include <string>
#include "canvas.h"
#include "drawable.h"
#include "vector2.h"
#include "rect.h"

class view {
public:
	static const int TYPE = 0;

	view();
	view(int x, int y, int width, int height);

	virtual ~view();

	int get_id() const;

	virtual void invalidate();
	virtual void invalidate(const rect& r);
	virtual void invalidate(bool forward_parent);
	virtual void invalidate(const rect& r, bool forward_parent);
	bool must_redraw() const;
	void invoke_redraw(canvas& c);

	virtual void set_xy(int x, int y);
	virtual void set_width(int new_width);
	virtual void set_height(int new_height);
	int get_x() const;
	int get_y() const;
	int get_width() const;
	int get_height() const;

	vector2 get_absolute_point() const;

	void set_background(drawable* new_background);

	virtual void draw(const canvas& c) = 0;

	/** @internal */
	void _set_parent(view* parent);
	bool has_parent() const;

	virtual int get_type() const;

protected:
	int x;
	int y;

	int width;
	int height;

private:
	int id;

	view* parent = nullptr;

	vector2 last_drawn;
	vector2 last_size;

	drawable* background;

	bool must_redrawn = true;
};

static int view_id = 0;

#endif //DSP_TEAM_PROJECT_VIEW_H
