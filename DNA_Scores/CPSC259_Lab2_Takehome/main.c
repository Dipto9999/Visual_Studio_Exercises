/*
 * File: main.c
 * Purpose: Interactive driver for CPSC 259 Lab2 Takehome
 * Author: Muntakim Rahman and Hao Qi
 * Date: June 20th 2021
 */

#define _CRT_SECURE_NO_WARNINGS

#include "dna.h"

/*
 * Main Function Drives the Program.
 * PRE: NULL (no pre-conditions)
 * POST: NULL (no side-effects)
 * RETURN: IF the program exits correctly
 *         THEN 0 ELSE 1
 */
int main(void) {
  /* Variables */
  char* sample_segment = NULL;
  char** candidate_segments = NULL;

  char main_menu_choices[NUMBER_OF_MENU_ITEMS][MAX_MENU_ITEM_SIZE] = {
    "1. Load file",
    "2. Perform analysis",
    "3. Exit"
  };

  int number_of_candidates = 0;
  int menu_choice = 0;
  int number_of_main_menu_choices = NUMBER_OF_MENU_ITEMS;

  /* Generates Menu and Responds to User Input. */
  do {
    /* Prints the Menu and Asks the User to Make a Choice. */
    menu_choice = get_menu_choice(PROGRAM_NAME, main_menu_choices, number_of_main_menu_choices);

    switch (menu_choice) {
      /* If the User Chooses 1, We Need To Load a File. */
      case 1:
        /* First Clear Any Existing Memory, Then Ask the User to Enter the File Name,
          and Then Try to Load It. */
        clear_memory(&sample_segment, &candidate_segments, &number_of_candidates);
        number_of_candidates = load_file(&sample_segment, &candidate_segments);
        break;

      /* If the User Chooses 2, We Want to Process the File. */
      case 2:
        /* But Only If a File Has Been Already Loaded! */
        if (sample_segment != NULL) analyze_segments(sample_segment, candidate_segments, number_of_candidates);
        break;

      /* If the User Chooses 3, We Want to Free Dynamically Allocated Memory, and End the Program. */
      case 3:
        clear_memory(&sample_segment, &candidate_segments, &number_of_candidates);
        end_program(0);
        break;

      /* We Have To Have a Default Choice In a Switch Statement. */
      default:
        break;
    }
  } while (TRUE);

  end_program(0);
}

/*
 * Displays a Menu, Asks the User to Choose a Menu Item, and Returns
 * a Valid Menu Choice.
 *
 * Using fgets and sscanf_s ensures that we only accept correct
 * user input: an integer representing one of the numbered
 * menu items, that is neither preceded nor proceeded by any
 * additional input except for white space.
 *
 * PARAM: pointer to a null-terminated string representing the menu name
 * PARAM: array of strings (menu choices)
 * PARAM: number of menu choices
 * PRE: NULL (no pre-conditions)
 * POST: NULL (no side-effects)
 * RETURN: int representing valid menu choice
 */
int get_menu_choice(char* menu_name, char menu_choices[][MAX_MENU_ITEM_SIZE], int number_of_choices) {
  /* Variables */
  char line[BUFSIZE];
  char extra[BUFSIZE];

  int i, menu_item;

  do {
    // Print Menu Options.
    printf("%s\n", menu_name);
    for (i = 0; i < number_of_choices; ++i) printf("%s\n", menu_choices[i]);
    printf("> ");

    /* If user enters EOF which is Control-C in Windows, then fgets returns a null pointer which is
       interpreted as 0.  The user probably wants to quit the program, so we clear the error in
       standard input and return the final menu item (quit, #3). */
    if (!(fgets(line, BUFSIZE, stdin))) {
      clearerr(stdin);
      return number_of_choices;
    }

  } while
    ((sscanf_s(line, "%d%s", &menu_item, extra, BUFSIZE) != 1)
    || (menu_item < 0) || (menu_item > number_of_choices));
  /* Disallows Incorrect Menu Choices by Accepting [0, #ofchoices] and Ignoring Other Input. */

  return menu_item;
}

/*
 * Clears Any Dynamically Allocated Memory and Resets the Candidate Count.
 *
 * PARAM: double pointer to the sample segment.
 * PARAM: triple pointer to the candidate segments.
 * PARAM: pointer to the int that stores the number of candidate segments.
 * PRE: pointers are valid pointers to dynamically allocated and populated memory.
 * POST: memory has been deallocated, number of candidates reset to 0.
 * RETURN: VOID
 */
void clear_memory(char** sample_segment, char*** candidate_segments, int* number_of_candidates) {
  int i = 0;

  if (*sample_segment != NULL) {
    free(*sample_segment);
    *sample_segment = NULL;
  }

  if (*candidate_segments != NULL) {
    for (i = 0; i < *number_of_candidates; ++i) free(*(*candidate_segments + i)); /* Freeing Triple Pointers Can Be Tricky! */
    free(*candidate_segments);
    *candidate_segments = NULL;

    *number_of_candidates = 0; /* Reset The Candidate Counter! */
  }
}

/*
 * Copies the Specified File into Main Memory and Returns the Number of Candidate
 * Segments Found.
 *
 * PARAM: double pointer to the sample segment.
 * PARAM: triple pointer to a collection of candidate segments.
 * PRE: file with the user-specified name exists in the Resource Files folder.
 * POST: file has been copied to main memory.
 * RETURN: number of candidate sequences in specified file.
 */
int load_file(char** sample_segment, char*** candidate_segments) {
  /* Variables */
  char   file_name[BUFSIZE];
  FILE* fp = NULL;
  int    i = 0;
  int    error = FALSE;
  int    number_of_candidates = 0;

  /* Acquires File Name From User. */
  get_user_input("\nEnter file name: ", file_name);

  printf("Loading file %s\n", file_name);

  /* Opens File. */
  error = fopen_s(&fp, file_name, "r");

  /* If the Return Value Specifies That the File Cannot Be Opened,
     Prints a Suitable Message to Standard Output and Returns 0. */
  if (error != FALSE) {
    fprintf(stderr, "File %s cannot be loaded\n", file_name);
    return 0;
  }

  /* Extracts Contents of the File, and Determines Number of Candidate Segments. */
  number_of_candidates = extract_dna(fp, sample_segment, candidate_segments);

  /* Closes the File and Returns Number of Candidates Extracted From The DNA. */
  fclose(fp);

  return number_of_candidates;
}

/*
 * Displays Specified Message and Asks the User for a Response.
 *
 * PARAM: pointer to a null-terminated string representing the message.
 * PARAM: pointer to a buffer where the response will be stored.
 * PRE: response buffer is BUFSIZE characters in size.
 * POST: response buffer contains the user response.
 * RETURN: VOID
 */
void get_user_input(char* message, char* response) {
  char line[BUFSIZE];

  do {
    printf("%s", message);

    /* If user enters EOF which is Control-C in Windows
       then fgets returns a null pointer which is
       interpreted as 0.  We clear the error in
       standard input and end program. */
    if (!(fgets(line, BUFSIZE, stdin))) {
      clearerr(stdin);
      printf("Error acquiring user input\n");
      end_program(1);
    }
  } while (sscanf_s(line, "%s", response, BUFSIZE) != 1);

  return;
}

/*
 * Ends the Program.  Forces the System to Pause First.
 * PARAM: exit value
 * PRE: NULL (no pre-conditions)
 * POST: execution has ended
 * RETURN: VOID
 */
void end_program(int exit_value) {
  system("pause");
  exit(exit_value);
}