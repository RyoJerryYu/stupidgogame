#include "head.h"
using namespace gogame;
int main() {
	initialize();
	point active;
	while (!finish_flag_) {
		for (int i = 1; i <= playernum_; i++) {
			if (!finish_flag_) {
				active=input();
			}
			if (finish_flag_)break;
			playon(i)(active);
		}
	}
	return 0;
}