# Bourgade

## Table of Contents
1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [Usage](#usage)
4. [Contributors](#contributors)

## Introduction
This project is inspired by the board game [Little Town](https://iello.fr/jeux/little-town/). It allows for automated gameplay of an adapted version of the game.

## Project Structure
The project is organized as follows:
```
.
├── Makefile
├── project
├── README.md
├── .gitignore
├── compte-rendu/
│   ├── achievements.tex
│   ├── conclusion.tex
│   ├── config.tex
│   ├── glossaire.tex
│   ├── ...
├── src/
│   ├── board.c
│   ├── board.h
│   ├── ...
├── test/
│   ├── test.c
│   ├── testBoard.c
│   ├── testBoard.h
│   ├── ...
```
## Code Structure
The code is organized into several directories and files, each serving a specific purpose:

- **board.c**: Manages the game board, including initialization, player setup, building placement, and resource collection.
- **building.c**: Defines the structure and creation of buildings.
- **color.c**: Provides functions for handling color representations.
- **decision.c**: Contains logic for player decisions.
- **employee.c**: Manages employee creation, properties, and actions within the game.
- **game.c**: Controls the main game loop.
- **mine.c**: Implements functionalities related to mines.
- **position.c**: Handles position-related operations.
- **project.c**: Entry point of the project, handles command-line arguments and starts the game.
- **resource.c**: Manages resources.

## Usage
To compile and run the project, use the following commands:

1. **Build the project:**
   ```sh
   make
   ```

2. **Run the project:**
   ```sh
   ./project
   ```

3. **Run the tests:**
   ```sh
   make test
   ```

4. **Clean the project:**
    ```sh
    make clean
    ```

### Command Line Options
The project executable supports the following command line options:
- `-s rng_seed`: Set the random number generator seed.
- `-p num_players`: Set the number of players (maximum of 4).
- `-c position_seed`: Set the position seed.

Example:
```sh
./project -s 123 -p 4 -c 456
```

## Contributors
- **Mélissa Colin** - [Github](https://github.com/ddsmlf)
- **Benjamin Chew** - [Github](https://github.com/)
