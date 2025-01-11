#include "decision.h"

void index_to_xy(int index, unsigned int *x, unsigned int *y) {
  *x = index % (MAX_X);
  *y = index / (MAX_X);
}

static struct decision_data_t decision_data[MAX_PLAYERS];

bool wishes_to_build(__attribute__((unused)) const struct board_t *board,
                     __attribute__((unused)) unsigned int player_id) {
  return rand() % 2 == 0;
}

bool wishes_to_activate(__attribute__((unused)) const struct board_t *board,
                        __attribute__((unused)) unsigned int player_id,
                        __attribute__((unused)) unsigned int building_id) {
  return rand() % 2 == 0;
}

unsigned int
select_building(__attribute__((unused)) const struct board_t *board, __attribute__((unused)) unsigned int player_id,
                __attribute__((unused)) unsigned int *buildings, unsigned int num_buildings) {
  return rand() % num_buildings;
}

void move_cursor(unsigned int* cursor, unsigned int i, unsigned int employee_count, unsigned int total_position_count) {
  while (i > 0 && cursor[i] == total_position_count - (employee_count - i)) {
    i--;
  }
  if (i == 0 && cursor[i] == total_position_count - employee_count) {
    for (unsigned int j = 0; j < employee_count; ++j) {
      cursor[j] = 0;
    }
  } else {
    cursor[i]++;
    for (unsigned int j = i + 1; j < employee_count; ++j) {
      cursor[j] = cursor[j - 1] + 1;
    }
  }
}

void get_resources_per_position(const struct board_t *board, unsigned int resources_per_position[MAX_POSITIONS][NUM_RESOURCES]) {
  for (unsigned int i = 0; i < MAX_POSITIONS; i++) {
    unsigned int x = i % (MAX_X);
    unsigned int y = i / (MAX_X);
    struct position_t* pos = make_position(x, y);
    if (position_x(pos) != x || position_y(pos) != y){
      for (unsigned int j = 0; j < NUM_RESOURCES; ++j) {
        resources_per_position[i][j] = 0;
      }
    } else {
      collect_resources_test(board, pos, resources_per_position[i]);
    }
    
  }
}


int resource_bigger_than(unsigned int r1[NUM_RESOURCES], unsigned int r2[NUM_RESOURCES]){
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (r1[i] > r2[i]) {
            return 1;
        }
    }
    return 0;
}

// Renvoie 1 si le vecteur du ressource du candidat à au moins un élément supérieur à celui d'un candidat déjà présent dans le tableau
int is_not_comparable_or_greater(struct candidate_t candidate, struct candidate_t* candidates, unsigned int candidate_count) {
  for (unsigned int i = 0; i < candidate_count; ++i) {
    if (resource_bigger_than(candidate.resources, candidates[i].resources)) {
        return 1;
      }
  }
  return 0;
}

int is_comparable_and_smaller(unsigned int r1[NUM_RESOURCES], unsigned int r2[NUM_RESOURCES]) {
  for (unsigned int i = 0; i < NUM_RESOURCES; ++i) {
    if (r1[i] > r2[i]) {
      return 0;
    }
  }
  return 1;
}

void add_candidate(struct candidate_t* candidates, unsigned int* candidate_count, struct candidate_t candidate, int max_elements) {
  candidates[*candidate_count] = candidate;
  *candidate_count = *candidate_count + 1;
  if (*candidate_count >= (unsigned int)max_elements) {
    printf("ERROR: candidate_count overflow\n");
    return;
  }
  if (*candidate_count > 1) {
    for (unsigned int i = 0; i < *candidate_count; ++i) {
      if (is_comparable_and_smaller(candidates[i].resources, candidate.resources)) {
        for(unsigned int j = i; j < *candidate_count; j++) candidates[j] = candidates[j + 1];
        *candidate_count = *candidate_count - 1;
      }
    }
  }
}

