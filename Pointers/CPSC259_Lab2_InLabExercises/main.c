/*
 * File: main.c
 * Purpose:	Driver for Lab 2 In-Lab.
 * Author: Muntakim Rahman
 * Date: June 20th 2021
 */

#include <stdlib.h>

#define SMALL_ARRAY 25

/*
 * Main Function Drives the Program.  Every C Program Must Have One
 * Main Function.  A Project Will Not Compile Without One.
 * PRE: NULL (no pre-conditions)
 * POST: NULL (no side-effects)
 * RETURN: IF the program exits correctly
 *	 	   THEN 0 ELSE 1
 */
int main(void) {
	/* Variables */
	int* pointer_to_some_ints = (int*)malloc(SMALL_ARRAY * sizeof(int));

	for (int i = 0; i < SMALL_ARRAY; ++i) *(pointer_to_some_ints + i) = i;

	/* The System Command Forces the System to Pause Before Closing Executable Window. */
	system("pause");
	return 0;
}