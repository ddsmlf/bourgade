CC = gcc
SRC_DIR = ./src
TEST_DIR = ./test
CFLAGS = -Wall -Wextra -std=c99 -g3 -I$(SRC_DIR) -I$(TEST_DIR)
BOURGADE_FLAGS = -DMAX_X=$(MAX_X) -DMAX_Y=$(MAX_Y) -DNUM_RESOURCES=$(NUM_RESOURCES)
LDFLAGS = $(BOURGADE_FLAGS)

# Paramètres configurables
MAX_X ?= 4
MAX_Y ?= 4
NUM_RESOURCES ?= 6

# Fichiers
SRCS := $(filter-out $(SRC_DIR)/project.c, $(wildcard $(SRC_DIR)/*.c)) 
OBJS := $(SRCS:.c=.o)
TEST_SRCS := $(filter-out $(SRC_DIR)/test.c, $(wildcard $(TEST_DIR)/*.c)) 
TEST_OBJS := $(TEST_SRCS:.c=.o)
TEST_EXECS := $(TEST_DIR)/test_exec

# Règles principales
.PHONY: all clean test

all: project

project: $(OBJS) $(SRC_DIR)/project.o
	$(CC) $(CFLAGS) $^ -o $@

# Compilation des fichiers objets sources
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Création de l'exécutable de test
$(TEST_DIR)/test_exec: $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Règle pour exécuter les tests
test: $(TEST_DIR)/test_exec
	@chmod +x $(TEST_DIR)/test_exec
	@$(TEST_DIR)/test_exec || exit 1

# Nettoyage
clean:
	@rm -f project $(OBJS) $(SRC_DIR)/project.o $(TEST_OBJS) $(TEST_EXECS)
	@rm -f ./*.o
	@rm -f $(SRC_DIR)/*.o
	@rm -f $(TEST_DIR)/*.o
	@find $(TEST_DIR) -maxdepth 1 -type f -executable -delete
