#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdbool.h>
#include "employee.h"
#include "building.h"
#include "color.h"
#include "decision.h"

// Constants
#define MAX_PLAYERS 4
#define MAX_BUILDINGS_PER_PLAYER 10
#define MAX_MINE ((MAX_POSITIONS/4) < 4 ? 4 : (MAX_POSITIONS/4))
#define MAX_BUILDING (MAX_MINE+MAX_AVAILABLE_BUILDING)
#define MAX_EMPLOYEE 10
#define IND(x,y) (MAX_X*y + x)

struct building_t;
// Structures
struct player_t {
    enum color_t color;
    unsigned int resources[NUM_RESOURCES];
    struct employee_t employees[MAX_WORKERS_PER_PLAYER];
    unsigned int num_employees;
    bool eliminated;
};

struct board_t {
    struct player_t players[MAX_PLAYERS];
    struct building_t building[MAX_BUILDING];
    unsigned int num_players;
    unsigned int num_building;
    unsigned int seed;
};

// Function Prototypes

/**
 * @brief Initializes the game board.
 *
 * This function initializes the game board with the specified number of players and seed.
 * It sets up the initial positions, buildings, and players.
 *
 * @param num_players The number of players in the game.
 * @param seed_t The seed value for random type of game board generation.
 * @return A struct board_t representing the initialized game board.
 */
struct board_t init_board(unsigned int num_players, unsigned int seed_t);

/**
 * @brief Finds an empty position on the game board.
 *
 * This function searches for an empty position on the game board and returns it.
 *
 * @param board A pointer to the game board.
 * @return A pointer to the empty position found, or an invalid position if none are found.
 */
struct position_t* find_empty_position(const struct board_t* board);

/**
 * @brief Lists all empty positions on the game board.
 *
 * This function lists all empty positions on the game board and stores them in the provided array.
 *
 * @param board A pointer to the game board.
 * @param empty_positions An array to store the empty positions.
 * @param num_empty_positions A pointer to store the number of empty positions found.
 */
void list_empty_positions(const struct board_t* board, struct position_t** empty_positions, unsigned int* num_empty_positions);

/**
 * @brief Checks if a position is free on the game board.
 *
 * This function checks if a given position is free (not occupied by any player or building) on the game board.
 *
 * @param board A pointer to the game board.
 * @param pos A pointer to the position to check.
 * @return True if the position is free, false otherwise.
 */
bool is_position_free(const struct board_t* board, const struct position_t* pos);

/**
 * @brief Lists all affordable buildings for a player.
 *
 * This function lists all buildings that a player can afford to construct based on their resources.
 *
 * @param board A pointer to the game board.
 * @param player_id The ID of the player.
 * @param affordable_buildings An array to store the IDs of affordable buildings.
 * @param num_affordable A pointer to store the number of affordable buildings found.
 */
void list_affordable_buildings(struct board_t* board, unsigned int player_id, unsigned int* affordable_buildings, unsigned int* num_affordable);

/**
 * @brief Collects resources for a player.
 *
 * This function collects resources for a player from the specified position and its neighbors.
 *
 * @param board A pointer to the game board.
 * @param player_id The ID of the player.
 * @param pos A pointer to the position to collect resources from.
 */
void collect_resources(struct board_t* board, unsigned int player_id, const struct position_t* pos);

/**
 * @brief Tests the possible resource collection for a position.
 *
 * This function tests resource collection for a given position and stores the acquired resources in the provided array.
 *
 * @param board A pointer to the game board.
 * @param pos A pointer to the position to test resource collection from.
 * @param acquired_resources An array to store the acquired resources.
 */
void collect_resources_test(const struct board_t* board, const struct position_t* pos, unsigned int acquired_resources[NUM_RESOURCES]);

/**
 * @brief Resets the employees for all players.
 *
 * This function resets the employees for all players on the game board.
 *
 * @param board A pointer to the game board.
 */
void reset_employees(struct board_t* board);

/**
 * @brief Finds free employees for a player.
 *
 * This function finds all free (unassigned) employees for a player and stores their IDs in the provided array.
 *
 * @param player A pointer to the player.
 * @param free_employees An array to store the IDs of free employees.
 * @param num_free A pointer to store the number of free employees found.
 */
void find_free_employees(const struct player_t* player, unsigned int* free_employees, unsigned int* num_free);

/**
 * @brief Gets the building ID at a position.
 *
 * This function gets the ID of the building at a given position on the game board.
 *
 * @param board A pointer to the game board.
 * @param pos A pointer to the position to check.
 * @return The ID of the building at the position, or -1 if no building is found.
 */
int get_building_id(const struct board_t* board, const struct position_t* pos);

/**
 * @brief Pays employees for all players.
 *
 * This function pays the employees for all players on the game board. If a player cannot pay their employees, they are eliminated.
 *
 * @param board A pointer to the game board.
 */
void pay_employees(struct board_t* board);

/**
 * @brief Counts the number of active players.
 *
 * This function counts the number of active (not eliminated) players on the game board.
 *
 * @param board A pointer to the game board.
 * @return The number of active players.
 */
unsigned int count_players(struct board_t* board);

/**
 * @brief Activates a building for a player.
 *
 * This function activates a building for a player, transferring resources as needed.
 *
 * @param board A pointer to the game board.
 * @param player_id The ID of the player.
 * @param building_id The ID of the building to activate.
 */
void activate_building(struct board_t* board, unsigned int player_id, unsigned int building_id);

/**
 * @brief Eliminates a player.
 *
 * This function eliminates a player from the game, setting their resources to zero.
 *
 * @param board A pointer to the game board.
 * @param player_id The ID of the player to eliminate.
 */
void eliminate_player(struct board_t* board, unsigned int player_id);

/**
 * @brief Constructs a building for a player.
 *
 * This function constructs a building for a player at the specified position.
 *
 * @param board A pointer to the game board.
 * @param player_id The ID of the player.
 * @param building_id The ID of the building to construct.
 * @param position A pointer to the position to construct the building at.
 */
void construct_building(struct board_t* board, unsigned int player_id, unsigned int building_id, struct position_t* position);

/**
 * @brief Checks if a position has valid neighbors.
 *
 * This function checks if a given position has valid neighbors of neightbors on the game board. (for the mine placement)
 *
 * @param p A pointer to the position to check.
 * @return 1 if the position has valid neighbors, 0 otherwise.
 */
unsigned int has_valid_neighbors(const struct position_t* p);


#endif // __BOARD_H__
