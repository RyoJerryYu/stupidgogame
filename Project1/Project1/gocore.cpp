#include "head.h"
bool gocore::playerset::allpass() {
	int allpass = 1;
	for (player i : *this) {
		allpass *= i.pass;
	}
	return (bool)allpass;
}

int& gocore::point::board() { 
	return ::board[*this]; 
};
int& gocore::point::air() {
	return ::air[*this]; 
};
gocore::player gocore::point::player() {
	return players[board()];
}

gocore::pool::pool(int v, int r, int c) {
	Pool = std::vector<std::vector<int> >(r, std::vector<int>(c, v));
};
int& gocore::pool::operator[](point p) {
	return Pool[p.row][p.col]; 
};
std::vector<int>& gocore::pool::operator[](int i) {
	return Pool[i]; 
};

gocore::pointset gocore::around(point p) {
	pointset set;
	if (p.row > 0) set.push_back(point(p.row - 1, p.col));
	if (p.col > 0) set.push_back(point(p.row, p.col - 1));
	if (p.row < row_ - 1) set.push_back(point(p.row + 1, p.col));
	if (p.col < col_ - 1) set.push_back(point(p.row, p.col + 1));
	return set;
};
gocore::pointset gocore::around(point p, predicate&& cmp) {
	pointset set;
	if (p.row > 0) {
		point a(p.row - 1, p.col);
		if (cmp(a))set.push_back(a);
	}
	if (p.col > 0) {
		point a(p.row, p.col - 1);
		if (cmp(a))set.push_back(a);
	}
	if (p.row < row_ - 1) {
		point a(p.row + 1, p.col);
		if (cmp(a))set.push_back(a);
	}
	if (p.col < col_ - 1) {
		point a(p.row, p.col + 1);
		if (cmp(a))set.push_back(a);
	}
	return set;
}

gocore::pointset gocore::linked(point p) {
	pool found;
	pointset stark, res;
	found[p] = 1;
	stark.push_back(p);
	res.push_back(p);
	while (!stark.empty()) {
		point x = stark.back();
		stark.pop_back();
		for (point y : around(x)) {
			if (y.board() == x.board() && found[y] != 1) {
				found[y] = 1;
				stark.push_back(y);
				res.push_back(y);
			}
		}
	}
	return res;
}
gocore::pointset gocore::linked(point p,predicate&& cmp) {
	pool found;
	pointset stark, res;
	if(!cmp(p)){
		res.clear();
		return res;
	}
	found[p] = 1;
	stark.push_back(p);
	res.push_back(p);
	while (!stark.empty()) {
		point x = stark.back();
		stark.pop_back();
		for (point y : around(x)) {
			if (y.board() == x.board() && found[y] != 1) {
				if (!cmp(y)) {
					res.clear();
					return res;
				}
				found[y] = 1;
				stark.push_back(y);
				res.push_back(y);
			}
		}
	}
	return res;
}

int gocore::placeon(int player, point posi) {
	board[posi] = player;
	for (point x : around(posi)) {
		air[x]--;
	}
	return 0;
}
int gocore::remove(point posi) {
	if (board[posi] == 0)return 0;
	board[posi] = 0;
	for (point x : around(posi)) {
		air[x]++;
	}
	return 0;
}
int gocore::remove(pointset posis) {
	for (const point& x : posis) {
		remove(x);
	}
	return 0;
}