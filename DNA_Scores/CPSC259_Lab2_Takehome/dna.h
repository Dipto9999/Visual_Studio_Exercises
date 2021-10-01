/*
 * File: dna.h
 * Purpose: Contains Constants, Prototypes, and Two
 *          Helpful Arrays.
 * Author: Muntakim Rahman
 * Date: June 20th 2021
 */

#pragma once

/* Include Headers */

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>

#include <time.h>

/* Preprocessor Directives */
#define FALSE 0
#define TRUE 1

#define ERROR -1

#define STRINGS_EQUAL 0

#define PROGRAM_NAME  "DNA Matcher 1.0"
#define MAX_MENU_ITEM_SIZE  32
#define NUMBER_OF_MENU_ITEMS 3
#define FIRST_MENU_ITEM      1
#define LAST_MENU_ITEM       3
#define BUFSIZE            512
#define LINESIZE           512
#define ASCII_OFFSET        48
#define CODON_SYMBOL_LENGTH  4
#define CODON_LENGTH         3
#define CODON_NAME_LENGTH   14
#define NUMBER_OF_CODONS    64

#define MINIMUM_SCORE 0
#define MINIMUM_COMPARISONS 1
#define CODON_PERFECT_SCORE 10
#define CODON_AMINO_ACID_SCORE 5
#define NUCLEOTIDE_IDENTICAL_SCORE 2
#define NUCLEOTIDE_BASE_PAIR_SCORE 1

/* Function Prototypes */

int    get_menu_choice(char* menu_name, char menu_items[][MAX_MENU_ITEM_SIZE], int number_of_choices);
void   clear_memory(char** sample_segment, char*** candidate_segments, int* number_of_candidates);
int    load_file(char** sample_segment, char*** candidate_segments);
void   end_program(int exit_value);
int    is_base_pair(char nucleotide_1, char nucleotide_2);
int    get_codon_index(char* codon_code);
void   get_user_input(char* message, char* response);
int    extract_dna(FILE* file_pointer, char** sample_segment, char*** candidate_segments);

void   analyze_segments(char* sample_segment, char** candidate_segments, int number_of_candidates);
int    calculate_score(char* sample_segment, char* candidate_segment);
int    calculate_shift_score(char* sample_segment, char* effective_candidate_segment, int sample_codons);
int    calculate_codon_score(char* sample_codon, char* candidate_codon);

static const char codon_codes[NUMBER_OF_CODONS][CODON_SYMBOL_LENGTH] =
{ "TTT", "TTC", "TTA", "TTG", "CTT", "CTC",
  "CTA", "CTG", "ATT", "ATC", "ATA", "ATG",
    "GTT", "GTC", "GTA", "GTG", "TCT", "TCC",
  "TCA", "TCG", "CCT", "CCC", "CCA", "CCG",
    "ACT", "ACC", "ACA", "ACG", "GCT", "GCC",
  "GCA", "GCG", "TAT", "TAC", "TAA", "TAG",
    "CAT", "CAC", "CAA", "CAG", "AAT", "AAC",
  "AAA", "AAG", "GAT", "GAC", "GAA", "GAG",
    "TGT", "TGC", "TGA", "TGG", "CGT", "CGC",
  "CGA", "CGG", "AGT", "AGC", "AGA", "AGG",
    "GGT", "GGC", "GGA", "GGG" };

static const char codon_names[NUMBER_OF_CODONS][CODON_NAME_LENGTH] =
{ "phenylalanine", "phenylalanine", "leucine",       "leucine",       "leucine",       "leucine",
"leucine",       "leucine",       "isoleucine",    "isoleucine",    "isoleucine",    "methionine",
"valine",        "valine",        "valine",        "valine",        "serine",        "serine",
"serine",        "serine",        "proline",       "proline",       "proline",       "proline",
"threonine",     "threonine",     "threonine",     "threonine",     "alanine",       "alanine",
"alanine",       "alanine",       "tyrosine",      "tyrosine",      "stop",          "stop",
"histidine",     "histidine",     "glutamine",     "glutamine",     "asparagine",    "asparagine",
"lysine",        "lysine",        "aspartic acid", "aspartic acid", "glutamic acid", "glutamic acid",
"cysteine",      "cysteine",      "stop",          "tryptophan",    "arginine",      "arginine",
"arginine",      "arginine",      "serine",        "serine",        "arginine",      "arginine",
"glycine",       "glycine",       "glycine",       "glycine" };