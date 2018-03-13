#include "head.h"
using namespace gogame;
int judgement() {
	pool found;
	struct Isinner {
		point bound;
		Isinner(point c):bound(c) {};
		bool operator()(point p) {
			for (point x : around(p)) {
				if (board[x] != board[p] && board[x] != board[bound])return false;
			}
			return true;
		}
	};
	for (int r = 0; r < row_; r++)
		for (int c = 0; c < col_; c++)
			if (board[r][c] != 0 && found[r][c] == 0) {
				point p(r, c);
				int lifeflag = 0;
				//lifeflage means the number of air insite linked(p),
				//while lifeflag smaller than 2, linked(p) is a dead block.
				pointset airbuff;
				auto isair = [](point a)->bool {return board[a] == 0; };
				Isinner isinner(p);
				for (point x : linked(p)) {
					found[p] = 1;
					for (point ar : around(x, isair)) {
						if (found[ar] == 1)continue;
						pointset innerair = linked(ar, isinner);
					}
				}
			}
}