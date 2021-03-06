/* Breanna Devore-McDonald
 * main.c
 * Compiler for the better-than-bash language
 * Sept 16 2016
 */

#include "parser.tab.h"
#include "stmt.h"
#include "expr.h"
#include "decl.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yyparse();
extern int yylex();
extern struct stmt * program;
int errors;

int parse ();
int resolve();
void strip_string(char * s);
void strip_quotes(char * s);

int main(int argc, char *argv[]) {
	if (argc > 1) {
		fprintf(stderr, "ERROR: too many arguments\n");
		exit(1);
	} 
	return resolve();
}

int parse(){

	if( yyparse() == 0 ){
		printf("Parse successful!\n");
		stmt_print(program, 0);
//		printf("\nEvaluates to: ");
//	   	stmt_evaluate(program);
//		printf("\n");

		return 0;
	} else {
		printf("Parse failed\n");
		return 1;
	}
}

int resolve(){
	if(yyparse() == 0){
		head = 0;
		scope_enter();
		stmt_resolve(program);
	 	scope_exit();
		return 0;
	} else {
		return 1;
		//exit(1);
	}

}

void strip_string(char * s){
	int len = strlen(s);
	strip_quotes(s);

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

void strip_quotes(char * s) {
	int len = strlen(s); 
	if(len > 0)
		memmove(s, s+1, len); // rid first char
	if(len > 1)
		s[len - 2] = '\0'; // rid last char
}

