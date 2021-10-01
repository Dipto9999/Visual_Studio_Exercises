/*
 * File: mazesolver.c
 * Purpose: To Produce Solutions to a Maze Provided From a Text File and
 * 				  Analyze the Best Solutions in Terms of Cost and Distance.
 * Author: Muntakim Rahman
 * Date: September 9th 2021
 */

#define _CRT_SECURE_NO_WARNINGS

/* Include Header */
#include "mazesolver.h"

/*
 * Contains the Majority of the Maze Solver Logic.
 * PARAM: maze_file is a file pointer to a text file containing a maze.
 * PRE: maze file exists in the project.
 * POST: data about maze solutions printed to terminal.
 * RETURN: VOID
 */
void process(FILE* maze_file) {
  /* Local Variables */
  maze_cell** maze = NULL;

  int dimension = 0;

  char** paths = NULL;
  char best_path[BUFFER];

  int num_paths = 0;

  if (maze_file) {
    /* Get the Size of the Maze and Store it in the Dimension Variable. */
    dimension = get_dimension(maze_file);
    /* Copy the Maze into Memory. */
    maze = parse_maze(maze_file, dimension);
  }
  else {
    fprintf(stderr, "Unable to Parse Maze File: %s\n", maze_file);
    system("pause");
    return;
  }

  generate_paths(
    &paths, // Generated Paths
    &num_paths, // Number of Paths Found
    maze, // Maze
    dimension, // Dimension
    0, // Row
    0, // Column
    "" // Current Path
  );

  print_paths(paths, num_paths);

  printf(strcpy(best_path, find_shortest(paths, num_paths, "")));
  printf(strcpy(best_path, find_cheapest(paths, num_paths, "")));

  return TRUE;
}

/*
 * Acquires and Returns the Maze Size.
 *  Note: The Maze is Always a Square. We Only Need to
 *        Find the Length of the Top Row.
 * PARAM: maze_file is a pointer to a filestream
 * PRE: maze_file is an initialized pointer to a correctly-formatted maze file
 * POST: maze_file's internal pointer is set to beginning of stream
 * RETURN: length of the first line of text in the maze file EXCLUDING any EOL characters
 *         ('\n' or '\r') and EXCLUDING the string-terminating null ('\0') character.
 */
int get_dimension(FILE* maze_file)  {
  /* Local Variables */
  int dimension = 0;
  char line_buffer[BUFFER];

	dimension = strlen(fgets(line_buffer, BUFFER, maze_file));

	/* Reset the File's Internal Pointer
     to the Beginning of File. */
	fseek(
    maze_file, // File Pointer
    FALSE, // Number of Bytes to Offset From Origin
    SEEK_SET // Origin Set as Beginning of File
  );

  /*
   * Checks if Text File was Created in Windows and Contains '\r'.
	 *   IF TRUE reduce strlen by 2 in order to omit '\r' and '\n' from each line
	 *   ELSE reduce strlen by 1 in order to omit '\n' from each line.
   */
  if (strchr(line_buffer, '\r')) return (dimension - OMIT_WINDOWS);
  else return (dimension - OMIT_OTHER);
}

/*
 * Parses and Stores Maze as a 2D Array of maze_cell.  This Requires a Few Steps:
 * (1) Allocating Memory For a 2D Array of maze_cell (e.g. maze_cell[rows][columns]).
 *      (a) Dynamically Allocates Memory for 'dimension' Pointers to maze_cell, and Assign
 *	       the Memory (Case as a Double Pointer to maze_cell) to Maze, Which is a
 *         Double Pointer to maze_cell (Makes the maze[rows] Headers).
 * 	    (b) For Each Row of the Maze, Dynamically Allocate Memory for 'dimension' maze_cells
 * 	       and Assign It (Cast As a Pointer to maze_cell) to maze[row].
 * (2) Copying the File to the Allocated Space.
 *      (a) For Each Row Obtained From the File Using fgets and Temporarily Stored in line_buffer.
 * 	        (i) For Each of the 'dimension' Columns in That Row.
 * 	        (ii) Assign the char From the File to the struct, and Set the struct to Unvisited.
 * (3) Returns the Double Pointer Called maze.
 *************************************************************************************************
 * PARAM: maze_file pointer to an open filestream
 * PARAM: dimension is an int representing the size of the maze
 * PRE: maze_file is a pointer to a correctly-formatted maze file
 * PRE: dimension contains the correct size of the square maze
 * POST: maze contains a dynamically allocated copy of the maze stored in the maze_file
 * RETURN: maze, a maze_cell double pointer, which points to 'dimension' single pointers
 *         to maze_cell, each of which points to 'dimension' maze_cell structs.
 */
