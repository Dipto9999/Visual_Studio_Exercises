#include "CppUnitTest.h"

extern "C" {
  #include <string.h>

  #include "lab2_in-lab_exercises.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPSC259_Lab2_InLabUnitTests {
  TEST_CLASS(Swap_Ints) {
    public :

    TEST_METHOD(Test_Swap_Ints_BothPositive) {
      int first = 1;
      int second = 2;

      swap_ints(&first, &second);

      Assert::AreEqual(first, 2);
      Assert::AreEqual(second, 1);
    }

    TEST_METHOD(Test_Swap_Ints_BothNegative) {
        int first = -1;
        int second = -2;

        swap_ints(&first, &second);

        Assert::AreEqual(first, -2);
        Assert::AreEqual(second, -1);
    }

    TEST_METHOD(Test_Swap_Ints_OnePositive) {
        int first = 0;
        int second = 1;

        swap_ints(&first, &second);

        Assert::AreEqual(first, 1);
        Assert::AreEqual(second, 0);
    }

    TEST_METHOD(Test_Swap_Ints_OneNegative) {
      int first = 0;
      int second = -1;

      swap_ints(&first, &second);

      Assert::AreEqual(first, -1);
      Assert::AreEqual(second, 0);
    }

    TEST_METHOD(Test_Swap_Ints_OnePositiveNegative) {
        int first = 1;
        int second = -1;

        swap_ints(&first, &second);

        Assert::AreEqual(first, -1);
        Assert::AreEqual(second, 1);
    }

    TEST_METHOD(Test_Swap_Ints_Bound) {
      int first = INT_MAX;
      int second = INT_MIN;

      swap_ints(&first, &second);

      Assert::AreEqual(first, INT_MIN);
      Assert::AreEqual(second, INT_MAX);
    }
  };

  TEST_CLASS(Reverse_String) {
    public :

    TEST_METHOD(Test_Reverse_String_Capitalized) {
      char original[] = "Canada";
      char reversed[] = "adanaC";

      reverse_string(original);

      int comparison = strcmp(original, reversed);

      Assert::AreEqual(comparison, STRINGS_EQUAL);
    }

    TEST_METHOD(Test_Reverse_String_Empty) {
      char original[] = "";
      char reversed[] = "";

      int length = strlen(original);

      reverse_string(original);

      int comparison = strncmp(original, reversed, length);

      Assert::AreEqual(comparison, STRINGS_EQUAL);
    }

    TEST_METHOD(Test_Reverse_String_SingleChar) {
      char original[] = "A";
      char reversed[] = "A";

      int length = strlen(original);

      reverse_string(original);

      int comparison = strncmp(original, reversed, length);

      Assert::AreEqual(comparison, STRINGS_EQUAL);
    }

    TEST_METHOD(Test_Reverse_String_DuplicateChar) {
        char original[] = "AAAAA";
        char reversed[] = "AAAAA";

        int length = strlen(original);

        reverse_string(original);

        int comparison = strncmp(original, reversed, length);

        Assert::AreEqual(comparison, STRINGS_EQUAL);
    }

    TEST_METHOD(Test_Reverse_String_Spaces) {
        char original[] = "A man a plan a canal Panama";
        char reversed[] = "amanaP lanac a nalp a nam A";

        int length = strlen(original);

        reverse_string(original);

        int comparison = strncmp(original, reversed, length);

        Assert::AreEqual(comparison, STRINGS_EQUAL);
    }

    TEST_METHOD(Test_Reverse_String_Tab) {
        char original[] = "This \t is a tab";
        char reversed[] = "bat a si \t sihT";

        int length = strlen(original);

        reverse_string(original);

        int comparison = strncmp(original, reversed, length);

        Assert::AreEqual(comparison, STRINGS_EQUAL);
    }

    TEST_METHOD(Test_Reverse_String_SpecialChar) {
      char original[] = "\u2500\u2501\n";
      char reversed[] = "\n\u2501\u2500";

      int length = strlen(original);

      reverse_string(original);

      int comparison = strncmp(original, reversed, length);

      Assert::AreEqual(comparison, STRINGS_EQUAL);
    }
  };

  TEST_CLASS(Contains_Sample) {
    public :

    TEST_METHOD(Test_Contains_Sample_Positive_Start) {
      char candidate[] = "soupspoon";
      char sample[] = "soup";

      int found = contains_sample(candidate, sample);

      Assert::AreEqual(found, TRUE);
    }

    TEST_METHOD(Test_Contains_Sample_Positive_End) {
      char candidate[] = "soupspoon";
      char sample[] = "spoon";

      int found = contains_sample(candidate, sample);

      Assert::AreEqual(found, TRUE);
    }

    TEST_METHOD(Test_Contains_Sample_Negative_StartSimilar) {
      char candidate[] = "Soupspoon";
      char sample[] = "soup";

      int found = contains_sample(candidate, sample);

      Assert::AreEqual(found, FALSE);
    }

    TEST_METHOD(Test_Contains_Sample_Negative_EndSimilar) {
      char candidate[] = "soupspoon";
      char sample[] = "Spoon";

      int found = contains_sample(candidate, sample);

      Assert::AreEqual(found, FALSE);
    }

    TEST_METHOD(Test_Contains_Sample_Positive_Same) {
      char candidate[] = "soupspoon";
      char sample[] = "soupspoon";

      int found = contains_sample(candidate, sample);

      Assert::AreEqual(found, TRUE);
    }

    TEST_METHOD(Test_Contains_Sample_Negative_Similar) {
        char candidate[] = "soupspoon";
        char sample[] = "SoupSpoon";

        int found = contains_sample(candidate, sample);

        Assert::AreEqual(found, FALSE);
    }

    TEST_METHOD(Test_Contains_Sample_Positive_SampleEmpty) {
      char candidate[] = "soupspoon";
      char sample[] = "";

      int found = contains_sample(candidate, sample);

      Assert::AreEqual(found, TRUE);
    }

    TEST_METHOD(Test_Contains_Sample_Negative_CandidateEmpty) {
      char candidate[] = "";
      char sample[] = "soupspoon";

      int found = contains_sample(candidate, sample);

      Assert::AreEqual(found, FALSE);
    }

    TEST_METHOD(Test_Contains_Sample_Positive_BothEmpty) {
      char candidate[] = "";
      char sample[] = "";

      int found = contains_sample(candidate, sample);

      Assert::AreEqual(found, TRUE);
    }
  };

  TEST_CLASS(Find_Index) {
    public :

    TEST_METHOD(Test_Find_Index_Start) {
      char candidate[] = "soupspoon";
      char sample[] = "soup";

      int index = find_index(candidate, sample);

      Assert::AreEqual(0, index);
    }

    TEST_METHOD(Test_Find_Index_End) {
      char candidate[] = "soupspoon";
      char sample[] = "spoon";

      int index = find_index(candidate, sample);

      Assert::AreEqual(4, index);
    }

    TEST_METHOD(Test_Find_Index_Middle) {
      char candidate[] = "soupspoonsoup";
      char sample[] = "spoon";

      int index = find_index(candidate, sample);

      Assert::AreEqual(4, index);
    }

    TEST_METHOD(Test_Find_Index_Same) {
      char candidate[] = "soupspoon";
      char sample[] = "soupspoon";

      int index = find_index(candidate, sample);

      Assert::AreEqual(0, index);
    }

    TEST_METHOD(Test_Find_Index_EmptySample) {
      char candidate[] = "soupspoon";
      char sample[] = "";

      int index = find_index(candidate, sample);

      Assert::AreEqual(0, index);
    }

    TEST_METHOD(Test_Find_Index_Negative_EmptyCandidate) {
        char candidate[] = "";
        char sample[] = "soupspoon";

        int index = find_index(candidate, sample);

        Assert::AreEqual(ERROR, index);
    }

    TEST_METHOD(Test_Find_Index_BothEmpty) {
        char candidate[] = "";
        char sample[] = "";

        int index = find_index(candidate, sample);

        Assert::AreEqual(0, index);
    }

    TEST_METHOD(Test_Find_Index_Negative_LargeSample) {
        char candidate[] = "soupspoon";
        char sample[] = "soupspoons";

        int index = find_index(candidate, sample);

        Assert::AreEqual(ERROR, index);
    }

    TEST_METHOD(Test_Find_Index_Negative_Similar) {
        char candidate[] = "soupspoon";
        char sample[] = "Soupspoon";

        int index = find_index(candidate, sample);

        Assert::AreEqual(ERROR, index);
    }
  };
}