void update_optimal_employee_positions(const struct board_t *board, unsigned int player_id, unsigned int employee_count) {
  if (employee_count == 0) {
    return;
  }
  struct position_t* empty_positions[MAX_POSITIONS];
  unsigned int empty_position_count;
  list_empty_positions(board, empty_positions, &empty_position_count);

  unsigned int cursor[employee_count];

  for (unsigned int i = 0; i < employee_count; ++i) {
    cursor[i] = i;
  }
  if (empty_position_count < employee_count) {
    employee_count = empty_position_count; // pour le moment si on a moins de positions que d'employés on met autant d'employés que de positions restantes a voir si on veut faire autrement
  }
  unsigned long long max_combinations = 1;

  for (unsigned int i = 0; i < employee_count; ++i) {
    max_combinations *= (unsigned long long)(empty_position_count - i);
  }

  if (max_combinations > UINT_MAX) {
    printf("ERROR: max_combinations overflow\n");
    return;
  }

  unsigned int initial_size = 10;
  struct candidate_t* candidates = (struct candidate_t*)malloc(initial_size * sizeof(struct candidate_t));
  if (candidates == NULL) {
    printf("ERROR: Memory allocation failed\n");
    return;
  }

  // ajouter comme premier élément un candidat avec des ressources à 0
  struct candidate_t candidate;
  for (unsigned int j = 0; j < NUM_RESOURCES; ++j) {
    candidate.resources[j] = 0;
  }
  for (unsigned int j = 0; j < employee_count; j++) {
    candidate.positions[j] = empty_positions[j];
  }
  candidates[0] = candidate;

  unsigned int resources_per_position[MAX_POSITIONS][NUM_RESOURCES];
  get_resources_per_position(board, resources_per_position);
  unsigned int candidate_count = 1;

  for (unsigned int i = 0; i < max_combinations; i++) {
    struct candidate_t candidate;

    for (unsigned int j = 0; j < employee_count; j++) {
      candidate.positions[j] = make_invalid_position();
    }

    for (unsigned int j = 0; j < employee_count; j++) {
      struct position_t *position = empty_positions[cursor[j]];
      candidate.positions[j] = position;
    }

    move_cursor(cursor, employee_count - 1, employee_count, empty_position_count);

    for (unsigned int j = 0; j < NUM_RESOURCES; ++j) {
      candidate.resources[j] = 0;
    }
    int invalid = 0;
    for (unsigned int j = 0; j < employee_count; j++) {
      if (is_valid_position(candidate.positions[j])) {
        unsigned int position_index = IND(position_x(candidate.positions[j]), position_y(candidate.positions[j]));
        resource_add(candidate.resources, resources_per_position[position_index], candidate.resources);
      }
      else{
        invalid = 1;
        break;
      }
    }
    if (!invalid && is_not_comparable_or_greater(candidate, candidates, candidate_count)) {
       add_candidate(candidates, &candidate_count, candidate, initial_size);
    }
  }

  decision_data[player_id].optimal_positions_tail = 0;
  // pour l'instant considérons que la meillerue c'est al première amsi il faudas choisir sleon les couts des batiments
  for (unsigned int i = 0; i < employee_count; ++i) {
    decision_data[player_id].optimal_positions[i] = candidates[0].positions[i];
    decision_data[player_id].optimal_positions_tail += 1;
  }

  free(candidates);
}

void init_decision_data(const struct board_t *board, unsigned int player_id) {
  unsigned int free_employee_count = 0;
  unsigned int free_employees[MAX_WORKERS_PER_PLAYER];
  find_free_employees(&board->players[player_id], free_employees, &free_employee_count);
  update_optimal_employee_positions(board, player_id, free_employee_count);
}

struct employee_placement_t place_employee(const struct board_t *board, unsigned int player_id,
        __attribute__((unused)) unsigned int *free_employees, unsigned int free_employee_count) {
  struct decision_data_t *player_decision_data = &decision_data[player_id];
  unsigned int i = player_decision_data->optimal_positions_head;

  while (i < player_decision_data->optimal_positions_tail) {
  if (is_position_free(board, player_decision_data->optimal_positions[i])) {
    struct employee_placement_t employee_placement = {
        .position = player_decision_data->optimal_positions[i],
        .employee = 0
    };
    player_decision_data->optimal_positions_head = i + 1;
    return employee_placement;
  }
  i++;
  }

  update_optimal_employee_positions(board, player_id, free_employee_count);
  player_decision_data->optimal_positions_head = 0;

  struct employee_placement_t employee_placement = {
      .position = player_decision_data->optimal_positions[player_decision_data->optimal_positions_head],
      .employee = 0
  };
  player_decision_data->optimal_positions_head++;
  return employee_placement;
}
