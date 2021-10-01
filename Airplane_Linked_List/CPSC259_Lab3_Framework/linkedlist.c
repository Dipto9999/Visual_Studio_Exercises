/*
 * File: linkedlist.c
 * Purpose: Implements the Linked List Functions Whose Prototypes
 *          Are Declared in the Included Header File.
 * Author: Muntakim Rahman
 * Date: July 2nd 2021
 */

/* Preprocessor Directives */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

/*
 * Main Function Drives The Program.  Every C Program Must Have One
 * Main Function.  A Project Will Not Compile Without One.
 *
 * In Our Program, the Main Function Does Nothing.  That's Because
 * Our Program Doesn't Do Anything.  We're Just Implementing a Linked
 * List and Testing It Using Our Unit Tests.
 *
 * PRE: NULL (no pre-conditions)
 * POST: NULL (no side-effects)
 * RETURN: IF the program exits correctly
 * 		   THEN 0 ELSE 1
 */
int main(void) {
	/* The System Command Forces the System to Pause. */
	system("pause");

	return 0;
}

/*
 * Returns a Pointer to a New, Empty Linked List of Struct Node.
 * PRE: NULL (no pre-conditions)
 * POST: NULL (no side-effects)
 * RETURN: pointer to a new, empty linked list of struct node (NULL).
 */
node* create_linked_list() {
	return NULL;
}

/*
 * Returns a Dynamically Allocated Struct Node That Contains the Specified
 * Struct Airplane.  The Node's Next Pointer Doesn't Point to Anything (e.g., It Is Equal to NULL).
 * PARAM: plane, a struct airplane
 * PRE: NULL (no pre-conditions)
 * POST: NULL (no side-effects)
 * RETURN: pointer to a dynamically allocated struct node a) that contains
 *         the specified struct airplane, and b) whose next pointer points to NULL.
 */
node* create_node(airplane plane) {
	// Dynamically Allocate Memory for Node.
	node* new_node = (node*)malloc(sizeof(node)) ;

	// Initialize Node with Default Members.
	new_node->plane = plane;
	new_node->next = NULL;

	return new_node;
}

/*
 * Prepends a Struct Node Passed As a Parameter To The List Passed As a
 * Parameter, and Returns a Pointer To The Result.
 * PARAM: list is a pointer to a (possibly empty) linked list of struct node.
 * PARAM: new_node is a pointer to a struct node.
 * PRE: new_node is not NULL.
 * POST: specified struct node is added to the beginning of the list
 *       and its next pointer points to the node that used to be first.
 * RETURN: pointer to a linked list which contains all of the nodes
 *         of the list passed as a parameter, plus a prepended node.
 */
node* prepend_node(node* list, node* new_node) {
	new_node->next = list;

	return new_node;
}

/*
 * Deletes The First Struct Node In The Specified List,
 * and Returns a Pointer to the Shortened List.
 * PARAM: list is a pointer to a (possibly empty) linked list of struct node
 * PRE: NULL
 * POST: list passed as a parameter has one fewer node, and the dynamically
 *       allocated memory which contained that removed node has been freed
 * RETURN: IF the list is empty
 *         THEN NULL, ELSE a pointer to the shortened list
 */
node* delete_node(node* list) {
	node* node_to_delete = list;

	if (list != NULL) {
		if (list->next != NULL) list = list->next;
		else list = NULL;
		// Deallocate Heap Memory for Node to Delete.
		free(node_to_delete);
	}

	return list;
}

/*
 * Returns the Number of Nodes In the Specified Linked List of Struct Node.
 * PARAM: list is a pointer to a (possibly empty) linked list of struct node.
 * PRE: NULL (no pre-conditions)
 * POST: NULL (no side-effects)
 * RETURN: length of the specified list, an int.
 */
int length_list(node* list) {
	/* Variables */
	int length = 0;
	node* current_node = list;

	// Traverse the Linked List.
	while (current_node != NULL) {
		current_node = current_node->next;
		length++;
	}

	return length;
}

