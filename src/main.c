/* Breanna Devore-McDonald
 * main.c
 * Compiler for the better-than-bash language
 * Sept 16 2016
 */

#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yyparse();
extern int yylex();

int scan (char * file);
int parse (char * file);
void strip_string(char * s);
void strip_quotes(char * s);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "ERROR: not enough arguments\n");
		exit(1);
	} 
	scan(argv[1]);
	parse(argv[1]);
}

int scan(char* file) {
	extern FILE *yyin;
	extern int yylex();
	extern char *yytext;
	
	yyin = fopen(file, "r");

	if(!yyin) {
		fprintf(stderr, "ERROR: could not open %s\n", file);
		exit(1);
	}

	while(1) {
		//token_t t = yylex();
		enum yytokentype t = yylex();
		/*
		if (t == TOKEN_EOF) {
			break;
		}
		else if (t == TOKEN_ERROR){
			fprintf(stderr, "ERROR: %s is an invalid token\n", yytext);
			exit(1);
		} 
		else if (t == INTEGER_LITERAL || t == FLOAT_LITERAL) {
			printf("%s %s\n", str_token_t(t), yytext);
		}
		else if (t == STRING_LITERAL) {
			if (strlen(yytext) > 255) { // null terminator
				fprintf(stderr, "ERROR: string literal is too long\n");
				exit(1);
			} else {
				strip_string(yytext);
				printf("%s %s\n", str_token_t(t), yytext);
			}
		}
		else if (t == IDENTIFIER ) {
			if (strlen(yytext) > 256) {
				fprintf(stderr, "ERROR: indentifier is too long\n");
				exit(1);
			} else {
				printf("%s %s\n", str_token_t(t), yytext);
			}
		}	
		else {
			printf("%s\n", str_token_t(t));
		}*/
	}
	return 0;
}

int parse( char * file){
	extern FILE * yyin;
	extern char * yytext;

	yyin = fopen(file, "r");
	if( !yyin ){
		fprintf(stderr, "ERROR: invalid file");
		exit(1);
	}
	if( yyparse() == 0 ){
		printf("Parse successful!");
		return 0;
	} else {
		printf("Parse failed");
		return 1;
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

