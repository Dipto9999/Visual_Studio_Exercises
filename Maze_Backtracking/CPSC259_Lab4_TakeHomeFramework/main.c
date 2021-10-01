/*
 * File: main.c
 * Purpose: Driver for Maze Backtracking Algorithm.
 * Author: Muntakim Rahman
 * Date: September 9th 2021
 */

#define _CRT_SECURE_NO_WARNINGS

/* Include Header */
#include "mazesolver.h"

/*
 * Main Function Drives the Program.
 * PRE: None
 * POST: None
 * RETURN: TRUE IF the program runs as intended
 *          OTHERWISE FALSE
*/
int main(void) {
	FILE* maze_file = NULL;
  char file_names[NUMBER_MAZES][BUFFER] = {MAZE1, MAZE2, MAZE3, MAZE119, MAZE3877};

  int maze_index = FALSE;
  int error = FALSE;

  /* Opens and Parses the Test Files. */
  for (maze_index = 0; maze_index < NUMBER_MAZES; maze_index++) {
    /* Opens and Parses the Test File. */
  	maze_file = fopen(file_names[maze_index], "r" );
    if (maze_file == NULL) {
      fprintf(stderr, "Unable to Open File: %s\n", file_names[maze_index]);

      /* Ends Main Function. */
      system("pause");
      return FALSE;
    }
    else {
      process(maze_file);
    }
  }

  fclose(maze_file);

  /* Ends Main Function. */
  system("pause");
  return TRUE;
}