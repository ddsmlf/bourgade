#ifndef DECISION_H
#define DECISION_H

#include "mine.h"
#include <limits.h>


/**
 * @struct candidate_t
 * @brief Represents a candidate for optimal employee placement.
 * 
 * @var candidate_t::resources
 * Array of resources associated with the candidate.
 * @var candidate_t::positions
 * Array of positions associated with the candidate.
 */
struct candidate_t {
    unsigned int resources[NUM_RESOURCES];
    struct position_t* positions[MAX_WORKERS_PER_PLAYER];
};

/**
 * @struct decision_data_t
 * @brief Stores decision data for optimal employee placement.
 * 
 * @var decision_data_t::optimal_positions_head
 * Head index for optimal positions.
 * @var decision_data_t::optimal_positions_tail
 * Tail index for optimal positions.
 * @var decision_data_t::optimal_positions
 * Array of optimal positions for employee placement.
 */
struct decision_data_t {
    unsigned int optimal_positions_head;
    unsigned int optimal_positions_tail;
    struct position_t* optimal_positions[MAX_WORKERS_PER_PLAYER];
};

/**
 * @brief Determines if the player wishes to build a building.
 * 
 * @param board Pointer to the game board.
 * @param player_id ID of the player.
 * @return true if the player wishes to build, false otherwise.
 */
bool wishes_to_build(const struct board_t* board, unsigned int player_id);

/**
 * @brief Selects a building for the player to build.
 * 
 * @param board Pointer to the game board.
 * @param player_id ID of the player.
 * @param buildings Array of available buildings.
 * @param num_buildings Number of available buildings.
 * @return Index of the selected building.
 */
unsigned int select_building(const struct board_t* board, unsigned int player_id, unsigned int* buildings, unsigned int num_buildings);

/**
 * @brief Determines if the player wishes to activate a building.
 * 
 * @param board Pointer to the game board.
 * @param player_id ID of the player.
 * @param building_id ID of the building.
 * @return true if the player wishes to activate the building, false otherwise.
 */
bool wishes_to_activate(const struct board_t* board, unsigned int player_id, unsigned int building_id);

/**
 * @brief Initializes decison data for the player.
 * 
 * @param board Pointer to the game board.
 * @param player_id ID of the player.
 */
void init_decision_data(const struct board_t *board, unsigned int player_id);

/**
 * @brief Places an employee on the board.
 * 
 * @param board Pointer to the game board.
 * @param player_id ID of the player.
 * @param free_employees Array of free employees.
 * @param free_employee_count Number of free employees.
 * @return Struct containing the employee placement information.
 */
struct employee_placement_t place_employee(const struct board_t *board, unsigned int player_id, unsigned int *free_employees, unsigned int free_employee_count);

#endif // DECISION_H