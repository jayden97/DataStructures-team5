#include "windows_thing.h"
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

//관리자 모드 패스워드
#define ADMIN_PASSWORD 1111

using namespace std;
void adminSigHandler(int signum);
void adminMode();
void showAdminMenu();
int inputMenu();

int main(int argc, char const *argv[]) {
    doWindowsStuff();

    if (signal(SIGUSR1, adminSigHandler) == SIG_ERR)
        perror("adminSigHandler() error!");
    while (1) {
        pause();
    }

    return 0;
}

void showAdminMenu() {
    cout << "관리자 모드" << endl;
    cout << "1. 영화 추가" << endl;
    cout << "2. 영화 삭제" << endl;
    cout << "3. 메인 으로" << endl;
}

int inputMenu() {
    int menuNum;
    cout << "입력 : " << endl;
    cin >> menuNum;
    return menuNum;
}
void adminSigHandler(int signum) {
    // pid를 받으면 관리자 모드 진입을 위한 핸들러
    int password;
    if (signum == SIGUSR1) {
        cout << "비밀번호 입력";
        cin >> password;
        if (ADMIN_PASSWORD == password)
            adminMode();
        else {
            cout << "비밀번호가 틀립니다." << endl;
            return;
        }
    }
}

void adminMode() {
    showAdminMenu();
    switch (inputMenu()) {
    case 1:
        //영화추가 함수 호출
        break;
    case 2:
        //영화삭제 함수 호출
        break;
    case 3:
        //메인 으로 돌아가기
        break;
    default:
        cout << "잘못입력하셨습니다." << endl;
    }
}
