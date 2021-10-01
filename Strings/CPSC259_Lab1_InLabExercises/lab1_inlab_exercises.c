/*
 * File:         lab1_inlab_exercises.c
 * Purpose:      Exercises for Lab 1
 * Author:       Muntakim Rahman
 * Date:         September 9th 2021
 */

/* Preprocessor Directives */
#include <stdlib.h> // For System Command

#include "lab1_inlab_exercises.h"

/*
 * Try to avoid using numbers in code.  Programmers will often call
 * numbers in your code 'magic numbers'.  We avoid using magic numbers
 * because it is easier to debug code that doesn't use them.
 * Define and use a constant like this instead: #define CONSTANT_NAME value
 */
#define SOME_CONSTANT 10

/*
 * Main Function Drives the Program. Every C Program Must Have One and
 * Only One Main Function.
 * PRE:    NULL (no pre-conditions)
 * POST:	 NULL (no side-effects)
 * RETURN: IF the program exits correctly
 * THEN 0 ELSE 1
 */
int main(void) {
  /* Start every function with a list of variables. Then start doing things,
   like invoking functions and assigning their return values to variables. */

  // System Command Forces the System to Pause Before Closing Executable Window.
  system("pause");

  return 0;
}

/*
 * Reverses the Order of an Array of Integers.
 * For Example,
 * { 1, 2, 3, 4 } -> {4, 3, 2, 1 }
 * { 1, 2, 3 } -> { 3, 2, 1 }
 * {1} -> {1}
 * {} -> {}
 * PARAM:  array, an array of integers
 * PARAM:  length, the number of elements in array
 * PRE:    array is an array of integers
 * PRE:    length is the correct length of the array
 * POST:   the elements in array have been reversed in order
 * RETURN: N/A
 */
void reverse_array(int array[], int length) {
	/* Variables */
	int original_index, switch_index;
	int temp_var;

	for (original_index = 0; original_index < length/2; original_index++) {
		switch_index = (length - 1) - original_index;

		// Use a Temp Variable.
		temp_var = array[switch_index];
		array[switch_index] = array[original_index];
		array[original_index] = temp_var;
	}
}

/*
 * Returns the Length of the Specified C String (Array of
 * Characters that Ends With the Null Character '\0')
 * PARAM:  string is a standard C array of characters that terminates
 * 		   with the null character '\0'
 * PRE:    string is a null-terminated array of characters
 * POST:   NULL (no side-effects)
 * RETURN: number of char (excluding the terminating null) in string
 */
int length(const char string[]) {
	int index = 0;

	while (string[index] != '\0') index++;

	return index;
}

/*
 * Returns the Number of Occurrences of the Specified
 * Char in the Specified Char Array (String).
 * PARAM:  string is a standard C array of characters that terminates
 * 		   with the null character '\0'
 * PARAM:  letter, a char
 * PRE:    string is a null-terminated array of characters
 * POST:   NULL (no side-effects)
 * RETURN: number of occurences of letter_sought in string
 */
int count_letters(const char string[], char letter) {
	/* Variables */
	int index;
	int occurences = 0;
	int str_length = length(string);

	for (index = 0; index < str_length; index++) {
		if (string[index] == letter) occurences++;
  	}
  	return occurences;
}

/*
 * Determines if a String is a Palindrome. Skips Spaces.
 * For Example,
 * 	""     -> Returns 1 (Empty String is a Palindrome)
 * 	"the"  -> Returns 0
 * 	"abba" -> Returns 1
 * 	"Abba" -> Returns 0
 * 	"Never Odd or Even" -> Returns 1 ("neveroddoreven" Reversed is the Same)
 * PARAM:  string is a standard C array of characters that terminates
 * 		   with the null character '\0'
 * PRE:    string is a null-terminated array of characters
 * POST:   no side-effects (e.g., nothing is printed or changed)
 * RETURN: IF string is a palindrome THEN 1
 * 		   ELSE IF string is not a palindrome THEN 0
*/
int is_palindrome(const char string[]) {
	/* Variables */
	int i, j;
	int str_length = length(string);

	for (i = 0, j = str_length - 1; i < j; i++, j--) {
		// Skip Space From Left.
		while (string[i] == ' ') i++;

		// Skip Space From Right.
		while (string[j] == ' ') j--;

		// Check if Letters Are the Same or that End of String Not Reached.
		if (string[i] != string[j] && string[i] != '\0') return FALSE;
	}

	// Otherwise String is Palindrome.
	return TRUE;
}