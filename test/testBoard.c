#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "position.h"
#include "resource.h" 
#include "mine.h"
#include "employee.h"

bool test_init_board(char **message) {
    struct board_t board = init_board(2, 0);

    if (board.num_players != 2) {
        *message = "init_board n'a pas initialisé correctement le nombre de joueurs (attendu 2).";
        return false;
    }

    struct board_t board1 = init_board(3, 50);
    if (board1.num_players != 3) {
        *message = "init_board n'a pas initialisé correctement le nombre de joueurs (attendu 3).";
        return false;
    }

    struct board_t board2 = init_board(4, 100);
    if (board2.num_players != 4) {
        *message = "init_board n'a pas initialisé correctement le nombre de joueurs (attendu 4).";
        return false;
    }

    struct board_t board3 = init_board(1, 10);
    if (board3.num_players != 1) {
        *message = "init_board n'a pas initialisé correctement le nombre de joueurs (attendu 1).";
        return false;
    }

    return true;

}

bool test_list_empty_positions(char **message) {
    struct board_t board = init_board(2, 0);
    for (int i=0; i<MAX_BUILDING; i++) {
        board.building[i].position = NULL;
    }
    struct position_t* empty_positions[MAX_X * MAX_Y];
    unsigned int num_empty_positions = 0;

    list_empty_positions(&board, empty_positions, &num_empty_positions);
    if (num_empty_positions != MAX_X * MAX_Y) {
        static char buffer[100];
        snprintf(buffer, sizeof(buffer), "list_empty_positions n'a pas trouvé toutes les positions vides. Trouvé: %d, Attendu: %d", num_empty_positions, MAX_X * MAX_Y);
        *message = buffer;
        return false;
    }

    for (unsigned int i = 0; i < num_empty_positions; i++) {
        struct position_t* pos = empty_positions[i];
        if (!is_position_free(&board, pos)) {
            *message = "list_empty_positions a trouvé une position occupée.";
            return false;
        }
    }

    return true;
}

bool test_is_position_free(char **message) {
    struct board_t board = init_board(2, 0);
    for (unsigned int x = 0; x <= MAX_X; x++) {
        for (unsigned int y = 0; y <= MAX_Y; y++) {
            struct position_t *pos = make_position(x, y);   
            if (is_position_free(&board, pos)) {
                if (get_building_id(&board, pos) != -1) {
                    *message = "is_position_free a marqué une position libre comme occupée.";
                    return false;
                }
            }
            else {
                if (get_building_id(&board, pos) == -1) {
                    *message = "is_position_free a marqué une position occupée comme libre.";
                    return false;
                }
            }
        }
    }
    
    return true;
}

bool test_list_affordable_buildings(char **message) {
    struct board_t board = init_board(2, 0);
    unsigned int affordable_buildings[MAX_AVAILABLE_BUILDING];
    unsigned int num_affordable = 0;    

    for (int i = 0; i < NUM_RESOURCES; i++) {
        board.players[0].resources[i] = 0;
    }

    list_affordable_buildings(&board, 0, affordable_buildings, &num_affordable);

    if (num_affordable != 0) {
        *message = "list_affordable_buildings a trouvé des bâtiments abordables pour un joueur sans ressources.";
        return false;
    }
    for (int i = 0; i < NUM_RESOURCES; i++) {
        board.players[0].resources[i] = 100;
    }
    list_affordable_buildings(&board, 0, affordable_buildings, &num_affordable);

    if (num_affordable != MAX_AVAILABLE_BUILDING) {
        *message = "list_affordable_buildings n'a pas trouvé tous le bâtiment abordable pour un joueur avec des ressources.";
        return false;
    }

    return true;
}

bool test_collect_resources(char **message) {
    struct board_t board = init_board(2, 0);
    for (int i = 0; i < NUM_RESOURCES; i++) {
        board.players[0].resources[i] = 0;
    }
    struct position_t* pos_mine = board.building[0].position;
    struct position_t* neighbors[MAX_NEIGHBORS];
    list_neighbors(pos_mine, neighbors);
    collect_resources(&board, 0, neighbors[0]);
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (board.players[0].resources[i] != 0) {
            return true;
        }
    }

    *message = "collect_resources n'a pas collecté de ressources.";
    return false;
}

bool test_collect_resources_test(char **message) {
    struct board_t board = init_board(2, 0);
    struct position_t* pos_mine = board.building[0].position;
    struct position_t* neighbors[MAX_NEIGHBORS];
    list_neighbors(pos_mine, neighbors);
    unsigned int acquired_resources[NUM_RESOURCES];
    collect_resources_test(&board, neighbors[0], acquired_resources);
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (acquired_resources[i] != 0) {
            return true;
        }
    }

    *message = "collect_resources_test n'a pas collecté de ressources.";
    return false;
}

