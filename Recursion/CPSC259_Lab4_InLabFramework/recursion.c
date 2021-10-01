/*
 * File: recursion.c
 * Purpose: Recursion Exercises
 * Author: Muntakim Rahman
 * Date: September 9th 2021
 */

/* Include Header */
#include "recursion.h"

/*
 * Calculates the Power.
 * PARAM: base is an integer
 * PARAM: power is an integer
 * PRE: base != 0
 * RETURN: base^power
 */
double calculate_power(int base, int power) {
	/* Base Case (i.e. x^0 = 1) */
	if (power == 0) return 1;
	/* Recursive Case for Positive Power (i.e. x^a = x * x^(a-1)) */
	else if (power > 0) return base * calculate_power(base, power - 1);
	/* Recursive Case for Negative Power (i.e. x^a = 1 / (x * x^(a-1))) */
	else if (power < 0) return 1 / (double)calculate_power(base, abs(power)) ;
}

/*
 * Returns the number of digits in an integer
 * PARAM: number is an integer
 * PRE: 0 < number <= INT_MAX
 * RETURN: number of digits in the number
 */
int count_digits(int number) {
	/* Base Case (Single Digit Integer) */
	if (number/10 == 0) return 1;
	/* Recursive Case (Multiple Digit Integer) */
	else return 1 + count_digits(number/10);
}

/*
 * Returns the Length of the Specified String.
 * PARAM: string, a pointer to an array of char.
 * PRE: string pointer is not a dangling pointer.
 * RETURN: length of the string passed as a parameter.
 */
int string_length(char* string) {
	/* Base Case ('\0' Character) */
	if (*string == '\0') return 0;
	/* Recursive Case (Increment Pointer) */
	else return 1 + string_length(string + 1);
}

/*
 * Determines If a String Is a Palindrome.  Does Not Skip Spaces.
 * For Example :
 * 		""     -> returns 1 (Empty String Is a Palindrome)
 * 		"the"  -> returns 0
 * 		"abba" -> returns 1
 * 		"Abba" -> returns 0
 * 		"never odd or even" -> returns 0
 * PARAM: string, a pointer to an array of char
 * PARAM: string_length, the length of the string
 * PRE: string pointer is not a dangling pointer
 * PRE: string_length is the correct length of the string
 * RETURN: IF string is a palindrome
 *         THEN 1 ELSE 0
 */
int is_palindrome(char* string, int string_length) {
	/* Variables */
	char* start_address = string;
	char* end_address = string + (string_length - 1);

	char left_character = *start_address;
	char right_character = *end_address;

	// Return False as Soon as Characters Don't Match.
	if (left_character != right_character) return FALSE;

	/* Base Case (Compare Characters At Center) */
	if ((end_address - start_address) <= 1) return TRUE;
	/* Recursive Case (Shift Pointers Inwards) */
	else return is_palindrome(start_address + 1, string_length - 2);
}

/*
 * Draws a Ramp. The Length of The Longest Rows is Specified By The Parameter.
 * For the Recursive Call, Be Aware That Both Parameters Can Be Modified.
 * PARAM: number, an integer
 * PARAM: buffer, a character array of sufficient length.
 * PRE: number >= 0
 *      buffer has sufficient length and contains null characters from the buffer
 *      address to the end of its length.
 * POST: draws a ramp whose height is the specified number into buffer
 * RETURN: the number of characters written into buffer.
 *         Don't forget to count your newline characters!
 */
int draw_ramp(int number, char* buffer) {
	int count = draw_row(number, buffer);

	/* Base Case (Single Star Row) */
	if (number == 1) {
		return count;
	}
	/* Recursive Case (Surrounds Inner Row With number Stars on Top and Bottom) */
	else {
		*(buffer + count) = '\n';
		count++;

		count += draw_ramp(number - 1, buffer + count);

		*(buffer + count) = '\n';
		count++;

		count += draw_row(number, buffer + count);

		return count;
	}
}

/*
 * Draws a Row of Asterisks Of The Specified Length.
 * For the Recursive Call, Be Aware That Both Parameters Can Be Modified.
 * PARAM: size, an integer
 * PARAM: buffer, a character array of sufficient length.
 * PRE: size >= 0
 *      buffer has sufficient length and contains null characters from the buffer
 *      address to the end of its length.
 * POST: draws a row of asterisks of specified length to buffer.
 * RETURN: number of characters drawn.
 */
int draw_row(int size, char* buffer) {
	*buffer = '*';

	/* Base Case (Return 1) */
	if (size == 1) return 1;
	/* Recursive Case (Return Sum of 1 and Size - 1) */
	else return 1 + draw_row(size - 1, buffer + 1);
}