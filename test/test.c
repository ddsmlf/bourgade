#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "testBoard.h"
#include "testPosition.h"
#include "testResource.h"
#include "testBuilding.h"
#include "testEmployee.h"
#include "testMine.h"
#include "testDecision.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"


typedef struct {
    bool (*test_function)(char **message);
    const char *test_name;
} test_t;

void run_test(test_t test) {
    char *message = "Réussi";
    bool result = test.test_function(&message);

    if (result) {
        printf(GREEN "✔ %s : %s\n" RESET, test.test_name, message);
    } else {
        printf(RED "✘ %s : %s\n" RESET, test.test_name, message);
    }
}

void run_group(char* group_name, test_t* tests, int num_tests) {
    printf("\n\n%s\n", group_name);
    for (int i = 0; i < num_tests; i++) {
        run_test(tests[i]);
    }
}

int main() {
    char* groupe_name[] = {
        "\n\nPosition.c",
        "Resources.c",
        "Building.c",
        "Employee.c",
        "Mine.c",
        "Board.c",
        "Decision.c"
    };



    test_t tests_position[] = {
        {test_make_position, "Création de position"},
        {test_is_valid_position, "Validité de position"},
        {test_list_neighbors, "Liste des voisins"},
    };

    test_t tests_resources[] = {
        {test_resource_add, "Addition de ressources"},
        {test_resource_sub, "Soustraction de ressources"},
        {test_resource_le_than, "Comparaison de ressources"}
    };

    test_t tests_building[] = {
        {test_make_building, "Création de bâtiment"},
        {test_available_building, "Bâtiments disponibles"}
    };

    test_t tests_employee[] = {
        {test_employee_create, "Création d'employé"}
    };

    test_t tests_mine[] = {
        {test_make_mine, "Création de mine"},
        {test_get_random_mine_type, "Type de mine aléatoire"},
        {test_place_mines, "Placement des mines"},
        {test_is_mine_here, "Mine sur la position"}
    };

    test_t tests_board[] = {
        {test_init_board, "Initialisation du plateau"},
        {test_is_position_free, "Position libre"},
        {test_list_empty_positions, "Liste des positions libres"},
        {test_list_affordable_buildings, "Liste des bâtiments abordables"},
        {test_collect_resources, "Collecte des ressources"},
        {test_collect_resources_test, "Collecte des ressources (test)"},
        {test_find_free_employees, "Employés libres"},
        {test_get_building_id, "Récupération de l'ID du batiment sur une position"},
        {test_pay_employees, "Paiement des employés"},
        {test_count_players, "Compter les joueurs encore en lice"},
        {test_activate_building, "Activation des buildings"},
        {test_eliminate_player, "Elimination de joueurs"},
        {test_construct_building, "Construction d'un batiment"}
    };

    test_t tests_decision[] = {
        {test_place_employee, "Placement d'employé"},
        {test_init_decision_data, "Initialisation des données de décision"}
    };

    
    test_t* tests_group[] = {
        tests_position,
        tests_resources,
        tests_building,
        tests_employee,
        tests_mine,
        tests_board,
        tests_decision
    };

    for (long unsigned int i = 0; i < sizeof(tests_group) / sizeof(tests_group[0]); i++) {
        int num_tests;
        if (i == 0) {
            num_tests = sizeof(tests_position) / sizeof(tests_position[0]);
        } else if (i == 1) {
            num_tests = sizeof(tests_resources) / sizeof(tests_resources[0]);
        } else if (i == 2) {
            num_tests = sizeof(tests_building) / sizeof(tests_building[0]);
        } else if (i == 3) {
            num_tests = sizeof(tests_employee) / sizeof(tests_employee[0]);
        } else if (i == 5) {
            num_tests = sizeof(tests_board) / sizeof(tests_board[0]);
        }
        else if (i == 4) {
            num_tests = sizeof(tests_mine) / sizeof(tests_mine[0]);
        }
        else if (i == 6) {
            num_tests = sizeof(tests_decision) / sizeof(tests_decision[0]);
        }
        run_group(groupe_name[i], tests_group[i], num_tests);
    }


    return 0;
}
