#include "type.h"

struct type * type_create( type_kind_t kind, struct param_list *params, struct type *subtype) {
	struct type * new_type = malloc(sizeof * new_type);
	new_type -> kind = kind;
	new_type -> params = params;
	new_type -> subtype = subtype;
	new_type -> expr = NULL;
	return new_type;
}

