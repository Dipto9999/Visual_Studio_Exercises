#include <sstream>
#include <iostream>

#include "CppUnitTest.h"

extern "C" {
	#include "linkedlist.h"
}
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/**************************/
/* Precompiler Directives */
/**************************/

#define CORRECT_STRUCT_AIRPLANE_SIZE 28
#define CORRECT_STRUCT_NODE_SIZE     32
#define CORRECT_STRUCT_ELEMENT_SIZE  4

#define VANCOUVER_TO_TORONTO_PLANE { 100, "Vancouver", "Toronto", 1, 900, 36000, 350 }

#define TORONTO_TO_HALIFAX_PLANE { 200, "Toronto", "Halifax", 2, 800, 26000, 280 }

#define CALGARY_TO_HALIFAX_PLANE { 300, "Calgary", "Halifax", 2, 800, 26000, 280 }
#define CALGARY_TO_EDMONTON_PLANE { 300, "Calgary", "Edmonton", 3, 700, 30000, 200 }

#define KELOWNA_TO_PRINCE_GEORGE_PLANE { 400, "Kelowna", "Prince George", 4, 600, 20000, 100 }

/**************/
/* Unit Tests */
/**************/

namespace UnitTests {
	TEST_CLASS(ToDo_01_Struct_Airplane) {
		public:
		airplane test_airplane;

		TEST_METHOD(Test_1_Struct_Airplant_Size) {
			Assert::AreEqual((int)sizeof(test_airplane), CORRECT_STRUCT_AIRPLANE_SIZE);
		}

		TEST_METHOD(Test_2_Flight_Number_Type_Size) {
			Assert::AreEqual((int)sizeof(test_airplane.flight_number), CORRECT_STRUCT_ELEMENT_SIZE);
		}

		TEST_METHOD(Test_3_City_Origin_Type_Size) {
			Assert::AreEqual((int)sizeof(test_airplane.city_origin), CORRECT_STRUCT_ELEMENT_SIZE);
		}

		TEST_METHOD(Test_4_City_Destination_Type_Size) {
			Assert::AreEqual((int)sizeof(test_airplane.city_destination), CORRECT_STRUCT_ELEMENT_SIZE);
		}

		TEST_METHOD(Test_5_Priority_Type_Size) {
			Assert::AreEqual((int)sizeof(test_airplane.priority), CORRECT_STRUCT_ELEMENT_SIZE);
		}

		TEST_METHOD(Test_6_Maximum_Speed_KPH_Type_Size) {
			Assert::AreEqual((int)sizeof(test_airplane.maximum_speed_kph), CORRECT_STRUCT_ELEMENT_SIZE);
		}

		TEST_METHOD(Test_7_Cruising_Altitude_Type_Size) {
			Assert::AreEqual((int)sizeof(test_airplane.cruising_altitude), CORRECT_STRUCT_ELEMENT_SIZE);
		}

		TEST_METHOD(Test_8_Capacity_Type_Size) {
			Assert::AreEqual((int)sizeof(test_airplane.capacity), CORRECT_STRUCT_ELEMENT_SIZE);
		}
	};

	TEST_CLASS(ToDo_02_Struct_Node) {
		public:
		node test_node;

		TEST_METHOD(Test_1_Struct_Node_Size) {
			Assert::AreEqual((int)sizeof(test_node), CORRECT_STRUCT_NODE_SIZE);
		}

		TEST_METHOD(Test_2_Data_Size) {
			Assert::AreEqual((int)sizeof(test_node.plane), CORRECT_STRUCT_AIRPLANE_SIZE);
		}

		TEST_METHOD(Test_3_Pointer_Size) {
			Assert::AreEqual((int)sizeof(test_node.next), CORRECT_STRUCT_ELEMENT_SIZE);
		}
	};

	TEST_CLASS(ToDo_03_Create_Linked_List) {
		public:

		TEST_METHOD(Test_1_List_Empty) {
			node* test_list = create_linked_list();

			Assert::IsNull(test_list);
		}
	};

	TEST_CLASS(ToDo_04_Create_Node) {
		public:

		TEST_METHOD(Test_1_New_Node) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;
			node* test_node = create_node(test_airplane);

			Assert::IsNotNull(test_node);
		}

		TEST_METHOD(Test_2_New_Node_Pointer) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;
			node* test_node = create_node(test_airplane);

