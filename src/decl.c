#include "decl.h"
#include "expr.h"
#include <string.h>
#include <stdio.h>

extern int errors;

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

void decl_resolve(struct decl *d) {
	if (!d) return;

	if (scope_level() == 1) {
		d->symbol = symbol_create(SYMBOL_GLOBAL, d->type, d->name, d->params);

	} else {
		// nonglobal functions
		if (d->type->kind == TYPE_FUNCTION) {
			fprintf(stderr, "ERROR: cannot declare non-global function %s\n", d->name);
			exit(1);
		} else { // local vars
			d->symbol = symbol_create(SYMBOL_LOCAL, d->type, d->name, d->params);
		}
	}

	// redeclarations
	if(scope_lookup_local(d->name)) {
		if(d->type->kind == TYPE_FUNCTION && scope_lookup_local(d->name)) { 
		} else {
			fprintf(stderr, "ERROR: cannot declare %s more than once\n", d->name);
			exit(1);
		}
	}

	// finish the decl
	scope_bind(d->symbol->name, d->symbol);
	expr_resolve(d->value);

	if (d->code) {
		scope_enter();
		stmt_resolve(d->code);
		scope_exit();
	}
	decl_resolve(d->next);
}

struct type *decl_typecheck(struct decl *d) {
	if(!d) return type_create(TYPE_VOID);

	struct type *t;
	if (d->value) {
	 	struct type *expr_result = expr_typecheck(d->value);

		if (d->type->kind == expr_result->kind) {
			t = type_create(d->type->kind);
		} else { //typing conflict
			printf("ERROR: %s was given a ", d->name);
			type_print(expr_result);
			printf(" when expecting a(n) ");
			type_print(d->type);
		 	printf("\n");

			errors++;
		}
	} else if (d->expr) {
		struct type *t1 = type_create(TYPE_STRING);
		struct type *t2 = type_create(TYPE_ARRAY);

		if (type_compare(d->type, t1)  || type_compare(d->type, t2)){
			printf("ERROR: cannot declare array or execution of type");
			type_print(d->type);
			errors++;
		}
	} else if (d->code) {
		struct type *cd = stmt_typecheck(d->code);

		if (cd) {
			if (type_compare(d->type, cd) == 1) {
				t = type_create(d->type->kind);
			} else {
				printf("ERROR: %s returned ", d->name);
				type_print(cd);
				printf(" but a(n)");
				type_print(d->type);
				printf(" was expected\n");

				errors++;
			}

		} else {
			/*
			if(d->type->subtype->kind == TYPE_VOID) {
				t = type_create(TYPE_VOID);
			} else {
				printf("ERROR: missing return value in %s , expected a(n) ", d->name);
				type_print(d->type->subtype);

				errors++;
			}*/
		}
	} else { //has no code
		//arrays not implemented
	}
	decl_typecheck(d->next);
	return t;
}

