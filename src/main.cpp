#include "windows_thing.h"
#include <array>
#include <csignal>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <string>
#include <unistd.h>

//관리자 모드 패스워드
#define ADMIN_PASSWORD 1111
#define MOVIE_FILE "./moviesFile.dat"

using namespace std;

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

    void setName(string name) { this->name = name; }

    void setGenre(string genre) { this->genre = genre; }

    void serialize(int fd) {
        write(fd, &number, sizeof(int));

        int length = name.length();
        write(fd, &length, sizeof(int));
        write(fd, name.c_str(), length);

        length = genre.length();
        write(fd, &length, sizeof(int));
        write(fd, genre.c_str(), length);
    }

    static void deserialize(int fd, string &name, string &genre) {
        char *buf;

        int length;
        read(fd, &length, sizeof(int));
        buf = new char[length];
        read(fd, buf, length);

        name = buf;
        delete[] buf;

        read(fd, &length, sizeof(int));
        buf = new char[length];
        read(fd, buf, length);
        genre = buf;
        delete[] buf;
    }

  private:
    int number;
    string name;
    string genre;
};

class Theater {
  public:
    static const int ROW = 10;
    static const int COLUMN = 20;

    Theater(Movie *movie) {
        this->movie = movie;

        array<int, COLUMN> rows{};
        rows.fill(0);
        seat.fill(rows);
    }

    Movie *getMovie() const { return this->movie; }

    void setSeat(int row, int column) {
        if (row >= ROW || column >= COLUMN) {
            throw invalid_argument("invalid row & column");
        }

        this->seat[row][column] = 1; // TODO set user id here
    }

    int getSeat(int row, int column) {
        if (row >= ROW || column >= COLUMN) {
            throw invalid_argument("invalid row & column");
        }

        return this->seat[row][column];
    }

  private:
    array<array<int, COLUMN>, ROW> seat;
    Movie *movie;
};

class Cinema {
  public:
    Cinema() {
        movieNumber = 1;
        readMovies();

        for (auto &movie : movieList) {
            theaterList.emplace_back(&movie);
        }

        if (instance == nullptr) {
            instance = this;
        }
    }

    ~Cinema() { delete instance; }

    int generate_movieNumber() {

        int max = 0;
        list<Movie>::iterator iter;

        for (iter = movieList.begin(); iter != movieList.end(); ++iter) {
            if (max < iter->getNumber())
                max = iter->getNumber();
        }
        return ++max;
    }

    void showMenu() {
        //좌석확인은 추가가능하면 추가할 기능이기에 일단 넣어놨음. 무시하고
        //코드짜면 됨.
        cout << "========================================" << endl;
        cout << "[1]    영화검색" << endl;
        cout << "[2]    예약" << endl;
        cout << "[3]    에약취소" << endl;
        cout << "[4]    예약조회 및 좌석확인" << endl;
        cout << "[5]    종료" << endl;
        cout << "========================================" << endl;
    }

    void showAdminMenu() {
        cout << "==============================" << endl;
        cout << "|          관리자 모드       | " << endl;
        cout << "==============================" << endl;
        cout << "[1]    영화 추가" << endl;
        cout << "[2]    영화 삭제" << endl;
        cout << "[3]    메인 으로" << endl;
    }

