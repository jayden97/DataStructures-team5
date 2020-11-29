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
	cout << "***** ��ȭ ���� ���α׷��Դϴ� *****" << endl;
}

int Console::menu() {
	cout << endl << endl;
	cout << "����:1, ���:2, ����:3, ������:4>> ";
	int n;
	cin >> n;
	return n;
}

int Console::time() {
	cout << "07��:1, 12��:2, 17��:3>> ";
	int t;
	cin >> t;
	return t;
}

int Console::num() {
	cout << "�¼� ��ȣ>> ";
	int num;
	cin >> num;
	return num;
}

string Console::name() {
	cout << "�̸� �Է�>> ";
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
		schedule[0].setTime("07��");
		schedule[1].setTime("12��");
		schedule[2].setTime("17��");
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
