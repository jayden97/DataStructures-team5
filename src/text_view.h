#ifndef DSP_TEAM_PROJECT_TEXT_VIEW_H
#define DSP_TEAM_PROJECT_TEXT_VIEW_H

#include "view.h"

class text_view: public view {
public:
	explicit text_view(std::string text_value);

	void draw(const canvas& c) override;

private:
	std::string text;
};


#endif //DSP_TEAM_PROJECT_TEXT_VIEW_H
