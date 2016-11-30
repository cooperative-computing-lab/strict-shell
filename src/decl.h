
#ifndef DECL_H
#define DECL_H

#include "type.h"
#include "stmt.h"
#include "param_list.h"
#include "expr.h"
#include <stdio.h>

struct decl {
	char *name;
	struct type *type;

	struct decl *params;
	struct type *subtype;
	struct expr *expr;

	struct expr *value;
	struct stmt *code;
	struct symbol *symbol;
	struct decl *next;
};

struct decl * decl_create( char *name, struct type *t, struct decl *p, struct type *st, struct expr *expr, struct expr *v,  struct stmt *c, struct decl *next);
struct decl * decl_create_func( char *name, struct type *t, struct decl *p, struct type *st, struct expr *expr, struct expr *v,  struct stmt *c, struct decl *next);
struct decl * decl_create_array( char *name, struct type *t, struct decl *p, struct type *st, struct expr *expr, struct expr *v,  struct stmt *c, struct decl *next);
void decl_print(struct decl *d, int indent, int param);
void decl_print_params(struct decl *p);
void decl_print_elems(struct expr *e);
#endif


