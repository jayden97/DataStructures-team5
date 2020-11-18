#ifndef DSP_TEAM_PROJECT_POINT_H
#define DSP_TEAM_PROJECT_POINT_H

class point {
public:
	point(int x, int y);

	int get_x() const;
	int get_y() const;

	void set_x(int x);
	void set_y(int y);
private:
	int x;
	int y;
};


#endif //DSP_TEAM_PROJECT_POINT_H
