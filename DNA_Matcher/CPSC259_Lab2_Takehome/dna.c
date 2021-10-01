/*
 * File: dna.c
 * Purpose: Consumes a Formatted DNA Sequence File
 *          to Determine Which of a Group of Candidate
 *          Sequences of Nucleotides Best Matches a
 *          Specified Sample.  The Formatted DNA
 *          Sequence File is a txt File (Threes Samples
 *          are Provided in the Resource Files Folder).
 * Author: Muntakim Rahman
 * Date: June 20th 2021
*/

#define _CRT_SECURE_NO_WARNINGS

#include "dna.h"

/*
 * Determines if the Specified Molecules (chars) are a Base Pair.
 * PARAM: a char
 * PARAM: a char
 * PRE: molecule is an alphanumeric ascii char.
 * RETURN: IF nucleotide_1 == nucleotide_2
 *			   THEN 1
 *         ELSE 0
 */
int is_base_pair(char nucleotide_1, char nucleotide_2) {
  switch (nucleotide_1) {
    case 'A': case 'a':
      if (nucleotide_2 == 'T' || nucleotide_2 == 't') return TRUE;
      break;
    case 'T': case 't':
      if (nucleotide_2 == 'A' || nucleotide_2 == 'a') return TRUE;
      break;
    case 'C': case 'c':
      if (nucleotide_2 == 'G' || nucleotide_2 == 'g') return TRUE;
      break;
    case 'G': case 'g':
      if (nucleotide_2 == 'C' || nucleotide_2 == 'c') return TRUE;
      break;
    default:
      return ERROR;
      break;
  }

  return FALSE;
}

/*
 * Acquires and Returns the Specified codon Code's Index From the
 * codon_codes 2D Array in the Header File.
 *
 * PARAM: pointer to a sequence of characters.
 * PRE: Valid pointer to a sequence of 3 characters.
 * RETURN: IF the specified codon_code is in the codon_codes 2D array in the header file
 *         THEN returns the index of the specified codon_code in the codon_codes 2D array
 *         ELSE -1
 */
int get_codon_index(char* codon_code) {
  for (int i = 0; i < NUMBER_OF_CODONS; ++i) {
    if (codon_codes[i][0] == codon_code[0]
      && codon_codes[i][1] == codon_code[1]
      && codon_codes[i][2] == codon_code[2])
      return i;
  }

  return ERROR;
}

/*
 * Extracts the DNA Segment Information Stored In a Correctly Formatted File.
 *
 * This Function Does Not Copy Newline Characters, But It Does Append a Terminating
 * null ('\0') Character to The End of Each DNA Segment Stored in the Heap.  This Lets Us
 * Use Functions From string.h (e.g. strncmp and strlen) to Process the DNA Segments.
 *
 * PARAM: pointer to a filestream to copy to main memory
 * PARAM: double pointer to the sample segment
 * PARAM: triple pointer to a collection of candidate segments
 * PRE: all the pointers are valid
 * POST: sample_segment now points to dynamically allocated memory that
 *       contains the sample DNA sequence extracted from the specified file
 * POST: candidate_segments now points to dynamically allocated memory that
 *       contains the candidate DNA sequences extracted from the specified file
 * RETURN: the number of candidate_segments extracted from the specified file
 */
