#ifndef HEAD_H_
#define HEAD_H_

#include <vector>
#include <string>
extern int row_, col_;
extern int playernum_;

namespace gocore {
	struct player {
		std::string name;
		wchar_t display;
		bool pass = false;
		int score = 0;
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
		gocore::player player();
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
	pointset around(point,predicate&&);
	pointset linked(point);
	pointset linked(point,predicate&&);
	int placeon(int,point);
	int remove(point);
	int remove(pointset);
}

extern gocore::pool board;
extern gocore::pool air;
extern gocore::playerset players;

int initialize();
gocore::point input(int);
int mainphase(const int&,gocore::point&);
int display();
int passinfo(int);
int killdead();
int countscore();
int displayscore();
#endif //HEAD_H_