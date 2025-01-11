#include "employee.h"
#include "board.h"

struct employee_t employee_create(const char* name, const unsigned int cost[NUM_RESOURCES]) {

  struct employee_t employee;

  strncpy(employee.name, name, sizeof(employee.name) - 1);

  employee.name[sizeof(employee.name) - 1] = '\0';

    memcpy(employee.cost, cost, sizeof(employee.cost));
    employee.position = NULL;

  return employee;
}

void employee_print(const struct employee_t* e)
{
    printf("Employee %s\n", e->name);
    printf("Cost: ");
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        printf("%d ", e->cost[i]);
    }
    printf("\n");
}