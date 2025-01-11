#include "board.h"


void initialize_players(struct board_t* gb, enum color_t player_colors[MAX_PLAYERS]) {
  unsigned int initial_resources[6] = {0, 50, 20, 20, 20, 40};
  const unsigned int cost[NUM_RESOURCES] = {0, 1, 0, 0, 0};

  for (unsigned int i = 0; i < MAX_PLAYERS; i++) {
    struct player_t* player = &gb->players[i];
    player->num_employees = MAX_WORKERS_PER_PLAYER;
    player->eliminated = false;
    player->color = player_colors[i];
    memcpy(player->resources, initial_resources, sizeof(initial_resources));
    struct employee_t employee_template = employee_create("employee-----------", cost);
    for(unsigned int j = 0; j < MAX_WORKERS_PER_PLAYER; j++) {
      player->employees[j] = employee_template;
    }
  }
}

void initialize_buildings(struct board_t* gb) {
    struct building_t buildings[MAX_AVAILABLE_BUILDING];
    available_building(buildings);
    for (unsigned int i = 0; i < MAX_AVAILABLE_BUILDING; i++) {
        gb->building[gb->num_building + i] = buildings[i];
        gb->building[gb->num_building + i].position = NULL;
    }

    gb->num_building += MAX_AVAILABLE_BUILDING;
}

struct board_t init_board(unsigned int num_players, unsigned int seed_t) {
  struct board_t gb;
  gb.seed = seed_t;
  init_positions(gb.seed);
  gb.num_players = num_players;
  gb.num_building = 0;
  place_mines(&gb);
  gb.num_building = MAX_MINE;

  initialize_buildings(&gb);

  enum color_t player_colors[MAX_PLAYERS] = {WHITE, ORANGE, PINK, VIOLET};
  initialize_players(&gb, player_colors);

  return gb;
}

struct position_t* find_empty_position(const struct board_t* board) {
  for (unsigned int x = 0; x < MAX_X; x++) {
    for (unsigned int y = 0; y < MAX_Y; y++) {
      struct position_t* pos = make_position(x, y);
      if (is_position_free(board, pos)) {
        return pos;
      }
    }
  }
  return make_invalid_position();
}

void list_empty_positions(const struct board_t* board, struct position_t** empty_positions, unsigned int* num_empty_positions) {
  *num_empty_positions = 0;
  for (unsigned int x = 0; x < MAX_X; x++) {
    for (unsigned int y = 0; y < MAX_Y; y++) {
      struct position_t* pos = make_position(x, y);
      if (is_position_free(board, pos)) {
        empty_positions[*num_empty_positions] = pos;
        *num_empty_positions = (*num_empty_positions)+1;
      }
    }
  }
}

int get_building_id(const struct board_t* board, const struct position_t* pos) {
  int found = -1;
  
  for (unsigned int i = 0; i < (board->num_building); ++i) {
    if(board->building[i].position != NULL ){
      if (board->building[i].position == pos) {
        return (int)i;
      }
    }
    i++;
  }

  return found;
}

bool is_position_free(const struct board_t* board, const struct position_t* pos) {
  for (unsigned int i = 0; i < board->num_players; i++) {
    struct player_t player = board->players[i];
    for (unsigned int j = 0; j < player.num_employees; j++) {
      if (player.employees[j].position != NULL && position_x(player.employees[j].position) == position_x(pos) && position_y(player.employees[j].position) == position_y(pos)) {
        return false;
      }
    }
  }
  return get_building_id(board, pos) < 0;
}

void find_free_employees(const struct player_t* player, unsigned int* free_employees, unsigned int* num_free) {
  unsigned int count = 0;
  for (unsigned int i = 0; i < player->num_employees; i++) {
    if (player->employees[i].position == NULL) {
      free_employees[count++] = i;
    }
  }
  *num_free = count;
}

void collect_resources_test(const struct board_t* board, const struct position_t* pos, unsigned int acquired_resources[NUM_RESOURCES]) {
  memset(acquired_resources, 0, sizeof(unsigned int) * NUM_RESOURCES);
  struct position_t* neighbors[MAX_NEIGHBORS];
  list_neighbors(pos, neighbors);
  
  for (unsigned int i = 0; (i < MAX_NEIGHBORS) && (is_valid_position(neighbors[i])); i++) {    

    int building_id = get_building_id(board, neighbors[i]);
    if (building_id >= 0) {
      const struct building_t *building = &board->building[building_id];
      if (building->is_mine) {
        resource_add(acquired_resources, (unsigned int*)building->supplies, acquired_resources);
      }
    }
  }
}