maze_cell** parse_maze(FILE* maze_file, int dimension) {
	/* Variables */
	maze_cell** maze = NULL;
  char line_buffer[BUFFER];

  int row = FALSE;
	int column = FALSE;

  /* Allocates Memory for Correctly-Sized Maze. */
  maze = (maze_cell**)calloc(dimension, sizeof(maze_cell*));
  for (row = 0; row < dimension; row++) maze[row] = (maze_cell*)calloc(dimension, sizeof(maze_cell));

	row = 0;
  /* Copies Maze File to Memory Line By Line */
  while (fgets(line_buffer, BUFFER, maze_file)) {
    for (column = 0; column < dimension; column++) {
        maze[row][column].character = line_buffer[column];
        maze[row][column].visited = UNVISITED;
	  }
    row++;
  }

	return maze;
}

/*
 * Generates All Paths Through a Maze Recursively.
 ********************************************************************************************
 * PARAM: pointer to a 2D array of all generated paths
 *        (pass the 2D array by reference - actual parameter to be modified by function)
 * PARAM: pointer to number of paths found
 *        (pass the integer by reference - actual parameter to be modified by function)
 * PARAM: pointer to a 2D array of maze_cell
 * PARAM: dimension of the square maze
 * PARAM: starting position row
 * PARAM: starting position column
 * PARAM: pointer to a string of chars which contains the 'current' path
 ********************************************************************************************
 * PRE: maze contains a representation of the maze
 * PRE: dimension contains the correct dimension of the maze
 * PRE: row contains a valid row coordinate
 * PRE: column contains a valid column coordinate
 * PRE: path contains a sequence of characters (the first time you invoke this
 *      function, the passed parameter should be an empty string, e.g., "" (not NULL)
 ********************************************************************************************
 * POST: IF current coordinate is not out of maze bounds &&
 *       current coordinate is not a wall
 *       THEN path contains current coordinate
 * POST: IF current coordinate is at maze finish line (right boundary)
 *       THEN paths contains the path from start to finish.
 * POST: dereferenced pathset contains all paths found
 * POST: dereferences numpaths contains the number of paths found
 * RETURN: VOID
 */
void generate_paths(char*** generated_paths, int* paths_found, maze_cell** maze,
  int dimension, int row, int column, char* current_path) {
  /* Variables */
	char* new_path = NULL;
	char* new_point = NULL;

	int path_length = FALSE;

  /* Base Cases. */
  if (row < 0 || row >= dimension) return; /* Row Boundaries */
  if (column < 0 || column >= dimension) return; /* Column Boundaries */
	if (maze[row][column].character == MAZE_WALL) return; /* Maze Wall */
  if (maze[row][column].visited == VISITED) return; /* Point Visited */

  /*
   * Otherwise Deal with the Recursive Case.
   * Pushes the Current Coordinate Onto the Path and Checks to
   * See If the Right Boundary of the Maze Has Been Reached.
	 * IF Right Boundary Reached
	 *   THEN Path is Added to the List as a Successful Path and Function Returns
	 *   ELSE The Current Location is Marked as Used and the Search Continues
	 *    In Each Cardinal Direction Using a Recursive Call Using These Steps :
	 *      1. Get Length of Path.
	 *      2. Allocate Space For a Larger New Path.
	 *      3. Allocate Space For a New Point to Add To The Path.
	 *      4. Assign the Value in the Maze Cell to the New Point.
	 *      5. Concatenate Old Path to New Path.
	 *      6. Concatenate New Point to New Path.
   */
	path_length = strlen(current_path);

  /* Dynamically Allocate Adequate Space for New Maze Cell in Path.
     Leave At Minimum One Extra Space at End. */
  new_path = (char*)calloc(++path_length, sizeof(char));
  new_point = (char*)calloc(2, sizeof(char));

  /* Get Value in Maze Cell. */
  *new_point = maze[row][column].character;

  /* Copy Old Path. */
  if (path_length) new_path = strcat(new_path, current_path);
  /* Add New Point to Path. */
  new_path = strcat(new_path, new_point);

  /* Deallocate Memory for New Point. */
  free(new_point);

  /* Solution is Found. */
  if (column == (dimension - 1)) {
    /*
     * 1. Reallocate Memory in Global paths Array to Make Room For a New Solution String.
     * 2. Copy the Solution Path to the Location of New String.
     * 3. Increment Paths Counter.
     */
	  *generated_paths = (char**)realloc(*generated_paths, ((*paths_found) + 1) * sizeof(char*));
    *((*generated_paths) + (*paths_found)) = (char*)calloc((strlen(new_path) + 1), sizeof(char));

    strcpy(*((*generated_paths) + (*paths_found)), new_path);
	  (*paths_found)++;
  }
  /* Searching for Solution. */
  else {
	  /*
     * 1. Mark Point As Visited.
	   * 2. Recursively Search in Each Direction Using the New Path.
	   * 3. Mark Point as Unvisited.
     */
	  maze[row][column].visited = VISITED;
    generate_paths(generated_paths, paths_found, maze, dimension, row + 1, column, new_path);
    generate_paths(generated_paths, paths_found, maze, dimension, row - 1, column, new_path);
    generate_paths(generated_paths, paths_found, maze, dimension, row, column + 1, new_path);
    generate_paths(generated_paths, paths_found, maze, dimension, row, column - 1, new_path);
    maze[row][column].visited = UNVISITED;
  }

  return;
}

