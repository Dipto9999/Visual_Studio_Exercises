/*
 * File: lab2_inlab_exercises.h
 * Purpose: Exercises for lab 2
 * Author: Muntakim Rahman
 * Date: June 20th 2021
 */

/*
 * #pragma once is a non-standard but widely supported preprocessor
 * directive designed to cause the current source file to be included
 * only once in a single compilation. Thus, #pragma once serves the same
 * purpose as #include guards, but with several advantages, including:
 * a) writing less code
 * b) avoiding name clashes
 * c) improving (sometimes) compile speed.
 */
#pragma once

/* Preprocessor Directives */

#define FALSE 0
#define TRUE 1

#define ERROR -1

#define STRINGS_EQUAL 0

/* Function Prototypes */

void swap_ints(int* first_int, int* second_int );
void reverse_string(char* string );
int contains_sample(char* candidate, char* sample );
int generate_score(char* candidate, char* sample );
int find_index(char* candidate, char* sample );