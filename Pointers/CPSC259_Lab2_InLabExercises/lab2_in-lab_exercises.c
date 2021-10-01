/*
 * File: lab2_inlab_exercises.c
 * Purpose: Exercises for lab 2
 * Author: Muntakim Rahman
 * Date: June 20th 2021
 */

/********************/
/*** Header Files ***/
/********************/

#include <stdlib.h>
#include <string.h>

#include "lab2_in-lab_exercises.h"

/*
 * Swaps the Contents of Two Integer Variables Using Pointers.
 *
 * PARAM:     first_int is a pointer to an int
 * PARAM:     second_int is a pointer to an int
 * PRE:       both pointers are valid pointers to int
 * POST:      the contents of two integer variables are swapped
 * RETURN:    VOID
 */
void swap_ints(int* first_int, int* second_int) {
	int temp_int = *first_int;
	*first_int = *second_int;
	*second_int = temp_int;
}

/*
 * Reverses the Contents of the String Passed to the Function.
 * Does Not Move the Terminating Null '\0' Character.
 *
 * PARAM: string is a pointer to an array of char (a string)
 * PRE: the array of char terminates with a null '\0'
 * POST: the char array has been reversed
 * RETURN: VOID
 */
void reverse_string(char* string) {
	/* Variables */
	char* first_char = string;
	char* last_char = string + (strlen(string) - 1);

	char temp_char;

	while (last_char > first_char) {
		temp_char = *last_char;
		*last_char = *first_char;
		*first_char = temp_char;

		// Decrement and Increment the Pointers.
		last_char--;
		first_char++;
	}
}

/*
 * Determines if Candidate Contains Sample.
 *
 * PARAM: candidate is a pointer to an array of char (a string)
 * PARAM: sample is a pointer to an array of char (a string)
 * PRE: the arrays of char terminate with a null '\0'
 * PRE: candidate != NULL; sample != NULL
 * POST: N/A
 * RETURN: IF candidate contains sample THEN 1 ELSE 0.
 */
int contains_sample(char* candidate, char* sample) {
	char* result = strstr(candidate, sample);

	if (result == '\0' || (strlen(sample) > strlen(candidate))) return FALSE;
	else return TRUE;
}

/*
 * Returns the First Index Where Sample is Located Inside the
 * Candidate.  For Example:
 * IF candidate = "Hello", sample = "Hello", RETURNS 0
 * IF candidate = "soupspoon", sample = "spoon", RETURNS 4
 * IF candidate = "ACGTACGTA", sample = "CGT", RETURNS 1
 * IF candidate = "CGTACGTA", sample = "CGTT", RETURNS -1
 *
 * PARAM: candidate is a pointer to an array of char (a string)
 * PARAM: sample is a pointer to an array of char (a string)
 * PRE: the arrays of char terminate with a null '\0'
 * POST: N/A
 * RETURN: IF candidate contains sample THEN the index where the
 * 		   first letter of sample is inside candidate ELSE -1.
 */
int find_index(char* candidate, char* sample) {
	/* Variables */
	int length_candidate = strlen(candidate);
	int length_sample = strlen(sample);
	int i,j;

	if (contains_sample(candidate, sample) !=0) {
		// Check If Empty String.
		if (length_sample == 0) return 0;

		for (i = 0; i < length_candidate; i++) {
			// Iterate Through Sample String.
			j = 0;

			if (candidate[i] == sample[j]) {
				// Iterate Through Sample String While Characters Are the Same.
				while ((j < (length_sample - 1)) && candidate[i + j] == sample[j]) j++;

				// If at End of Sample String and Characters.
				if ((j == (length_sample - 1)) && (candidate[i + j] == sample[j])) return i;
			}
		}
	}
	else {
		return ERROR;
	}
}
