#include "platform_dependant.h"
#include "window.h"
#include "text_view.h"
#include "linear_layout.h"
#include "button.h"
#include "fill_drawable.h"
#include <array>
#include <csignal>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
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
    static const int COLUMN = 6;

    Theater(Movie *movie) {
        this->movie = movie;

        array<int, COLUMN> rows{};
        rows.fill(0);
        seat.fill(rows);
    }

    Movie *getMovie() const { return this->movie; }

    void unsetSeat(int row, int column) {
    	if(row >= ROW || column >= COLUMN) {
    		throw invalid_argument("invalid row & column);");
    	}

    	this->seat[row][column] = 0;
    }

    void setSeat(int row, int column) {
        if (row >= ROW || column >= COLUMN) {
            throw invalid_argument("invalid row & column");
        }

        this->seat[row][column] = 1; // TODO set user id here
    }

    int getSeat(int row, int column) const {
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
        while (true) {
            showAdminMenu();
            switch (inputMenu()) {
            case 1:
                addMovieList();
                break;
            case 2:
                deleteMovieList();
                break;
            case 3:
                exit(0);
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

            switch (inputMenu()) {
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
                return;
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
                int count = 0;
                for (int i = 0; i < Theater::ROW; i++)
                    for (int j = 0; j < Theater::COLUMN; j++) {
	                    if (reservation->getSeat(i, j) == 1) {
		                    cout << rowToChar(i) << j << "]"
		                         << "자리에 예약되어있습니다."
		                         << endl; /// i want print seat!

                            count++;
	                    }
                    }

                if(count == 0) {
                	cout << "예약된 자리가 없습니다." << endl;
                }
	            break;
            }
        }

        cout << "영화를 찾을 수 없습니다" << endl;
    }

    void displaySeatWindow(const Theater& theater, bool reserveMode, int& row, int& column) {
    	Movie* movie = theater.getMovie();
    	if(movie == nullptr) {
    		throw std::invalid_argument("invalid theater given");
    	}

    	int maxWidth, maxHeight;
    	get_width_height(maxWidth, maxHeight);

    	auto* w = new window(maxWidth, maxHeight);

    	auto* layout = new linear_layout(VERTICAL, maxWidth, maxHeight);

    	auto* tv = new text_view(movie->getName());
    	tv->set_background(new fill_drawable(color::BACKGROUND_CYAN));
    	tv->set_width(maxWidth);
    	tv->set_height(1);
    	layout->add_child(tv);

    	for(int r = 0; r < Theater::ROW; r++) {
		    auto* margin_top = new linear_layout(VERTICAL, maxWidth, 1);
		    margin_top->set_background(new fill_drawable(color::BACKGROUND_CYAN));
		    layout->add_child(margin_top);

		    auto* seats = new linear_layout(HORIZONTAL, maxWidth, 1);
		    seats->set_background(new fill_drawable(color::BACKGROUND_CYAN));

		    for(int c = 0; c < Theater::COLUMN; c++) {
		    	stringstream st_str;
		    	st_str << '[';
		    	if(theater.getSeat(r, c) == 0) {
		    		if(reserveMode) {
					    st_str << rowToChar(r) << c;
				    }else{
		    			st_str << "--";
		    		}
		    	}else{
		    		if(reserveMode) {
					    st_str << "--";
				    }else{
		    			st_str << rowToChar(r) << c;
		    		}
		    	}
		    	st_str << ']';

		    	auto* btn = new button(st_str.str());
		    	btn->set_width(10);
		    	btn->set_height(1);
		    	btn->set_click_listener([r, c, &row, &column, &w](view* v) {
		    		row = r;
		    		column = c;
		    		w->end_input();
		    	});

		    	seats->add_child(btn);
    		}

		    layout->add_child(seats);
    	}

    	w->set_view(layout);

    	init_screen();
    	w->render();
    	w->start_input();

    	delete w;

    	console::set_colors(color::WHITE, color::BACKGROUND_BLACK);
    	close_screen();
    	clear_screen();
    }

    // 남는 좌석 표시 함수
    void seat(int targetMovie, int& row, int& column) {
    	row = -1, column = -1;

    	for(auto& theater : theaterList) {
    		Movie* movie = theater.getMovie();
    		if(movie != nullptr && movie->getNumber() == targetMovie) {
    			displaySeatWindow(theater, true, row, column);

    			if(row == -1 || column == -1) {
    				cout << "좌석을 선택하지 않았습니다.";
    			}

    			theater.setSeat(row, column);
			    cout << endl << "예약 성공! 자리: " << rowToChar(row) << column << endl;
    			return;
    		}
    	}

    	cout << "영화를 찾을 수 없습니다" << endl;
    }

    void reserveMovie() {
        int targetMovie;
        cout << "영화 예약 메뉴입니다." << endl;
        cout << "원하시는 영화의 번호를 입력해주세요." << flush;
        cin >> targetMovie;

	    int row, column;
        seat(targetMovie, row, column); //좌석 표시 함수
    }

    void printReservedSeats(int targetMovie) {
    	for(auto& theater : theaterList) {
    		Movie* movie = theater.getMovie();
    		if(movie != nullptr && movie->getNumber() == targetMovie) {
    			for(int row = 0; row < Theater::ROW; row++) {
    				for(int column = 0; column < Theater::COLUMN; column++) {
    					if(theater.getSeat(row, column) == 1) {
    						cout << rowToChar(row) << column << endl;
    					}
    				}
    			}

    			break;
    		}
    	}
    }

    void reserveCancel() {
        int targetMovie;
        cout << "예약 취소" << endl;

        cout << "영화 번호를 입력하세요: " << endl;
        cin >> targetMovie;

        for(auto& theater : theaterList) {
        	Movie* movie = theater.getMovie();
        	if(movie != nullptr && movie->getNumber() == targetMovie) {
        		int row, column;
        		displaySeatWindow(theater, false, row, column);
        		if(row == -1 || column == -1) {
        			cout << "좌석을 선택하지 않았습니다." << endl;
        			return;
        		}

        		if(theater.getSeat(row, column) == 0) {
        			cout << "예약되지 않은 자리입니다." << endl;
        		}else{
        			theater.unsetSeat(row, column);
        			cout << endl << rowToChar(row) << column << " 자리의 예약을 취소했습니다" << endl;
        		}

        		return;
        	}
        }

        cout << "영화가 존재하지 않습니다." << endl;
    }

    static char rowToChar(int row) {
	    char rowChars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N'};
	    return rowChars[row % 13];
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
    Cinema cinema;

    if (signal(SIGUSR1, Cinema::signalHandler) == SIG_ERR) {
        perror("adminSigHandler() error!");
    }

    cinema.startProgram();

    return 0;
}
