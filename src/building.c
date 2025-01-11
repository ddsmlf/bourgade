#include "building.h"
#include "board.h" 


void update_not_implemented(struct building_t *building, struct board_t *board) {
    (void)building;
    (void)board;
}


struct building_t make_building(const char *name, const unsigned int value[NUM_RESOURCES], const unsigned int earns[NUM_RESOURCES], const unsigned int costs[NUM_RESOURCES], const unsigned int supplies[NUM_RESOURCES], bool is_mine, struct position_t *position, void (*update_building)(struct building_t*, struct board_t*))
{
    struct building_t b;
    strncpy(b.name, name, MAX_BUILDING_STR);
    for (int i = 0; i < NUM_RESOURCES; i++) {
        b.value[i] = value[i];
        b.earns[i] = earns[i];
        b.costs[i] = costs[i];
        b.supplies[i] = supplies[i];
    }
    b.owned = false;
    b.is_mine = is_mine;
    b.position = position;
    b.update_building = (update_building != NULL) ? update_building : update_not_implemented;
    return b;
}




void generate_random_values(unsigned int values[NUM_RESOURCES], unsigned int max) {
    values[0] = 0;
    for (int i = 1; i < NUM_RESOURCES; i++) {
        values[i] = rand() % max;
    }
}

void update_cathedral(struct building_t *building, struct board_t *board) {
    struct position_t* neighbors[MAX_NEIGHBORS];
    list_neighbors(building->position, neighbors);
    for (unsigned int j = 0; j < MAX_NEIGHBORS; j++) {
        if (neighbors[j] != NULL && is_valid_position(neighbors[j])) {
            for (unsigned int k = 0; k < board->num_players; k++) {
                if (board->players[k].eliminated) {
                    continue;
                }
                for (unsigned int l = 0; l < MAX_EMPLOYEE; l++) {
                    if (board->players[k].employees[l].position == neighbors[j]) {
                        building->earns[GOLD] += 1;
                    }
                }
            }
        }
    }
}

void update_castle(struct building_t *building, struct board_t *board) {
    struct position_t* neighbors[MAX_NEIGHBORS];
    list_neighbors(building->position, neighbors);
    for (unsigned int j = 0; j < MAX_NEIGHBORS; j++) {
        if (neighbors[j] != NULL && is_valid_position(neighbors[j])) {
            for (unsigned int k = 0; k < MAX_BUILDING; k++) {
                if (board->building[k].position == neighbors[j] && board->building[k].owner_id == building->owner_id) {
                    building->earns[GOLD] += 1;
                }
            }
        }
    }
}

void update_guard_tower(struct building_t *building, struct board_t *board) {
    struct position_t* neighbors[MAX_NEIGHBORS];
    list_neighbors(building->position, neighbors);
    for (unsigned int j = 0; j < MAX_NEIGHBORS; j++) {
        if (neighbors[j] != NULL && is_valid_position(neighbors[j]) && is_position_free(board, neighbors[j])) {
            building->earns[GOLD] += 1;
        }
    }
}

void list_buildings(struct building_t building_av[]) {
    const char *names[] = {"Farm", "Sawmill", "Pontoon", "Quarry", "Market", "Bank", "Factory", "Cathedral", "Guard Tower", "Castle"};
    void (*update_building[10])(struct building_t*, struct board_t*) = {NULL};
    for (int i = 0; i < 10; i++) {
        unsigned int cost[NUM_RESOURCES];
        unsigned int earns[NUM_RESOURCES];
        unsigned int supplies[NUM_RESOURCES];
        unsigned int value[NUM_RESOURCES];
        generate_random_values(cost, 4);
        generate_random_values(earns, 5);
        generate_random_values(supplies, 10);
        generate_random_values(value, 3);

        building_av[i] = make_building(names[i], value, earns, cost, supplies, false, NULL, update_building[i]);
    }
}
void available_building(struct building_t building[MAX_AVAILABLE_BUILDING]){
    const unsigned int total_building = 10;
    struct building_t building_av[total_building];
    list_buildings(building_av);

    unsigned int last_selected_building = 100;
    for (int i = 0; i < MAX_AVAILABLE_BUILDING; i++) {
        unsigned int building_value;
        do {
            building_value = rand() % total_building;
        } while (building_value == last_selected_building);
        last_selected_building = building_value;
        building[i] = building_av[building_value];
    }
}