int extract_dna(FILE* file_pointer, char** sample_segment, char*** candidate_segments) {
  /* Variables */
  int  return_value = 0;
  int  new_line = 0;
  int  line_length = 0;
  int  sequence_length = 0;
  int  number_of_candidates = 0;
  char character = ' ';
  char line_buffer[BUFSIZE];

  /* Moves To The Beginning of the File. */
  fseek(file_pointer, 0, SEEK_SET);

  /* Here's An Easy Way to Ignore the First Line (The Header)! */
  while ((character = fgetc(file_pointer)) != '\n') { ; }

  /* Acquires Sample Sequence (We Know It's In The Second Line). */
  while (new_line == 0 && fgets(line_buffer, BUFSIZE, file_pointer)) {
    /* Check If The Line Ends With a Newline Character and Increments the Sample Length. */
    if (line_buffer[strlen(line_buffer) - 1] == '\n') {
      new_line = 1;
      line_length = strlen(line_buffer) - 1;
    }
    else {
      new_line = 0;
      line_length = strlen(line_buffer);
    }

    /* Reallocates Some Space For The (Additional) Nucleotides. */
    *sample_segment = (char*)realloc(*sample_segment, sizeof(char) * (sequence_length + line_length));

    /* Copies the Contents of the Line Buffer to The End of The Dynamically Reallocated Memory. */
    for (int i = 0; i < line_length; ++i) *(*sample_segment + sequence_length + i) = line_buffer[i];
    sequence_length += line_length;
  }

  /* Adds Terminating null ('\0') Character To Sample, So We Can Treat It As a Null-Terminated String. */
  *sample_segment = (char*)realloc(*sample_segment, sizeof(char) * (sequence_length + 1));
  *(*sample_segment + sequence_length) = '\0';

  /* Acquires Number of Candidate Sequences (From the Third Line of the File). */
  fgets(line_buffer, BUFSIZE, file_pointer);
  return_value = sscanf_s(line_buffer, "%d", &number_of_candidates);

  /* Allocates Pointers for Correct Number of Candidate Sequences. */
  *candidate_segments = (char**)malloc(sizeof(char*) * number_of_candidates);
  for (int i = 0; i < number_of_candidates; ++i) *(*candidate_segments + i) = NULL; /* What Happens If We Omit This Line? */

  /* Copies Each Candidate Sequence, In Order, From the File to the Memory We Just Dynamically Allocated. */
  for (int i = 0; i < number_of_candidates; ++i) {
    sequence_length = 0; /* Resets the Variable. */
    new_line = 0; /* Resets the Variable. */

    /* Here's an Easy Way to Ignore Each Candidate Sequence's Header. */
    while ((character = fgetc(file_pointer)) != '\n') { ; }

    /* Acquires Candidate Sequence. */
    while (new_line == 0 && fgets(line_buffer, BUFSIZE, file_pointer)) {
      /* Check If the Line Ends With a Newline Character and Sets Length. */
      if (line_buffer[strlen(line_buffer) - 1] == '\n') {
        new_line = 1;
        line_length = strlen(line_buffer) - 1;
      }
      else {
        new_line = 0;
        line_length = strlen(line_buffer);
      }

      /* Reallocates Some Space For the Additional Nucleotides. */
      *(*candidate_segments + i) = (char*)realloc(*(*candidate_segments + i), sizeof(char) * (sequence_length + line_length));

      /* Copies the Contents Of the Line Buffer to The End of The Dynamically Reallocated Memory. */
      for (int j = 0; j < line_length; ++j) *(*(*candidate_segments + i) + sequence_length + j) = line_buffer[j];
      sequence_length += line_length;
    }

    /* Adds Terminating null ('\0') Character to Candidate, So We Can Treat It as a Null-Terminated String. */
    *(*candidate_segments + i) = (char*)realloc(*(*candidate_segments + i), sizeof(char) * (sequence_length + 1));
    *(*(*candidate_segments + i) + sequence_length) = '\0';

    new_line = 0;
  }

  return number_of_candidates;
}

/*
 * Analyzes the Segments. This is a Simple and Straight-Forward Algorithm Which Does
 * Not Include any Optimization, Except That it Returns Immediately if a Perfect Match is Found.
 *
 * This Function Must Do These Things (Though Not Necessarily In This Order):
 *
 * a) Check if any candidate segments are perfect matches, and if so, report
 *    all of the perfect matches (and do nothing else) using a message of this format:
 *    "Candidate number %d is a perfect match\n" where %d is the candidate
 *    segment's number in its sample file, then return from the function.
 * b) If no perfect matches are found, then find a best match using
 *    the scoring method described in the lab specification.
 * c) After a best match is found, the scores for ALL of the candidates that are best
 *    matches is printed out and formatted like this:
 *    ("Candidate number %d matched with a best score of %d\n") where %d is the
 *    candidate segment's number in its sample file.
 *
 * PARAM: pointer to the sample segment.
 * PARAM: pointer to the candidate segments.
 * PARAM: the number of candidate segments.
 * PRE: pointers are valid pointers to dynamically allocated and populated memory.
 * PRE: number_of_candidates correctly reports the number of candidate sequences.
 * POST: NULL
 * RETURN: VOID
 */
