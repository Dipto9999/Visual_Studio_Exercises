/*
 * File:         tide_analyzer.h
 * Purpose:      Contains Prototypes
 * Author:       Muntakim Rahman
 * Date:         March 12th 2021
 */

#ifndef TIDE_ANALYZER_H
#define TIDE_ANALYZER_H

/* Preprocessor Directives */

#define NUMBER_OF_READINGS 131072 /* 131072 = 2^17 */
#define NOISE_FILTER 0.01   /* Used to Eliminate Noise from Observation. */
#define EXPONENT 17 /* Used for Call to FFT. */
#define LINESIZE 128 /* Maximum Line Length in Data File. */
#define SAMPLING_FREQUENCY  24 /* Number of Tidal Readings Taken Per Day. */
#define MIN_VALUES_PER_LINE 1 /* Min # of Integers on Each Line of Data File. */
#define MAX_VALUES_PER_LINE 5 /* Max # of Integers on Each Line of Data File. */

/*
* If you Experience This Error Upon
* Closing Your Program, Increase the Size
* of the Readings Array to
* NUMBER_OF_READINGS + FFT_ALGOR_BUFFER.
*/
#define FFT_ALGOR_BUFFER 4 /* Prevents Run Time Check Failure #2. */

#define FILE_NAME "puddlejump.txt"
#define RESULT_FILE_NAME "result.txt"

#define FORWARD_TRANSFORM 1

#define TRUE 1
#define FALSE 0
#define ERROR -1

/* Function Prototypes */

void initialize_tidal_frequencies(double omega[], int sampling_frequency, int number_of_readings);
void process_file(double array_to_populate[], FILE* pointer_to_data_file);
void transform_readings(double readings[], double complex_components[], int number_of_readings);
void analyze_fft(double transformed_readings[], double omega[], char* fileName, int number_of_readings);

#endif