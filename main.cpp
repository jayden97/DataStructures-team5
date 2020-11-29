

#include <iostream>
#include <string>
#include "rsvv.h"
using namespace std;

int main()
{
	Movie moive;
	Console::start();

	for (;;)
	{
		int n = Console::menu();

		if (n == 1) {
			int t = Console::time();
			moive.reservation(t);
		}

		else if (n == 2) {
			int t = Console::time();
			moive.cancle(t);
		}

		else if (n == 3) {
			moive.showAll();
		}

		else if (n == 4) {
			cout << "예약 시스템을 종료합니다." << endl;
			break;
		}

		else
		{

		}
	}
}