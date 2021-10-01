/*
 * File: main.c
 * Purpose: Driver for Recursion Exercises
 * Author: Muntakim Rahman
 * Date: September 9th 2021
 */

/* Preprocessor Directives */
#include <stdio.h>
#include <stdlib.h>

#include "recursion.h"

#define BUFFERLENGTH 1024

void test_output(int draw_number);

/*
 * Main Function Drives the Program.
 * PRE: NULL (no pre-conditions)
 * POST: NULL (no side-effects)
 * RETURN: IF the program exits correctly
 *         THEN 0 ELSE 1
 */
int main(void) {
  printf("Testing Output From draw_ramp() Function:\n");

  for (int test_index = 1; test_index <= 5; test_index++) test_output(test_index);

  system("pause");
  return 0;
}


void test_output(int draw_number) {
  char output_buff[BUFFERLENGTH];

  // Initialize Output Buffer.
  for (int index = 0; index < BUFFERLENGTH; index++) output_buff[index] = '\0';
  draw_ramp(draw_number, output_buff);

	printf("_______draw_ramp(%d)_______\n\n", draw_number);
  printf("%s\n", output_buff);
}