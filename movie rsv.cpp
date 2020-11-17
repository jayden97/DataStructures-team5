#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
	int seat[4][7] = { { 0 } }; // 영화관 좌석 선언
	int hang, yul; // 영화관 좌석 행렬
	int com1[6], com2[6]; // 컴퓨터 행렬 값

	char select; // y,n 값

	int i, j;

	srand((time(NULL)));

start:
	for (i = 0; i < 6; i++)
	{
		com1[i] = rand() % 4 + 1; // 행 랜덤
	}
	for (i = 0; i < 6; i++)
	{
		com2[i] = rand() % 7 + 1; // 열 랜덤
	}

	for (j = 0; j < i; j++)
	{
		if (com2[i] == com2[j])
			goto start;
	}

	cout << "---------좌 석 예 매 프 로 그 램---------" << endl;
	cout << endl;
	cout << "     1열 2열 3열 4열 5열 6열 7열" << endl;

	for (i = 0; i < 4; i++)
	{
		cout << i + 1 << "행";

		for (j = 0; j < 7; j++)
		{
			cout << seat[i][j];
		}

		cout << endl;
		cout << "---------------------------------------------" << endl;
	}

	cout << endl;

again:
	cout << "예약할 자리를 고르세요" << endl;
	cout << "몇 행 : ";
	cin >> hang;
	cout << "몇 열 : ";
	cin >> yul;

	fflush(stdin);

	for (i = 0; i < 6; i++)
	{
		if (hang == com1[i] && yul == com2[i])
		{
			cout << "예약 되지 않은 자리를 찾으세요" << endl;
			cout << endl;
			goto again;
		}
	}

	if ((hang < 0 || yul < 0) || (hang > 4 || yul > 7) || (hang == 0 || yul == 0))
	{
		cout << "형식에 맞춰 입력해주세요" << endl;
		goto again;
	}

	seat[hang - 1][yul - 1] = 'X';
	cout << "     1열 2열 3열 4열 5열 6열 7열" << endl;

	for (i = 0; i < 4; i++)
	{
		cout << i + 1;
		for (j = 0; j < 7; j++)
		{
			cout << seat[i][j];
		}

		cout << endl;
		cout << "---------------------------------------------" << endl;
	}

	cout << endl;

	cout << "선택한 좌석을 예매하시겠습니까?" << endl;
	cout << "y나 n을 눌러서 선택하세요 1.yes 2.no" << endl;
	cin >> select;

	if (select == 'y')
	{
		seat[hang - 1][yul - 1] = 'O';
		cout << "     1열 2열 3열 4열 5열 6열 7열" << endl;

		for (i = 0; i < 4; i++)
		{
			cout << i + 1;
			for (j = 0; j < 7; j++)
			{
				cout << seat[i][j];
			}
			cout << endl;
			cout << "---------------------------------------------";
		}
		cout << endl;
		cout << "예약되셨습니다" << endl;
	}

	else if (select == 'n')
	{
		cout << "종료합니다";
	}

	else
	{
		cout << "재시작 해주세요";
	}

}