			Assert::IsNull(test_node->next);
		}

		TEST_METHOD(Test_3_New_Node_Plane_Flight_Number) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;
			node* test_node = create_node(test_airplane);

			Assert::AreEqual((test_node->plane).flight_number, test_airplane.flight_number);
		}

		TEST_METHOD(Test_4_New_Node_Plane_City_Origin) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;
			node* test_node = create_node(test_airplane);

			Assert::AreEqual((test_node->plane).city_origin, test_airplane.city_origin);
		}

		TEST_METHOD(Test_5_New_Node_Plane_City_Destination) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;
			node* test_node = create_node(test_airplane);

			Assert::AreEqual((test_node->plane).city_destination, test_airplane.city_destination);
		}

		TEST_METHOD(Test_6_New_Node_Plane_Priority) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;
			node* test_node = create_node(test_airplane);

			Assert::AreEqual((test_node->plane).priority, test_airplane.priority);
		}

		TEST_METHOD(Test_7_New_Node_Plane_Maximum_Speed_KPH) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;
			node* test_node = create_node(test_airplane);

			Assert::AreEqual((test_node->plane).maximum_speed_kph, test_airplane.maximum_speed_kph);
		}

		TEST_METHOD(Test_8_New_Node_Plane_Cruising_Altitude) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;
			node* test_node = create_node(test_airplane);

			Assert::AreEqual((test_node->plane).cruising_altitude, test_airplane.cruising_altitude);
		}

		TEST_METHOD(Test_9_New_Node_Plane_Capacity) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;
			node* test_node = create_node(test_airplane);

			Assert::AreEqual((test_node->plane).capacity, test_airplane.capacity);
		}
	};

	TEST_CLASS(ToDo_05_Prepend_Node) {
		public:

		TEST_METHOD(Test_1_List_Empty) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = prepend_node(test_list, test_node);

			Assert::AreEqual((int)test_list, (int)test_node);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane.capacity);

			Assert::IsNull(test_list->next);
		}

		TEST_METHOD(Test_2_List_NonEmpty) {
			airplane test_airplane_one = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			Assert::AreEqual((int)test_list, (int)test_node_three);

			Assert::AreEqual((test_list->plane).city_origin, test_airplane_three.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_three.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_three.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_three.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_three.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_three.capacity);

			test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_two);

			Assert::AreEqual((test_list->plane).city_origin, test_airplane_two.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_two.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_two.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_two.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_two.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_two.capacity);

			test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_one);

			Assert::AreEqual((test_list->plane).city_origin, test_airplane_one.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_one.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_one.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_one.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_one.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_one.capacity);

			Assert::IsNull(test_list->next);
		}
	};

	TEST_CLASS(ToDo_06_Delete_Node) {
		public:

		TEST_METHOD(Test_1_List_Empty) {
			node* test_list = create_linked_list();

			test_list = delete_node(test_list);
			Assert::IsNull(test_list);
		}

		TEST_METHOD(Test_2_List_Length_One) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = prepend_node(test_list, test_node);

			test_list = delete_node(test_list);
			Assert::IsNull(test_list);
		}

		TEST_METHOD(Test_3_List_Length_Three) {
			airplane test_airplane_one = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_HALIFAX_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			test_list = delete_node(test_list);

			Assert::IsNotNull(test_list);

			Assert::AreEqual((int)test_list, (int)test_node_two);

			Assert::AreEqual((test_list->plane).city_origin, test_airplane_two.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_two.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_two.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_two.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_two.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_two.capacity);

			test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_one);

			Assert::AreEqual((test_list->plane).city_origin, test_airplane_one.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_one.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_one.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_one.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_one.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_one.capacity);

			Assert::IsNull(test_list->next);
		}
	};

	TEST_CLASS(ToDo_07_length_list) {
		public:

		TEST_METHOD(Test_1_Empty_List) {
			node* test_list = create_linked_list();

			int length = length_list(test_list);

			Assert::IsNull(test_list);
			Assert::AreEqual(length, 0);
		}

		TEST_METHOD(Test_2_List_Length_One) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = prepend_node(test_list, test_node);

			int length = length_list(test_list);

			Assert::IsNotNull(test_list);
			Assert::AreEqual(length, 1);
		}

		TEST_METHOD(Test_3_List_Length_Three) {
			airplane test_airplane_one = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two = TORONTO_TO_HALIFAX_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);

			int length = length_list(test_list);

			Assert::IsNotNull(test_list);
			Assert::AreEqual(length, 2);
		}
	};

	TEST_CLASS(ToDo_08_Delete_List) {
		public:

		TEST_METHOD(Test_1_List_Empty) {
			node* test_list = create_linked_list();
			test_list = delete_list(test_list);

			int length = length_list(test_list);

			Assert::AreEqual(length, 0);
			Assert::IsNull(test_list);
		}

		TEST_METHOD(Test_2_List_Length_One) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = prepend_node(test_list, test_node);
			test_list = delete_list(test_list);

			int length = length_list(test_list);

			Assert::AreEqual(length, 0);
			Assert::IsNull(test_list);
		}

		TEST_METHOD(Test_3_List_Length_Three) {
			airplane test_airplane_one = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			test_list = delete_list(test_list);

			int length = length_list(test_list);

			Assert::AreEqual(length, 0);
			Assert::IsNull(test_list);
		}
	};

	TEST_CLASS(ToDo_11_Reverse_List) {
		public:

		TEST_METHOD(Test_1_List_Empty) {
			node* test_list = create_linked_list();

			test_list = reverse_list(test_list);

			int length = length_list(test_list);

			Assert::AreEqual(length, 0);
			Assert::IsNull(test_list);
		}

		TEST_METHOD(Test_2_List_Length_One) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = prepend_node(test_list, test_node);
			test_list = reverse_list(test_list);

			int length = length_list(test_list);

			Assert::AreEqual(length, 1);
			Assert::IsNotNull(test_list);
		}

		TEST_METHOD(Test_3_List_Length_Three_Not_Null) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_HALIFAX_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			test_list = reverse_list(test_list);

			int length = length_list(test_list);

			Assert::AreEqual(length, 3);
			Assert::IsNotNull(test_list);
		}

		TEST_METHOD(Test_4_List_Length_Three_Head_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_HALIFAX_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			test_list = reverse_list(test_list);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_one.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_one.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_one.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_one.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_one.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_one.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_one.capacity);

			Assert::AreEqual((int)test_list->next, (int)test_node_two);
			Assert::IsNull(test_list->next->next->next);
		}

		TEST_METHOD(Test_5_List_Length_Three_Middle_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_HALIFAX_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			test_list = reverse_list(test_list);

			test_list = test_list->next;

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_two.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_two.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_two.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_two.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_two.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_two.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_two.capacity);

			Assert::AreEqual((int)test_list->next, (int)test_node_three);
			Assert::IsNull(test_list->next->next);
		}

		TEST_METHOD(Test_6_List_Length_Three_Tail_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			test_list = reverse_list(test_list);

			for (int i = 0; i < 2; i++) test_list = test_list->next;

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_three.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_three.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_three.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_three.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_three.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_three.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_three.capacity);

			Assert::IsNull(test_list->next);
		}
	};

	TEST_CLASS(ToDo_12_Remove_From_List) {
		public:

		TEST_METHOD(Test_1_List_Empty) {
			node* test_list = create_linked_list();
			test_list = remove_from_list(test_list, "Vancouver");

			Assert::IsNull(test_list);
		}

		TEST_METHOD(Test_2_List_Length_One_Positive) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = prepend_node(test_list, test_node);
			test_list = remove_from_list(test_list, "Toronto");

			int length = length_list(test_list);

			Assert::AreEqual(length, 0);
			Assert::IsNull(test_list);
		}

		TEST_METHOD(Test_3_List_Length_One_Negative) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = prepend_node(test_list, test_node);
			test_list = remove_from_list(test_list, "Vancouver");

			int length = length_list(test_list);

			Assert::AreEqual(length, 1);
			Assert::IsNotNull(test_list);
		}

		TEST_METHOD(Test_4_List_Length_Three_Positive_Head_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			test_list = remove_from_list(test_list, "Edmonton");

			int length = length_list(test_list);
			Assert::AreEqual(length, 2);

			Assert::AreEqual((int)test_list, (int)test_node_two);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_two.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_two.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_two.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_two.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_two.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_two.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_two.capacity);

			test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_one);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_one.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_one.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_one.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_one.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_one.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_one.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_one.capacity);

			Assert::IsNull(test_list->next);
		}

		TEST_METHOD(Test_5_List_Length_Three_Positive_Tail_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			test_list = remove_from_list(test_list, "Toronto");

			int length = length_list(test_list);
			Assert::AreEqual(length, 2);

			Assert::AreEqual((int)test_list, (int)test_node_three);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_three.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_three.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_three.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_three.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_three.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_three.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_three.capacity);

			test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_two);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_two.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_two.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_two.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_two.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_two.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_two.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_two.capacity);

			Assert::IsNull(test_list->next);
		}

		TEST_METHOD(Test_6_List_Length_Three_Positive_Middle_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			test_list = remove_from_list(test_list, "Halifax");

			int length = length_list(test_list);
			Assert::AreEqual(length, 2);

			Assert::AreEqual((int)test_list, (int)test_node_three);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_three.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_three.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_three.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_three.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_three.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_three.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_three.capacity);

			test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_one);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_one.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_one.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_one.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_one.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_one.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_one.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_one.capacity);

			Assert::IsNull(test_list->next);
		}

		TEST_METHOD(Test_7_List_Length_Three_Negative) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			test_list = remove_from_list(test_list, "Calgary");

			int length = length_list(test_list);

			Assert::AreEqual(length, 3);
			Assert::IsNotNull(test_list);
		}
	};

	TEST_CLASS(ToDo_13_Retrieve_nth) {
		public:

		TEST_METHOD(Test_1_List_Empty) {
			node* test_list = create_linked_list();

			node* result = retrieve_node(test_list, 1);

			int length = length_list(result);

			Assert::AreEqual(length, 0);
			Assert::IsNull(result);
		}

		TEST_METHOD(Test_2_List_Length_One_Positive) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = prepend_node(test_list, test_node);

			node* result = retrieve_node(test_list, 1);
			Assert::IsNotNull(result);

			int length = length_list(result);
			Assert::AreEqual(length, 1);

			Assert::AreEqual((int)result, (int)test_node);

			Assert::AreEqual((result->plane).flight_number, test_airplane.flight_number);
			Assert::AreEqual((result->plane).city_origin, test_airplane.city_origin);
			Assert::AreEqual((result->plane).city_destination, test_airplane.city_destination);
			Assert::AreEqual((result->plane).priority, test_airplane.priority);
			Assert::AreEqual((result->plane).maximum_speed_kph, test_airplane.maximum_speed_kph);
			Assert::AreEqual((result->plane).cruising_altitude, test_airplane.cruising_altitude);
			Assert::AreEqual((result->plane).capacity, test_airplane.capacity);

			Assert::IsNull(result->next);
		}

		TEST_METHOD(Test_3_List_Length_One_Negative) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = prepend_node(test_list, test_node);

			node* result = retrieve_node(test_list, 2);
			Assert::IsNull(result);
		}

		TEST_METHOD(Test_4_List_Length_Three_Positive_Head_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			node* result = retrieve_node(test_list, 1);
			Assert::IsNotNull(result);

			int length = length_list(result);
			Assert::AreEqual(length, 3);

			Assert::AreEqual((int)result, (int)test_node_three);

			Assert::AreEqual((result->plane).flight_number, test_airplane_three.flight_number);
			Assert::AreEqual((result->plane).city_origin, test_airplane_three.city_origin);
			Assert::AreEqual((result->plane).city_destination, test_airplane_three.city_destination);
			Assert::AreEqual((result->plane).priority, test_airplane_three.priority);
			Assert::AreEqual((result->plane).maximum_speed_kph, test_airplane_three.maximum_speed_kph);
			Assert::AreEqual((result->plane).cruising_altitude, test_airplane_three.cruising_altitude);
			Assert::AreEqual((result->plane).capacity, test_airplane_three.capacity);

			Assert::AreEqual((int)result->next, (int)test_node_two);

			Assert::IsNull(result->next->next->next);
		}

		TEST_METHOD(Test_5_List_Length_Three_Positive_Middle_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			node* result = retrieve_node(test_list, 2);
			Assert::IsNotNull(result);

			int length = length_list(result);
			Assert::AreEqual(length, 2);

			Assert::AreEqual((int)result, (int)test_node_two);

			Assert::AreEqual((result->plane).flight_number, test_airplane_two.flight_number);
			Assert::AreEqual((result->plane).city_origin, test_airplane_two.city_origin);
			Assert::AreEqual((result->plane).city_destination, test_airplane_two.city_destination);
			Assert::AreEqual((result->plane).priority, test_airplane_two.priority);
			Assert::AreEqual((result->plane).maximum_speed_kph, test_airplane_two.maximum_speed_kph);
			Assert::AreEqual((result->plane).cruising_altitude, test_airplane_two.cruising_altitude);
			Assert::AreEqual((result->plane).capacity, test_airplane_two.capacity);

			Assert::AreEqual((int)result->next, (int)test_node_one);

			Assert::IsNull(result->next->next);
		}

		TEST_METHOD(Test_6_List_Length_Three_Positive_Tail_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			node* result = retrieve_node(test_list, 3);
			Assert::IsNotNull(result);

			int length = length_list(result);
			Assert::AreEqual(length, 1);

			Assert::AreEqual((int)result, (int)test_node_one);

			Assert::AreEqual((result->plane).flight_number, test_airplane_one.flight_number);
			Assert::AreEqual((result->plane).city_origin, test_airplane_one.city_origin);
			Assert::AreEqual((result->plane).city_destination, test_airplane_one.city_destination);
			Assert::AreEqual((result->plane).priority, test_airplane_one.priority);
			Assert::AreEqual((result->plane).maximum_speed_kph, test_airplane_one.maximum_speed_kph);
			Assert::AreEqual((result->plane).cruising_altitude, test_airplane_one.cruising_altitude);
			Assert::AreEqual((result->plane).capacity, test_airplane_one.capacity);

			Assert::IsNull(result->next);
		}

		TEST_METHOD(Test_7_List_Length_Three_Negative) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);

			node* result = retrieve_node(test_list, 4);
			Assert::IsNull(result);
		}
	};

	TEST_CLASS(ToDo_14_Insert_nth) {
		public:

		TEST_METHOD(Test_1_List_Empty_Positive) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = insert_node(test_list, test_node, 1);
			Assert::IsNotNull(test_list);

			int length = length_list(test_list);
			Assert::AreEqual(length, 1);

			Assert::AreEqual((int)test_list, (int)test_node);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane.capacity);

			Assert::IsNull(test_list->next);
		}

		TEST_METHOD(Test_2_List_Empty_Negative) {
			airplane test_airplane = VANCOUVER_TO_TORONTO_PLANE;

			node* test_list = create_linked_list();
			node* test_node = create_node(test_airplane);

			test_list = insert_node(test_list, test_node, 2);
			Assert::IsNull(test_list);
		}

		TEST_METHOD(Test_3_List_Length_One_Head_Node) {
			airplane test_airplane_one = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two = TORONTO_TO_HALIFAX_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);

			test_list = prepend_node(test_list, test_node_one);
			test_list = insert_node(test_list, test_node_two, 1);

			int length = length_list(test_list);
			Assert::AreEqual(length, 2);

			Assert::AreEqual((int)test_list, (int)test_node_two);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_two.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_two.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_two.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_two.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_two.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_two.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_two.capacity);

			test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_one);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_one.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_one.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_one.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_one.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_one.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_one.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_one.capacity);

			Assert::IsNull(test_list->next);
		}

		TEST_METHOD(Test_4_List_Length_One_Tail_Node) {
			airplane test_airplane_one = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two = TORONTO_TO_HALIFAX_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one = create_node(test_airplane_one);
			node* test_node_two = create_node(test_airplane_two);

			test_list = prepend_node(test_list, test_node_one);
			test_list = insert_node(test_list, test_node_two, 2);

			int length = length_list(test_list);
			Assert::AreEqual(length, 2);

			Assert::AreEqual((int)test_list, (int)test_node_one);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_one.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_one.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_one.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_one.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_one.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_one.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_one.capacity);

			test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_two);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_two.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_two.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_two.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_two.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_two.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_two.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_two.capacity);

			Assert::IsNull(test_list->next);
		}

		TEST_METHOD(Test_5_List_Length_Four_Negative) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;
			airplane test_airplane_four  = CALGARY_TO_HALIFAX_PLANE;
			airplane test_airplane_five  = KELOWNA_TO_PRINCE_GEORGE_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one   = create_node(test_airplane_one);
			node* test_node_two   = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);
			node* test_node_four  = create_node(test_airplane_four);
			node* test_node_five  = create_node(test_airplane_five);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);
			test_list = prepend_node(test_list, test_node_four);

			int length = length_list(test_list);
			Assert::AreEqual(length, 4);

			test_list = insert_node(test_list, test_node_five, 6);

			length = length_list(test_list);
			Assert::AreEqual(length, 4);
		}

		TEST_METHOD(Test_6_List_Length_Four_Positive_Head_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;
			airplane test_airplane_four  = CALGARY_TO_HALIFAX_PLANE;
			airplane test_airplane_five  = KELOWNA_TO_PRINCE_GEORGE_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one   = create_node(test_airplane_one);
			node* test_node_two   = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);
			node* test_node_four  = create_node(test_airplane_four);
			node* test_node_five  = create_node(test_airplane_five);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);
			test_list = prepend_node(test_list, test_node_four);

			int length = length_list(test_list);
			Assert::AreEqual(length, 4);

			test_list = insert_node(test_list, test_node_five, 1);

			length = length_list(test_list);
			Assert::AreEqual(length, 5);

			Assert::AreEqual((int)test_list, (int)test_node_five);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_five.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_five.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_five.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_five.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_five.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_five.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_five.capacity);

			test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_four);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_four.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_four.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_four.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_four.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_four.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_four.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_four.capacity);

			Assert::IsNull(test_list->next->next->next->next);
		}

		TEST_METHOD(Test_7_List_Length_Four_Positive_Middle_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;
			airplane test_airplane_four  = CALGARY_TO_HALIFAX_PLANE;
			airplane test_airplane_five  = KELOWNA_TO_PRINCE_GEORGE_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one   = create_node(test_airplane_one);
			node* test_node_two   = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);
			node* test_node_four  = create_node(test_airplane_four);
			node* test_node_five  = create_node(test_airplane_five);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);
			test_list = prepend_node(test_list, test_node_four);

			int length = length_list(test_list);
			Assert::AreEqual(length, 4);

			test_list = insert_node(test_list, test_node_five, 3);

			length = length_list(test_list);
			Assert::AreEqual(length, 5);

			Assert::AreEqual((int)test_list, (int)test_node_four);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_four.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_four.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_four.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_four.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_four.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_four.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_four.capacity);

			for (int i = 0; i < 2; i++) test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_five);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_five.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_five.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_five.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_five.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_five.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_five.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_five.capacity);

			test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_two);

			Assert::IsNull(test_list->next->next);
		}

		TEST_METHOD(Test_8_List_Length_Four_Positive_Middle_Node) {
			airplane test_airplane_one   = VANCOUVER_TO_TORONTO_PLANE;
			airplane test_airplane_two   = TORONTO_TO_HALIFAX_PLANE;
			airplane test_airplane_three = CALGARY_TO_EDMONTON_PLANE;
			airplane test_airplane_four  = CALGARY_TO_HALIFAX_PLANE;
			airplane test_airplane_five  = KELOWNA_TO_PRINCE_GEORGE_PLANE;

			node* test_list = create_linked_list();

			node* test_node_one   = create_node(test_airplane_one);
			node* test_node_two   = create_node(test_airplane_two);
			node* test_node_three = create_node(test_airplane_three);
			node* test_node_four  = create_node(test_airplane_four);
			node* test_node_five  = create_node(test_airplane_five);

			test_list = prepend_node(test_list, test_node_one);
			test_list = prepend_node(test_list, test_node_two);
			test_list = prepend_node(test_list, test_node_three);
			test_list = prepend_node(test_list, test_node_four);

			int length = length_list(test_list);
			Assert::AreEqual(length, 4);

			test_list = insert_node(test_list, test_node_five, 5);

			length = length_list(test_list);
			Assert::AreEqual(length, 5);

			Assert::AreEqual((int)test_list, (int)test_node_four);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_four.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_four.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_four.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_four.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_four.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_four.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_four.capacity);

			for (int i = 0; i < 4; i++) test_list = test_list->next;

			Assert::AreEqual((int)test_list, (int)test_node_five);

			Assert::AreEqual((test_list->plane).flight_number, test_airplane_five.flight_number);
			Assert::AreEqual((test_list->plane).city_origin, test_airplane_five.city_origin);
			Assert::AreEqual((test_list->plane).city_destination, test_airplane_five.city_destination);
			Assert::AreEqual((test_list->plane).priority, test_airplane_five.priority);
			Assert::AreEqual((test_list->plane).maximum_speed_kph, test_airplane_five.maximum_speed_kph);
			Assert::AreEqual((test_list->plane).cruising_altitude, test_airplane_five.cruising_altitude);
			Assert::AreEqual((test_list->plane).capacity, test_airplane_five.capacity);

			Assert::IsNull(test_list->next);
		}
	};
}