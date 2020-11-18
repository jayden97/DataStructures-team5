#ifndef DSP_TEAM_PROJECT_WINDOW_H
#define DSP_TEAM_PROJECT_WINDOW_H

#include "view.h"

class window {
public:
	window();
	~window();

	void set_root(view* root);

private:
	view* root;
};


#endif //DSP_TEAM_PROJECT_WINDOW_H
