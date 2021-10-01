/*
 * File: linkedlist.h
 * Purpose: Prototypes For a Linked List Implementation
 * Author: Muntakim Rahman
 * Date: July 2nd 2021
 */

#pragma once

/*************************/
/* Structure Definitions */
/************************/

typedef struct airplane {
	int flight_number;

	char* city_origin;
	char* city_destination;

	int priority;

	int maximum_speed_kph;
	int cruising_altitude;

	int capacity;
} airplane;

typedef struct node {
	airplane plane;
	struct node* next;
} node;

/***********************/
/* Function Prototypes */
/***********************/

node* create_linked_list();
node* create_node(airplane plane);
node* prepend_node(node* list, node* new_node);

int length_list(node* list);

node* delete_node(node* list);
node* delete_list(node* list);
node* remove_from_list(node* list, char* destination_city);

node* retrieve_node(node* list, int ordinality);
node* insert_node(node* list, node* node_to_insert, int ordinality);

node* reverse_list(node* list);

void print_node(node* node_to_print);
void print_list(node* list_to_print);
