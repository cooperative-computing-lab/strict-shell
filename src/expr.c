#include "expr.h"
#include "type.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right ) {
	struct expr * new_expr = malloc(sizeof * new_expr);
	new_expr -> kind = kind;
	new_expr -> left = left;
	new_expr -> right = right;
	new_expr -> name = 0;
	new_expr -> symbol = 0;
	new_expr -> literal_value = 0;
	new_expr -> float_literal = 0;
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
	new_expr -> literal_value = 0;
	new_expr -> float_literal = 0;
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
	new_expr -> float_literal = 0;
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
	new_expr -> float_literal = 0;
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
	new_expr -> literal_value = 0;
	new_expr -> float_literal = c;
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
	new_expr -> float_literal = 0;
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
	new_expr -> literal_value = 0;
	new_expr -> float_literal = 0;
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
		case EXPR_ARR_LIST:
			if (e->right) printf("][");
			break;
		case EXPR_FUNCT:	
			printf("("); 
			break;
		case EXPR_GROUP:
			printf("(");
			break;
		case EXPR_BLOCK:
			printf("{");
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
		case EXPR_FLOAT:	
			printf("%f", e->float_literal); 
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
	}
	expr_print(e->right);

	if (e->kind == EXPR_BLOCK)  printf("}");
	if (e->kind == EXPR_FUNCT) printf(")"); 
	if (e->kind == EXPR_ARR) printf("]"); 
	if (e->kind == EXPR_GROUP) printf(")");
}

/*
Recursively evaluate an expression by performing
the desired operation and returning it up the tree.
*/
struct value * expr_evaluate( struct expr *e ) {

	if(!e) return 0;

	struct value * l = expr_evaluate(e->left);
	struct value * r = expr_evaluate(e->right);

	// TODO only works for same type for now 
	// return filled out struct, all NULL except for type

	struct value * new_val = malloc(sizeof * new_val);
	new_val->value_int = 0;
	new_val->value_bool = 0;
	new_val->value_float = 0;
	new_val->value_char = 0;
	new_val->value_str = 0;
	// fill out kind in leaf funcs

	switch(e->kind) {
		case EXPR_ADD:
			if (l->kind == r->kind){
				//printf("%d", l->value_int + r->value_int);
				//printf("%d", (expr_eval_add(new_val, l, r))->value_int);
				return expr_eval_add(new_val, l, r);
			}
			break;
		case EXPR_SUB:
			if (l->kind == r->kind){
				return expr_eval_sub(new_val, l, r);
			}
			break;
		case EXPR_MUL:
			if (l->kind == r->kind){
				return expr_eval_mul(new_val, l, r);
			}
			break;
		case EXPR_DIV:
			if(r == 0) {
				printf("runtime error: divide by zero\n");
				exit(1);
			}
			if (l->kind == r->kind){
				return expr_eval_div(new_val, l, r);
			}
			break;
		case EXPR_EXP:
			// error check?
			if (l->kind == r->kind){
				return expr_eval_exp(new_val, l, r);
			}
			break;
		case EXPR_MOD:
			if (l->kind == r->kind){
				return expr_eval_mod(new_val, l, r);
			}
			break;
		case EXPR_INT:
			new_val->kind = VAL_INT;
			new_val->value_int = e->literal_value;
			return new_val;
			break;
		case EXPR_BOOL:
			new_val->kind = VAL_BOOL;
			new_val->value_bool = e->literal_value;
			return new_val;
			break;
		case EXPR_FLOAT:
			new_val->kind = VAL_FLOAT;
			new_val->value_float = e->float_literal;
			return new_val;
			break;
		case EXPR_CHAR:
			new_val->kind = VAL_CHAR;
			new_val->value_char = e->literal_value;
			return new_val;
			break;
		case EXPR_STR:
			new_val->kind = VAL_STR;
			// TODO
			//new_val->value_str = e->string_literal;
			return new_val;
			break;
		case EXPR_NAME:
			// TODO
			break;
	}

	return 0;
}

struct value * expr_eval_add( struct value * new_val, struct value * l, struct value * r){

	value_t kind = l->kind;
	new_val->kind = kind;

