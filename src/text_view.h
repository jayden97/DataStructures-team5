#ifndef DSP_TEAM_PROJECT_TEXT_VIEW_H
#define DSP_TEAM_PROJECT_TEXT_VIEW_H

#include "attributes.h"
#include "console.h"
#include "view.h"

class text_view: public view {
public:
	explicit text_view(std::string text_value);

	void set_text_color(int color);
	void set_text(std::string new_text);

	void draw(canvas& c) override;

private:
	std::string text;

	int text_color = attributes::WHITE;
};


#endif //DSP_TEAM_PROJECT_TEXT_VIEW_H
