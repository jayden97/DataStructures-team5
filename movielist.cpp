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
		int id; // ��ȭ ���� ��ȣ
		string name; // ��ȭ�̸�
		string genre; // �帣	
		int theater_n; // ��ȭ�󿵰�

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
	/*��ȭ txt ���Ͽ���
	��ȭ ������ȣ
	��ȭ����
	��ȭ�帣
	��ȭ�󿵰�
	�̷��� ������ִٰ� ����*/
	


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


		cout << "( ��ȭ�˻� )\n";

		cout << "==================================================\n";
		cout << "������ȣ" << "\t\t" << "����" << "\t\t" << "�帣" << "\t\t" << "�󿵰�" << endl;

		list<Movie>::iterator i;
		for (i = movielist.begin(); i != movielist.end(); ++i) {
			cout << i->getid() << "\t\t" << i->getname() << "\t\t" << i->getgenre() << "\t\t"<<i->gettheater_n()<<"��"<<endl;
		}
		cout << endl;
		cout << "--------------------------------------------------\n";



	}





};


int main() {
	cinema c = cinema();
	c.showMovie();
}

