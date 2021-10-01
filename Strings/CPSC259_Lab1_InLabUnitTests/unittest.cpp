#include "CppUnitTest.h"

/*
 * We Need to 'include' the Header File(s) For the Project We are Testing.
 */

extern "C" {
  #include "lab1_inlab_exercises.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPSC259_Lab1_InLabUnitTests {
  TEST_CLASS(ReverseArray) {
    public :

    TEST_METHOD(Test_ReverseArray_Length_One) {
      /* Variables */
      int array_one[] = {2014};
      int array_two[] = {2014};

      int array_length = sizeof(array_one) / sizeof(*array_one);

      reverse_array(array_one, array_length);
      Assert::AreEqual(array_one[0], array_two[0]);
    }

    TEST_METHOD(Test_ReverseArray_Length_Even) {
      /* Variables */
      int array_one[] = {13, 21, 34, 55, 89, 144};
      int array_two[] = {144, 89, 55, 34, 21, 13};

      int array_length = sizeof(array_one) / sizeof(*array_one);
      int i;

      reverse_array(array_one, array_length);
      for (i = 0; i < array_length; i++) Assert::AreEqual(array_one[i], array_two[i]);
    }

    TEST_METHOD(Test_ReverseArray_Length_Odd) {
      /* Variables */
      int array_one[] = {1, 8, 27, 64, 125};
      int array_two[] = {125, 64, 27, 8, 1};

      int array_length = sizeof(array_one) / sizeof(*array_one);
      int i = 0;

      reverse_array(array_one, array_length);
      for (i = 0; i < array_length; ++i) Assert::AreEqual(array_one[i], array_two[i]);
    }
  };

	TEST_CLASS(Length) {
		public :

    TEST_METHOD(Test_Length_Empty_01) {
      char string[] = "";

      Assert::AreEqual(length(string), 0);
    }

    TEST_METHOD(Test_Length_Empty_02) {
      char string[] = {'\0'};

      Assert::AreEqual(length(string), 0);
    }

    TEST_METHOD(Test_Length_NonTrivial_01) {
      char string[] = "Hello World";

      Assert::AreEqual(length(string), 11);
    }

    TEST_METHOD(Test_Length_NonTrivial_02) {
      char string[] =
        {'H', 'i', ' ', '.', 'H', 'o', 'w', ' ', 'a', 'r', 'e', ' ', 'y', 'o', 'u', '?', '\0'};

      Assert::AreEqual(length(string), 16);
    }
  };

	TEST_CLASS(CountLetters) {
		public :

    TEST_METHOD(Test_CountLetters_Empty_01) {
      char string[] = "";

      Assert::AreEqual(count_letters(string, '\0'), 0);
    }

    TEST_METHOD(Test_CountLetters_Empty_02) {
      char string[] = {'\0'};

      Assert::AreEqual(count_letters(string, '\0'), 0);
    }

    TEST_METHOD(Test_CountLetters_Length_One_Positive) {
      char string[] = "A";

      Assert::AreEqual(count_letters(string, 'A'), 1);
    }

    TEST_METHOD(Test_CountLetters_Length_One_Negative) {
      char string[] = "A";

      Assert::AreEqual(count_letters(string, 'a'), 0);
    }

    TEST_METHOD(Test_CountLetters_Length_NonTrivial_AllCharFound) {
      char string[] = "AAAAAAAAAA";

      Assert::AreEqual(count_letters(string, 'A'), 10);
    }

    TEST_METHOD(Test_CountLetters_Length_NonTrivial_FirstCharFound) {
      char string[] = "ABCDEFGHIJ";

      Assert::AreEqual(count_letters(string, 'A'), 1);
    }

    TEST_METHOD(Test_CountLetters_Length_NonTrivial_MiddleCharFound) {
      char string[] = "ABCDEFGHIJ";

      Assert::AreEqual(count_letters(string, 'E'), 1);
    }

    TEST_METHOD(Test_CountLetters_Length_NonTrivial_LastCharFound) {
      char string[] = "ABCDEFGHIJ";

      Assert::AreEqual(count_letters(string, 'J'), 1);
    }

    TEST_METHOD(Test_CountLetters_Length_NonTrivial_NoCharFound) {
      char string[] = "ABCDEFGHIJ";

      Assert::AreEqual(count_letters(string, 'Z'), 0);
    }
  };

	TEST_CLASS(IsPalindrome) {
		public :

    TEST_METHOD(Test_IsPalindrome_Empty) {
      char string[] = "";

      Assert::AreEqual(is_palindrome(string), 1);
    }

    TEST_METHOD(Test_IsPalindrome_Negative_Odd) {
      char string[] = "happy";

      Assert::AreEqual(is_palindrome(string), 0);
    }

    TEST_METHOD(Test_IsPalindrome_Negative_Even) {
      char string[] = "little";

      Assert::AreEqual(is_palindrome(string), 0);
    }

    TEST_METHOD(Test_IsPalindrome_Positive_Odd) {
      char string[] = "hannnah";

      Assert::AreEqual(is_palindrome(string), 1);
    }

      TEST_METHOD(Test_IsPalindrome_Positive_Even) {
      char string[] = "applehannahhannahelppa";

      Assert::AreEqual(is_palindrome(string), 1);
    }

    TEST_METHOD(Test_IsPalindrome_Positive_SymmetricSpaces) {
      char string[] = "able was i ere i saw elba";

      Assert::AreEqual(is_palindrome(string), 1);
    }

    TEST_METHOD(Test_IsPalindrome_Positive_AsymmetricSpaces_01) {
      char string[] = "a nut for a jar of tuna";

      Assert::AreEqual(is_palindrome(string), 1);
    }

    TEST_METHOD(Test_IsPalindrome_Positive_AsymmetricSpaces_02) {
      char string[] = "a  nut     for a jar  of tuna";

      Assert::AreEqual(is_palindrome(string), 1);
    }

    TEST_METHOD(Test_IsPalindrome_Positive_AllSpacesOdd) {
      char string[] = "   ";

      Assert::AreEqual(is_palindrome(string), 1);
    }

    TEST_METHOD(Test_IsPalindrome_Positive_AllSpacesEven) {
      char string[] = "    ";

      Assert::AreEqual(is_palindrome(string), 1);
    }
  };
}