/*
 * Deletes An Entire List.  This Function Iterates Along a List and Deallocates the
 * Memory Containing Each Struct Node.
 * PARAM: list is a pointer to a (possibly empty) linked list of struct node
 * PRE: NULL (no pre-conditions)
 * POST: memory containing all of the nodes in the list has been freed
 * RETURN: an empty list (NULL)
 */
node* delete_list(node* list) {
	while (list != NULL) list = delete_node(list);

	return list;
}

/*
 * Prints the Data Stored In a Node.  For the Struct Airplane in the Node,
 * Prints the Fields On Separate Lines.  For Each Field, Prints the Field Name
 * and the Field Value.  For the Pointer, Prints "Link = NULL\n" if the Pointer Points
 * to NULL, Else Prints "Link points to address xxx.\n", Where xxx is the Pointer Address
 * in Hexademical. If node_to_print is NULL, prints "The node is empty.\n"
 * PARAM: node_to_print is a pointer to a (possibly null) struct node.
 * PRE: NULL (no pre-conditions)
 * POST: Information about node_to_print has been printed to standard output.
 * RETURN: NULL
 */
void print_node(node * node_to_print) {
	if (node_to_print != NULL) {
		// Airplane Field Values.
		printf("Flight Number: %d\n", node_to_print->plane.flight_number);
		printf("City Origin: %s\n", node_to_print->plane.city_origin);
		printf("City Destination: %s\n", node_to_print->plane.city_destination);
		printf("Priority: %d\n", node_to_print->plane.priority);
		printf("Maximum Speed KPH: %d\n", node_to_print->plane.maximum_speed_kph);
		printf("Cruising Altitude: %d\n", node_to_print->plane.cruising_altitude);
		printf("Capacity: %d\n", node_to_print->plane.capacity);

	    // Pointer to Next Node.
		if (node_to_print->next != NULL) printf("Link points to address %p.\n", &(node_to_print->next));
		else printf("Link = NULL\n");
	}
	else {
		printf("The node is empty.\n");
	}
}

/*
 * Prints the Data Stored In All Nodes in the Specified List to Print.
 * For Each Node, Prints the Data Inside the Node the Same Way That It
 * is Printed by print_node.  If the List is empty, a Suitable Message
 * is Printed to Standard Output.
 * PARAM: node_to_print is a pointer to a (possibly empty)
 *        linked list of struct node.
 * PRE: NULL (no pre-conditions)
 * POST: Information about list_to_print has been printed to standard output.
 * RETURN: NULL
 */
void print_list(node* list_to_print) {
	/* Variables */
	node* node_to_print = list_to_print;

	int i;

	// Traverse List and Print Each Node.
	for (i = 0; i < length_list(list_to_print); i ++){
		print_node(node_to_print);
		node_to_print = node_to_print->next;
	}
}

/*
 * Reverses a List.
 * PARAM: list is a pointer to a (possibly empty) linked list of struct node
 * PRE:   NULL (no pre-conditions)
 * POST:  order of the nodes in the list passed as a parameter has been
 *        reversed.
 * RETURN: list of struct node that is the reverse of the list passed as a
 *         parameter.
 */
node* reverse_list(node* list) {
	// Reverse Not Required.
	if (length_list(list) <= 1) return list;

	/* Variables */
	node* previous_node = NULL;
	node* current_node = list;
	node* next_node = current_node->next;

	// Traverse List to Reverse Order.
	while (current_node != NULL) {
		// Store Next Node Address.
		next_node = current_node->next;
		// Current Node Points to Previous Node.
		current_node->next = previous_node;
		previous_node = current_node;
		current_node = next_node;
	}

	return previous_node;
}

