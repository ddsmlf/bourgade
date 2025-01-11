#include "mine.h"
#include "board.h"
#include "position.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


bool test_make_mine(char **message) {
    struct position_t* pos = make_position(1, 2);
    struct building_t mine = make_mine(FIELDS, pos);
    unsigned int supplies[NUM_RESOURCES] = {0};
    supplies[CORN] = 1;
    if (strcmp(mine.name, "Fields") != 0) {
        *message = "make_mine n'a pas correctement initialisé le type de mine.";
        return false;
    }

    if (position_x(mine.position) != position_x(pos) || position_y(mine.position) != position_y(pos)) {
        *message = "make_mine n'a pas correctement placé la mine à la position donnée.";
        return false;
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (mine.value[i] != 0) {
            *message = "make_mine n'a pas correctement initialisé les valeurs de la mine.";
            return false;
        }
        if (mine.earns[i] != 0) {
            *message = "make_mine n'a pas correctement initialisé les gains de la mine.";
            return false;
        }
        if (mine.costs[i] != 0) {
            *message = "make_mine n'a pas correctement initialisé les coûts de la mine.";
            return false;
        }
        if (mine.supplies[i] != supplies[i]) {
            *message = "make_mine n'a pas correctement initialisé les ressources de la mine.";
            return false;
        }
    }
    return true;
}

bool test_get_random_mine_type(char **message) {
    enum mine_type_t type = get_random_mine_type();

    if (type != FIELDS && type != LAKE && type != FOREST && type != QUARRY) {
        *message = "get_random_mine_type a retourné une valeur invalide.";
        return false;
    }

    return true;
}

bool test_place_mines(char **message) {
    struct board_t board = init_board(2, 0);

    unsigned int mine_count = 0;
    for (int x = 0; x <= MAX_X; x++) {
        for (int y = 0; y <= MAX_Y; y++) {
            struct position_t* pos = make_position(x, y);
            if (is_mine_here(&board, pos)) {
                mine_count++;
            }
        }
    }

    if (mine_count != MAX_MINE) {
        *message = "place_mines n'a pas placé le bon nombre de mines.";
        return false;
    }

    return true;
}

bool test_is_mine_here(char **message) {
    struct board_t board = init_board(2, 0);
    struct position_t* pos;
    for (int x = 0; x < MAX_X; x++) {
        for (int y = 0; y < MAX_Y; y++) {
            pos = make_position(x, y);
            int found = -1;
            for (int i=0; i<MAX_MINE; i++) {
                if (board.building[i].position == pos) {
                    found = i;
                    if (!is_mine_here(&board, pos)) {
                        *message = "is_mine_here n'a pas trouvé une mine qui est pourtant présente.";
                        return false;
                    }
                }
            }
            if (is_mine_here(&board, pos) && found == -1) {
                *message = "is_mine_here a trouvé une mine qui n'est pas présente.";
                return false;
            }
        }
    }

    return true;
}
