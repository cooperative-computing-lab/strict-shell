
#ifndef SYMBOL_H
#define SYMBOL_H

#include "type.h"

typedef enum {
	SYMBOL_LOCAL,
	SYMBOL_PARAM,
	SYMBOL_GLOBAL
} symbol_t;

struct symbol {
	symbol_t kind;
	int which;
	struct type *type;
	char *name;

	struct decl *params;
};

struct symbol * symbol_create( symbol_t kind, struct type *type, char *name, struct decl *params );
int symbol_compare(struct symbol *s1, struct symbol *s2);
#endif
