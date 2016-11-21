#include "type.h"

struct type * type_create( type_kind_t kind, struct param_list *params, struct type *subtype) {
	struct type * new_type = malloc(sizeof * new_type);
	new_type -> kind = kind;
	new_type -> params = params;
	new_type -> subtype = subtype;
	new_type -> expr = NULL;
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
