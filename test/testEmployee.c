#include <stdio.h>
#include <stdbool.h>
#include "employee.h"
#include <string.h>


bool test_employee_create(char **message) {
    const char name[14] = "David Renault";
    unsigned int cost[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++) {
        cost[i] = i + 1;
    }
    struct employee_t employee = employee_create(name, cost);

    if (strcmp(employee.name, name) != 0) {
        *message = "Le nom de l'employé n'a pas été correctement initialisé.";
        return false;
    }

    for (unsigned int i = 0; i < NUM_RESOURCES; i++) {
        if (employee.cost[i] != i + 1) {
            *message = "Le coût de l'employé n'a pas été correctement initialisé.";
            return false;
        }
    }

    return true;
}

