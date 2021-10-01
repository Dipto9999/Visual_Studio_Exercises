/*
 * File: pivot.c
 * Purpose: Count Number of Possible Pivots After
 * 			An Iteration of QuickSort.
 * Author: Muntakim Rahman
 * Date: September 13th 2021
 */

/*********************/
/* Include Libraries */
/*********************/

#include <stdio.h>
#include <stdlib.h>

#include "pivot.h"

/*
 * Main Function Drives the Program.
 * PRE: NULL (No Pre-Conditions)
 * POST: NULL (No Side-Effects)
 * RETURN: IF the program exits correctly
 *         	THEN TRUE ELSE FALSE
 */

int main(void){
	system("pause");
	return TRUE;
}

/*
 * Print an Array of Integers.
 * Then, Count All Possible Pivot Elements in the Array from
 * the Prior Iteration of QuickSort.
 *************************************************************
 * PARAM: array - an array of integers to be displayed.
 * PARAM: size - the number of actual elements in the array (size >= 1).
 * POST: check each element of the list to see if it could have
 * 		 been a pivot in an iteration of quicksort partition
 * RETURN: number of possible pivots
*/
int count_pivots(int* array, int size) {
	/* Variables */
	int pivot_status = TRUE;
	int pivot_count = 0;

	int pivot_index = 0;
	int comparison_index = 0;

	while (pivot_index < size) {
		comparison_index = 0;
		pivot_status = TRUE;

		/* Check if Array Elements Prior to Pivot are Smaller Than Pivot. */
		while (pivot_status && comparison_index < pivot_index) pivot_status = (*(array + comparison_index++) <= *(array + pivot_index));

		/* Check if Array Elements Following Pivot are Greater Than or Equal to Pivot. */
		while (pivot_status && comparison_index < size) pivot_status = (*(array + comparison_index++) >= *(array + pivot_index));

		/* Increment Pivot Count if the Array Element is a Possible Pivot Element. */
		if (pivot_status) pivot_count++;

		pivot_index++;
	}

  	return pivot_count;
}