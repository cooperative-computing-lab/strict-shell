#include "scope.h"
#include "node.h"
#include "hash_table.h"
#include "stdio.h"

void scope_enter() {
	struct hash_table *h = hash_table_create(0,0);
	
	struct node *old_head = head;
	head = (struct node*)malloc(sizeof(struct node));
	head->hash_table = h;
	head->params = 0;
	head->next = old_head;
}

void scope_exit() {
	if (head) {
		struct node *old_head = head;
	    head = head->next;
		hash_table_delete(old_head->hash_table);
	    free(old_head);
	}
}

int scope_level() {
	int i = 0;
	struct node* n = head;

	while (n) {
		i++;
		n = n->next;
	}

	return i;
}

void scope_bind(const char *name, struct symbol *s) {

	if(head) {
		hash_table_insert(head->hash_table, name, s);
	}

	switch(s->kind) {
		case SYMBOL_LOCAL:
			s->which = hash_table_size(head->hash_table);
			printf("%s resolves to local %d\n", name, s->which - head->params);
			break;
		case SYMBOL_PARAM:
			s->which = hash_table_size(head->hash_table);
			printf("%s resolves to param %d\n", name, s->which);
			break;
		case SYMBOL_GLOBAL:
			printf("%s resolves to global %s\n", name, name);
			break;
	}
}

struct symbol *scope_lookup(const char *name) {
	struct node *n = head;
	struct symbol *s;

	while (n) {
		if((s = hash_table_lookup(n->hash_table, name))) return s;
		n = n->next;
	}
	return 0;
}

struct symbol *scope_lookup_local(const char *name) {
	if(!head) return 0;
	return hash_table_lookup(head->hash_table, name);
}

void scope_remove_local(const char *key) {
	if(!head) return;
	hash_table_remove(head->hash_table, key);
}