bool test_find_free_employees(char **message) {
    struct board_t board = init_board(2, 0);
    unsigned int free_employees[MAX_WORKERS_PER_PLAYER];
    unsigned int num_free = 0;

    find_free_employees(&board.players[0], free_employees, &num_free);

        if (num_free != MAX_WORKERS_PER_PLAYER) {
        *message = "find_free_employees n'a pas trouvé tous les employés libres.";
        return false;
    }

    for (int i = 0; i < MAX_WORKERS_PER_PLAYER; i++) {
        unsigned int x = i % (MAX_X);
        unsigned int y = i / (MAX_X);
        board.players[0].employees[i].position = make_position(x, y);
    }

    find_free_employees(&board.players[0], free_employees, &num_free);


    if (num_free != 0) {
        *message = "find_free_employees a trouvé des employés libres alors qu'il n'y en a pas.";
        return false;
    }
    return true;
}


bool test_get_building_id(char **message) {
    struct board_t board = init_board(2, 0);
    // positionner un batiment sur une position
    for (unsigned int x = 0; x <= MAX_X; x++) {
        for (unsigned int y = 0; y <= MAX_Y; y++) {
            struct position_t *pos = make_position(x, y);   
            if (is_position_free(&board, pos)) {
                if (get_building_id(&board, pos) != -1) {
                    *message = "get_building_id a trouvé un bâtiment alors qu'il n'y en avais pas.";
                    return false;
                }
                construct_building(&board, 0, 0, pos);
                if (get_building_id(&board, pos) != 0) {
                    *message = "get_building_id n'a pas trouvé le bon bâtiment.";
                    return false;
                }
                break;
            }
        }
    }
    
    return true;
}


bool test_pay_employees(char **message) {
    struct board_t board = init_board(2, 0);
    for (int i = 0; i < NUM_RESOURCES; i++) {
        board.players[0].resources[i] = 0;
    }
    if (board.players[0].eliminated) {
        *message = "pay_employees a éliminé un joueur sans employés.";
        return false;
    }
    pay_employees(&board);
    if (board.players[0].eliminated) {
        *message = "pay_employees a éliminé un joueur sans employés.";
        return false;
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        board.players[0].resources[i] = 100;
    }
    struct position_t* empty_positions[MAX_X * MAX_Y];
    unsigned int num_empty_positions = 0;

    list_empty_positions(&board, empty_positions, &num_empty_positions);
    
    board.players[0].employees[0].position = empty_positions[0];

    pay_employees(&board);
    if (board.players[0].eliminated) {
        *message = "pay_employees a éliminé un joueur qui avasi les ressources nécessaires.";
        return false;
    }

    return true;
}

bool test_count_players(char **message) {
    struct board_t board = init_board(2, 0);

    if (count_players(&board) != 2) {
        *message = "count_players n'a pas trouvé le bon nombre de joueurs actifs (attendu 2).";
        return false;
    }

    board.players[0].eliminated = true;

    if (count_players(&board) != 1) {
        *message = "count_players n'a pas trouvé le bon nombre de joueurs actifs (attendu 1).";
        return false;
    }

    board.players[1].eliminated = true;

    if (count_players(&board) != 0) {
        *message = "count_players n'a pas trouvé le bon nombre de joueurs actifs (attendu 0).";
        return false;
    }

    return true;
}


bool test_activate_building(char **message)
{
    struct board_t board = init_board(2, 0);
    struct position_t* empty_positions[MAX_X* MAX_Y];
    unsigned int num_empty_positions = 0;

    list_empty_positions(&board, empty_positions, &num_empty_positions);

    if (num_empty_positions == 0) {
        *message = "activate_building n'a pas trouvé de positions vides pour construire un bâtiment.";
        return false;
    }

    for (int i = 0; i< NUM_RESOURCES; ++i){
        board.players[0].resources[i] = 10;
    }
    struct position_t* pos = empty_positions[0];
    construct_building(&board, 0, 0, pos);

    activate_building(&board, 0, 0);

    if (get_building_id(&board, pos) != 0) {
        *message = "activate_building n'a pas activé le bâtiment correctement.";
        return false;
    }
    for (int i = 0; i< NUM_RESOURCES; ++i){
        if (board.players[0].resources[i] != 10){
            return true;
        }
    }

    *message = "activate_building n'a pas donné les ressources au joueur.";
    return false;
}

bool test_eliminate_player(char **message) {
    struct board_t board = init_board(2, 0);

    eliminate_player(&board, 0);

    if (!board.players[0].eliminated) {
        *message = "eliminate_player n'a pas éliminé le joueur correctement.";
        return false;
    }

    return true;
}

bool test_construct_building(char **message) {
    struct board_t board = init_board(2, 0);
    struct position_t* empty_positions[MAX_X * MAX_Y];
    unsigned int num_empty_positions = 0;

    list_empty_positions(&board, empty_positions, &num_empty_positions);

    if (num_empty_positions == 0) {
        *message = "construct_building n'a pas trouvé de positions vides pour construire un bâtiment.";
        return false;
    }

    struct position_t* pos = empty_positions[0];
    construct_building(&board, 0, 0, pos);

    if (get_building_id(&board, pos) != 0) {
        *message = "construct_building n'a pas construit le bâtiment correctement.";
        return false;
    }

    return true;
}