    int inputMenu() {
        int menuNum;
        cout << "[입력] : " << endl;
        cin >> menuNum;
        if (cin.fail()) {
            cout << "숫자만 입력해 주세요!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        return menuNum;
    }

    static void signalHandler(int signum) {
        if (instance != nullptr) {
            instance->adminSigHandler(signum);
        }
    }

    void adminSigHandler(int signum) {
        // pid를 받으면 관리자 모드 진입을 위한 핸들러
        string password = "";

        if (signum == SIGUSR1) {
            cout << "관리자 모드 진입 중..." << endl;
            while (true) {
                int status = 0;
                cout << "비밀번호를 입력하세요  <<";
                cin >> password;
                if (ADMIN_PASSWORD == stoi(password))
                    status = adminMode();
                else
                    cout << "비밀번호가 틀립니다." << endl;

                if (status == 1) {
                    return;
                }
            }
        }
    }

    //관리자 모드 함수
    int adminMode() {
        bool q = true;
        while (q) {
            showAdminMenu();
            switch (inputMenu()) {
            case 1:
                addMovieList();
                break;
            case 2:
                deleteMovieList();
                break;
            case 3:
                return 1; //바로 자식프로세스를 죽이고 메인화면으로 넘어가는걸
                          //모르겠음ㅠ
            default:
                cout << "잘못입력하셨습니다." << endl;
            }
        }
    }

    void startProgram() {
        cout << "========================================" << endl;
        cout << getpid() << "극장에 오신걸 환영합니다." << endl;
        while (true) {
            showMenu();

            switch (int menuNum = inputMenu()) {
            case 1:
                searchMovie();
                break;
            case 2:
                reserveMovie();
                break;
            case 3:
                reserveCancel();
                break;
            case 4:
                reserveCheck();
                break;
            case 5:
                break;
            default:
                cout << "잘못입력하셨습니다. 다시 입력해 주세요!" << endl;
                break;
            }
        }
    }

    void saveMovies() {
        int fd = open(MOVIE_FILE, O_CREAT | O_WRONLY, 0644);
        if (fd == -1) {
            perror("open() error!");
            exit(-1);
        }

        list<Movie>::iterator iter;
        for (iter = movieList.begin(); iter != movieList.end(); ++iter) {
            iter->serialize(fd);
        }

        close(fd);
    }

    //영화 추가
    void addMovieList() {
        string name, genre;

        printMovieList();
        cout << ">>>추가 할 영화 정보 입력<<<" << endl;
        cout << "영화 이름 입력 <<" << endl;
        cin >> name;
        cout << "영화 장르 입력 <<" << endl;
        cin >> genre;
        Movie movies(generate_movieNumber(), name, genre);
        movieList.push_back(movies);

        saveMovies();
        cout << "영화 입력 완료!" << endl;
    }

    //영화 삭제
    void deleteMovieList() {
        cout << ">>>삭제 할 고유 영화 번호 입력<<<" << endl;
        printMovieList();
        int n = inputMenu();

        list<Movie>::iterator iter;
        for (iter = movieList.begin(); iter != movieList.end(); ++iter) {
            if (iter->getNumber() == n)
                movieList.erase(iter);
        }
        cout << "삭제 완료!" << endl;
        saveMovies();
    }

    void printMovieList() {
        for (auto &movie : movieList) {
            cout << "MOVIE_NUMBER: " << movie.getNumber()
                 << " NAME: " << movie.getName()
                 << " GENRE : " << movie.getGenre() << endl;
        }
    }

    //영화 목록을 출력
    void readMovies() {

        int fd = open(MOVIE_FILE, O_CREAT | O_RDONLY, 0644);
        if (fd == -1) {
            perror("open() error");
            exit(-1);
        }

        string name, genre;

        int number;
        cout << "영화 목록" << endl;
        while (read(fd, &number, sizeof(int)) > 0) {
            Movie::deserialize(fd, name, genre);
            movieList.emplace_back(number, name, genre);
        }

        close(fd);
    }

    //"영화검색,예약,취소,좌석확인" 성철,재현
    void searchMovie() {}

    void listReserve() {}

    void reserveMovie() {}

    void reserveCancel() {}

    void reserveCheck() {}

  private:
    static Cinema *instance;

    list<Movie> movieList;
    list<Theater> theaterList;
    int movieNumber;
};

// asldkfjlsdajflsdf
Cinema *Cinema::instance;

int main(int argc, char const *argv[]) {
    doWindowsStuff();
    Cinema cinema;

    if (signal(SIGUSR1, Cinema::signalHandler) == SIG_ERR) {
        perror("adminSigHandler() error!");
    }

    cinema.startProgram();

    while (1) {
        pause();
    }

    return 0;
}
