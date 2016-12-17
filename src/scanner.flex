%{
#include "parser.tab.h"
%}
DIGIT [0-9]
LETTER [a-zA-Z]
%%
(" "|\t|\n)							/* skip whitespace */
[/][*][^*]*[*]+([^/*][^*]*[*]+)*[/]	{ return C_COMMENT; }
\/\/[^\r\n]*						{ return CPP_COMMENT; }

==									{ return EQ; }
\<=									{ return LE; }
\>=									{ return GE; }
!=									{ return NE; }
\<									{ return LT; }
\>									{ return GT; }

\+									{ return ADD; }
\+\+								{ return INCREMENT; }
\-									{ return MINUS; }
\-\-								{ return DECREMENT; }
\^									{ return EXPON; }
\*									{ return MULTIPLY; }
\%									{ return MOD; }
\/									{ return DIVIDE; }

&&									{ return AND; }
\|\|								{ return OR; }
!									{ return NOT; }

\|									{ return PIPE; }
\&									{ return BG; }
\<\>								{ return RW; }

\$									{ return DOLLAR; }
=									{ return ASSIGN; }
\:									{ return COLON; }
\;									{ return SEMICOLON; }
,									{ return COMMA; }
\.									{ return DOT; }

\[									{ return L_BRACKET; }
\]									{ return R_BRACKET; }
\(									{ return L_PAREN; }
\)									{ return R_PAREN; }
\{									{ return L_BRACE; }
\}									{ return R_BRACE; }

array								{ return ARRAY; }
int 								{ return INTEGER; }
bool								{ return BOOLEAN; }
string								{ return STRING; }
void								{ return VOID; }

if									{ return IF; }
else								{ return ELSE; }
while								{ return WHILE; }
for									{ return FOR; }
case								{ return CASE; }
switch								{ return SWITCH; }
default								{ return DEFAULT; }

return								{ return RETURN; }
END									{ return END; }
true								{ return TRUE; }
false								{ return FALSE; }
break								{ return BREAK; }
print								{ return PRINT; }

\"(.)*\"							{ return STRING_LITERAL; }
\$({LETTER}|_)({LETTER}|_|{DIGIT})* { return IDENTIFIER; }
({LETTER}|_)({LETTER}|_|{DIGIT})* { return COMMAND; }
\'(.{1}|\\{LETTER}|\\0|\\\\)\'	{ return CHAR_LITERAL; }
{DIGIT}+							{ return INTEGER_LITERAL; }
{DIGIT}+\.({DIGIT}*)?				{ return FLOAT_LITERAL; }

.									{ return TOKEN_ERROR; }
%%
void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}
int yywrap () {
	return 1;
}
