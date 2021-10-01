/*
 * File:         tide_analyzer.h
 * Purpose:      Contains Prototypes
 * Author:       Muntakim Rahman and Hao Qi
 * Student #s:   71065221 and 50813344
 * CS Accounts:  y0f2b and d5j2b
 * Date:         September 9th 2019
 */

#ifndef TIDE_ANALYZER_H
#define TIDE_ANALYZER_H

/* Preprocessor Directives */

#define NUMBER_OF_READINGS 131072 /* This = 2^17 (hint!). */
#define NOISE_FILTER 0.01   /* Used to eliminate noise from observation. */
#define EXPONENT 17 /* Can be used for call to fft. */
#define LINESIZE 128 /* Maximum line length in data file. */
#define SAMPLING_FREQUENCY  24 /* Number of tidal readings taken per day. */
#define MIN_VALUES_PER_LINE 1 /* Min # of integers on each line of data file. */
#define MAX_VALUES_PER_LINE 5 /* Max # of integers on each line of data file. */

/*
* If you experience this error upon
* closing your program, increase the size
* of the readings array to
* NUMBER_OF_READINGS + FFT_ALGOR_BUFFER.
*/
#define FFT_ALGOR_BUFFER 4 /* Prevents Run Time Check Failure #2. */

#define FILE_NAME "puddlejump.txt"
#define RESULT_FILE_NAME "result.txt"

#define FORWARD_TRANSFORM 1

#define TRUE 1
#define FALSE 0
#define ERROR -1

#pragma once

/* Function Prototypes */

void initialize_tidal_frequencies(double omega[], int sampling_frequency, int number_of_readings);
void process_file(double array_to_populate[], FILE* pointer_to_data_file);
void transform_readings(double readings[], double complex_components[], int number_of_readings);
void analyze_fft(double transformed_readings[], double omega[], char* fileName, int number_of_readings);

#endif