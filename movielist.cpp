#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<fstream>
#include<cstdlib>


using namespace std;

class cinema {



	class Movie {
	private:
		int id; // 영화 고유 번호
		string name; // 영화이름
		string genre; // 장르	
		int theater_n; // 영화상영관

	public:
		Movie(int i, string n, string g,int t) {
			id = i;
			name = n;
			genre = g;
			theater_n = t;


		}
		int getid() {
			return id;
		}
		string getname() { return name; }
		string getgenre() 
		{
			return genre;
		}
		int gettheater_n() 
		{
			return theater_n;
		}

	};
public:

	list<Movie> movielist; 
	/*영화 txt 파일에는
	영화 고유번호
	영화제목
	영화장르
	영화상영관
	이렇게 저장되있다고 가정*/
	


	void showMovie() {
		string buf;
		
		ifstream file("./movielist.txt");
		while (file.peek() != EOF) {

			getline(file, buf);

			
			int id = atoi(buf.c_str());

			getline(file, buf);

			
			string name = buf;

			getline(file, buf);

			
			string genre = buf;
			getline(file, buf);

			
			int theater_n = atoi(buf.c_str());

			Movie movie = Movie(id, name, genre,theater_n);
			movielist.push_back(movie);


		}


		cout << "( 영화검색 )\n";

		cout << "==================================================\n";
		cout << "고유번호" << "\t\t" << "제목" << "\t\t" << "장르" << "\t\t" << "상영관" << endl;

		list<Movie>::iterator i;
		for (i = movielist.begin(); i != movielist.end(); ++i) {
			cout << i->getid() << "\t\t" << i->getname() << "\t\t" << i->getgenre() << "\t\t"<<i->gettheater_n()<<"관"<<endl;
		}
		cout << endl;
		cout << "--------------------------------------------------\n";



	}





};


int main() {
	cinema c = cinema();
	c.showMovie();
}

