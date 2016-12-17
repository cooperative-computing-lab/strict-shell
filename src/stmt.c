#include "stmt.h"
#include "expr.h"
#include "decl.h"

extern int errors;

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
	if (!s) return;
	int i = indent;
	switch (s->kind) {
		case STMT_DECL:
			decl_print(s->decl, indent, 0);
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

	struct value * v = malloc(sizeof * v);
	
	switch(s->kind) {
		case STMT_DECL:
			break;
		case STMT_EXPR:
			v = expr_evaluate(s->expr);
			/*switch (v->kind) {
				case VAL_INT:
					printf("%d", v->value_int);
					break;
				case VAL_FLOAT:
					printf("%f", v->value_float);
					break;
				case VAL_BOOL:
					printf("%d", v->value_bool);
					break;
				case VAL_CHAR:
					printf("%c", v->value_char);
					break;
				case VAL_STR:
					fprintf(stderr, "ERROR: unimplemented");
					exit(1);
					break;
			}*/
			break;
		case STMT_IF_ELSE:
			v = expr_evaluate(s->expr);
			if (v->kind == VAL_BOOL && v->value_bool > 0) {
				stmt_evaluate(s->body);
			} else {
				stmt_evaluate(s->else_body);
			}
			// error check, check other types
		case STMT_FOR:
			break;
		case STMT_WHILE:
			fprintf(stderr, "ERROR: unimplemented");
			exit(1);
			break;
		case STMT_PRINT:
			break;
		case STMT_RETURN:
			break;
		case STMT_BLOCK:
			break;
		case STMT_CASE:
			fprintf(stderr, "ERROR: unimplemented");
			exit(1);
			break;
		case STMT_SWITCH:
			fprintf(stderr, "ERROR: unimplemented");
			exit(1);
			break;
		case STMT_BREAK:
			break;
		case STMT_EMPTY:
			break;

	}
	stmt_evaluate(s->next);
	return;
}

void stmt_resolve(struct stmt *s) {
	if(!s) return;

	switch(s->kind) {
		case STMT_DECL:
			decl_resolve(s->decl);
			break;
		case STMT_EXPR:
			expr_resolve(s->expr);
			break;
		case STMT_EXEC:
			expr_resolve(s->expr);
			break;
		case STMT_IF_ELSE:
			expr_resolve(s->expr);

			scope_enter();
			stmt_resolve(s->body);
			scope_exit();

			scope_enter();
			stmt_resolve(s->else_body);
			scope_exit();
			break;
		case STMT_FOR:
			expr_resolve(s->init_expr);
			expr_resolve(s->expr);
			expr_resolve(s->next_expr);
			stmt_resolve(s->body);
			break;
		case STMT_PRINT:
			expr_resolve(s->expr);
			break;
		case STMT_RETURN:
			expr_resolve(s->expr);
			break;
		case STMT_BLOCK:
			scope_enter();
			stmt_resolve(s->body);
			scope_exit();
			break;
		case STMT_CASE:
			fprintf(stderr, "ERROR: unimplemented");
			exit(1);
			break;
		case STMT_SWITCH:
			fprintf(stderr, "ERROR: unimplemented");
			exit(1);
			break;
		case STMT_WHILE:
			fprintf(stderr, "ERROR: unimplemented");
			exit(1);
			break;
	}
	stmt_resolve(s->next);
}


struct type *stmt_typecheck(struct stmt *s) {
	if (!s) return 0;

	struct type *s_next = stmt_typecheck(s->next);

	decl_typecheck(s->decl);
	expr_typecheck(s->init_expr);
	struct type * expr_recurse = expr_typecheck(s->expr);
	expr_typecheck(s->next_expr);

	/* possible type conflicts in stmt */
	struct type *next_expr;

	switch (s->kind) {
		case STMT_RETURN:
			next_expr = expr_typecheck(s->expr);
			if(!s_next || next_expr->kind == s_next->kind) {
				s_next = next_expr;
			} else {
				printf("ERROR: more than one type returned from function\n");
				errors++;
			}
			break;
		case STMT_PRINT:
			expr_typecheck(s->expr->left);
			break;
		case STMT_DECL:
			if (s->decl->type->kind == TYPE_FUNCTION){
				printf("ERROR: cannot declare a nested function\n");
				errors++;
			}
			break;
		case STMT_FOR:
			printf("ERROR: unimplemented");
			exit(1);
			break;
		case STMT_IF_ELSE:
			if (expr_recurse->kind != TYPE_BOOLEAN){
				printf("ERROR: cannot declare a condition of type ");
				type_print(expr_recurse);
				printf("\n");
				errors++;
			}
			break;
	}

	// body, else_body, next, not stmt-type specific
	struct type *body = stmt_typecheck(s->body);
	struct type *else_body = stmt_typecheck(s->else_body);
	if (body) {
		if (body->kind == s_next->kind || !s_next) {
			s_next = body;
		} else {
			printf("ERROR: more than one type returned from function\n");
			errors++;
		}
	}

	if (else_body) {
		if(else_body->kind == s_next->kind || !s_next) {
			s_next = else_body;
		} else {
			printf("ERROR: more than one type returned from function\n");
			errors++;
		}
	}

	return s_next;
}

