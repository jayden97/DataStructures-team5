#include "windows_thing.h"
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <list>
#include <unistd.h>

//관리자 모드 패스워드
#define ADMIN_PASSWORD 1111

using namespace std;
void adminSigHandler(int signum);
void adminMode();
void showAdminMenu();
int inputMenu();
void addMoiveList();
void deleteMovieList();

class Movie {
  public:
    Movie() {}
    Movie(int number, string name, string genre) {
        this->number = number;
        this->name = name;
        this->genre = genre;
    }
    int getNumber() { return number; }
    string getName() { return name; }
    string getGenre() { return genre; }

    string setName(string name) { this->name = name; }
    string setGenre(string genre) { this->genre = genre; }

  private:
    int number;
    string name;
    string genre;
};

class Cinema {
  public:
    Cinema() {}

    int generate_movieNumber() {
        //영화고유번호 방식 나중에 바꿀수도 있음.
        return movieNumber++;
    }

    void showMenu() {
        //좌석확인은 추가가능하면 추가할 기능이기에 일단 넣어놨음. 무시하고
        //코드짜면 됨.
        cout << "1. 영화검색" << endl;
        cout << "2. 예약" << endl;
        cout << "3. 에약취소" << endl;
        cout << "4. 예약조회 및 좌석확인" << endl;
        cout << "5. 종료" << endl;
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
    //관리자 모드 함수
    void adminMode() {
        showAdminMenu();
        switch (inputMenu()) {
        case 1:
            addMovieList();
            break;
        case 2:
            deleteMovieList();
            break;
        case 3:
            //메인으로
            break;
        default:
            cout << "잘못입력하셨습니다." << endl;
        }
    }

    //영화 추가
    void addMovieList() {
        Cinema add;
        Movie movies;
        string name, genre;

        add.printMovieList();
        cout << "추가 할 영화 정보 입력" << endl;
        cout << "영화 이름";
        getline(cin, name);
        cout << "영화 장르";
        getline(cin, genre);
        movies.setName(name);
        movies.setGenre(genre);
    }
    //영화 삭제
    void deleteMovieList() {}

    //영화 목록을 출력
    void printMovieList() {}

    //"영화검색,예약,취소,좌석확인" 성철,재현
    void searchMovie() {}
    void listReserve() {}
    void reserveMovie() {}
    void reserveCancel() {}
    void reserveCheck() {}

  private:
    list<Movie> movieList;
    int movieNumber = 1;
};

int main(int argc, char const *argv[]) {
    doWindowsStuff();
    Cinema c1;
    if (signal(SIGUSR1, adminSigHandler) == SIG_ERR)
        perror("adminSigHandler() error!");
    while (1) {
        pause();
    }

    return 0;
}
