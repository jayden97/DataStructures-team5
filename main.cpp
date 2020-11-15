#include<stdio.h> 
#include<time.h> 
#include<stdlib.h> 

int main() 
{
	int seat[4][7] = { { 0 } }; //영화관 좌석  
	int hang, yul; //좌석의 행렬 
	int com1[6], com2[6]; //컴퓨터의 행//렬 값 
	

	char select; 
	int i, j;


	srand((time(NULL)));

start:;
	for (i = 0; i < 6; i++) {
		com1[i] = rand() % 4 + 1; //4행의 랜덤  
	}

	for (i = 0; i < 6; i++) {
		com2[i] = rand() % 7 + 1;
	}//7열의 랜덤 
	for (j = 0; j < i; j++) { //좌석 6개 나오기위해 비교하여 다시 돌린다. 
		if (com2[i] == com2[j])
			goto start;
	}


	for (i = 0; i < 6; i++) { //랜덤함수로 예약된 자리표기 
		seat[com1[i] - 1][com2[i] - 1] = 'O';
	}


	printf("---------좌 석 예 매 시 스 템--------\n\n");
	printf("    1열 2열 3열 4열 5열 6열 7열\n");

	for (i = 0; i < 4; i++) {
		printf("%d행  ", i + 1);
		for (j = 0; j < 7; j++) {
			printf(" %c  ", seat[i][j]);
		}
		printf("\n");
		printf("-------------------------------------\n"); //행칸 나누기 
	}
	printf("\n");

again:;
	printf("예약할 자리를 고르세요\n");

	printf("몇행:");
	scanf_s("%d", &hang);
	printf("몇열:");

	scanf_s("%d", &yul);
	fflush(stdin); 

	for (i = 0; i < 6; i++) {
		if (hang == com1[i] && yul == com2[i]) {
			printf("예약 되지 않은 자리를 선택하세요\n");
			printf("\n");
			goto again;
		}

	}

	if ((hang < 0 || yul < 0) || (hang > 4 || yul > 7) || (hang == 0 || yul == 0)) {
		printf("행과 열에 맞춰 선택해주세요\n");
		printf("\n");
		goto again;
	}


	seat[hang - 1][yul - 1] = 'X';
	printf("    1열 2열 3열 4열 5열 6열 7열\n");

	for (i = 0; i < 4; i++) {
		printf("%d행  ", i + 1);
		for (j = 0; j < 7; j++) {
			printf(" %c  ", seat[i][j]);
		}
		printf("\n");
		printf("-------------------------------------\n"); //행칸 나누기 
	}
	printf("\n");



	printf("선택한 좌석을 예매하시겠습니까?\n");
	printf("y나 n을 눌러서 선택하세요 1.y=예 2.n=아니오 \n");
	scanf_s("%c", &select);
	//fflush(stdin); 


	if (select == 'y') {
		seat[hang - 1][yul - 1] = 'O';
		printf("    1열 2열 3열 4열 5열 6열 7열\n");

		for (i = 0; i < 4; i++) {
			printf("%d행  ", i + 1);
			for (j = 0; j < 7; j++) {
				printf(" %c  ", seat[i][j]);
			}
			printf("\n");
			printf("-------------------------------------\n"); //행칸 나누기 
		}
		printf("\n");
		printf("예약이완료되었습니다 감사합니다\n");
	}

	else if (select == 'n') {

		printf("프로그램을 종료합니다\n");
	}
	else {
		printf("잘못입력하셨습니다 종료합니다\n");

	}
}