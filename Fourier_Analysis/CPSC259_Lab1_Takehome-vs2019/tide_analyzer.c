/*
 * File:         tide_analyzer.c
 * Purpose:      Consumes a Semi-Formatted Tide Measurement File and
 * 				 Determines if the Corresponding Tide is Once- or
 * 				 Twice-Daily Using a Fast Discrete Fourier Transformation.
 * 				 The Tide Measurement File is a Text File Whose Name
 * 				 Corresponds to the Name Defined in the Preprocessor
 * 				 Directive.  It is a Series of NUMBER_OF_READINGS Tidal
 * 				 Readings (in mm) Taken Hourly.
 * Author:       Muntakim Rahman
 * Date:         March 12th 2021
 */

/* Include Headers */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tide_analyzer.h"
#include "discrete_fourier_transform.h"

/*
 * Main Function Drives the Program.
 * PRE:       NULL (no pre-conditions)
 * POST:      NULL (no side-effects)
 * RETURN:    IF the program exits correctly THEN 0 ELSE 1
 */
int main(void) {
	/* Variables */
	FILE* file_pointer = NULL;

	double readings[NUMBER_OF_READINGS + FFT_ALGOR_BUFFER]; /* Data File Contents. */
	double complex_component[NUMBER_OF_READINGS + FFT_ALGOR_BUFFER]; /* Complex Results of FFT. */
	double omega[NUMBER_OF_READINGS]; /* Tidal frequencies */

	initialize_tidal_frequencies(omega, SAMPLING_FREQUENCY, NUMBER_OF_READINGS);

	/*
	 * Opens the File (a Text File, not a Binary File) for Reading, and Not Writing,
	 * By Invoking the fopen_s Function With The Correct Parameters.
	 */
	fopen_s(&file_pointer, FILE_NAME, "r");

	/* Invokes the Process File Function, Passing the Data Readings Array and the File Pointer. */
	process_file(readings, file_pointer);

	/*
	 * If the File Pointer Does Not Equal
	 * NULL THEN Closes the Pointer.
	 */
	if (file_pointer != NULL) fclose(file_pointer);

	/*
	 * Performs the Fourier Transformation By Passing the Data Readings, the Complex Result
	 * Array, and Two Other Parameters to the fft Function. Since Arrays are Passed by Reference
	 * and Not Passed By Value, the Function Will Be Able to Directly Change the Values in the
	 * Cells.
	 */
	fft(FORWARD_TRANSFORM, EXPONENT, readings, complex_component);

	transform_readings(readings, complex_component, NUMBER_OF_READINGS);

	analyze_fft(readings, omega, RESULT_FILE_NAME, NUMBER_OF_READINGS);

	fprintf(stdout, "\nAnalysis Complete...\nresult.txt Created.\n");

	system("pause");
	return TRUE;
}

/*
 * Initialize the Tidal Frequencies.
 * PARAM:     omega is an array which is at least large enough
 *            to contain the data in the specified file
 * PARAM:     sampling_frequency is a positive integer which
 * 			  represents the frequency at which the tidal measurements are collected.
 * PARAM:     number_of_readings is a positive integer which
 * 			  represents the number of tidal measurements in each sample.
 * PRE:       NULL (no pre-conditions)
 * POST:      The tidal frequency calculations have been copied to the
 *            specified array.
 * RETURN:    VOID
 */
void initialize_tidal_frequencies(double omega[], int sampling_frequency, int number_of_readings) {
	/*
	 * Starts by Initializing the Elements in the Tidal Frequency Array So that Each omega[i] Equals
	 * i * SAMPLING_FREQUENCY / NUMBER_OF_READINGS.  The Sampling Frequency That We Have to Use When
	 * Analyzing the Discrete Fourier Transform must Be the One that Was Used to Measure the Signal.
	 * There is Only One Correct Value (i.e. SAMPLING_FREQUENCY = 24). Otherwise
	 * It Will Give Us the Wrong Frequencies.
	 */
	for (int i = 0; i < number_of_readings; i++) omega[i] = i * ((double)sampling_frequency) / number_of_readings;
}

