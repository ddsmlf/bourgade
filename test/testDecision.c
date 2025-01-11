#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "position.h"
#include "resource.h"
#include "employee.h"
#include "decision.h"

bool test_place_employee(char **message) {
    struct board_t board = init_board(2, 0);
    unsigned int player_id = 0;
    unsigned int free_employee_count = 0;
    unsigned int free_employees[MAX_WORKERS_PER_PLAYER];
    find_free_employees(&(board.players[player_id]), free_employees, &free_employee_count);

    struct employee_placement_t placement = place_employee(&board, player_id, free_employees, free_employee_count);

    if (placement.position == NULL || !is_valid_position(placement.position)) {
        *message = "place_employee a retourné une position invalide.";
        return false;
    }

    if (!is_position_free(&board, placement.position)) {
        *message = "place_employee a choisi une position occupée.";
        return false;
    }

    return true;
}

bool test_init_decision_data(char **message) {
    struct board_t board = init_board(2, 0);
    unsigned int player_id = 0;
    *message = "Réussi";
    init_decision_data(&board, player_id);

    return true;
}
