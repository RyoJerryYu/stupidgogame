#ifndef HEAD_H_
#define HEAD_H_

#include <vector>
extern bool finish_flag_;
extern int row_, col_;
extern int playernum_;

namespace gogame {
	class player {	};

	class playerset :public std::vector<player> {};

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

	pointset around(point);
	pointset linked(point);
	int poson(int,point);
	int remove(point);
}

extern gogame::pool board;
extern gogame::pool air;
extern gogame::playerset players;

int initialize();
gogame::point input();
#endif //HEAD_H_