void collect_resources(struct board_t* board, unsigned int player_id, const struct position_t* pos) {
  struct position_t* neighbors[MAX_NEIGHBORS];
  list_neighbors(pos, neighbors);
  struct player_t *player = &board->players[player_id];
  
  for (unsigned int i = 0; (i < MAX_NEIGHBORS) && (is_valid_position(neighbors[i])); i++) {  

    int building_id = get_building_id(board, neighbors[i]);
    if (building_id < 0) {
      continue;
    }
    
    struct building_t *building = &board->building[building_id];
    bool activate = false;
    
    if (building->is_mine) {
      activate = true;
    } else if (building->owned && (building->owner_id == player_id || resource_le_than(building->costs, player->resources))) {
      activate = wishes_to_activate(board, player_id, building_id);
    }
    
    if (activate) {
      activate_building(board, player_id, building_id);
    }
  }
}

void activate_building(struct board_t* board, unsigned int player_id, unsigned int building_id) {
  struct building_t* building = &board->building[building_id];
  struct player_t* player = &board->players[player_id];
  if (building->owned && building->owner_id != player_id) {
    resource_sub(player->resources, building->costs, player->resources);
    struct player_t* owner = &board->players[building->owner_id];
    if (!owner->eliminated) {
      resource_add(owner->resources, building->costs, owner->resources);
    }
  }
  resource_add(player->resources, building->supplies, player->resources);
}

void list_affordable_buildings(struct board_t* board, unsigned int player_id, unsigned int* affordable_buildings, unsigned int* num_affordable) {
  *num_affordable = 0;
  struct player_t* player = &board->players[player_id];
  for (unsigned int i = 0; i < board->num_building; i++) {
    struct building_t* building = &board->building[i];
    if (building->position == NULL && resource_le_than(building->costs, player->resources)) {
      affordable_buildings[*num_affordable] = i;
      *num_affordable += 1;
    }
  }
}

void eliminate_player(struct board_t* board, unsigned int player_id) {
  board->players[player_id].eliminated = true;
  board->players[player_id].resources[GOLD] = 0;
}

unsigned int count_players(struct board_t* board) {
  unsigned int player_count = 0;
  for (unsigned int i = 0; i < board->num_players; i++) {
    player_count += !board->players[i].eliminated;
  }

  return player_count;
}

void pay_employees(struct board_t* board) {
  for (unsigned int player_id = 0; player_id < board->num_players; player_id++) {
    struct player_t* player = &board->players[player_id];
    if (player->eliminated) {
      continue;
    }
    bool can_pay_all = true;
    for (unsigned int employee_id = 0; employee_id < player->num_employees; employee_id++) {
      if (player->employees[employee_id].position == NULL) {
        continue;
      }
      if (!resource_le_than(player->employees[employee_id].cost, player->resources)) {
        can_pay_all = false;
        break;
      }
    }
    if (can_pay_all) {
      for (unsigned int employee_id = 0; employee_id < player->num_employees; employee_id++) {
        resource_sub(player->resources, player->employees[employee_id].cost, player->resources);
      }
    } else {
      eliminate_player(board, player_id);
    }
  }
}

void construct_building(struct board_t* board, unsigned int player_id, unsigned int building_id, struct position_t* position) {
  struct player_t* player = &board->players[player_id];
  struct building_t* building = &board->building[building_id];
  
  for (unsigned int i = 0; i < NUM_RESOURCES; i++) {
    player->resources[i] = player->resources[i] - building->value[i] + building->earns[i];
  }
  
  building->position = position;
  building->owner_id = player_id;
  building->owned = true;
}

void reset_employees(struct board_t* board) {
  for (unsigned int player_id = 0; player_id < board->num_players; player_id++) {
    struct player_t* player = &board->players[player_id];
    if (!player->eliminated) {
      memset(player->employees, 0, sizeof(struct employee_t) * player->num_employees);
    }
  }
}


unsigned int has_valid_neighbors(const struct position_t *p)
{
  struct position_t *neighbors[MAX_NEIGHBORS];
  list_neighbors(p, neighbors);

  for (int i = 0; i < MAX_NEIGHBORS; ++i)
  {
    if (neighbors[i] != NULL && is_valid_position(neighbors[i]))
    {
      return 1;
    }
  }
  return 0;
}