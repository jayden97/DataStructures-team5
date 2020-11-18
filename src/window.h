#ifndef DSP_TEAM_PROJECT_WINDOW_H
#define DSP_TEAM_PROJECT_WINDOW_H

#include "root_layout.h"

class window {
public:
	window();
	~window();

	void set_view(view* v);
	void render() const;
private:
	root_layout* root;
};


#endif //DSP_TEAM_PROJECT_WINDOW_H
