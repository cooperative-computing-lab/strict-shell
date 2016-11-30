#include "decl.h"
#include "expr.h"
#include "param_list.h"
#include <string.h>
#include <stdio.h>

struct decl * decl_create( char *name, struct type *t, struct decl *p, struct type *st, struct expr *expr, struct expr *v,  struct stmt *c, struct decl *next){
	struct decl * new_decl = malloc(sizeof *new_decl);
	new_decl -> name = name;
	new_decl -> type = t; 
	new_decl -> params = p;
	new_decl -> subtype = st;
	new_decl -> expr = expr;
	new_decl -> value = v;
	new_decl -> code = c;
	new_decl -> next = next;
	return new_decl;
}
struct decl * decl_create_array( char *name, struct type *t, struct decl *p, struct type *st, struct expr *expr, struct expr *v,  struct stmt *c, struct decl *next){
	struct decl * new_decl = malloc(sizeof *new_decl);
	new_decl -> name = name;
	new_decl -> type = type_create(TYPE_ARRAY); 
	new_decl -> params = p;
	new_decl -> subtype = st;
	new_decl -> expr = expr;
	new_decl -> value = v;
	new_decl -> code = c;
	new_decl -> next = next;
	return new_decl;
}
struct decl * decl_create_func( char *name, struct type *t, struct decl *p, struct type *st, struct expr *expr, struct expr *v,  struct stmt *c, struct decl *next){
	struct decl * new_decl = malloc(sizeof *new_decl);
	new_decl -> name = name;
	new_decl -> type = type_create(TYPE_FUNCTION); 
	new_decl -> params = p;
	new_decl -> subtype = st;
	new_decl -> expr = expr;
	new_decl -> value = v;
	new_decl -> code = c;
	new_decl -> next = next;
	return new_decl;
}


void decl_print(struct decl *d, int indent, int param){
	int i = indent;
	if (!d) return;
	for(; i>0; i--) printf("\t");

	if (d->subtype) type_print(d->subtype);
	else type_print(d->type);
	printf(" %s", d->name);

	if (d->params) {
		printf("(");
		if (d->params) decl_print_params(d->params);
		printf(")");
	}
	if (d->expr) {
		printf("[");
		decl_print_elems(d->expr);
		printf("]");
	}
	if (d->type->kind == TYPE_FUNCTION) {
		printf("{");
		if (d->code) {
			printf("\n");	
			stmt_print(d->code, indent+1);
		}
		printf("}\n");
	} else if (d->value) {
		 printf(" = ");
		 expr_print(d->value);
		 if (!param) printf(";\n");
	} else {
		if (!param) printf(";\n");
	}
	

	if (!d->next) return;
}

void decl_print_params(struct decl *p){


	decl_print(p, 0, 1);
	if (!p->next) return;
	else printf(", ");
	decl_print_params(p->next);

}

void decl_print_elems(struct expr *e){

	if (!e) return;

	expr_print(e);
	//printf(", ");
	//decl_print_elems(e->next);

}
