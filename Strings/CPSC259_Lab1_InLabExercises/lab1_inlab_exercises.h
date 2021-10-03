/*
 * File:         lab1_inlab_exercises.h
 * Purpose:      Contains Prototypes of Functions
 * Author:       Muntakim Rahman
 * Date:         March 12th 2021
 */

/* Preprocessor Directives */
#define TRUE 1
#define FALSE 0
#define ERROR -1

/* Function Prototypes.  A Function Prototype Tells the Compiler
	a) Name of the Function you are Writing
	b) Type it Returns (Or Void, If It Returns Nothing)
	c) Type(s) of its Arguments (Or Void, If There Are None) */

void reverse_array(int array[], int length);
int length(const char string[]);
int count_letters(const char string[], char letter);
int is_palindrome(const char string[]);