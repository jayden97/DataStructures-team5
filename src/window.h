#ifndef DSP_TEAM_PROJECT_WINDOW_H
#define DSP_TEAM_PROJECT_WINDOW_H

#include "root_layout.h"

class window {
public:
	window(int width, int height);
	~window();

	void set_view(view* v);
	void render() const;

	void start_input();
	void end_input();
private:
	root_layout* root;

	bool wait_keyboard = false;
};


#endif //DSP_TEAM_PROJECT_WINDOW_H
