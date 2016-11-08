#include "expr.h"
#include "type.h"
#include <string.h>

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right ) {
	struct expr * new_expr = malloc(sizeof * new_expr);
	new_expr -> kind = kind;
	new_expr -> left = left;
	new_expr -> right = right;
	new_expr -> name = 0;
	new_expr -> symbol = 0;
	new_expr -> string_literal = 0;
	return new_expr;
}

struct expr * expr_create_name( const char *n ) {
	struct expr * new_expr = malloc(sizeof * new_expr);
	new_expr -> kind = EXPR_NAME;
	new_expr -> left = 0;
	new_expr -> right = 0;
	new_expr -> name = n;
	new_expr -> symbol = 0;
	new_expr -> string_literal = n;
	return new_expr;
}

struct expr * expr_create_boolean_literal( int c ) {
	struct expr * new_expr = malloc(sizeof * new_expr);
	new_expr -> kind = EXPR_BOOL;
	new_expr -> left = 0;
	new_expr -> right = 0;
	new_expr -> name = 0;
	new_expr -> symbol = 0;
	new_expr -> literal_value = c;
	new_expr -> string_literal = 0;
	return new_expr;
}

struct expr * expr_create_integer_literal( int c ) {
	struct expr * new_expr = malloc(sizeof * new_expr);
	new_expr -> kind = EXPR_INT;
	new_expr -> left = 0;
	new_expr -> right = 0;
	new_expr -> name = 0;
	new_expr -> symbol = 0;
	new_expr -> literal_value = c;
	new_expr -> string_literal = 0;
	return new_expr;
}

struct expr * expr_create_float_literal( float c ) {
	struct expr * new_expr = malloc(sizeof * new_expr);
	new_expr -> kind = EXPR_FLOAT;
	new_expr -> left = 0;
	new_expr -> right = 0;
	new_expr -> name = 0;
	new_expr -> symbol = 0;
	new_expr -> literal_value = c;
	new_expr -> string_literal = 0;
	return new_expr;
}

struct expr * expr_create_character_literal( int c ) {
	struct expr * new_expr = malloc(sizeof * new_expr);
	new_expr -> kind = EXPR_CHAR;
	new_expr -> left = 0;
	new_expr -> right = 0;
	new_expr -> name = 0;
	new_expr -> symbol = 0;
	new_expr -> literal_value = c;
	new_expr -> string_literal = 0;
	return new_expr;
}

struct expr * expr_create_string_literal( const char *str ) {
	struct expr * new_expr = malloc(sizeof * new_expr);
	new_expr -> kind = EXPR_STR;
	new_expr -> left = 0;
	new_expr -> right = 0;
	new_expr -> name = 0;
	new_expr -> symbol = 0;
	new_expr -> string_literal = str;
	return new_expr;
}

void expr_print( struct expr *e ) {
	if (!e) { return; }

	if (e->kind==EXPR_GROUP) {
		printf("(");
	}

	expr_print(e->left);
	
	switch (e->kind) {
		case EXPR_ADD:
			printf("+"); 
			break;
		case EXPR_SUB:	
			printf("-"); 
			break;
		case EXPR_MUL:	
			printf("*");
		   	break;
		case EXPR_DIV:	
			printf("/");
		   	break;
		case EXPR_EXP:	
			printf("^"); 
			break;
		case EXPR_MOD:	
			printf("%"); 
			break;
		case EXPR_GT:	
			printf(">"); 
			break;
		case EXPR_GE:	
			printf(">="); 
			break;
		case EXPR_LT:	
			printf("<"); 
			break;
		case EXPR_LE:	
			printf("<="); 
			break;
		case EXPR_NE:	
			printf("!="); 
			break;
		case EXPR_EQ:	
			printf("=="); 
			break;
		case EXPR_AND:	
			printf("&&"); 
			break;
		case EXPR_OR:	
			printf("||"); 
			break;
		case EXPR_NOT:	
			printf("!"); 
			break;
		case EXPR_INCR:	
			printf("++"); 
			break;
		case EXPR_DECR:	
			printf("--"); 
			break;
		case EXPR_NEG:	
			printf("-"); 
			break;
		case EXPR_ASSIGN:	
			printf("="); 
			break;
		case EXPR_ARR:	
			printf("["); 
			break;
		case EXPR_FUNCT:	
			printf("("); 
			break;
		case EXPR_BOOL:	
			if (e->literal_value == 1) {
				printf("true");
			} else {
				printf("false");
			} 
			break;
		case EXPR_NAME:	
			printf("%s", e->string_literal); 
			break;
		case EXPR_INT:	
			printf("%d", e->literal_value); 
			break;
		case EXPR_CHAR:	
			printf("'%c'", e->literal_value); 
			break;
		case EXPR_STR:
			for(int i = 0; i < strlen(e->string_literal); i++) {	
				printf("%c", e->string_literal[i]); 
			}
			break;
		case EXPR_LIST:	
			if (e->right) printf(", ");
			break;
		case EXPR_BLOCK:
			printf("{");
			break;
		case EXPR_ARR_LIST:
			if (e->right) printf("][");
			break;
	}
	expr_print(e->right);

	if (e->kind == EXPR_BLOCK)  printf("}");
	if (e->kind == EXPR_FUNCT) printf(")"); 
	if (e->kind == EXPR_ARR) printf("]"); 
	if (e->kind == EXPR_GROUP) printf(")");
}

