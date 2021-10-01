/*
 * File:         lab1_inlab_exercises.h
 * Purpose:      Contains Prototypes of Functions
 * Author:       Muntakim Rahman and Hao Qi
 * Student #s:   71065221 and 50813344
 * CS Accounts:  y0f2b and d5j2b
 * Date:         September 9th 2019
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