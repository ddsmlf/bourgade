#ifndef PR103_24333_GAME_H
#define PR103_24333_GAME_H

#include "board.h"

struct player_score_t {
    unsigned int player_id;
    unsigned int score;
};
void play_game(struct board_t board, unsigned int rounds);
#endif