/*
 * Removes Every Node From The List Which Contains An Airplane Destined For
 * The City Name Passed In The Second Parameter.
 * PARAM: list is a pointer to a (possibly empty) linked list of struct node.
 * PARAM: destination_city is a pointer to a null-terminated array of char.
 * PRE: NULL (no pre-conditions)
 * POST: any struct node in the list which contains an airplane struct
 *       destined for the destination_city is removed from the list, and
 *       the memory deallocated.
 * RETURN: a list of struct node that does not contain any struct node that
 *         has an airplane destined for the destination_city.
 */
node* remove_from_list(node* list, char* destination_city) {
	/* Variables */
	int length = length_list(list);

	// Empty Lists.
	if (length == 0) return list;
	// Single Node Lists.
	else if (length == 1 ) {
		if (strcmp((list->plane).city_destination, destination_city) == 0) list = delete_node(list);
		return list;
	}

	node* current_node = NULL;
	node* next_node = list;

	while (next_node != NULL) {
		// Found Plane With Destination City.
		if (strcmp((next_node->plane).city_destination, destination_city) == 0) next_node = delete_node(next_node);

		// Handle Edge Cases With NULL Pointers.
		if (current_node == NULL) {
			list = next_node;
		}
		else {
			current_node->next = next_node;
			if (next_node == NULL) return list;
		}

		// Traverse the List.
		current_node = next_node;
		next_node = next_node->next;
	}

	return list;
}

/*
 * Returns a Reference To a Node (But Does Not Remove It) In The
 * Specified List.  If The List Is Too Short, Returns NULL.
 * PARAM: list is a pointer to a (possibly empty) linked list of struct node.
 * PARAM: ordinality is an integer.
 * PRE: ordinality > 0
 * POST: NULL (no side-effects)
 * RETURN: IF ordinality <= length of list
 *         THEN a pointer to the nth node
 *         ELSE NULL
 */
node* retrieve_node(node* list, int ordinality) {
	/* Variables */
	int length = length_list(list);
	int i;

	node* nth = list;

	// List Does Not Have nth Node.
	if (ordinality > length) return NULL;

	for (i = 1; i < ordinality; i++) nth = nth->next;

	return nth;
}

/*
 * Inserts the Specified Node Into The Specified List of Nodes At The Specified Ordinality.
 * For Example :
 * 	If ordinality = 1 :
 * 		a simple prepend_node operation.
 * 	If ordinality = 3 :
 * 		when this function is finished, 3rd node in the list will be the node_to_insert.
 * 	If ordinality = length of the list + 1 :
 * 		node_to_insert is appended to the end of the list.
 *  If ordinality > length of the list + 1 :
 * 		function returns a pointer to the unchanged list.
 * PARAM: list is a pointer to a (possibly empty) linked list of struct node.
 * PARAM: ordinality is an integer.
 * PRE: ordinality > 0
 * PRE: node_to_insert is NEVER a null (it is always a correct node pointer).
 * POST: NULL (no side-effects)
 * RETURN: IF ordinality <= length of list + 1
 *         THEN a pointer to the list which contains the node_to_insert
 * 			in the correct location
 *         ELSE a pointer to the unchanged list
 */
node* insert_node(node* list, node* node_to_insert, int ordinality) {
	/* Variables */
	node* current_node;
	node* next_node;

	int length = length_list(list);
	int i;

	if (ordinality > (length + 1)) {
		// Return Unchanged List.
		return list;
	}
	else if (ordinality == 1) {
		// Prepend Node to List.
		return prepend_node(list, node_to_insert);
	}
	else if (ordinality == length + 1) {
		node_to_insert->next = NULL;
		// Traverse The List.
		current_node = retrieve_node(list, length);
		current_node->next = node_to_insert;
		return list;
	}

	// Traverse The List Until (n-1)th Position.
	current_node = retrieve_node(list, (ordinality-1));
	next_node = current_node -> next;

	// Insert Node at nth Position.
	current_node->next = node_to_insert;
	node_to_insert->next = next_node;

	return list;
}
