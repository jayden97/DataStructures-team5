#include "attributes.h"
#include "platform_dependant.h"
#include "window.h"
#include <stack>

window::window(int width, int height) {
	this->root = new root_layout(width, height);
}

window::~window() {
	delete this->root;
}

void window::set_view(view *v) {
	this->root->add_child(v);
}

void window::render() const {
	if(this->root != nullptr) {
		this->root->invalidate();
	}
}

void window::start_input() {
	if(this->wait_keyboard) return;

	this->wait_keyboard = true;

	while(this->wait_keyboard) {
		int c = get_char();
		arrow a = is_arrow_key(c);
		if(a != arrow::NONE && this->root != nullptr) {
			view* top = this->root->get_view();
			if(top == nullptr) continue;

			int focused_x = 0;
			int focused_y = 0;
			if(this->focused != nullptr) {
				vector2 vec = this->focused->get_absolute_point();
				focused_x = vec.get_x();
				focused_y = vec.get_y();
			}

			view* new_focus = nullptr;

			int min_xdiff = INT32_MAX;
			int min_ydiff = INT32_MAX;

			std::stack<std::pair<view*, int>> s; // <target view, iterated children count>
			s.push(std::pair<view*, int>(top, 0));

			while(!s.empty()) {
				std::pair<view*, int>& pair = s.top();
				view* v = pair.first;
				std::vector<view*> children = v->get_children();

				if(children.size() <= pair.second) {
					s.pop();
				}else{
					view* child = children[pair.second++];
					s.push(std::pair<view*, int>(child, 0));

					if(!child->is_focusable()) continue;

					vector2 point = child->get_absolute_point();
					int child_x = point.get_x();
					int child_y = point.get_y();
					switch(a) {
						case arrow::UP:
							if(child_y < focused_y) {
								if(min_ydiff > focused_y - child_y) {
									min_ydiff = focused_y - child_y;
									new_focus = child;
								}else if(min_ydiff == focused_y - child_y) {
									if(min_xdiff > abs(focused_x - child_x)) {
										min_xdiff = abs(focused_x - child_x);
										new_focus = child;
									}
								}
							}
							break;
						case arrow::DOWN:
							if(child_y > focused_y) {
								if(min_ydiff > child_y - focused_y) {
									min_ydiff = child_y - focused_y;
									new_focus = child;
								}else if(min_ydiff == child_y - focused_y) {
									if(min_xdiff > abs(focused_x - child_x)) {
										min_xdiff = abs(focused_x - child_x);
										new_focus = child;
									}
								}
							}
							break;
						case arrow::LEFT:
							if(child_x < focused_x) {
								if(min_xdiff > focused_x - child_x) {
									min_xdiff = focused_x - child_x;
									new_focus = child;
								}else if(min_xdiff == focused_x - child_x) {
									if(min_ydiff > abs(focused_y - child_y)) {
										min_ydiff = abs(focused_y - child_y);
										new_focus = child;
									}
								}
							}
							break;
						case arrow::RIGHT:
							if(child_x > focused_x) {
								if(min_xdiff > child_x - focused_x) {
									min_xdiff = child_x - focused_x;
									new_focus = child;
								}else if(min_xdiff == child_x - focused_x) {
									if(min_ydiff > abs(focused_y - child_y)) {
										min_ydiff = abs(focused_y - child_y);
										new_focus = child;
									}
								}
							}
							break;
						case NONE: // unreachable
							break;
					}
				}
			}

			if(new_focus != nullptr) {
				if(this->focused != nullptr)
					this->focused->set_focused(false);

				new_focus->set_focused(true);
				this->focused = new_focus;
			}
		}
	}
}
