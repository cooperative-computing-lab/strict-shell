#include "stmt.h"
#include "expr.h"
#include "decl.h"

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

void stmt_print ( struct stmt * s, int indent ){
	int i = indent;
	switch (s->kind) {
		case STMT_DECL:
			decl_print(s->decl, indent);
			break;
		case STMT_EXPR:
			for(; i > 0; --i) printf("\t");
			expr_print(s->expr);
			printf(";");
			if(s->next) printf("\n");
			break;
		case STMT_IF_ELSE:
			for(; i > 0; --i) printf("\t");
			printf("if (");
			expr_print(s->expr);
			printf(") ");
			stmt_print(s->body, indent);
			 if(s->else_body) {
				printf(" else ");
		   		stmt_print(s->else_body, indent);
			}
			break;
		case STMT_FOR:
			for(; i > 0; --i) printf("\t");
			printf("for (");
			expr_print(s->init_expr);
			printf("; ");
			expr_print(s->expr);
			printf("; ");
			expr_print(s->next_expr);
			printf(") ");
			stmt_print(s->body, indent);
			printf("\n");
			break;
		case STMT_WHILE:
			break;
		case STMT_PRINT:
			for(; i > 0; --i) printf("\t");
		    printf("print ");
			expr_print(s->expr);
			printf(";\n");
			break;
		case STMT_RETURN:
			for(; i > 0; --i) printf("\t");
		    printf("return ");
			expr_print(s->expr);
			printf(";\n");
			break;
		case STMT_BLOCK:
			break;
		case STMT_CASE:
			break;
		case STMT_SWITCH:
			break;
		case STMT_BREAK:
			for(; i > 0; --i) printf("\t");
		    printf("break ");
			printf(";\n");
			break;
		case STMT_EMPTY:
			break;
	}
	stmt_print(s->next, indent);

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


