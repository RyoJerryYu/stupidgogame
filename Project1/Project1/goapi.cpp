#include "head.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace gocore;
point input(int tplayer) {
	using std::cin;
	using std::cout;
	using std::endl;
	int r, c;
	std::string s;
	cout << "Turn of player: " << tplayer << endl;
	cout << "Please write a position as \"row col\", as: 3 4" << endl;
	cin >> s;
	if (s.substr(0, 4) == "pass") {
		players[tplayer].pass = true;
		return point();
	}
	r = std::stoi(s);
	cin >> c;
	while (r < 0 || r >= row_ || c < 0 || c >= col_ || board[r][c] != 0) {
		if (r < 0 || r >= row_ || c < 0 || c >= col_) {
			cout << "This position is out of board!\nPlease write a position on the board:" << endl;
			cin >> r >> c;
		}
		else {
			cout << "This position already has a stones!\nPlease write another position:" << endl;
			cin >> r >> c;
		}
	}
	return point(r, c);
}
int display() {
	std::system("cls");
	using std::cin;
	using std::wcout;
	using std::endl;
	wcout.imbue(std::locale("chs"));
	const wchar_t displaygrid[3][3] = { 
		L'©°',L'©Ð',L'©´',
		L'©À',L'©à',L'©È',
		L'©¸',L'©Ø',L'©¼' };
	for (int c = 0; c < col_; c++) {
		wcout << " " << c%10;
	}
	wcout << endl;
	for (int r = 0; r < row_; r++) {
		wcout << r % 10;
		for (int c = 0; c < col_; c++) {
			if (board[r][c] != 0) {
				wcout << players[board[r][c]].display;
			}
			else {//display board[r][c] as grid.
				int dr, dc;
				if (r == 0)dr = 0;
				else if (r == row_ - 1)dr = 2;
				else dr = 1;
				//row of displaygrid.
				if (c == 0)dc = 0;
				else if (c == col_ - 1)dc = 2;
				else dc = 1;
				//col of displaygrid.
				wcout << displaygrid[dr][dc] << ' ';
			}
		}
		wcout << r % 10 << endl;
	}
	for (int c = 0; c < col_; c++) {
		wcout << " " << c % 10;
	}
	wcout << endl;
	return 0;
}
int passinfo(int tplayer) {
	std::cout << "Player: " << players[tplayer].name << " was passed!" << std::endl;
	return 0;
}
int displayscore() {
	for (int tplayer = 1; tplayer <= playernum_; tplayer++) {
		std::cout << "Player: " << players[tplayer].name << "\t get score:" << players[tplayer].score << std::endl;
	}
	std::system("pause>nul");
	return 0;
}