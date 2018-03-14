#include "head.h"
#include <cstdlib>
using namespace gocore;
int initialize() {
	std::system("color 2f");
	std::system("mode con cols=50 lines=25");
	std::system("title stupid gogame");
	row_ = 9, col_ = 9;
	playernum_ = 2;
	board = pool(0);
	air = pool(4);
	for (int i = 0; i < col_; i++) {
		air[0][i]--;
		air[row_ - 1][i]--;
	}
	for (int i = 0; i < row_; i++) {
		air[i][0]--;
		air[i][col_ - 1]--;
	}
	players.clear();
	const wchar_t outstr[3] = { L'\0',L'¡ð',L'¡ñ' };
	players.push_back(player("NULL",outstr[0],true));//first of players is null
	for (int i = 1; i <= playernum_; i++) {
		players.push_back(player("player"+std::to_string(i),outstr[i],false));//size of players equal to playernum_+1
	}
	return 0;
}