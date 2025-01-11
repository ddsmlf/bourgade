#include "game.h"

int compare_score(const void* a, const void* b)
{
  struct player_score_t score_a = * ((struct player_score_t*)a);
  struct player_score_t score_b = * ((struct player_score_t*)b);
  return (score_a.score < score_b.score) - (score_a.score > score_b.score);
}

bool are_neightbors(struct position_t* pos1, struct position_t* pos2) {
    struct position_t* neighbors[MAX_NEIGHBORS] = { NULL }; // Initialize array to NULL
  list_neighbors(pos1, neighbors);
  for (unsigned int i = 0; i < MAX_NEIGHBORS; i++) {
    if (neighbors[i] != NULL) {
      if (is_valid_position(neighbors[i]) && neighbors[i] == pos2){
          return true;
      }

    }
  }
  return false;
}

void goals(struct board_t* board){
  unsigned int playe_with_max_buildings = 1000;
  unsigned int max_buildings = 0;
  for (unsigned int i = 0; i < board->num_players; i++) {
    struct player_t* player = &board->players[i];
    if (!(player->eliminated)){
      unsigned int buildings_count = 0;
      unsigned int buildings_corn_count = 0;
      struct position_t* building_pos[MAX_BUILDING];
      for (unsigned int j = MAX_MINE-1; j < MAX_BUILDING; j++) {
        if (board->building[j].owned && board->building[j].owner_id == i){
          building_pos[buildings_count++] = board->building[j].position;
          if (board->building[j].supplies[CORN] > 0){
            buildings_corn_count++;
          }
        }
      }
      if (buildings_count > MAX_WORKERS_PER_PLAYER){
        player->resources[GOLD] += 3;
        printf("Player %d has more than %d buildings, he win 3 Golds !\n", i, MAX_WORKERS_PER_PLAYER);
      }
      if (buildings_corn_count > 2){
        player->resources[GOLD] += 2;
        printf("Player %d has more than 2 buildings with corn, he win 2 Golds !\n", i);
      }
      for (unsigned int j = 0; j < buildings_count; j++) {
        for (unsigned int k = 0; k < buildings_count; k++) {
          if (j != k && are_neightbors(building_pos[j], building_pos[k])) {
            for (unsigned int l = 0; l < buildings_count; l++) {
              if (l != j && l != k && (are_neightbors(building_pos[k], building_pos[l]) || are_neightbors(building_pos[j], building_pos[l]))) {
                player->resources[GOLD] += 2;
                printf("Player %d has tree buildings connected, he wins 2 Golds!\n", i);
                break;
              }
            }
          }
        }
      }
      if (buildings_count > max_buildings){
        max_buildings = buildings_count;
        playe_with_max_buildings = i;
      }

    }
  }
  if (playe_with_max_buildings != 1000){
    board->players[playe_with_max_buildings].resources[GOLD] += 5;
    printf("Player %d has the most buildings, he wins 5 Golds!\n", playe_with_max_buildings);
  }
}

void print_scores(struct board_t* board) {
  goals(board);
  struct player_score_t scores[board->num_players];
  for (unsigned int player_id = 0; player_id < board->num_players; player_id++) {
    struct player_score_t score = {player_id, board->players[player_id].resources[GOLD] };
    scores[player_id] = score;
  }
  qsort(scores, board->num_players, sizeof(struct player_score_t), compare_score);
  printf("Scores:\n");

  unsigned int rank = 1;
  unsigned int current_score = scores[0].score;
  for (unsigned int i = 0; i < board->num_players; i++) {
    if (scores[i].score < current_score) {
      rank++;
    }
    printf("%d. %s Player %d %s (%d)\n", rank, color_start(board->players[scores[i].player_id].color),
           scores[i].player_id, color_stop(), scores[i].score);
  }
}

void play_game(struct board_t board, unsigned int rounds) {
  unsigned int round = 0;
  printf("players: %d\n", board.num_players);
  bool playing = true;
  while (round < rounds && playing) {
    bool continue_round = true;

    for (unsigned int player_id = 0; player_id < board.num_players; player_id++) {
      struct player_t *player = &board.players[player_id];
      if (player->eliminated) {
        continue;
      }

      init_decision_data(&board, player_id);
    }

    unsigned int player_id = rand() % (board.num_players - 1);
    while (continue_round) {
      continue_round = false;
      struct player_t *player = &board.players[player_id];
      if (player->eliminated) {
        continue;
      }
      unsigned int free_employee_count = 0;
      unsigned int free_employees[MAX_WORKERS_PER_PLAYER];
      find_free_employees(&board.players[player_id], free_employees, &free_employee_count);
      if (free_employee_count > 0) {
        struct position_t* free_pos = find_empty_position(&board);
        if (free_pos != NULL && is_valid_position(free_pos)) {
          continue_round = true;
          struct employee_placement_t employee_placement = place_employee(&board, player_id, free_employees,
                                                                          free_employee_count);
          if (employee_placement.employee >= free_employee_count || employee_placement.position == NULL ||
              !is_valid_position(employee_placement.position) ||
              !is_position_free(&board, employee_placement.position)) {
            eliminate_player(&board, player_id);
            continue;
          }
          player->employees[free_employees[employee_placement.employee]].position = employee_placement.position;
          unsigned int affordable_buildings[MAX_BUILDING];
          unsigned int affordable_building_count = 0;
          list_affordable_buildings(&board, player_id, affordable_buildings, &affordable_building_count);
          if (affordable_building_count > 0 && wishes_to_build(&board, player_id)) {
            unsigned int selected_building = select_building(&board, player_id, affordable_buildings, affordable_building_count);
            if (selected_building >= affordable_building_count) {
              eliminate_player(&board, player_id);
              continue;
            }
            construct_building(&board, player_id, affordable_buildings[selected_building], free_pos);
          } else {
            collect_resources(&board, player_id, free_pos);
          }
        }
      }
      if (player_id >= board.num_players - 1) {
        player_id = 0;
      } else {
        player_id++;
      }
    }
    pay_employees(&board);
    reset_employees(&board);
    for(unsigned int i = 0; i < board.num_building; i++){
      if (!board.building[i].is_mine && board.building[i].position != NULL && is_valid_position(board.building[i].position)){
        board.building[i].update_building(&board.building[i], &board);
      }
    }
    if (count_players(&board) < 2) {
      playing = false;
    }
    round++;
  }

  print_scores(&board);
}
