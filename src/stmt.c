#include "stmt.h"
#include "expr.h"

struct stmt * stmt_create( stmt_kind_t kind, struct decl *d, struct expr *init_expr, struct expr *e, struct expr *next_expr, struct stmt *body, struct stmt *else_body ) {
	struct stmt * new_stmt = malloc(sizeof * new_stmt);
	new_stmt -> kind = kind;
	new_stmt -> decl = d;
	new_stmt -> init_expr = init_expr;
	new_stmt -> expr = e;
	new_stmt -> next_expr = next_expr;
	new_stmt -> body = body;
	new_stmt -> else_body = else_body;
	return new_stmt;
}


/*
Recursively evaluate an expression by performing
the desired operation and returning it up the tree.
*/
void stmt_evaluate( struct stmt *s ) {
	if(!s) return;

	struct value * v = expr_evaluate(s->expr);

	switch(s->kind) {
		case STMT_IF_ELSE:
			if (v->kind == VAL_BOOL && v->value_bool > 0) {
				stmt_evaluate(s->body);
			} else {
				stmt_evaluate(s->else_body);
			}
			// error check, check other types
		case STMT_DECL:
			break;
		case STMT_FOR:
			break;

	}
	return;
}


