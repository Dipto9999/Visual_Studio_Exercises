#include "pch.h"

#include <sstream>
#include <iostream>
#include <climits>

#include "CppUnitTest.h"

extern "C" {
	#include "mazesolver.h"
}

#define STRINGS_EQUAL 0
#define MAX_DIMENSION 10

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests_NoFileIO {
	TEST_CLASS(Calculate_PathCost) {
		public:

		TEST_METHOD(Test_PathCost_Zero_01) {
			Assert::AreEqual(path_cost("\0"), 0);
		}

		TEST_METHOD(Test_PathCost_Zero_02) {
			Assert::AreEqual(path_cost("0\0"), 0);
		}

		TEST_METHOD(Test_PathCost_Zero_03) {
			Assert::AreEqual(path_cost("0000000000"), 0);
		}

		TEST_METHOD(Test_PathCost_OneDigit_01) {
			Assert::AreEqual(path_cost("1\0"), 1);
		}

		TEST_METHOD(Test_PathCost_OneDigit_02) {
			Assert::AreEqual(path_cost("8"), 8);
		}

		TEST_METHOD(Test_PathCost_TwoDigits_01) {
			Assert::AreEqual(path_cost("33"), 6);
		}

		TEST_METHOD(Test_PathCost_TwoDigits_02) {
			Assert::AreEqual(path_cost("99"), 18);
		}

		TEST_METHOD(Test_PathCost_ManyDigits_01) {
			Assert::AreEqual(path_cost("832\0"), 13);
		}

		TEST_METHOD(Test_PathCost_ManyDigits_02) {
			Assert::AreEqual(path_cost("979"), 25);
		}

		TEST_METHOD(Test_PathCost_ManyDigits_03) {
			Assert::AreEqual(path_cost("999999999999"), 108);
		}
	};

	TEST_CLASS(Find_ShortestPath) {
	public:

		TEST_METHOD(Test_ShortestPath_OneByOne) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 				5
			 ******************************
			 */

			strcpy(*(paths + 0), "5");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_shortest(paths, 1, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Shortest Path : 5\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_ShortestPath_TwoByTwo_01) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  4 4
			 * 			  5 1
			 ******************************
			 */

			strcpy(*(paths + 0), "44");
			strcpy(*(paths + 1), "451");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_shortest(paths, 2, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Shortest Path : 44\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_ShortestPath_TwoByTwo_02) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  1 9
			 * 			  1 1
			 ******************************
			 */

			strcpy(*(paths + 0), "19");
			strcpy(*(paths + 1), "111");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_shortest(paths, 2, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Shortest Path : 19\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_ShortestPath_TwoByTwo_03) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  1 *
			 * 			  1 1
			 ******************************
			 */

			strcpy(*(paths + 0), "111");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_shortest(paths, 1, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Shortest Path : 111\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_ShortestPath_ThreeByThree_01) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  1 1 3
			 * 			  * * X
			 * 			  X X X
			 ******************************
			 */

			strcpy(*(paths + 0), "113");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_shortest(paths, 1, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Shortest Path : 113\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_ShortestPath_ThreeByThree_02) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  9 9 9
			 * 			  * 3 2
			 * 			  X * 5
			 ******************************
			 */

			strcpy(*(paths + 0), "999");
			strcpy(*(paths + 1), "9932");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_shortest(paths, 2, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Shortest Path : 999\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_ShortestPath_ThreeByThree_03) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 2) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  9 9 9
			 * 			  * 3 2
			 * 			  X 4 5
			 ******************************
			 */

			strcpy(*(paths + 0), "999");
			strcpy(*(paths + 1), "9932");
			strcpy(*(paths + 2), "99345");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_shortest(paths, 3, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Shortest Path : 999\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_ShortestPath_ThreeByThree_04) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  1 * 3
			 * 			  2 9 9
			 * 			  * 1 1
			 ******************************
			 */

			strcpy(*(paths + 0), "1299");
			strcpy(*(paths + 1), "12911");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_shortest(paths, 2, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Shortest Path : 1299\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_ShortestPath_xByx_Unsolvable) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			* ..... *
			 * 			.........
			 *          .........
			 * 			* ..... *
			 ******************************
			 */

			strcpy(*(paths + 0), "");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_shortest(paths, 0, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "No Path Found."),
				STRINGS_EQUAL
			);
		}
	};

	TEST_CLASS(Find_CheapestPath) {
		public:

		TEST_METHOD(Test_CheapestPath_OneByOne) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 				5
			 ******************************
			 */

			strcpy(*(paths + 0), "5");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 1, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 5\nCheapest Path Cost : 5\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_TwoByTwo_01) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  4 4
			 * 			  5 1
			 ******************************
			 */

			strcpy(*(paths + 0), "44");
			strcpy(*(paths + 1), "451");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 2, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 44\nCheapest Path Cost : 8\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_TwoByTwo_02) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  4 4
			 * 			  1 3
			 ******************************
			 */

			strcpy(*(paths + 0), "44");
			strcpy(*(paths + 1), "413");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 2, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 44\nCheapest Path Cost : 8\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_TwoByTwo_03) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  1 9
			 * 			  1 1
			 ******************************
			 */

			strcpy(*(paths + 0), "19");
			strcpy(*(paths + 1), "111");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 2, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 111\nCheapest Path Cost : 3\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_TwoByTwo_04) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  1 *
			 * 			  1 1
			 ******************************
			 */

			strcpy(*(paths + 0), "111");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 1, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 111\nCheapest Path Cost : 3\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_ThreeByThree_01) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  1 1 3
			 * 			  * * X
			 * 			  X X X
			 ******************************
			 */

			strcpy(*(paths + 0), "113");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 1, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 113\nCheapest Path Cost : 5\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_ThreeByThree_02) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  9 9 9
			 * 			  * 3 2
			 * 			  X * 5
			 ******************************
			 */

			strcpy(*(paths + 0), "999");
			strcpy(*(paths + 1), "9932");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 2, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 9932\nCheapest Path Cost : 23\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_ThreeByThree_03) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  9 9 9
			 * 			  * 3 6
			 * 			  X * 5
			 ******************************
			 */

			strcpy(*(paths + 0), "999");
			strcpy(*(paths + 1), "9936");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 2, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 999\nCheapest Path Cost : 27\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_ThreeByThree_04) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 2) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  9 9 9
			 * 			  * 3 2
			 * 			  X 1 1
			 ******************************
			 */

			strcpy(*(paths + 0), "999");
			strcpy(*(paths + 1), "9932");
			strcpy(*(paths + 2), "99311");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 3, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 9932\nCheapest Path Cost : 23\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_ThreeByThree_05) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 2) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  9 9 9
			 * 			  * 3 5
			 * 			  X 1 1
			 ******************************
			 */

			strcpy(*(paths + 0), "999");
			strcpy(*(paths + 1), "9935");
			strcpy(*(paths + 2), "99311");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 3, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 99311\nCheapest Path Cost : 23\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_ThreeByThree_06) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));
			*(paths + 1) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			  1 * 3
			 * 			  2 9 9
			 * 			  * 1 1
			 ******************************
			 */

			strcpy(*(paths + 0), "1299");
			strcpy(*(paths + 1), "12911");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 2, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "Cheapest Path : 12911\nCheapest Path Cost : 14\n"),
				STRINGS_EQUAL
			);
		}

		TEST_METHOD(Test_CheapestPath_xByx_Unsolvable) {
			char** paths;
			char* message;

			/*
			 * Need to Dynamically Allocate Paths Double Array for
			 * Adequate Space to Copy Test String.
			 */
			paths = (char**)calloc(MAX_DIMENSION, sizeof(char*));

			*(paths + 0) = (char*)calloc(MAX_DIMENSION, sizeof(char));

			/*
			 ******************************
			 *** Representation of Maze ***
			 ******************************
			 * 			* ..... *
			 * 			.........
			 *          .........
			 * 			* ..... *
			 ******************************
			 */

			strcpy(*(paths + 0), "");

			/*
			 * Need to Dynamically Allocate Message for
			 * Adequate Space to Copy Test String.
			 */
			message = (char*)calloc(BUFFER, sizeof(char));

			strcpy(message, find_cheapest(paths, 0, ""));

			/* Deallocate Memory for Paths. */
			free(paths);

			Assert::AreEqual(
				strcmp(message, "No Path Found."),
				STRINGS_EQUAL
			);
		}
	};
}
