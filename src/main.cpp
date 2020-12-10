#include "platform_dependant.h"
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
                cout << "비밀번호를 입력하세요  <<" << endl << std::flush;
                cin >> password;
                if (ADMIN_PASSWORD == stoi(password))
                    status = adminMode();
                else
                    cout << "비밀번호가 틀립니다." << endl;

                if (status == 1) {
                    showMenu();
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
                listReserve();
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
            else {
                cout << "존재하지 않는 영화 입니다." << endl;
            }
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

    //이름으로 검색
    void searchbyName() {
        string name;
        cout << "제목을 입력하세요: " << endl;
        cin >> name;

        list<Movie>::iterator iter;
        int count = 0;
        for (iter = movieList.begin(); iter != movieList.end(); ++iter) {
            if (iter->getName() == name) {
                cout << iter->getNumber() << iter->getName() << iter->getGenre()
                     << endl;
                count++;
            }
        }
        if (count == 0)
            cout << "영화제목 " << name << "을 찾을 수 없습니다." << endl;
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
    }
    //장르로 검색
    void searchbyGenre() {
        string genre;
        cout << "원하시는 장르를 입력하세요: " << endl;
        cin >> genre;

        list<Movie>::iterator iter;
        int count = 0;
        for (iter = movieList.begin(); iter != movieList.end(); ++iter) {
            if (iter->getGenre() == genre) {
                cout << iter->getNumber() << iter->getName() << iter->getGenre()
                     << endl;
                count++;
            }
        }
        if (count == 0)
            cout << genre << " 장르의 영화를 찾을 수 없습니다." << endl;
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
    }

    //"영화검색,예약,취소,좌석확인" 성철,재현
    void searchMovie() {
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        cout << "영화 검색 창입니다" << endl;
        cout << " 1.전체 영화 목록 보기" << endl;
        cout << " 2.이름으로 검색하기" << endl;
        cout << " 3.장르로 검색하기" << endl;

        int N;
        cout << " 원하시는 방법을 숫자로 입력하세요(1~3) : " << endl;
        cin >> N;

        switch (N) {
        case 1:
            printMovieList();
            break;
        case 2:
            searchbyName();
            break;
        case 3:
            searchbyGenre();
            break;

        default:
            cout << "잘못입력하셨습니다." << endl;
            break;
        }
    }

    // compare [temp]
    void listReserve() {
        int temp;
        cout << "예약 조회" << endl;
        cout << "원하시는 영화의 번호를 입력해주세요: " << endl;
        printMovieList();

        if (cin >> temp) {

        } else {
            cout << "입력 실패하셨습니다." << endl;
            return;
        }

        list<Theater>::iterator reservation;
        for (reservation = theaterList.begin();
             reservation != theaterList.end(); ++reservation) {
            if (reservation->getMovie()->getNumber() == temp) {
                // wherㄷ
                for (int i = 0; i < 10; i++)
                    for (int j = 0; j < 20; j++)

                        if (reservation->getSeat(i, j) == 1)
                            cout << "좌석[" << i << "][" << j << "]"
                                 << "자리에 예약되어있습니다."
                                 << endl; /// i want print seat!
            }
            break;
        }
    }

    // 남는 좌석 표시 함수
    void seat(int t) {
        int temp;
        temp = t;
        list<Theater>::iterator reservation;
        for (reservation = theaterList.begin();
             reservation != theaterList.end(); ++reservation) {
            if (reservation->getMovie()->getNumber() == temp) {
                // wherㄷ
                for (int i = 0; i < 10; i++)
                    for (int j = 0; j < 20; j++)

                        if (reservation->getSeat(i, j) == 0)
                            cout << "좌석[" << i << "][" << j << "]"
                                 << endl; /// i want print seat!
                cout << "이 비어있습니다." << endl;
            }
            break;
        }
    }

    void reserveMovie() {
        int temp;
        int row, column;
        cout << "영화 예약 메뉴입니다." << endl;
        cout << "원하시는 영화의 번호를 입력해주세요." << endl;
        cin >> temp;
        seat(temp); //좌석 표시 함수
        cout << "원하시는 좌석 번호를 입력해주세요(행, 렬): " << endl;
        cin >> row >> column;

        list<Theater>::iterator Rmovie;

        for (Rmovie = theaterList.begin(); Rmovie != theaterList.end();
             ++Rmovie) {
            // fail
            if (Rmovie->getMovie()->getNumber() == temp) {

                if (Rmovie->getSeat(row, column) == 1) {
                    cout << "이미 예약되었습니다" << endl;
                }

                Rmovie->setSeat(row, column);
                cout << "예약해주셔서 고맙습니다." << endl;
            }
        }
    }
    void reserveCancel() {
        int temp;
        int row, column;

        cout << "예약 취소" << endl;

        cout << "영화 번호를 입력하세요: " << endl;
        cin >> temp;
        seat(temp);

        cout << "좌석번호를 입력해주세요: (행,렬)" << endl;
        cin >> row >> column;

        list<Theater>::iterator Cmovie;
        for (Cmovie = theaterList.begin(); Cmovie != theaterList.end();
             ++Cmovie) {
            if (Cmovie->getMovie()->getNumber() == temp) {

                if (Cmovie->getSeat(row, column) == -1) {
                    cout << "예약되어지지 않은 자리입니다. 다시 체크해주세요"
                         << endl;
                }

                Cmovie->setSeat(row, column);
                cout << "예약이 취소되었습니다." << endl;
                break;
            }
        }
    }

  private:
    static Cinema *instance;

    list<Movie> movieList;
    list<Theater> theaterList;
    int movieNumber;
};

// asldkfjlsdajflsdf
Cinema *Cinema::instance;

int main(int argc, char const *argv[]) {
    init_screen();

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
