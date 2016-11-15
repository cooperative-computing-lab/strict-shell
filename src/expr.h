#ifndef EXPR_H
#define EXPR_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	EXPR_ADD,	
	EXPR_SUB,	
	EXPR_MUL,	
	EXPR_DIV,	
	EXPR_EXP,	
	EXPR_MOD,	

	EXPR_GT,	
	EXPR_GE,	
	EXPR_LT,	
	EXPR_LE,	
	EXPR_NE,	
	EXPR_EQ,	

	EXPR_AND,	
	EXPR_OR,	
	EXPR_NOT,	

	EXPR_INCR,	
	EXPR_DECR,	

	EXPR_NEG,	
	EXPR_ASSIGN,

	EXPR_ARR,
	EXPR_ARR_LIST,	
	EXPR_FUNCT,	
	EXPR_GROUP,
	EXPR_BLOCK,	

	EXPR_BOOL,	
	EXPR_NAME,	
	EXPR_INT,	
    EXPR_FLOAT,	
	EXPR_CHAR,
	EXPR_STR,
	EXPR_LIST
} expr_t;

struct expr {
	/* used by all kinds of exprs */
	expr_t kind;
	struct expr *left;
	struct expr *right;

	/* used by various leaf exprs */
	const char *name;
	struct symbol *symbol;
	int literal_value;
	const char * string_literal;
};

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right );

struct expr * expr_create_name( const char *n );
struct expr * expr_create_boolean_literal( int c );
struct expr * expr_create_integer_literal( int c );
struct expr * expr_create_float_literal( float c );
struct expr * expr_create_character_literal( int c );
struct expr * expr_create_string_literal( const char *str );

void expr_print( struct expr *e );
double  expr_evaluate( struct expr *e );

#endif
