#ifndef DSP_TEAM_PROJECT_VECTOR2_H
#define DSP_TEAM_PROJECT_VECTOR2_H

class vector2 {
public:
	vector2(int x, int y);

	int get_x() const;
	int get_y() const;

	void set_x(int x);
	void set_y(int y);
private:
	int x;
	int y;
};


#endif //DSP_TEAM_PROJECT_VECTOR2_H