void analyze_segments(char* sample_segment, char** candidate_segments, int number_of_candidates) {
  /* Variables */
  char* current_candidate = *candidate_segments;

  int sample_length = 0;
  int candidate_length = 0;

  int perfect_matches = 0;

  int current_score = MINIMUM_SCORE;

  for (int i = 0; i < number_of_candidates; ++i) {
    current_candidate = *(candidate_segments + i);

    /* Calculate Length of The Segments. */
	  sample_length = strlen(sample_segment);
	  candidate_length = strlen(current_candidate);

    /* Check to See If Any Candidate Segment(s) Are a Perfect Match, and Report Them
     (REMEMBER: Don't Ignore trailing Nucleotides When Searching For a Perfect Score). */
	  if (strcmp(sample_segment, current_candidate) == STRINGS_EQUAL) {
		  printf("Candidate number %d is a perfect match\n", i + 1);
			perfect_matches++;
	  }
  }

  /* Return Early if We Have Found and Reported Perfect Match(es). */
  if (perfect_matches == 0) {
    /* Otherwise We Need to Calculate and Print All of the Scores by Invoking
       calculate_score For Each candidate_segment and Printing Each Result. */
    for (int i = 0; i < number_of_candidates; ++i) {
      current_candidate = *(candidate_segments + i);
      current_score = calculate_score(sample_segment, current_candidate);

      printf("Candidate number %d matched with a best score of %d\n", i + 1, current_score);
    }
  }

  /* End of Function. */
  return;
}

/*
 * Compares the Sample Segment and the Candidate Segment and Calculates a
 * Score Based on These Rules :
 *
 * 1. The score begins at 0.
 * 2. Let LENGTH be the number of codons in sample segment (which is always <= the candidate's length)
 * 3. Ignore any trailing nucleotides (there may be 1 or 2, but not more)
 * 4. For each of the LENGTH codons:
 *    a) if the two codons are exactly the same, add 10 to the score
 *    b) else if the 2 codons are different but specify the same amino acid, add 5 to the score
 *    c) else if the two codons are different and do not specify the same amino acid, then
 *       examine the 3 nucleotides in the codon separately:
 *		 For each of the 3 nucleotides:
 *		i)   If the two nucleotides are the same, add 2 to the score
 *      ii)  If the 2 nucleotides belong to a matching base pair (A and T, or C and G), add 1
 *      iii) Otherwise, add zero to the score (e.g., do nothing)
 * 5. Store the result
 * 6. Now skip the first codon in the candidate, e.g., shift the sample by 1 codon,
 *    and check the score of this new alignment.  Compare this score to the score
 *    you calculated before shifting, and store the higher score.  Keep shifting
 *    the sample deeper into the candidate by one codon at a time, checking the score, and
 *    storing ONLY the top score, until it no longer fits. Once the sample (ignoring the
 *    trailing nucleotides) extends beyond the length of the candidate we stop.
 * PARAM: pointer to the sample segment.
 * PARAM: pointer to the candidate segment.
 * PRE: pointers are valid pointers to dynamically allocated and populated memory.
 * POST: NULL
 * RETURN: int score representing the degree to which the two segments match.
 */
int calculate_score(char* sample_segment, char* candidate_segment) {
  /* Variables */
  int current_score = MINIMUM_SCORE;
  int max_score = current_score;

  int sample_length = strlen(sample_segment);
  int candidate_length = strlen(candidate_segment);

  /* Number of Shifts Required Given Codons in Sample and Candidate. */
  int sample_codons = sample_length / CODON_LENGTH;
  int candidate_codons = candidate_length / CODON_LENGTH;
  int number_of_comparisons = candidate_codons - sample_codons + MINIMUM_COMPARISONS;

  int shift_index;

  if (number_of_comparisons < MINIMUM_COMPARISONS) return ERROR;

  for (shift_index = 0; shift_index < number_of_comparisons; shift_index++) {
    current_score = calculate_shift_score(sample_segment, candidate_segment, sample_codons);
	  if (current_score > max_score) max_score = current_score;

    /* Shift Pointer To Address of Next Codon Onwards. */
    candidate_segment += CODON_LENGTH;
  }

  return max_score;
}

