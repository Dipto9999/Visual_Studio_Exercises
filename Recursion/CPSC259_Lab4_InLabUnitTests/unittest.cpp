#include <sstream>
#include <iostream>
#include <climits>
#include <string.h>

#include "CppUnitTest.h"

extern "C" {
	#include "recursion.h"
}

#define BUFFERLENGTH 1024
#define DOUBLE_PRECISION 2

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests {
	TEST_CLASS(Calculate_Power_Function) {
		public :

		TEST_METHOD(Test_PositiveBase_PositiveExponent) {
			double calculation = calculate_power(5, 3);

			Assert::AreEqual(calculation, 125.00, DOUBLE_PRECISION);
		}

		TEST_METHOD(Test_PositiveBase_ZeroExponent) {
			double calculation = calculate_power(5,0);

			Assert::AreEqual(calculation, 1.00, DOUBLE_PRECISION);
		}

		TEST_METHOD(Test_PositiveBase_NegativeExponent) {
			double calculation = calculate_power(5,-3);

			Assert::AreEqual(calculation, 1/(double)125, DOUBLE_PRECISION);
		}

		TEST_METHOD(Test_NegativeBase_PositiveOddExponent) {
			double calculation = calculate_power(-5, 3);

			Assert::AreEqual(calculation, -125.00, DOUBLE_PRECISION);
		}

		TEST_METHOD(Test_NegativeBase_PositiveEvenExponent) {
			double calculation = calculate_power(-5, 4);

			Assert::AreEqual(calculation, 625.00, DOUBLE_PRECISION);
		}

		TEST_METHOD(Test_NegativeBase_ZeroExponent) {
			double calculation = calculate_power(-5, 0);

			Assert::AreEqual(calculation, 1.00, DOUBLE_PRECISION);
		}

		TEST_METHOD(Test_NegativeBase_NegativeOddExponent) {
			double calculation = calculate_power(-5,-3);

			Assert::AreEqual(calculation, 1/(double)-125, DOUBLE_PRECISION);
		}

		TEST_METHOD(Test_NegativeBase_NegativeEvenExponent) {
			double calculation = calculate_power(-5,-4);

			Assert::AreEqual(calculation, 1/(double)625, DOUBLE_PRECISION);
		}
	};

	TEST_CLASS(Count_Digits_Function) {
		public :

		TEST_METHOD(Test_Positive_OneDigit_Minimum) {
			Assert::AreEqual(count_digits(1), 1);
		}

		TEST_METHOD(Test_Positive_OneDigit_Maximum) {
			Assert::AreEqual(count_digits(9), 1);
		}

		TEST_METHOD(Test_Positive_TwoDigit_Minimum) {
			Assert::AreEqual(count_digits(10), 2);
		}

		TEST_METHOD(Test_Positive_TwoDigit_Maximum) {
			Assert::AreEqual(count_digits(10), 2);
		}

		TEST_METHOD(Test_Positive_ManyDigits_Multiple10) {
			Assert::AreEqual(count_digits(24680), 5);
		}

		TEST_METHOD(Test_Positive_ManyDigits_NotMultiple10) {
			Assert::AreEqual(count_digits(24681), 5);
		}

		TEST_METHOD(Test_Positive_MaxDigits) {
			Assert::AreEqual(count_digits(INT_MAX), 10);
		}
	};

	TEST_CLASS(String_Length_Function) {
		public :

		TEST_METHOD(Test_Zero_01) {
			char string[] = "";

			Assert::AreEqual(string_length(string), 0);
		}

		TEST_METHOD(Test_Zero_02) {
			char string[] = {'\0'};

			Assert::AreEqual(string_length(string), 0);
		}

		TEST_METHOD(Test_Zero_03) {
			char* string = "";

			Assert::AreEqual(string_length(string), 0);
		}

		TEST_METHOD(Test_Zero_04) {
			char string[1];
			string[0] = '\0';

			Assert::AreEqual(string_length(string), 0);
		}

		TEST_METHOD(Test_OneWord) {
			char string[] = "alakazam";

			Assert::AreEqual(string_length(string), (int)strlen(string));
		}

		TEST_METHOD(Test_ManyWords) {
			char string[] = "abra kadabra alakazam";

			Assert::AreEqual(string_length(string), (int)strlen(string));
		}

		TEST_METHOD(Test_AllNullCharacters) {
			char string[] = {'\0', '\0', '\0'};

			Assert::AreEqual(string_length(string), 0 );
		}

		TEST_METHOD(Test_StartNullCharacter) {
			char string[] = {'\0', 'a', '\0', '\0', '\0' };

			Assert::AreEqual(string_length(string), 0);
		}

		TEST_METHOD(Test_StartNullCharacters) {
			char string[] = { '\0', '\0', 'a', '\0', '\0', '\0' };

			Assert::AreEqual(string_length(string), 0);
		}

		TEST_METHOD(Test_EndNullCharacters_01) {
			char string[] = { 'a', '\0', '\0', '\0' };

			Assert::AreEqual(string_length(string), 1);
		}

		TEST_METHOD(Test_EndNullCharacters_02) {
			char string[] = {'a', 'b', '\0', '\0'};

			Assert::AreEqual(string_length(string), 2);
		}
	};

	TEST_CLASS(Is_Palindrome_Function) {
		public :

		TEST_METHOD(Test_Length_Zero) {
			char string[] = "";
			int length = strlen(string);

			Assert::AreEqual(is_palindrome("", 0), TRUE);
		}

		TEST_METHOD(Test_Length_One) {
			char string[] = "A";
			int length = strlen(string);

			Assert::AreEqual(is_palindrome(string, length), TRUE);
		}

		TEST_METHOD(Test_Length_Two_Positive) {
			char string[] = "AA";
			int length = strlen(string);

			Assert::AreEqual(is_palindrome(string, length), TRUE);
		}

		TEST_METHOD(Test_Length_Two_Negative) {
			char string[] = "Aa";
			int length = strlen(string);

			Assert::AreEqual(is_palindrome(string, length), FALSE);
		}

		TEST_METHOD(Test_Length_NonTrivial_Positive) {
			char string[] = "able was i ere i saw elba";
			int length = strlen(string);

			Assert::AreEqual(is_palindrome(string, length), TRUE);
		}

		TEST_METHOD(Test_Length_NonTrivial_Negative) {
			char string[] = "definitely not a palindrome";
			int length = strlen(string);

			Assert::AreEqual(is_palindrome(string, length), FALSE);
		}
	};

	TEST_CLASS(Draw_Ramp_Function) {
		public :

		TEST_METHOD(Test_Ramp1) {
			char output_buff[BUFFERLENGTH];

			// Initialize the Output Buffer.
			for (int index = 0; index < BUFFERLENGTH; index++) output_buff[index] = '\0';

			char solution[] = "*";

			draw_ramp(1, output_buff);

			Assert::AreEqual(strcmp(output_buff, solution), STRINGS_EQUAL);
		}

		TEST_METHOD(Test_Ramp2) {
			char output_buff[BUFFERLENGTH];

			// Initialize the Output Buffer.
			for (int index = 0; index < BUFFERLENGTH; index++) output_buff[index] = '\0';

			char solution[] = "**\n*\n**";

			draw_ramp(2, output_buff);

			Assert::AreEqual(strcmp(output_buff, solution), STRINGS_EQUAL);
		}

		TEST_METHOD(Test_Ramp3) {
			char output_buff[BUFFERLENGTH];

			// Initialize the Output Buffer.
			for (int index = 0; index < BUFFERLENGTH; index++) output_buff[index] = '\0';

			char solution[] = "***\n**\n*\n**\n***";

			draw_ramp(3, output_buff);

			Assert::AreEqual(strcmp(output_buff, solution), STRINGS_EQUAL);
		}

		TEST_METHOD(Test_Ramp4) {
			char output_buff[BUFFERLENGTH];

			// Initialize the Output Buffer.
			for (int index = 0; index < BUFFERLENGTH; index++) output_buff[index] = '\0';

			char solution[] = "****\n***\n**\n*\n**\n***\n****";

			draw_ramp(4, output_buff);

			Assert::AreEqual(strcmp(output_buff, solution), STRINGS_EQUAL);
		}

		TEST_METHOD(Test_Ramp5) {
			char output_buff[BUFFERLENGTH];

			// Initialize the Output Buffer.
			for (int index = 0; index < BUFFERLENGTH; index++) output_buff[index] = '\0';

			char solution[] = "*****\n****\n***\n**\n*\n**\n***\n****\n*****";

			draw_ramp(5, output_buff);

			Assert::AreEqual(strcmp(output_buff, solution), STRINGS_EQUAL);
		}
	};
}