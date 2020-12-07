#ifndef DSP_TEAM_PROJECT_BUTTON_H
#define DSP_TEAM_PROJECT_BUTTON_H

#include "text_view.h"

class button: public text_view {
public:
	explicit button(std::string text);
	~button() override;

	void draw(canvas& c) override;

private:
	drawable* idle_background = nullptr;
	drawable* hover_background = nullptr;
};

#endif //DSP_TEAM_PROJECT_BUTTON_H
