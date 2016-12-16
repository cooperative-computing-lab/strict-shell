#ifndef TYPE_H
#define TYPE_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_FLOAT,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION,
	TYPE_VOID
} type_kind_t;

struct type {
	type_kind_t kind;
};

struct type * type_create(type_kind_t kind);
void type_print(struct type *t);
int type_compare(struct type *t1, struct type *t2);
struct type * type_copy(struct type *t);


#endif
