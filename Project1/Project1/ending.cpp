#include "head.h"
using namespace gocore; 
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
				int lifeflag = 0;
				//lifeflag means the number of air insite linked(p),
				//while lifeflag smaller than 2, linked(p) is a dead block.
				pool innermark;
				pointset linktop = linked(p);
				for (point x : linktop) {
					found[x] = 1;//FOUND of LOOP.1 , will never find this stones block again.
					if (lifeflag > 1)continue;
					for (point ar : around(x, isair())) {//LOOP.2 search AIR
						if (found[ar] == 1||innermark[ar]==1)continue;
						pointset innerair = linked(ar, isinner(p));
						if (innerair.empty()) {//Not inner air comes here.
							for (point outer : linked(ar))found[outer] = 1;//FOUND of LOOP.2
							continue;
						}
						//Only inner air could come here.
						if (innerair.size() > 4)lifeflag += 2;
						else lifeflag++;
						for (point inner : innerair)innermark[inner] = 1;//FOUND of LOOP.2
					}
				}
				if (lifeflag < 2)deadset.insert(deadset.end(), linktop.begin(), linktop.end());
			}
	remove(deadset);
	return 0;
}
int countscore() {
	pool found;
	for(int r=0;r<row_;r++)
		for(int c=0;c<col_;c++)
			if (board[r][c] != 0 && found[r][c] == 0) {//LOOP.1
				point p(r, c);
				for (point x : linked(p)) {
					found[x] = 1;//FOUND of LOOP.1
					players[board[p]].score++;
					for (point ar : around(x, isair())) {
						if (found[ar] == 1)continue;//LOOP.2
						pointset innerair = linked(ar, isinner(p));
						if (innerair.empty()) {
							for (point outer : linked(ar))found[outer] = 1;//FOUND of LOOP.2
							continue;
						}
						for (point inner : innerair) {
							found[inner] = 1;//FOUND of LOOP.2
							players[board[p]].score++;
						}
					}
				}
			}
	return 0;
}