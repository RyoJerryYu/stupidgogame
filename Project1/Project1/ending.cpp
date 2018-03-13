#include "head.h"
using namespace gogame; 
struct isinner :public predicate {
	point bound;
	isinner(point c) :bound(c) {};
	bool operator()(point p) {
		for (point x : around(p)) {
			if (board[x] != board[p] && board[x] != board[bound])return false;
		}
		return true;
	}
};
struct isair :public predicate {
	bool operator()(point p) {
		return board[p] == 0;
	}
};
int killdead() {
	pool found;
	pointset deadset;
	for (int r = 0; r < row_; r++)
		for (int c = 0; c < col_; c++)
			if (board[r][c] != 0 && found[r][c] == 0) {//LOOP.1, search STONES
				point p(r, c);
				found[p] = 1;//p and it's block will never be found again.
				int lifeflag = 0;
				//lifeflag means the number of air insite linked(p),
				//while lifeflag smaller than 2, linked(p) is a dead block.
				pool innermark;
				pointset linktop = linked(p);
				for (point x : linktop) {
					found[x] = 1;//FOUND of LOOP.1
					if (lifeflag > 1)continue;
					for (point ar : around(x, isair())) {//LOOP.2 search AIR
						if (found[ar] == 1||innermark[ar]==1)continue;
						pointset innerair = linked(ar, isinner(p));
						if (innerair.empty()) {//Not inner air comes here.
							for (point y : linked(ar))found[y] = 1;//FOUND LOOP.2
							continue;
						}
						//Only inner air could come here.
						if (innerair.size() > 4)lifeflag += 2;
						else lifeflag++;
						for (point y : innerair)innermark[y] = 1;//FOUND LOOP.2
					}
				}
				if (lifeflag < 2)deadset.insert(deadset.end(), linktop.begin(), linktop.end());
			}
	for (point p : deadset)board[p] = 0;
	return 0;
}