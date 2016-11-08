/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_TOKEN_H_INCLUDED
# define YY_YY_TOKEN_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_EOF = 258,
    C_COMMENT = 259,
    CPP_COMMENT = 260,
    EQ = 261,
    LE = 262,
    NE = 263,
    GE = 264,
    LT = 265,
    GT = 266,
    ADD = 267,
    MINUS = 268,
    INCREMENT = 269,
    DECREMENT = 270,
    EXPON = 271,
    MULTIPLY = 272,
    MOD = 273,
    DIVIDE = 274,
    NOT = 275,
    AND = 276,
    OR = 277,
    PIPE = 278,
    BG = 279,
    RW = 280,
    COMMA = 281,
    ASSIGNMENT = 282,
    SEMICOLON = 283,
    COLON = 284,
    DOLLAR = 285,
    DOT = 286,
    L_BRACKET = 287,
    R_BRACKET = 288,
    L_PAREN = 289,
    R_PAREN = 290,
    L_BRACE = 291,
    R_BRACE = 292,
    STRING = 293,
    ARRAY = 294,
    BOOLEAN = 295,
    INTEGER = 296,
    VOID = 297,
    IF = 298,
    ELSE = 299,
    FOR = 300,
    WHILE = 301,
    RETURN = 302,
    END = 303,
    TRUE = 304,
    FALSE = 305,
    IDENTIFIER = 306,
    STRING_LITERAL = 307,
    INTEGER_LITERAL = 308,
    FLOAT_LITERAL = 309,
    TOKEN_ERROR = 310
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKEN_H_INCLUDED  */
