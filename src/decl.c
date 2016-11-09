#include "decl.h"
#include "expr.h"
#include <string.h>
#include <stdio.h>

struct decl * decl_create( char *name, struct type *t, struct expr *v, struct stmt *c, struct stmt *next ) {
	struct decl * new_decl = malloc(sizeof *new_decl);
	new_decl -> name = name;
	new_decl -> type = t; 
	new_decl -> value = v;
	new_decl -> code = c;
	new_decl -> next = next;
	return new_decl;
}


