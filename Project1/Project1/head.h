#ifndef HEAD_H_
#define HEAD_H_

#include <vector>
#include <string>
extern bool finish_flag_;
extern int row_, col_;
extern int playernum_;

namespace gogame {
	struct player {
		std::string name;
		wchar_t display;
		bool pass = false;
		player(std::string s,wchar_t c,bool p) :name(s),display(c),pass(p) {};
	};

	class playerset :public std::vector<player> {
	public:
		bool allpass();
	};

	struct point {
		int row, col;
		point(int r = 0, int c = 0) :row(r), col(c) {};
		int& board();
		int& air();
		gogame::player player();
	};

	class pointset :public std::vector<point> {};

	class pool {
		std::vector<std::vector<int> > Pool;
	public:
		pool(int = 0, int = ::row_, int = ::col_);
		int& operator[](point);
		std::vector<int>& operator[](int);
	};

	struct predicate {
		virtual bool operator()(point) {
			return true;
		}
	};

	pointset around(point);
	pointset around(point,predicate);
	pointset linked(point);
	pointset linked(point,predicate);
	int placeon(int,point);
	int remove(point);
	int remove(pointset);
}

extern gogame::pool board;
extern gogame::pool air;
extern gogame::playerset players;

int initialize();
gogame::point input(int);
int phase(const int&,gogame::point&);
int display();
int passinfo(int);
int killdead();
#endif //HEAD_H_