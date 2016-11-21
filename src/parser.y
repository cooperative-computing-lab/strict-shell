%{
#include "stmt.h"
#include "decl.h"
#include "type.h"
#include "expr.h"
#include <stdio.h>
#include <string.h>

extern char *yytext;
extern int yylex();
extern int yyerror( char *str );

struct stmt * program = 0;
void strip_string_parse(char * s);
void strip_quotes_parse(char * s);

%}

%token TOKEN_EOF 
%token C_COMMENT 
%token CPP_COMMENT 

%token EQ 
%token LE 
%token NE 
%token GE 
%token LT 
%token GT 

%token ADD 
%token MINUS 
%token INCREMENT 
%token DECREMENT 
%token EXPON 
%token MULTIPLY 
%token MOD 
%token DIVIDE 

%token NOT 
%token AND 
%token OR 

%token PIPE 
%token BG 
%token RW 

%token COMMA 
%token ASSIGN 
%token SEMICOLON 
%token COLON 
%token DOLLAR 
%token DOT 

%token L_BRACKET 
%token R_BRACKET 
%token L_PAREN 
%token R_PAREN 
%token L_BRACE 
%token R_BRACE 

%token STRING 
%token ARRAY 
%token BOOLEAN 
%token INTEGER 
%token VOID 
%token FLOAT 

%token IF 
%token ELSE 
%token FOR 
%token WHILE
%token CASE
%token SWITCH
%token DEFAULT 

%token RETURN 
%token BREAK
%token END 
%token TRUE 
%token FALSE 
%token PRINT 

%token IDENTIFIER 
%token STRING_LITERAL 
%token INTEGER_LITERAL 
%token FLOAT_LITERAL 
%token TOKEN_ERROR

%union{
	struct decl *decl;
	struct stmt *stmt;
	struct expr *expr;
	struct type *type;
	char *id;
};

%start program 

%type <stmt> program decl decl_list real_decl_list stmt stmt_list case case_list
%type <expr> expr expr_list expr_or_nothing real_expr_list or_expr and_expr expr_compare       add_expr mul_expr exp_expr un_expr incr_expr expr_group /*expr_block real_expr_block*/ atomic
%type <type> type
%type <id> id

%left ADD MINUS
%left MULTIPLY DIVIDE MOD
/*precedence*/

%%
program : stmt SEMICOLON
		  { program = $1; return 0;}
		;

decl_list : real_decl_list
			{$$ = $1;}
		  | /* nothing */
			{$$ = 0;}
		  ;

real_decl_list : decl COMMA decl_list
				 { $$ = $1; $1->next = $3; }
			   | decl
				 { $$ = $1; }
			   ;

decl : type id /*used to be DOLLAR id, but changed regex in scanner*/
		{ 
			$$ = stmt_create(STMT_DECL, 
							decl_create($2, $1, 0, 0, NULL), 
							0, 0, 0, 0, 0); 
		}
	 | type id ASSIGN expr
		{ 
			$$ = stmt_create(STMT_DECL, 
							decl_create($2, $1, $4, 0, NULL), 
							0, 0, 0, 0, 0);
		}
	 | type id L_PAREN decl_list R_PAREN L_BRACE stmt_list R_BRACE
		{ 
			// what about $4? the params
			$$ = stmt_create(STMT_DECL, 
							decl_create($2, $1, 0, $7, NULL), 
							0, 0, 0, 0, 0);
		}
	 
	 | type id L_BRACKET expr_list R_BRACKET
		{ 
			// what about the parameters? $4
			$$ = stmt_create(STMT_DECL, 
							decl_create($2, $1, 0, 0, NULL), 
							0, 0, 0, 0, 0);
		}
	/* | type id L_BRACKET expr_list R_BRACKET ASSIGN 
		{ 
			// what about the parameters? and code?
			$$ = stmt_create(STMT_DECL, 
							decl_create($2, $1, 0, 0, NULL), 
							0, 0, 0, 0, 0);
		}*/
	 ;

id : IDENTIFIER
			 { $$ = strdup(yytext); }
		   ;
	 
