/*
 * File: main.c
 * Purpose: To Print All the Prime Numbers Between 1 and 100.
 * Author: Muntakim Rahman
 * Date: March 12th 2021
 */

/* Preprocessor Directives */

#include <stdio.h>
#include <stdlib.h>

#define A_NUMBER 17
#define MAX 100

/* Function Prototypes. */

void sieve(int list_of_numbers[], int length);

/*
 * Main Function Drives the Program.
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
	for (j = 0; j < MAX; ++j) numbers[j] = 0;
	fprintf(stdout, "\n");

	/* Function Call : Invokes the Sieve of Eratosthenes */
	sieve(numbers, MAX);

	// Prints Results
	fprintf(stdout, "The Primes Numbers Between 1 and %d Are:\n", MAX);
	for (i = 2; i < MAX; ++i) {
		if (numbers[i] == 0) printf("%d ", i);
	}
	printf("\n");

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
 * RETURN: VOID (nothing)
 */
void sieve(int array_of_zeros[], int length) {
	/* Variables */
	int i = 0, j = 0;
	int row = 0, col = 0;

	array_of_zeros[0] = 1; // 0 is Not Prime
	array_of_zeros[1] = 1; // 1 is Not Prime

	// Finds Prime Numbers (Note: 0 and 1 Are Not Prime)
	for (i = 2; i * i < length; ++i) {
		if (array_of_zeros[i] == 0) {
			// Not a Prime Number (Multiple of At Least 1, 2, and Itself)
			for (j = i + i; j < length; j += i) array_of_zeros[j] = 1;
		}
	}

	/* End of Function. */
	return;
}