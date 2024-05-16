/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_Y_TAB_H_INCLUDED
# define YY_YY_BUILD_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    COUT = 258,                    /* COUT  */
    ENDL = 259,                    /* ENDL  */
    SHR = 260,                     /* SHR  */
    SHL = 261,                     /* SHL  */
    BAN = 262,                     /* BAN  */
    BOR = 263,                     /* BOR  */
    BNT = 264,                     /* BNT  */
    BXO = 265,                     /* BXO  */
    ADD = 266,                     /* ADD  */
    SUB = 267,                     /* SUB  */
    MUL = 268,                     /* MUL  */
    DIV = 269,                     /* DIV  */
    REM = 270,                     /* REM  */
    NOT = 271,                     /* NOT  */
    GTR = 272,                     /* GTR  */
    LES = 273,                     /* LES  */
    GEQ = 274,                     /* GEQ  */
    LEQ = 275,                     /* LEQ  */
    EQL = 276,                     /* EQL  */
    NEQ = 277,                     /* NEQ  */
    LAN = 278,                     /* LAN  */
    LOR = 279,                     /* LOR  */
    VAL_ASSIGN = 280,              /* VAL_ASSIGN  */
    ADD_ASSIGN = 281,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 282,              /* SUB_ASSIGN  */
    MUL_ASSIGN = 283,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 284,              /* DIV_ASSIGN  */
    REM_ASSIGN = 285,              /* REM_ASSIGN  */
    BAN_ASSIGN = 286,              /* BAN_ASSIGN  */
    BOR_ASSIGN = 287,              /* BOR_ASSIGN  */
    BXO_ASSIGN = 288,              /* BXO_ASSIGN  */
    SHR_ASSIGN = 289,              /* SHR_ASSIGN  */
    SHL_ASSIGN = 290,              /* SHL_ASSIGN  */
    INC_ASSIGN = 291,              /* INC_ASSIGN  */
    DEC_ASSIGN = 292,              /* DEC_ASSIGN  */
    IF = 293,                      /* IF  */
    ELSE = 294,                    /* ELSE  */
    FOR = 295,                     /* FOR  */
    WHILE = 296,                   /* WHILE  */
    RETURN = 297,                  /* RETURN  */
    BREAK = 298,                   /* BREAK  */
    CONTINUE = 299,                /* CONTINUE  */
    VARIABLE_T = 300,              /* VARIABLE_T  */
    IDENT = 301,                   /* IDENT  */
    STR_LIT = 302,                 /* STR_LIT  */
    BOOL_LIT = 303,                /* BOOL_LIT  */
    INT_LIT = 304,                 /* INT_LIT  */
    FLOAT_LIT = 305                /* FLOAT_LIT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define COUT 258
#define ENDL 259
#define SHR 260
#define SHL 261
#define BAN 262
#define BOR 263
#define BNT 264
#define BXO 265
#define ADD 266
#define SUB 267
#define MUL 268
#define DIV 269
#define REM 270
#define NOT 271
#define GTR 272
#define LES 273
#define GEQ 274
#define LEQ 275
#define EQL 276
#define NEQ 277
#define LAN 278
#define LOR 279
#define VAL_ASSIGN 280
#define ADD_ASSIGN 281
#define SUB_ASSIGN 282
#define MUL_ASSIGN 283
#define DIV_ASSIGN 284
#define REM_ASSIGN 285
#define BAN_ASSIGN 286
#define BOR_ASSIGN 287
#define BXO_ASSIGN 288
#define SHR_ASSIGN 289
#define SHL_ASSIGN 290
#define INC_ASSIGN 291
#define DEC_ASSIGN 292
#define IF 293
#define ELSE 294
#define FOR 295
#define WHILE 296
#define RETURN 297
#define BREAK 298
#define CONTINUE 299
#define VARIABLE_T 300
#define IDENT 301
#define STR_LIT 302
#define BOOL_LIT 303
#define INT_LIT 304
#define FLOAT_LIT 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "./compiler.y"

    ObjectType var_type;

    bool b_var;
    int i_var;
    float f_var;
    char *s_var;

    Object object_val;

#line 178 "./build/y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_Y_TAB_H_INCLUDED  */
