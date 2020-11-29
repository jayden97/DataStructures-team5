#include <iostream>
#include <string>

using namespace std;

class Console {
public:
	static void start();
	static int menu();
	static int time();
	static int num();
	static string name();
};

void Console::start() {
	cout << "***** 영화 예약 프로그램입니다 *****" << endl;
}

int Console::menu() {
	cout << endl << endl;
	cout << "예약:1, 취소:2, 보기:3, 끝내기:4>> ";
	int n;
	cin >> n;
	return n;
}

int Console::time() {
	cout << "07시:1, 12시:2, 17시:3>> ";
	int t;
	cin >> t;
	return t;
}

int Console::num() {
	cout << "좌석 번호>> ";
	int num;
	cin >> num;
	return num;
}

string Console::name() {
	cout << "이름 입력>> ";
	string name;
	cin >> name;
	return name;
}

class Seat {
	string seatName;
public:
	Seat() { seatName = "---"; }
	string getName() { return seatName; }
	void setName(string name) { seatName = name; }
};

class Schedule {
	Seat *seat;
	string time;

public:
	Schedule() { seat = new Seat[8]; }
	~Schedule() { delete[] seat; }
	void setTime(string t) { time = t; }
	void show() {
		cout << time << " :";
		for (int i = 0; i < 8; ++i)
			cout << seat[i].getName() << "\t";
		cout << endl;
	}
	void reservationSeat(int num, string name) {
		seat[num - 1].setName(name);
	}
	void cancleSeat(int num, string name) {
		seat[num - 1].setName("---");
	}
};

class Movie
{
	Schedule *schedule;

public:
	Movie() {
		schedule = new Schedule[3];
		schedule[0].setTime("07시");
		schedule[1].setTime("12시");
		schedule[2].setTime("17시");
	}
	~Movie() { delete[] schedule; }
	void reservation(int t) {
		schedule[t - 1].show();
		int num = Console::num();
		string name = Console::name();
		schedule[t - 1].reservationSeat(num, name);
	}
	void cancle(int t) {
		schedule[t - 1].show();
		int num = Console::num();
		string name = Console::name();
		schedule[t - 1].cancleSeat(num, name);
	}
	void showAll() {
		for (int i = 0; i < 3; ++i)
			schedule[i].show();
	}
};