/*
 * Calculates the Cost for a Given Path.
 *  Examples:
 *    "" -> 0
 *    "2" -> 2
 *    "871" -> 16
 * PARAM: path is a pointer to an array of char
 * PRE: path_string is a pointer to a null-terminated array of char (a string)
 *      where each char represents a positive decimal integer value.
 * RETURN: int representing the cost of the path.
 */
int path_cost(char* path) {
	if (*path == '\0') return FALSE;
	else return (int)(*path - '0') + path_cost(path + 1);
}

/*
 * Writes the Shortest Path in the paths Global Variable into a Buffer
 * In the Event of a Tie, Use the First 'Shortest' Path Found.
 * Uses Format: "Shortest Path : XXXXXXXX"
 * PARAM: paths is a 2D array containing all paths found
 * PARAM: num_paths is the number of paths in paths_found
 * PARAM: current_path is a character array of sufficient length with the current shortest path.
 * PRE: the shortest path has the fewest cells.
 * RETURN: information about the shortest path.
 */
char* find_shortest(char** paths, int num_paths, char* current_path) {
  /* Variables */
  char* shortest_path;

  /* Edge Case */
  if (num_paths == 0) return "No Path Found.";


  if (*current_path == '\0') {
      current_path = calloc(BUFFER, sizeof(char));
      strcpy(current_path, *paths);
  }

  /* Dynamically Allocate Adequate Space for Shortest Path. */
  shortest_path = (char*)calloc(BUFFER, sizeof(char));

  /* Copy Details of Shortest Path. */
  if (strlen(*paths) < strlen(current_path)) strcpy(shortest_path, *paths);
  else strcpy(shortest_path, current_path);

  /* Base Case */
  if (num_paths == 1) sprintf(current_path, "Shortest Path : %s\n", shortest_path);
  /* Recursive Case */
  else strcpy(current_path, find_shortest(paths + 1, num_paths - 1, shortest_path));

  /* Deallocate Memory for Shortest Path. */
  free(shortest_path);

  return current_path;
}


/*
 * Writes the Cheapest Path in the paths Global Variable into a Buffer
 * In the Event of a Tie, Use the First 'Cheapest' Path Found.
 * Uses Format:
 *  "Cheapest Path : XXXXXXXX
 *   Cheapest Path Cost : 9999"
 * PARAM: paths is a 2D array containing all paths found.
 * PARAM: num_paths is the number of paths in paths_found.
 * PARAM: output_buff is a character array of sufficient length.
 * PRE: the cheapest path has the lowest sum value of its cells.
 * POST: current_path is a character array of sufficient length with the current cheapest path.
 * RETURN: information about the cheapest path.
 */
char* find_cheapest(char** paths, int num_paths, char* current_path) {
  /* Variables */
  char* cheapest_path;

  int cost = FALSE;

  /* Edge Case */
  if (num_paths == 0) return "No Path Found.";

  if (*current_path == '\0') {
      current_path = calloc(BUFFER, sizeof(char));
      strcpy(current_path, *paths);
  }

  /* Dynamically Allocate Adequate Space for Cheapest Path. */
  cheapest_path = (char*)calloc(BUFFER, sizeof(char));

  /* Copy Details of Shortest Path. */
  if (path_cost(*paths) < path_cost(current_path)) strcpy(cheapest_path, *paths);
  else strcpy(cheapest_path, current_path);

  cost = path_cost(cheapest_path);

  /* Base Case */
  if (num_paths == 1) sprintf(
    current_path, // Destination Buffer
    "Cheapest Path : %s\nCheapest Path Cost : %d\n", // String Format
    cheapest_path, // Value for String Format Specifier
    cost // Value for Decimal Integer Format Specifier
  );
  /* Recursive Case */
  else strcpy(current_path, find_cheapest(paths + 1, num_paths - 1, cheapest_path));

  /* Deallocate Memory for Cheapest Path. */
  free(cheapest_path);

  return current_path;
}

/*
 * Prints All Paths to Standard Output.
 * Uses Format:
 *  "Cheapest Path : XXXXXXXX
 *   Cheapest Path Cost : 9999"
 * PARAM: paths is a 2D array containing all paths found.
 * PARAM: num_paths is the number of paths in paths_found.
 * PRE: paths is initialized with the solutions to the maze.
 * POST: paths printed to terminal
 * RETURN: VOID
 */
void print_paths(char** paths, int num_paths) {
  if (num_paths > 1) printf("\n****** %d Paths Generated*****\n", num_paths);
  else printf("\n****** %d Path Generated*****\n", num_paths);

  for (int path_index = 0; path_index < num_paths; path_index++) {
	  printf("\n");
	  printf(*(paths + path_index));
  }
  printf("\n\n********************\n");
}