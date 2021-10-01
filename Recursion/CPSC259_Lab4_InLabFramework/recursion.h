/*
 * File: recursion.h
 * Purpose: Prototypes for Recursion Exercises
 * Author: Muntakim Rahman
 * Date: September 9th 2021
 */

#pragma once

/* Function Prototypes */

int count_digits(int number);
int string_length(char* string);
int is_palindrome(char* string, int string_length);

double calculate_power(int base, int power);

int draw_ramp(int number, char* buffer);
int draw_row(int size, char* buffer);

/* Preprocessor Directives */

#define FALSE 0
#define TRUE 1

#define STRINGS_EQUAL 0
