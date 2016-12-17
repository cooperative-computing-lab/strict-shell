#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "hash_table.h"

struct node {
	struct hash_table *hash_table;
	struct node *next;	
	int params;
};

struct node *head;

#endif