/*
 * Processes the Data File.
 * PARAM:     array_to_populate is an array which is at least large enough
 *            to contain the data in the specified file.
 * PARAM:     pointer_to_data_file is a valid and open file pointer.
 * PRE:       The file pointer is a reference to an open file.
 * PRE:       The file is a text file which contains between 1 and
 *            5 real integers per line.
 * POST:      The contents of the file have been copied to the
 *            specified array.
 * RETURN:    VOID
*/
void process_file(double array_to_populate[], FILE* pointer_to_data_file) {
	/* Local Variables */
	char line_buffer[LINESIZE];

	int values_per_line = 0;
	int readings_processed = 0;

	int extracted_integers[MAX_VALUES_PER_LINE];

	/* Copies the File, Line By Line, to Line Buffer Using fgets In a While Loop. */
	while (fgets(line_buffer, LINESIZE, pointer_to_data_file)) {
		/*
		 * Tries to Extract MAX_VALUES_PER_LINE ints From the Line Buffer and Assign
		 * Them to Local Array Cells Using sscanf_s or Equivalent. Stores the Return
		 * Value In a Local int.
		 */
		values_per_line = sscanf_s(
			line_buffer, // Output Buffer
			"%d %d %d %d %d", // String Format
			&extracted_integers[0], // Extracted Value
			&extracted_integers[1], // Extracted Value
			&extracted_integers[2], // Extracted Value
			&extracted_integers[3], // Extracted Value
			&extracted_integers[4] // Extracted Value
		);

		/*
		 * Copies The Extracted Integers to Our Data Array. Use a For Loop For Each
		 * Of the values_per_line Cells in the Local Array, and Add the Value
		 * Stored In the Cell to the End Of The Array We Are Populating With Data Value.
		 */
		for (int i = 0; i < values_per_line; i++) array_to_populate[readings_processed++] = extracted_integers[i];
	}

	/* End of Function. */
	return;
}

/*
 * Transform the Readings to Avoid Dealing With Complex Numbers.
 * PARAM:     readings is an array of doubles which contains the
 *            real component of the forward fourier transform.
 * PARAM:     complex_components is an array of doubles which contains the
 *  		  complex component of the forward fourier transform.
 * PARAM:     number_of_readings is a positive integer
 * 			  which represents the size of the arrays.
 * PRE:       readings and complex_components are initialized with the appropriate values.
 * POST:      The contents of the readings array are changed to the calculation for each element.
 * RETURN:    VOID
*/
void transform_readings(double readings[], double complex_components[], int number_of_readings) {
	/*
	* Let's Square the Real and the Complex Components,
	* Add Them, and Take the Square Root. Iterate Through the Elements of the Readings
	* Array and Change Each readings[i] to Equal (readings[i]^2 + complex_component[i]^2)^(1/2).
	*/
	for (int i = 0; i < number_of_readings; i++) readings[i] = sqrt(pow(readings[i],2) + pow(complex_components[i],2));

	/* End of function. */
	return;
}

/*
 * Analyze the Forward Fourier Transform and Write Analysis to a Text File.
 * PARAM:     transformed_readings is an array of doubles which contains the
 *			  amplitude of the forward fourier transform.
 * PARAM:     omega is an array of doubles which contains the tidal frequencies.
 * PARAM:     fileName is a char array which is the name of the text file to write to.
 * PRE:       transformed_readings and omega are initialized with the appropriate values.
 * PRE:       The maximum tidal frequency is written to the text file.
 * RETURN:    VOID
*/
void analyze_fft(double transformed_readings[], double omega[], char* fileName, int number_of_readings) {
	/* Local Variables */

	FILE* file_pointer = NULL;

	double frequency = 0.0; /* Most Common Tidal Frequency. */
	double amplitude = 0.0; /* Number of Times Tidal Frequency Occurs. */

	/*
	 * Searches through the results for the tidal frequency with the greatest amplitude.
	 * We needn't examine every value stored in the transformed readings array.  It is enough
	 * to look through the first NUMBER_OF_READINGS / 2.  Why?  The discrete Fourier transform does not accurately
	 * represent the Fourier coefficients for values of omega large than NUMBER_OF_READINGS / 2
	 * (it actually gives you the same as the first half, but in reverse
	 * order), and that is why they shouldn't be considered.
	 **********************************************************************************************
	 * So for each of the first NUMBER_OF_READINGS / 2 readings, make sure that the value in the
	 * frequency array omega is >= NOISE_FILTER.  If the frequency array value is greater than this
	 * minimum bound, then check if the value in the readings array is greater than any other so far.
	 * If it is, store both the frequency and the amplitude.
	 */
	for (int i = 0; i < number_of_readings / 2; i++) {
		if (omega[i] >= NOISE_FILTER && transformed_readings[i] > amplitude) {
			frequency = omega[i];
			amplitude = transformed_readings[i];
		}
	}

	printf("Max Frequency = %f\n", frequency);
	printf("Max Amplitude = %f\n", amplitude);

	/* Creates a Text File For the Result. */
	fopen_s(&file_pointer, fileName, "w");

	/* Writes the Result to the Text File. */
	fprintf(file_pointer, "Puddlejump Tidal Frequency: %f Per Day", frequency);

	/* Closes the Text File for the Result. */
	if (file_pointer != NULL) fclose(file_pointer);

	/* End of Function. */
	return;
}