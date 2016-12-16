#include "type.h"

struct type * type_create( type_kind_t kind) {
	struct type * new_type = malloc(sizeof * new_type);
	new_type -> kind = kind;
	return new_type;
}

void type_print( struct type *t){
	switch(t->kind) {
		case TYPE_BOOLEAN:
			printf("bool");
			break;
		case TYPE_CHARACTER:
		    printf("char");
			break;
		case TYPE_INTEGER:
			printf("int");
		    break;
		case TYPE_STRING:
		    printf("string");
			break;
		case TYPE_ARRAY:
			break;
        case TYPE_FUNCTION:
		   	break;
		case TYPE_VOID:
			printf("void");
			break;
	}
}

struct type * type_copy(struct type *t) {
	return type_create(t->kind);
}

int type_compare(struct type *t1, struct type *t2) {
	if(!t1 || !t2) return 0;
	return t1->kind == t2->kind;
}

