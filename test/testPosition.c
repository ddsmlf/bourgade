#include <stdio.h>
#include <stdbool.h>
#include "position.h"

bool test_make_position(char** message) {
    init_positions(0);
    struct position_t* p = make_position(1, 2);

    if (position_x(p) != 1 || position_y(p) != 2) {
        *message = "make_position n'a pas correctement initialisé les coordonnées.";
        return false;
    }

    struct position_t* invalid_p = make_invalid_position();
    if (is_valid_position(invalid_p)) {
        *message = "make_invalid_position n'a pas créé une position invalide.";
        return false;
    }

    return true;
}


bool test_is_valid_position(char** message) {    
    init_positions(0);
    struct position_t* p_valid = make_position(1, 1);

    if (!is_valid_position(p_valid)) {
        *message = "is_valid_position considère une position valide comme invalide.";
        return false;
    }

    struct position_t* p_invalid = make_invalid_position();
    if (is_valid_position(p_invalid)) {
        *message = "is_valid_position considère une position invalide comme valide.";
        return false;
    }

    struct position_t* p_invalid2 = make_position(MAX_X, MAX_Y);
    if (is_valid_position(p_invalid2)) {
        *message = "is_valid_position considère une position invalide comme valide.";
        return false;
    }


    return true;
}


bool test_list_neighbors(char** message) {
    init_positions(0);
    struct position_t* p = make_position(1, 1);
    struct position_t* neighbors[MAX_NEIGHBORS];
    struct position_t* neighbors_attendu_seed0[MAX_NEIGHBORS] = {make_position(1,0), make_position(0,1), make_position(2,0), make_position(0,0), make_position(0,2), make_position(1,2),make_position(2,1), make_position(2,2)};
    // struct position_t* neighbors_attendu_seed1[MAX_NEIGHBORS] = {make_position(2,1), make_position(2,0), make_position(2,3), make_position(2,4), make_position(1,2), make_position(0,2), make_position(3,2), make_position(4,2)};
    // struct position_t* neighbors_attendu_seed2[MAX_NEIGHBORS] = {make_position(3,3), make_position(1,1), make_position(3,1), make_position(1,3), make_position(0,0), make_position(4,4), make_position(4,0), make_position(0,4)};

    list_neighbors(p, neighbors);

    int valid_neighbors = 0;
    for (int i = 0; i < MAX_NEIGHBORS; i++) {
        if (is_valid_position(neighbors[i])) {
            unsigned int x = position_x(neighbors[i]);
            unsigned int y = position_y(neighbors[i]);
            for (int j = 0; j < MAX_NEIGHBORS; j++) {
                if (x == position_x(neighbors_attendu_seed0[j]) && y == position_y(neighbors_attendu_seed0[j])) {
                    valid_neighbors++;
                    break;
                }
            }
        }
    }

    if (valid_neighbors != 8) {
        *message = "list_neighbors n'a pas retourné le bon nombre de voisins valides.";
        return false;
    }

    return true;
}
