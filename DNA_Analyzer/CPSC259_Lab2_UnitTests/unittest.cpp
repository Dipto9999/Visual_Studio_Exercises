#include "CppUnitTest.h"

extern "C" {
	#include "dna.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests {
	TEST_CLASS(CodonScore_NucleotideIdentical) {
		public :

		TEST_METHOD(CodonScoreTest_NucleotideIdentical_First) {
			char sample_codon[] = "AAA"; // Lysine
			char candidate_codon[] = "ACC"; // Threonine

			int actual_score = NUCLEOTIDE_IDENTICAL_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideIdentical_Middle) {
			char sample_codon[] = {'C', 'C', 'A', '\0'}; // Proline
			char candidate_codon[] = {'A', 'C', 'C', '\0'}; // Threonine

			int actual_score = NUCLEOTIDE_IDENTICAL_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideIdentical_Last) {
			char sample_codon[] = "CAC"; // Histidine
			char candidate_codon[] = {'A', 'C', 'C', '\0'}; // Threonine

			int actual_score = NUCLEOTIDE_IDENTICAL_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideIdentical_FirstMiddle) {
			char sample_codon[] = {'T', 'G', 'C', '\0'}; // Cysteine
			char candidate_codon[] = "TGA"; // **Stop**

			int actual_score = 2 * NUCLEOTIDE_IDENTICAL_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideIdentical_FirstLast) {
			char sample_codon[] = "AAA"; // Lysine
			char candidate_codon[] = "ACA"; // Threonine

			int actual_score = 2 * NUCLEOTIDE_IDENTICAL_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideIdentical_MiddleLast) {
			char sample_codon[] = "CCA"; // Proline
			char candidate_codon[] = "ACA"; // Threonine

			int actual_score = 2 * NUCLEOTIDE_IDENTICAL_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}
	};

	TEST_CLASS(CodonScore_NucleotideBasePair) {
		public :

		TEST_METHOD(CodonScoreTest_NucleotideBasePair_One) {
			char sample_codon[] = "AAA"; // Lysine
			char candidate_codon[] = "TCC"; // Serine

			int actual_score = NUCLEOTIDE_BASE_PAIR_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideBasePair_Two) {
			char sample_codon[] = "AAA"; // Lysine
			char candidate_codon[] = "TCT"; // Serine
			int actual_score = 2 * NUCLEOTIDE_BASE_PAIR_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideBasePair_Three) {
			char sample_codon[] = {'A', 'A', 'A', '\0'}; // Lysine
			char candidate_codon[] = {'T', 'T', 'T', '\0'}; // Phenylalanine

			int actual_score = CODON_LENGTH * NUCLEOTIDE_BASE_PAIR_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideCombination__Identical_BasePair) {
			char sample_codon[] = "CTA"; // Leucine
			char candidate_codon[] = "TTT"; // Phenylaline

			int actual_score = NUCLEOTIDE_IDENTICAL_SCORE + NUCLEOTIDE_BASE_PAIR_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideCombination__BasePair_Identical) {
			char sample_codon[] = "ATC"; // Isoleucine
			char candidate_codon[] = "TTT"; // Phenylaline

			int actual_score = NUCLEOTIDE_BASE_PAIR_SCORE + NUCLEOTIDE_IDENTICAL_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideCombination__Identical_Space_BasePair) {
			char sample_codon[] = "ACA"; // Threonine
			char candidate_codon[] = "ATT"; // Isoleucine

			int actual_score = NUCLEOTIDE_IDENTICAL_SCORE + NUCLEOTIDE_BASE_PAIR_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideCombination__BasePair_Space_Identical) {
			char sample_codon[] = "TCT"; // Serine
			char candidate_codon[] = "ATT"; // Isoleucine

			int actual_score = NUCLEOTIDE_BASE_PAIR_SCORE + NUCLEOTIDE_IDENTICAL_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideCombination__BasePair_Identical_BasePair) {
			char sample_codon[] = "ACA"; // Threonine
			char candidate_codon[] = "TCT"; // Valine

			int actual_score = NUCLEOTIDE_BASE_PAIR_SCORE
				+ NUCLEOTIDE_IDENTICAL_SCORE + NUCLEOTIDE_BASE_PAIR_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_NucleotideCombination__Identical_BasePair_Identical) {
			char sample_codon[] = "ACA"; // Threonine
			char candidate_codon[] = "AGA"; // Serine

			int actual_score = NUCLEOTIDE_IDENTICAL_SCORE
				+ NUCLEOTIDE_BASE_PAIR_SCORE + NUCLEOTIDE_IDENTICAL_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_SameAminoAcid_RemainingNucleotidesNotBasePair) {
			char sample_codon[] = "AAA"; // Lysine
			char candidate_codon[] = "AAG"; // Lysine

			int actual_score = CODON_AMINO_ACID_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_SameAminoAcid_RemainingNucleotidesBasePair) {
			char sample_codon[] = "GGT"; // Glycine
			char candidate_codon[] = "GGA"; // Glycine

			int actual_score = CODON_AMINO_ACID_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}
	};

	TEST_CLASS(CodonScore_Bounds) {
		public :

		TEST_METHOD(CodonScoreTest_MinimumScore) {
			char sample_codon[] = "GTC"; // Valine
			char candidate_codon[] = "AGT"; // Serine

			int actual_score = MINIMUM_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(CodonScoreTest_PerfectScore) {
			char sample_codon[] = "GTT"; // Valine
			char effective_candidate_codon[] = "GTT"; // Valine

			int actual_score = CODON_PERFECT_SCORE;
			int calculated_score = calculate_codon_score(sample_codon, effective_candidate_codon);

			Assert::AreEqual(actual_score, calculated_score);
		}
	};

	TEST_CLASS(SegmentScore_ShiftScore_Examples) {
		public :

		TEST_METHOD(SegmentScoreTest_Example01) {
			char sample_segment[] = "AAAGGG";
			char candidate_segment[] = "CTCAAAGGGTAT";

			int actual_score = 20;
			int calculated_score = calculate_score(sample_segment, candidate_segment);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(ShiftScoreTest_Example01_01) {
			char sample_segment[] = "AAAGGG";
			char effective_candidate_segment[] = "CTCAAAGGGTAT";

			int sample_codons = 2;

			int actual_score = 1;
			int calculated_score = calculate_shift_score(sample_segment, effective_candidate_segment, sample_codons);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(ShiftScoreTest_Example01_02) {
			char sample_segment[] = "AAAGGG";
			char effective_candidate_segment[] = "AAAGGGTAT";

			int sample_codons = 2;

			int actual_score = 20;
			int calculated_score = calculate_shift_score(sample_segment, effective_candidate_segment, sample_codons);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(ShiftScoreTest_Example01_03) {
			char sample_segment[] = "AAAGGG";
			char effective_candidate_segment[] = "GGGTAT";

			int sample_codons = 2;

			int actual_score = MINIMUM_SCORE;
			int calculated_score = calculate_shift_score(sample_segment, effective_candidate_segment, sample_codons);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(SegmentScoreTest_Example02) {
			char sample_segment[] = "AAAGGGT";
			char candidate_segment[] = "AAAGGGA";

			int actual_score = 20;
			int calculated_score = calculate_score(sample_segment, candidate_segment);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(ShiftScoreTest_Example02) {
			char sample_segment[] = "AAAGGGT";
			char effective_candidate_segment[] = "AAAGGGA";

			int sample_codons = 2;

			int actual_score = 20;
			int calculated_score = calculate_shift_score(sample_segment, effective_candidate_segment, sample_codons);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(SegmentScoreTest_Example04) {
			char sample_segment[] = "AAAGGGT";
			char candidate_segment[] = "TTTAAAT";

			int actual_score = 3;
			int calculated_score = calculate_score(sample_segment, candidate_segment);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(ShiftScoreTest_Example04) {
			char sample_segment[] = "AAAGGGT";
			char effective_candidate_segment[] = "TTTAAAT";

			int sample_codons = 2;

			int actual_score = 3;
			int calculated_score = calculate_shift_score(sample_segment, effective_candidate_segment, sample_codons);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(SegmentScoreTest_Example05) {
			char sample_segment[] = "AAATTT";
			char candidate_segment[] = "GGGAAA";

			int actual_score = 3;
			int calculated_score = calculate_score(sample_segment, candidate_segment);

			Assert::AreEqual(actual_score, calculated_score);
		}

		TEST_METHOD(ShiftScoreTest_Example05) {
			char sample_segment[] = "AAATTT";
			char effective_candidate_segment[] = "GGGAAA";

			int sample_codons = 2;

			int actual_score = 3;
			int calculated_score = calculate_shift_score(sample_segment, effective_candidate_segment, sample_codons);

			Assert::AreEqual(actual_score, calculated_score);
		}
	};
}