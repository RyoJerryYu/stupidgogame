#include "head.h"
using namespace gogame;
point input() {
	int r, c;
	printf("Please write a position as \"row col\" as under:\n3 4\n");
	scanf_s("%d %d", &r, &c);
	while (r < 0 || r >= row_ || c < 0 || c >= col_ || board[r][c] != 0) {
		if (r < 0 || r >= row_ || c < 0 || c >= col_) {
			printf("This position is out of board!\nPlease write a position on the board!\n");
			scanf_s("%d %d", &r, &c);
		}
		else {
			
			printf("This position already has a stones!\nPlease write another position!\n");
			scanf_s("%d %d", &r, &c);
		}
	}
	return point(r, c);
}