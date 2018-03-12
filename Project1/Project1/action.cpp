#include "head.h"
using namespace gogame;
class playon {
	int player;
public:
	playon(int p) :player(p) {};
	int operator()(point posi) {
		board[posi] = player;
		for (point x : around(posi)) {
			air[x]--;
		}
		return 0;
	}
};
class remove {
public:
	remove() {};
	int operator()(point posi) {
		board[posi] = 0;
		for (point x : around(posi)) {
			air[x]--;
		}
		return 0;
	}
};
