#include "head.h"
using namespace gogame;

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
			phase(tplayer, activep);
		}
	}
	display();
	killdead();
	return 0;
}