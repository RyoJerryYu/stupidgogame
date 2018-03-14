#include "head.h"
using namespace gocore;

int main() {
	initialize();
	point activep;
	while (!players.allpass()) {
		for (int tplayer = 1; tplayer <= playernum_; tplayer++) {
			if (!players[tplayer].pass) {
				display();
				activep=input(tplayer);
			}
			if (players[tplayer].pass) {
				passinfo(tplayer);
				continue;
			}
			mainphase(tplayer, activep);
		}
	}
	killdead();
	display();
	countscore();
	displayscore();
	return 0;
}