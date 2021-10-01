/*
 * File:            main.c
 * Purpose:         Lab 1 : Fundamental C Concepts
 * Authors:         Hao Qi and Muntakim Rahman
 * Student Numbers: 50813344 and 71065221
 * CS Accounts:     d5j2b and y0f2b
 * Date:            September 09, 2019
 */

/* Preprocessor Directives */

#include <stdio.h>
#include <stdlib.h> // For Using the System Command Below.

/*
 * We try to avoid using numbers in code.  Programmers will often
 * call numbers in your code 'magic numbers'.  We avoid using magic
 * numbers  because it is easier to debug code that doesn't use them.
 * We do this by defining constants under your include preprocessor
 * directives. We define a constant like this:
 * #define CONSTANT_NAME value
 * This way you don't have to comb your way through your code
 * looking for 'magic numbers.'  You only have to change the values
 * of your constants, which you use in your code.  Note that 0, 1, and
 * 2 may be ok to use in your code and are not always considered magic
 * numbers.
 */
#define A_NUMBER 17
#define MAX 100

/*
 * Function Prototypes.  A Function Prototype Tells the Compiler
 *	a) Name of the Function you are Writing
 *	b) Type it Returns (Or Void, If It Returns Nothing)
 *	c) Type(s) of its Arguments (Or Void, If There Are None)
 */
void sieve(int list_of_numbers[], int length);

/*
 * Main Function Drives the Program.  Every C Program Must Have One and
 * Only One Main Function.
 * PRE:       NULL (no pre-conditions)
 * POST:      NULL (no side-effects)
 * RETURN:    IF program exits correctly
 *            THEN 0 ELSE 1
 */
int main(void) {
	/* Variables */

	int i = A_NUMBER;
	int j;
	int numbers[MAX];

	// Remember This?
	printf("The Address of the Variable i (in Decimal): %d\n", &i);
	printf("The Address of the Variable i (in Hex): %x\n", &i);
	printf("The Value Stored in the Variable i (In Decimal): %d\n", i);
	printf("The Value Stored in the Variable i (In Hex): %x\n", i);

	// Initializes all the Cells in the array of ints Called Numbers to 0.
	for (j = 0; j < MAX; ++j) {
		numbers[j] = 0;

		// This line is Commented Out. -> Mainly for Debugging Purposes.
		// printf("Cell Number %d Contains the Value %d\n", j, numbers[j]);
	}
	printf("\n");

	/* Function Call : Invokes the Sieve of Eratosthenes */
	sieve(numbers, MAX);

	// Prints Results
	printf("The primes numbers between 1 and %d are:\n", MAX);
	for (i = 2; i < MAX; ++i) {
		if (numbers[i] == 0) {
			printf("%d ", i);
		}
	}
	printf("\n"); // What Is This For?

	// And That's It
	system("pause");
	return 0;
}

/*
 * Sieve of Eratosthenes
 * PARAM:  array_of_zeros is an int array
 *         populated with zeros
 * PARAM:  length of the array
 * PRE:    length is the correct length of
 *         array_of_zeros
 * POST:   array_of_zeros contains 0s in cells
 *         whose indices are primes, and 1s
 *         elsewhere
 * RETURN: void (nothing)
 */
void sieve(int array_of_zeros[], int length) {
	/* Variables */
	int i = 0, j = 0;
	int row = 0, col = 0;

	array_of_zeros[0] = 1; // 0 is Not Prime
	array_of_zeros[1] = 1; // 1 is Not Prime

	// Finds Primes.  Note : 0 and 1 Aren't Primes.
	for (i = 2; i * i < length; ++i) {
		if (array_of_zeros[i] == 0) {
			// Not a Prime Number (Multiple of At Least 1, 2, and Itself)
			for (j = i + i; j < length; j += i) array_of_zeros[j] = 1;
		}
	}

	/* End of Function. */
	return;
}