#include "head.h"

bool finish_flag_ = false;
int row_ = 9, col_ = 9;
int playernum_ = 2;

gogame::pool board(0);
gogame::pool air(4);
gogame::playerset players;