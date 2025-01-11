#include <stdio.h>
#include <stdbool.h>
#include "resource.h"

bool test_resource_add(char **message) {
    unsigned int r1[NUM_RESOURCES] = {1, 2, 3, 4, 5, 6};
    unsigned int r2[NUM_RESOURCES] = {6, 5, 4, 3, 2, 1};
    unsigned int result[NUM_RESOURCES] = {0};

    resource_add(r1, r2, result);
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (result[i] != r1[i] + r2[i]) {
            *message = "resource_add n'a pas effectué correctement l'addition.";
            return false;
        }
    }
    return true;
}

bool test_resource_sub(char **message) {
    unsigned int r1[NUM_RESOURCES] = {1, 2, 3, 4, 5, 6};
    unsigned int r2[NUM_RESOURCES] = {6, 5, 4, 3, 2, 1};
    unsigned int result[NUM_RESOURCES] = {0};

    resource_add(r1, r2, result);
    resource_sub(result, r1, result);
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (result[i] != r2[i]) {
            *message = "resource_sub n'a pas effectué correctement la soustraction.";
            return false;
        }
    }
    return true;
}

bool test_resource_le_than(char **message) {
    unsigned int r1[NUM_RESOURCES] = {1, 2, 3, 4, 5, 6};
    unsigned int r2[NUM_RESOURCES] = {6, 5, 4, 3, 2, 1};

    if (resource_le_than(r2, r1)) {
        *message = "resource_le_than à retourner que  {6, 5, 4, 3, 2, 1} était plus petit que {1, 2, 3, 4, 5, 6}.";
        return false;
    }
    unsigned int r3[NUM_RESOURCES] = {0, 0, 0, 0, 0, 0};
    if (!resource_le_than(r3, r1)) {
        *message = "resource_le_than à retourner que {0, 0, 0, 0, 0, 0} est plus grand que {1, 2, 3, 4, 5, 6}.";
        return false;
    }

    return true;
}
