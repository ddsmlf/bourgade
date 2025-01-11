#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "building.h"
#include "position.h"


bool test_make_building(char **message) {
    unsigned int value[NUM_RESOURCES];
    unsigned int earns[NUM_RESOURCES];
    unsigned int costs[NUM_RESOURCES];
    unsigned int supplies[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++) {
        value[i] = i;
        earns[i] = 2+i;
        costs[i] = i;
        supplies[i] = 0;
    }

    struct position_t* position = make_position(1,1);

    struct building_t building = make_building("Test Building", value, earns, costs, supplies, true, position, NULL);

    if (strcmp(building.name, "Test Building") != 0) {
        *message = "make_building n'a pas correctement initialisé le nom du bâtiment.";
        return false;
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (building.value[i] != value[i]) {
            *message = "make_building n'a pas correctement initialisé la valeur.";
            return false;
        }
        if (building.earns[i] != earns[i]) {
            *message = "make_building n'a pas correctement initialisé les gains.";
            return false;
        }
        if (building.costs[i] != costs[i]) {
            *message = "make_building n'a pas correctement initialisé les coûts.";
            return false;
        }
        if (building.supplies[i] != supplies[i]) {
            *message = "make_building n'a pas correctement initialisé les approvisionnements.";
            return false;
        }
    }

    if (position_x(building.position) != position_x(position) || position_y(building.position) != position_y(position)) {
        *message = "make_building n'a pas correctement initialisé la position.";
        return false;
    }

    if (!building.is_mine) {
        *message = "make_building n'a pas correctement initialisé is_mine.";
        return false;
    }
    return true;
}

bool test_available_building(char **message) {
    struct building_t buildings[MAX_AVAILABLE_BUILDING];
    available_building(buildings);

    for (int i = 0; i < MAX_AVAILABLE_BUILDING; i++) {
        if (buildings[i].name[0] == '\0') {
            *message = "available_building a généré un bâtiment avec un nom vide.";
            return false;
        }
    }

    return true;
}
