#include "head.h"
using namespace gogame;
int main() {
	initialize();
	point activep;
	while (!finish_flag_) {
		for (int i = 1; i <= playernum_; i++) {
			if (!finish_flag_) {
				activep=input();
			}
			if (finish_flag_)break;
			poson(i, activep);
		}
	}
	return 0;
}