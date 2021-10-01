/*
 * File:         tide_analyzer.c
 * Purpose:      Consumes a semi-formatted tide measurement file and
 * 				 determines if the corresponding tide is once- or
 * 				 twice-daily using a fast discrete Fourier transformation.
 * 				 The tide measurement file is a txt file whose name
 * 				 corresponds to the name defined in the preprocessor
 * 				 directive.  It is a series of NUMBER_OF_READINGS tidal
 * 				 readings (in mm) taken hourly.
 * Author:       Muntakim Rahman and Hao Qi
 * Student #s:   71065221 and 50813344
 * CS Accounts:  y0f2b and d5j2b
 * Date:         September 9th 2019
 */

/* Preprocessor Directives */
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
	FILE* file_pointer = NULL; /* A "pointer" to a file */
	double readings[NUMBER_OF_READINGS + FFT_ALGOR_BUFFER]; /* Copy the data file to this array */

	double complex_component[NUMBER_OF_READINGS + FFT_ALGOR_BUFFER]; /* Can be used for the complex results of fft */
	double omega[NUMBER_OF_READINGS]; /* Tidal frequencies */

	initialize_tidal_frequencies(omega, SAMPLING_FREQUENCY, NUMBER_OF_READINGS);

	/*
	 * Opens the file (a text file, not a binary file) for reading, and not writing,
	 * by invoking the fopen_s function with the correct parameters.
	 */
	fopen_s(&file_pointer, FILE_NAME, "r");

	/* Invokes the process file function, passing the data readings array and the file pointer. */
	process_file(readings, file_pointer);

	/*
	 * If the file pointer does not equal
	 * NULL THEN closes the pointer.
	 */
	if (file_pointer != NULL) fclose(file_pointer);

	/*
	 * Performs the Fourier transformation by passing the data readings, the complex result
	 * array, and two other parameters to the fft function. Since arrays are pass by reference
	 * and not pass by value, the function will be able to directly change the values in the
	 * cells.  Contrast this with the idea of pass by value, where we pass the value of a
	 * variable and if we change this value, the original variable remains unchanged.
	 */
	fft(FORWARD_TRANSFORM, EXPONENT, readings, complex_component);

	transform_readings(readings, complex_component, NUMBER_OF_READINGS);

	analyze_fft(readings, omega, RESULT_FILE_NAME, NUMBER_OF_READINGS);

	/* And that's it. */
	printf("Analysis Complete, result.txt Created.\n");

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
	 * Starts by initializing the elements in the tidal frequency array so that each omega[i] equals
	 * i * SAMPLING_FREQUENCY / NUMBER_OF_READINGS.  The sampling frequency that we have to use when
	 * analyzing the discrete Fourier transform *has* to be the one that was used to measure the signal.
	 * There is only one correct value (in this case it's hourly, so SAMPLING_FREQUENCY = 24). Otherwise
	 * it will give us the wrong frequencies. Remember we're mixing ints and doubles here, and we want
	 * the results to be doubles, so you need to do some casting.
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
	/* Variables */
	char line_buffer[LINESIZE];

	int values_per_line = 0;
	int extracted_integers[MAX_VALUES_PER_LINE];

	int readings_processed = 0;

	/* Copies the file, line by line, to line buffer using fgets in a while loop. */
	while (fgets(line_buffer, LINESIZE, pointer_to_data_file)) {
		/*
		 * Tries to extract MAX_VALUES_PER_LINE ints from the line buffer and assign
		 * them to local array cells using sscanf_s or equivalent.  Stores the return
		 * value in a local int.
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
		 * Copies the extracted integers to our data array.  Use a for loop for each
		 * of the values_per_line cells in the local array, and add the value
		 * stored in the cell to the end of the array we are populating with data value.
		 */
		for (int i = 0; i < values_per_line; i++) {
			array_to_populate[readings_processed] = extracted_integers[i];
			/*
			 * Keep track of what has been processed.  Increment the number of readings processed
			 * by the number of values successfully extracted from the line in the file.
			 */
			readings_processed++;
		}
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
	/* Variables */
	double calculation; /* Calculation of (readings[i]^2 + complex_component[i]^2)^(1/2). */

	/*
	* Since the Microsoft Visual Studio 2012 compiler doesn't support complex
	* numbers without some tweaking, let's square the real and the complex components,
	* add them, and take the square root.  Iterate through the elements of the readings
	* array and change each readings[i] to equal (readings[i]^2 + complex_component[i]^2)^(1/2).
	*/
	for (int i = 0; i < number_of_readings; i++) {
		calculation = sqrt(pow(readings[i],2) + pow(complex_components[i],2));

		readings[i] = calculation;
	}

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
	/* Variables */
	FILE* file_pointer = NULL;

	double frequency = 0.0; /* Tides occur with this frequency the most... */
	double amplitude = 0.0; /* ...and that frequency occured this many times. */

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
	/*
	 * You can use this for debugging, or (even better) you can set a breakpoint
	 * on this line, and look at the values of frequency and amplitude using
	 * the debugger.
	 */

	/* Creates (opens) a result file using fopen_s. */
	fopen_s(&file_pointer, fileName, "w");

	/* Writes the result to the file. */
	fprintf(file_pointer, "Puddlejump tidal frequency: %f per day", frequency);

	/* Closes the result file. */
	if (file_pointer != NULL) fclose(file_pointer);

	/* End of function. */
	return;
}