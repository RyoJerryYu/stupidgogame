#include "head.h"
using namespace gogame;
struct captured :public predicate {
	bool operator()(point x) {
		return air[x] == 0;
	}
};
int phase(const int& tplayer,point& activep) {
	placeon(tplayer, activep);
	pointset removemark;
	for (point x : around(activep)) {
		if (x.board() != tplayer) {
			pointset a = linked(x, captured());//First mark the captured stones of other players.
			removemark.insert(removemark.end(), a.begin(), a.end());
		}
	}
	remove(removemark);//Then remove them together.
	removemark.clear();
	for (point x : around(activep)) {
		if (x.board() == tplayer) {
			pointset a = linked(x, captured());
			removemark.insert(removemark.end(), a.begin(), a.end());
		}
	}
	remove(removemark);//After remove other players' stones, remove your teamates'.
	removemark.clear();
	if (board[activep] == tplayer) {
		remove(linked(activep, captured()));//After all, remove yourselves'.
	}
	return 0;
}