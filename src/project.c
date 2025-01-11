#include <stdio.h>
#include <stdlib.h>
#include "board.h" 
#include "game.h"
#include <time.h>
#include <getopt.h>

int main(int argc, char *argv[])  {
  int num_players = 4;
  int position_seed = 0;
  int rng_seed = time(NULL);
  int opt;
  while ((opt = getopt(argc, argv, "s:p:c:")) != -1) {
    switch (opt) {
      case 's':
        rng_seed = atoi(optarg);
        break;
      case 'p':
        num_players = atoi(optarg);
        if (num_players > MAX_PLAYERS){
          fprintf(stderr, "Error: num_players (%d) exceeds maximum number of players (%d)\n", num_players, MAX_PLAYERS);
          exit(EXIT_FAILURE);
        }
        break;
      case 'c':
        position_seed = atoi(optarg);
        break;
      default: /* '?' */
        fprintf(stderr, "Usage: %s [-s rng_seed] [-p num_players] [-c position_seed]\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  srand(rng_seed);

  struct board_t board = init_board(num_players, position_seed);
  play_game(board, 4); 
  return 0;
}