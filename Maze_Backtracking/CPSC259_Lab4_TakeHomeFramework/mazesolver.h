/*
 * File: mazesolver.h
 * Purpose: Contains Constants, Prototypes, Globals
 * Author: Muntakim Rahman
 * Date: September 9th 2021
 */

#pragma once

/*******************/
/* Include Headers */
/*******************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/***************************/
/* Preprocessor Directives */
/***************************/

#define NUMBER_MAZES 5
#define MAZE1 "maze1.txt"
#define MAZE2 "maze2.txt"
#define MAZE3 "maze3.txt"
#define MAZE119 "maze119.txt"
#define MAZE3877 "maze3877.txt"

#define MAZE_WALL '*'
#define VISITED 'Y'
#define UNVISITED 'N'
#define MAZE_CELL_MEMBERS 2

#define BUFFER 128

#define OMIT_WINDOWS 2
#define OMIT_OTHER 1

#define TRUE 1
#define FALSE 0
#define ERROR -1

/* Structure Used as the Cell for the Maze Representation. */
typedef struct maze_cell {
  char character;
  char visited;
} maze_cell;

/***********************/
/* Function Prototypes */
/***********************/

/* Maze Paths */
void process(FILE* maze_file);

maze_cell** parse_maze(FILE* maze_file, int dimension);
int get_dimension(FILE* maze_file);

void generate_paths(char*** generated_paths, int* paths_found, maze_cell** maze,
  int dimension, int row, int column, char* current_path);

/* Path Processing */
int path_cost(char* path);

char* find_shortest(char** paths, int num_paths, char* output_buff);
char* find_cheapest (char** paths, int num_paths, char* output_buff);

/* Debugging */
void print_paths(char** paths, int num_paths);
