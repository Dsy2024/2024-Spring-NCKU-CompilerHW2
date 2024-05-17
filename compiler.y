/* Definition section */
%{
    #include "compiler_common.h"
    #include "compiler_util.h"
    #include "main.h"

    int yydebug = 1;
%}

/* Variable or self-defined structure */
%union {
    ObjectType var_type;

    bool b_var;
    int i_var;
    float f_var;
    char *s_var;

    Object object_val;
}

/* Token without return */
%token COUT
%token SHR SHL BAN BOR BNT BXO ADD SUB MUL DIV REM NOT GTR LES GEQ LEQ EQL NEQ LAN LOR
%token VAL_ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN REM_ASSIGN BAN_ASSIGN BOR_ASSIGN BXO_ASSIGN SHR_ASSIGN SHL_ASSIGN INC_ASSIGN DEC_ASSIGN
%token IF ELSE FOR WHILE RETURN BREAK CONTINUE

/* Token with return, which need to sepcify type */
%token <var_type> VARIABLE_T
%token <s_var> IDENT STR_LIT
%token <b_var> BOOL_LIT
%token <i_var> INT_LIT
%token <f_var> FLOAT_LIT


/* Nonterminal with return, which need to sepcify type */
%type <object_val> Expression Term Factor

%left ADD SUB
%left MUL DIV REM

/* Yacc will start at this nonterminal */
%start Program

%%
/* Grammar section */

Program
    : { pushScope(); } GlobalStmtList { dumpScope(); }
    | /* Empty file */
;

GlobalStmtList 
    : GlobalStmtList GlobalStmt
    | GlobalStmt
;

GlobalStmt
    : DefineVariableStmt
    | FunctionDefStmt
;

DefineVariableStmt
    : VARIABLE_T IDENT VAL_ASSIGN Expression ';'
;

/* Function */
FunctionDefStmt
    : VARIABLE_T IDENT { createFunction($<var_type>1, $<s_var>2); pushScope(); } '(' FunctionParameterStmtList ')' '{' StmtList '}' { dumpScope(); }
;
FunctionParameterStmtList 
    : FunctionParameterStmtList ',' FunctionParameterStmt
    | FunctionParameterStmt
    | /* Empty function parameter */
;
FunctionParameterStmt
    : VARIABLE_T IDENT { pushFunParm($<var_type>1, $<s_var>2, VAR_FLAG_DEFAULT); }
    | VARIABLE_T IDENT '[' ']' { pushFunParm($<var_type>1, $<s_var>2, VAR_FLAG_DEFAULT); }
;

/* Scope */
StmtList 
    : StmtList Stmt
    | Stmt
;
Stmt
    : ';'
    | COUT CoutParmListStmt ';' { stdoutPrint(); }
    | RETURN Expression ';' { printf("RETURN\n"); }
;

CoutParmListStmt
    : CoutParmListStmt SHL Expression { pushFunInParm(&$<object_val>3); }
    | SHL Expression { pushFunInParm(&$<object_val>2); }
    | SHL STR_LIT { printf("STR_LIT \"%s\"\n", $<s_var>2); }
;

Expression
    : Expression '+' Term
    | Expression '-' Term
    | Term
;
Term
    : Term '*' Factor 
    | Term '/' Factor
    | Term '%' Factor 
    | Factor
;
Factor
    : NOT Factor { $$ = $2; }
    | BOOL_LIT { $$ = *createVariable(OBJECT_TYPE_BOOL, "bool", VAR_FLAG_DEFAULT); }
    | SUB Factor { $$ = $2; }
    | '(' Expression ')' { pushFunInParm(&$<object_val>2); }
    | INT_LIT { printf("INT_LIT %d\n", $<i_var>1); }
    | FLOAT_LIT { $$ = *createVariable(OBJECT_TYPE_FLOAT, "float", VAR_FLAG_DEFAULT); }
    | IDENT { 
    Object* variable = findVariable($<s_var>1);
    printf("IDENT (name=%s, address=%ld)\n", $<s_var>1, variable->symbol->addr); 
    $$ = *variable; }
;

%%
/* C code section */