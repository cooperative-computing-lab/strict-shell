#include "symbol.h"
#include <string.h>

struct symbol * symbol_create( symbol_t kind, struct type *type, char *name, struct decl *params ) {
	struct symbol * sym = malloc(sizeof * sym);
	sym -> name = name;
	sym -> type = type;
	sym -> kind = kind;
	sym -> params = params;
	return sym;
}

int symbol_compare(struct symbol *s1, struct symbol *s2){
	if (!s1 || !s2) return 0;

	if (!(s1->name) && !(s2->name)) {
		return (s1->kind == s2->kind) && (s1->which == s2->which) && type_compare(s1->type, s2->type);
	} else if (!(s1->name) || !(s2->name)) {
		return 0;
	} else {
		return (s1->kind == s2->kind) && (s1->which == s2->which) && type_compare(s1->type, s2->type) && !strcmp(s1->name, s2->name);
	}
}