	if (kind == VAL_INT) {

		new_val->value_int = l->value_int+r->value_int;		
	} else if (kind == VAL_BOOL) {
		printf("runtime error: addition on boolean type\n");
		exit(1);
	} else if (kind == VAL_FLOAT) {
		new_val->value_float == l->value_float+r->value_float;
	} else if (kind == VAL_CHAR) {
		new_val->value_char = l->value_char+r->value_char;
	} else if (kind == VAL_STR) {
		/* return concatenation of two strings */
		char * concat  = malloc(strlen(l->value_str)+strlen(r->value_str)+1);
		strcpy(concat, l->value_str);
		strcat(concat, r->value_str);
		/* TODO */
		// new_val->str
		new_val->value_str = NULL;
		printf("runtime error: unimplemented\n");
		exit(1);
	} else {
		printf("runtime error: unimplemented\n");
		exit(1);
	}

	return new_val;
}

struct value * expr_eval_sub( struct value * new_val, struct value * l, struct value * r){
	
	value_t kind = l->kind;
	new_val->kind = kind;

	if (kind == VAL_INT) {
		new_val->value_int = l->value_int-r->value_int;		
	} else if (kind == VAL_BOOL) {
		printf("runtime error: subtraction on boolean type\n");
		exit(1);
	} else if (kind == VAL_FLOAT) {
		new_val->value_float == l->value_float-r->value_float;
	} else if (kind == VAL_CHAR) {
		new_val->value_char = l->value_char-r->value_char;
	} else if (kind == VAL_STR) {
		printf("runtime error: subtraction on string type\n");
		exit(1);
	}

	return new_val;
}

struct value * expr_eval_mul( struct value * new_val, struct value * l, struct value * r){
	
	value_t kind = l->kind;
	new_val->kind = kind;

	if (kind == VAL_INT) {
		new_val->value_int = l->value_int*r->value_int;		
	} else if (kind == VAL_BOOL) {
		// essentially an AND op 
		new_val->value_bool = l->value_bool*r->value_bool;		
	} else if (kind == VAL_FLOAT) {
		new_val->value_float == l->value_float*r->value_float;
	} else if (kind == VAL_CHAR) {
		new_val->value_char = l->value_char*r->value_char;
	} else if (kind == VAL_STR) {
		printf("runtime error: multiplication on string type\n");
		exit(1);
	}

	return new_val;
}

struct value * expr_eval_div( struct value * new_val, struct value * l, struct value * r){
	
	value_t kind = l->kind;
	new_val->kind = kind;

	if (kind == VAL_INT) {
		new_val->value_int = l->value_int/r->value_int;		
	} else if (kind == VAL_BOOL) {
		printf("runtime error: division on boolean type\n");
		exit(1);
	} else if (kind == VAL_FLOAT) {
		new_val->value_float == l->value_float/r->value_float;
	} else if (kind == VAL_CHAR) {
		new_val->value_char = l->value_char/r->value_char;
	} else if (kind == VAL_STR) {
		printf("runtime error: division on string type\n");
		exit(1);
	}

	return new_val;
}


struct value * expr_eval_exp( struct value * new_val, struct value * l, struct value * r){
	
	value_t kind = l->kind;
	new_val->kind = kind;

	if (kind == VAL_INT) {
		new_val->value_int = pow(l->value_int, r->value_int);		
	} else if (kind == VAL_BOOL) {
		printf("runtime error: exp on boolean type\n");
		exit(1);
	} else if (kind == VAL_FLOAT) {
		new_val->value_float == pow(l->value_float, r->value_float);
	} else if (kind == VAL_CHAR) {
		new_val->value_char = pow(l->value_char, r->value_char);
	} else if (kind == VAL_STR) {
		printf("runtime error: exp on string type\n");
		exit(1);
	}

	return new_val;
}

struct value * expr_eval_mod( struct value * new_val, struct value * l, struct value * r){
	
	value_t kind = l->kind;
	new_val->kind = kind;

	if (kind == VAL_INT) {
		new_val->value_int = l->value_int%r->value_int;		
	} else if (kind == VAL_BOOL) {
		printf("runtime error: modulo on boolean type\n");
		exit(1);
	} else if (kind == VAL_FLOAT) {
		printf("runtime error: modulo on float type\n");
		exit(1);
	} else if (kind == VAL_CHAR) {
		new_val->value_int = l->value_char%r->value_char;		
	} else if (kind == VAL_STR) {
		printf("runtime error: modulo on string type\n");
		exit(1);
	}

	return new_val;
}
