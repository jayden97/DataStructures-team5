#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
	int seat[4][7] = { { 0 } }; // ��ȭ�� �¼� ����
	int hang, yul; // ��ȭ�� �¼� ���
	int com1[6], com2[6]; // ��ǻ�� ��� ��

	char select; // y,n ��

	int i, j;

	srand((time(NULL)));

start:
	for (i = 0; i < 6; i++)
	{
		com1[i] = rand() % 4 + 1; // �� ����
	}
	for (i = 0; i < 6; i++)
	{
		com2[i] = rand() % 7 + 1; // �� ����
	}

	for (j = 0; j < i; j++)
	{
		if (com2[i] == com2[j])
			goto start;
	}

	cout << "---------�� �� �� �� �� �� �� ��---------" << endl;
	cout << endl;
	cout << "     1�� 2�� 3�� 4�� 5�� 6�� 7��" << endl;

	for (i = 0; i < 4; i++)
	{
		cout << i + 1 << "��";

		for (j = 0; j < 7; j++)
		{
			cout << seat[i][j];
		}

		cout << endl;
		cout << "---------------------------------------------" << endl;
	}

	cout << endl;

again:
	cout << "������ �ڸ��� ������" << endl;
	cout << "�� �� : ";
	cin >> hang;
	cout << "�� �� : ";
	cin >> yul;

	fflush(stdin);

	for (i = 0; i < 6; i++)
	{
		if (hang == com1[i] && yul == com2[i])
		{
			cout << "���� ���� ���� �ڸ��� ã������" << endl;
			cout << endl;
			goto again;
		}
	}

	if ((hang < 0 || yul < 0) || (hang > 4 || yul > 7) || (hang == 0 || yul == 0))
	{
		cout << "���Ŀ� ���� �Է����ּ���" << endl;
		goto again;
	}

	seat[hang - 1][yul - 1] = 'X';
	cout << "     1�� 2�� 3�� 4�� 5�� 6�� 7��" << endl;

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

	cout << "������ �¼��� �����Ͻðڽ��ϱ�?" << endl;
	cout << "y�� n�� ������ �����ϼ��� 1.yes 2.no" << endl;
	cin >> select;

	if (select == 'y')
	{
		seat[hang - 1][yul - 1] = 'O';
		cout << "     1�� 2�� 3�� 4�� 5�� 6�� 7��" << endl;

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
		cout << "����Ǽ̽��ϴ�" << endl;
	}

	else if (select == 'n')
	{
		cout << "�����մϴ�";
	}

	else
	{
		cout << "����� ���ּ���";
	}

}