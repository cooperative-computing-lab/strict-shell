#include "decl.h"
#include "expr.h"
#include <string.h>
#include <stdio.h>

struct decl * decl_create( char *name, struct type *t, struct expr *v, struct stmt *p, struct stmt *c, struct stmt *next) {
	struct decl * new_decl = malloc(sizeof *new_decl);
	new_decl -> name = name;
	new_decl -> type = t; 
	new_decl -> value = v;
	new_decl -> params = p;
	new_decl -> code = c;
	new_decl -> next = next;
	return new_decl;
}


void decl_print( struct decl *d, int indent, int param){
	int i = indent;
	if (!d) return;
	for(; i>0; i--) printf("\t");

	type_print(d->type);
	printf(" %s", d->name);

	if (d->params) {
		printf("(");
		decl_print(d->params->decl, 0, 1);
		printf(")");
	}
	if (d->code) {
		printf("{\n");
		stmt_print(d->code, indent+1);
		printf("}\n");
	} else if (d->value) {
		 printf(" = ");
		 expr_print(d->value);
		 printf(";\n");
	} else {
		if (!param) printf(";\n");
	}
	

	if (!d->next) return;
	else {
		if (param) printf(", ");
		decl_print(d->next->decl, indent, param);
	}
}