stmt_list : stmt SEMICOLON stmt_list
			{ $$ = $1; $1->next = $3; }
		  |
			{ $$ = 0; }
		  ;

stmt : decl
		{ $$ = $1; }
	 | FOR L_PAREN expr_or_nothing SEMICOLON expr_or_nothing SEMICOLON expr_or_nothing R_PAREN stmt_list END
		{ $$ = stmt_create(STMT_FOR, 0, $3, $5, $7, $9, 0); }
	 | RETURN expr
		{ $$ = stmt_create(STMT_RETURN, 0, 0, $2, 0, 0, 0); }
	 | IF L_PAREN expr R_PAREN stmt_list END
		{ $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, 0); }
	 | IF L_PAREN expr R_PAREN stmt_list ELSE stmt_list END
		{ $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, $7); } 
	 | expr
		{ $$ = stmt_create(STMT_EXPR, 0, 0, $1, 0, 0, 0); }
	 | PRINT expr_list
		{ $$ = stmt_create(STMT_PRINT, 0, 0, $2, 0, 0, 0); }
	 | SWITCH L_PAREN expr R_PAREN case_list END
		{ $$ = stmt_create(STMT_SWITCH, 0, 0, $3, 0, $5, 0); }
	 | WHILE L_PAREN expr R_PAREN stmt_list END
		{ $$ = stmt_create(STMT_WHILE, 0, 0, $3, 0, $5, 0); }
	 | BREAK
		{ $$ = stmt_create(STMT_BREAK, 0, 0, 0, 0, 0, 0); }
	 ;

case_list : case case_list
			{ $$ = $1; $1->next = $2; }
		  |  DEFAULT COLON stmt_list
			{ $$ = stmt_create(STMT_CASE, 0, 0, NULL, 0, $3, 0); }
			/* TODO: null expr? */
		  ;

case : CASE expr COLON stmt_list
		{ $$ = stmt_create(STMT_CASE, 0, 0, $2, 0, $4, 0); }
	 ;

expr_list : real_expr_list
		    { $$ = $1; }
		  | /*nothing */
			{ $$ = 0; }
		  ;

/* pipeline_list : expr */

real_expr_list : expr COMMA real_expr_list
				 { $$ = expr_create(EXPR_LIST, $1, $3); }
			   | expr
				 { $$ = expr_create(EXPR_LIST, $1, 0); }
		       /*| pipeline_list
				   TODO but push off work to typechecker */
			   ;
/*
real_expr_block : expr_block COMMA real_expr_block
				  { $$ = expr_create(EXPR_LIST, $1, $3); }
				| expr_block
				  { $$ = expr_create(EXPR_LIST, $1, 0); }
			    | real_expr_list
				  { $$ = $1; }
				;
expr_block : L_BRACE real_expr_block R_BRACE
			 { $$ = expr_create(EXPR_BLOCK, 0, $2); }
		   ;
*/

expr_or_nothing : expr
		          { $$ = $1; }
		        | /* nothing */
		          { $$ = 0; }
		        ;

expr : or_expr ASSIGN expr
	   { $$ = expr_create( EXPR_ASSIGN, $1, $3 ); }
	 | or_expr
	   { $$ = $1; }
	 ;

/* or is before and */
or_expr : or_expr OR and_expr
		  { $$ = expr_create( EXPR_OR, $1, $3); }
	    | and_expr
		 { $$ = $1; }
	    ;

and_expr : and_expr AND expr_compare
		   { $$ = expr_create( EXPR_AND, $1, $3); }
	     | expr_compare
		   { $$ = $1; }
	     ;

expr_compare : expr_compare GT add_expr
			    { $$ = expr_create( EXPR_GT, $1, $3); }
	         | expr_compare GE add_expr
		       { $$ = expr_create( EXPR_GE, $1, $3); }
	         | expr_compare LT add_expr
	           { $$ = expr_create( EXPR_LT, $1, $3); }
	         | expr_compare LE add_expr
	           { $$ = expr_create( EXPR_LE, $1, $3); }
	         | expr_compare EQ add_expr
	           { $$ = expr_create( EXPR_EQ, $1, $3); }
	         | expr_compare NE add_expr
	           { $$ = expr_create( EXPR_NE, $1, $3); }
	         | add_expr
	           { $$ = $1; }
	         ;

