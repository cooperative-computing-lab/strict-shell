
#ifndef DECL_H
#define DECL_H

#include "type.h"
#include "stmt.h"
#include "expr.h"
#include <stdio.h>

struct decl {
	char *name;
	struct type *type;
	struct expr *value;
	struct stmt *code;
	struct symbol *symbol;
	struct stmt *next;
};

struct decl * decl_create( char *name, struct type *t, struct expr *v, struct stmt *c, struct stmt *next );

#endif


