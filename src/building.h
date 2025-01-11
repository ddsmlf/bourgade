#ifndef PR103_24333_BUILDING_H
#define PR103_24333_BUILDING_H

#define MAX_BUILDING_STR 40
#define MAX_AVAILABLE_BUILDING (MAX_POSITIONS/3)

#include <stdbool.h>
#include "resource.h"
#include "position.h"
#include <string.h>
#include <stdlib.h>

// Forward declaration of struct board_t
struct board_t;

struct building_t {
    char name[MAX_BUILDING_STR];
    unsigned int value[NUM_RESOURCES]; // valeur d'achat
    unsigned int earns[NUM_RESOURCES]; // gain immédita
    unsigned int costs[NUM_RESOURCES]; //  cout d'activation
    unsigned int supplies[NUM_RESOURCES]; // recuperer pares activation
    struct position_t* position;
    unsigned int owner_id;
    bool owned;
    bool is_mine;
    void (*update_building)(struct building_t*, struct board_t*);
};

struct building_t make_building(const char* name, const unsigned int value[NUM_RESOURCES], const unsigned int earns[NUM_RESOURCES], const unsigned int costs[NUM_RESOURCES], const unsigned int supplies[NUM_RESOURCES], bool is_mine, struct position_t *position, void (*update_building)(struct building_t*, struct board_t*));
void available_building(struct building_t building[MAX_AVAILABLE_BUILDING]);

#endif // PR103_24333_BUILDING_H