/*
 * Calculates a Score by Comparing the
 * Sample Segment and the Shifted Candidate Segment.
 *
 * PARAM: pointer to the sample segment.
 * PARAM: pointer to the effective candidate segment.
 * PARAM: number of codons in the sample segment.
 * PRE: pointers are valid pointers to dynamically allocated and populated memory.
 * PRE: sample_codons correctly reports the number of sample codons.
 * POST: NULL
 * RETURN: int score representing the degree to which the two segments match.
 */
int calculate_shift_score(char* sample_segment, char* effective_candidate_segment, int sample_codons) {
    /* Variables */
    int shift_score = MINIMUM_SCORE;

    /* Dynamically Allocate Memory for Codons. */
    char* current_sample_codon = (char*)malloc((CODON_LENGTH + 1) * sizeof(char));
    char* current_candidate_codon = (char*)malloc((CODON_LENGTH + 1) * sizeof(char));

    int codon_index;

	  // Note -> Codons of Candidate are a Reference.
	  for (codon_index = 0; codon_index < sample_codons; codon_index++) {
      /* Copy Current Codon to a String. */
	    strncpy(current_sample_codon, (sample_segment + (codon_index * CODON_LENGTH)), CODON_LENGTH);
	    strncpy(current_candidate_codon, (effective_candidate_segment + (codon_index * CODON_LENGTH)), CODON_LENGTH);

      shift_score += calculate_codon_score(current_sample_codon, current_candidate_codon);
	  }

    /* Free Dynamically Allocated Memory. */
    free(current_sample_codon);
    free(current_candidate_codon);

    return shift_score;
}

/*
 * Calculates a Score by Comparing the
 * Sample Codon and the Candidate Codon.
 *
 * PARAM: pointer to the sample codon.
 * PARAM: pointer to the effective candidate codon.
 * PRE: pointers are valid pointers to dynamically allocated and populated memory.
 * POST: NULL
 * RETURN: int score representing the degree to which the two codons match.
 */
int calculate_codon_score(char* sample_codon, char* candidate_codon) {
  /* Variables */
  int codon_score = MINIMUM_SCORE;

  /* Find Index of Each Codon in the codon_codes Array. */
  int sample_codon_index = get_codon_index(sample_codon);
  int candidate_codon_index = get_codon_index(candidate_codon);
  // Note -> Assume Both Codons Found in the Array.

  char sample_nucleotide;
  char candidate_nucleotide;

  int nucleotide_index;

  /* Check if Current Codons are Identical -> Add 10 Points. */
	if (sample_codon_index == candidate_codon_index) {
	  codon_score += CODON_PERFECT_SCORE;
	}
  /* Check if Current Codons Represent Same Amino Acid -> Add 5 Points. */
	else if (strcmp((codon_names + sample_codon_index), (codon_names + candidate_codon_index)) == STRINGS_EQUAL) {
		codon_score += CODON_AMINO_ACID_SCORE;
	}
	/* Check Each Nucleotide Within Both Codons. */
	else {
		for (nucleotide_index = 0; nucleotide_index < CODON_LENGTH; nucleotide_index++) {
      /* Shift Pointers to Codon for Each Nucleotide. */
      sample_nucleotide = *(sample_codon + nucleotide_index);
      candidate_nucleotide = *(candidate_codon + nucleotide_index);

      /* Check If Nucleotides Are the Same. */
			if (sample_nucleotide == candidate_nucleotide) codon_score += NUCLEOTIDE_IDENTICAL_SCORE;
      /* Check If Nucleotides Form a Base Pair. */
			else if (is_base_pair(sample_nucleotide, candidate_nucleotide)) codon_score += NUCLEOTIDE_BASE_PAIR_SCORE;
		}
	}

  return codon_score;
}