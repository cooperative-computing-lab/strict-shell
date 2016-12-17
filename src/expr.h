#ifndef EXPR_H
#define EXPR_H

#include <stdlib.h>
#include "decl.h"
#include "scope.h"
#include "stmt.h"

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
	EXPR_CMD,	
	EXPR_INT,	
    EXPR_FLOAT,	
	EXPR_CHAR,
	EXPR_STR,
	EXPR_LIST
} expr_t;

typedef enum {
	VAL_INT,
	VAL_BOOL,
	VAL_FLOAT,
	VAL_CHAR,
	VAL_STR
} value_t;


struct expr {
	/* used by all kinds of exprs */
	expr_t kind;
	struct expr *left;
	struct expr *right;

	/* used by various leaf exprs */
	const char *name;
	struct symbol *symbol;
	int literal_value;
	float float_literal;
	const char * string_literal;
};

struct value {
	value_t kind;
	int value_int;
	int value_bool; // TODO: error check value
	float value_float;
	char value_char;
	char * value_str;

};

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right );

struct expr * expr_create_name( const char *n );
struct expr * expr_create_command( const char *n );
struct expr * expr_create_boolean_literal( int c );
struct expr * expr_create_integer_literal( int c );
struct expr * expr_create_float_literal( float c );
struct expr * expr_create_character_literal( int c );
struct expr * expr_create_string_literal( const char *str );

void expr_print( struct expr *e );

struct value * expr_evaluate( struct expr *e );
struct value * expr_eval_add(struct value * new_val, struct value * l, struct value * r);
struct value * expr_eval_sub(struct value * new_val, struct value * l, struct value * r);
struct value * expr_eval_mul(struct value * new_val, struct value * l, struct value * r);
struct value * expr_eval_div(struct value * new_val, struct value * l, struct value * r);
struct value * expr_eval_exp(struct value * new_val, struct value * l, struct value * r);
struct value * expr_eval_mod(struct value * new_val, struct value * l, struct value * r);

void expr_resolve(struct expr *e);
struct type * expr_typecheck(struct expr *e);
#endif
