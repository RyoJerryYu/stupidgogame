#include "head.h"
int& gogame::point::board() { 
	return ::board[*this]; 
};
int& gogame::point::air() {
	return ::air[*this]; 
};
gogame::player gogame::point::player() {
	return players[board()];
}

gogame::pool::pool(int v, int r, int c) {
	Pool = std::vector<std::vector<int> >(r, std::vector<int>(c, v));
};
int& gogame::pool::operator[](point p) {
	return Pool[p.row][p.col]; 
};
std::vector<int>& gogame::pool::operator[](int i) {
	return Pool[i]; 
};

gogame::pointset gogame::around(point p) {
	pointset set;
	if (p.row != 0) {
		set.push_back(point(p.row - 1, p.col));
	}
	if (p.col != 0) {
		set.push_back(point(p.row, p.col - 1));
	}
	if (p.row != row_) {
		set.push_back(point(p.row + 1, p.col));
	}
	if (p.col != col_) {
		set.push_back(point(p.row, p.col + 1));
	}
	return set;
};

gogame::pointset gogame::linked(point p) {
	pool buff;
	pointset stark, res;
	buff[p] = 1;
	stark.push_back(p);
	res.push_back(p);
	while (!stark.empty()) {
		point x = stark.back();
		stark.pop_back();
		for (point& y : around(x)) {
			if (y.board() == x.board() && buff[y] != 1) {
				buff[y] = 1;
				stark.push_back(y);
				res.push_back(y);
			}
		}
	}
	return res;
}

int gogame::poson(int player, point posi) {
	board[posi] = player;
	for (point x : around(posi)) {
		air[x]--;
	}
	return 0;
}
int gogame::remove(point posi) {
	board[posi] = 0;
	for (point x : around(posi)) {
		air[x]--;
	}
	return 0;
}