add_expr : add_expr ADD mul_expr
		   { $$ = expr_create( EXPR_ADD, $1, $3); }
		 | add_expr MINUS mul_expr
		   { $$ = expr_create( EXPR_SUB, $1, $3); }
		 | mul_expr
	       { $$ = $1; }
	     ;

mul_expr : mul_expr MULTIPLY exp_expr
		    { $$ = expr_create( EXPR_MUL, $1, $3); }
		  | mul_expr MOD exp_expr
		    { $$ = expr_create( EXPR_MOD, $1, $3); }
		  | mul_expr DIVIDE exp_expr
		    { $$ = expr_create( EXPR_DIV, $1, $3); }
		  | exp_expr
		    { $$ = $1; }
	      ;

exp_expr : exp_expr EXPON un_expr
		   { $$ = expr_create( EXPR_EXP, $1, $3); }
		 | un_expr
		   { $$ = $1; }
	     ;

un_expr : MINUS un_expr
		     { $$ = expr_create( EXPR_NEG, 0, $2); }
		   | NOT un_expr
			 { $$ = expr_create( EXPR_NOT, 0, $2); }
		   | incr_expr
			 { $$ = $1; }
		   ;

incr_expr : expr_group INCREMENT
		    { $$ = expr_create( EXPR_INCR, $1, 0); }
		  | expr_group DECREMENT
		    { $$ = expr_create( EXPR_DECR, $1, 0); }
		  | expr_group
		    { $$ = $1; }
	      ;

expr_group : L_PAREN expr R_PAREN
	         { $$ = expr_create( EXPR_GROUP, $2, 0); }
		   | id L_PAREN expr_list R_PAREN
		     { $$ = expr_create( EXPR_FUNCT, expr_create_name($1), $3); }
		   /*| L_BRACKET real_expr_block R_BRACKET
		     { $$ = expr_create( 0, 0, 0); }*/
	       | atomic
	    	 { $$ = $1; }
		   ;

atomic : TRUE
			{ $$ = expr_create_boolean_literal(1); }
	   | FALSE 
			{ $$ = expr_create_boolean_literal(0); }
	   | id 
			{ $$ = expr_create_name($1); }
	   | STRING_LITERAL
			{ $$ = expr_create_string_literal(strdup(yytext)); }
	   | INTEGER_LITERAL 
			{ $$ = expr_create_integer_literal(atoi(yytext)); }
	   | FLOAT_LITERAL 
			{ $$ = expr_create_float_literal(atof(yytext)); }
	   /*| COMMAND*/
			/* TODO */
	   ;

type : STRING 
		{ $$ = type_create(TYPE_STRING, NULL, NULL); }
	 | ARRAY 
		/* TODO: fix this*/
		{ $$ = type_create(TYPE_ARRAY, NULL, NULL); }
	 | BOOLEAN 
		{ $$ = type_create(TYPE_BOOLEAN, NULL, NULL); }
	 | INTEGER 
		{ $$ = type_create(TYPE_INTEGER, NULL, NULL); }
	 | VOID
		{ $$ = type_create(TYPE_VOID, NULL, NULL); }
	 | FLOAT 
		{ $$ = type_create(TYPE_FLOAT, NULL, NULL); }
	 ;

%%

/*  C Postamble Code */

int yywrap() { return 0; }

void strip_string_parse(char * s){
    int len = strlen(s);
    strip_quotes_parse(s);

    int i;
    for (i = 0; i < len; i++) {
        if (s[i] == '\\'){
            if (s[i+1] == 'n'){
                s[i+1] = '\n';
            }
            else if (s[i+1] == '0'){
                s[i+1] = '\0';
            }
            memmove(&s[i], &s[i+1], len - i); // remove leading backslash
        }
    }
}

void strip_quotes_parse(char * s) {
    int len = strlen(s);
    if(len > 0)
        memmove(s, s+1, len); // rid first char
    if(len > 1)
        s[len - 2] = '\0'; // rid last char
}


