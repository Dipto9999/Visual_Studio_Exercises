#include "CppUnitTest.h"

extern "C" {
	#include "pivot.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests {
	TEST_CLASS(UnitTests) {
		public:

		TEST_METHOD(Pivot_Size1) {
			int size = 1;
			int quicksort_list[] = { 5 };

			int calculated_amount = count_pivots(quicksort_list, size);
			int actual_amount = 1;


			Assert::AreEqual(actual_amount, calculated_amount);
		}

		TEST_METHOD(Pivot_Size2) {
			int size = 2;
			int quicksort_list[] = { 4, 2 };

			int calculated_amount = count_pivots(quicksort_list, size);
			int actual_amount = 0;


			Assert::AreEqual(actual_amount, calculated_amount);
		}

		TEST_METHOD(Pivot_Size5) {
			int size = 5;
			int quicksort_list[] = { 2, 6, 6, 6, 9 };

			int calculated_amount = count_pivots(quicksort_list, size);
			int actual_amount = 5;


			Assert::AreEqual(actual_amount, calculated_amount);
		}

		TEST_METHOD(Pivot_Size7) {
			int size = 7;
			int quicksort_list[] = { 6, 3, 8, 5, 10, 99, 98 };

			int calculated_amount = count_pivots(quicksort_list, size);
			int actual_amount = 1;


			Assert::AreEqual(actual_amount, calculated_amount);
		}

		TEST_METHOD(Pivot_Size8) {
			int size = 8;
			int quicksort_list[] = { 7, 12, 9, 17, 16, 10, 14, 20 };

			int calculated_amount = count_pivots(quicksort_list, size);
			int actual_amount = 2;


			Assert::AreEqual(actual_amount, calculated_amount);
		}

		TEST_METHOD(Pivot_Size12) {
			int size = 12;
			int quicksort_list[] = { -4, -17, 3, 0, 12, 13, 22, 18, 55, 61, 78, 73 };

			int calculated_amount = count_pivots(quicksort_list, size);
			int actual_amount = 4;


			Assert::AreEqual(actual_amount, calculated_amount);
		}
	};
}
