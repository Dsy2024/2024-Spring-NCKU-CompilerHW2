#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

#define debug printf("%s:%d: ############### debug\n", __FILE__, __LINE__)

#define toupper(_char) (_char - (char)32)

const char* objectTypeName[] = {
    [OBJECT_TYPE_UNDEFINED] = "undefined",
    [OBJECT_TYPE_VOID] = "void",
    [OBJECT_TYPE_INT] = "int",
    [OBJECT_TYPE_FLOAT] = "float",
    [OBJECT_TYPE_BOOL] = "bool",
    [OBJECT_TYPE_STR] = "string",
    [OBJECT_TYPE_FUNCTION] = "function",
};

char* yyInputFileName;
bool compileError;

int indent = 0;
int scopeLevel = -1;
int funcLineNo = 0;
int variableAddress = -1;
ObjectType variableIdentType;

Node *symbolTable = NULL;
FuncParmNode *funcParmStack = NULL;
SymbolTableStackNode* symbolTableStack = NULL;

void pushScope() {
    SymbolTableStackNode* newStackNode = (SymbolTableStackNode*)malloc(sizeof(SymbolTableStackNode));
    newStackNode->symbolTable = NULL;  // Initialize with an empty symbol table
    newStackNode->next = symbolTableStack;
    symbolTableStack = newStackNode;

    scopeLevel++;
    printf("> Create symbol table (scope level: %d)\n", scopeLevel);
}

void dumpScope() {
    SymbolTableStackNode* topStackNode = symbolTableStack;
    symbolTableStack = symbolTableStack->next;
    Node* current = topStackNode->symbolTable;
    printf("\n> Dump symbol table (scope level: %d)\n", scopeLevel);
    printf("Index     Name                Type      Addr      Lineno    Func_sig\n");
    int index = 0;
    while (current != NULL) {
        Object* obj = current->data;
        printf("%-10d %-20s %-10s %-10ld %-10d %s\n", index++, obj->symbol->name, objectTypeName[obj->type], obj->symbol->addr, obj->symbol->lineno, obj->symbol->func_sig);
        current = current->next;
    }
    scopeLevel--;
}

Object* createVariable(ObjectType variableType, char* variableName, int variableFlag) {
    // Allocate memory for the new variable
    Object* newVariable = (Object*)malloc(sizeof(Object));
    // if (!newVariable) {
    //     fprintf(stderr, "Error: Could not allocate memory for new variable.\n");
    //     return NULL;
    // }

    // Initialize the fields of the new variable
    newVariable->type = variableType;
    newVariable->symbol = (SymbolData*)malloc(sizeof(SymbolData));
    newVariable->symbol->name = strdup(variableName); // Allocate memory and copy the name
    // if (!newVariable->symbol->name) {
    //     fprintf(stderr, "Error: Could not allocate memory for variable name.\n");
    //     free(newVariable);
    //     return NULL;
    // }
    newVariable->symbol->addr = variableAddress++;  // Assign and increment the address for non-literals
    newVariable->symbol->lineno = yylineno; // Assuming yylineno keeps track of the current line number
    newVariable->symbol->func_sig = "-";

    // Allocate memory for the new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    // if (!newNode) {
    //     fprintf(stderr, "Error: Could not allocate memory for new node.\n");
    //     free(newVariable->symbol->name);
    //     free(newVariable);
    //     return NULL;
    // }

    // Initialize the node
    newNode->data = newVariable;
    newNode->next = symbolTableStack->symbolTable;
    symbolTableStack->symbolTable = newNode;

    printf("> Insert `%s` (addr: %ld) to scope level %d\n", variableName, newVariable->symbol->addr, scopeLevel);

    return newVariable;
}

void pushFunParm(ObjectType variableType, char* variableName, int variableFlag) {
    // Set func_sig based on variableType
    char* funcSignature;
    switch (variableType) {
        case OBJECT_TYPE_INT:
            funcSignature = "(II)I"; // Two integers, returns an integer
            break;
        case OBJECT_TYPE_FLOAT:
            funcSignature = "(FF)F"; // Two floats, returns a float
            break;
        case OBJECT_TYPE_BOOL:
            funcSignature = "(ZZ)Z"; // Two booleans, returns a boolean
            break;
        case OBJECT_TYPE_STR:
            funcSignature = "(Ljava/lang/String;)V"; // One string, returns void
            break;
        // Add cases for other variable types as needed
        default:
            funcSignature = "(unknown)";
            break;
    }
    //symbolTableStack->symbolTable->data->symbol->func_sig = funcSignature;

    Object* variable = createVariable(variableType, variableName, variableFlag);
    if (!variable) {
        fprintf(stderr, "Error: Could not create function parameter variable.\n");
        return;
    }

    FuncParmNode* newParmNode = (FuncParmNode*)malloc(sizeof(FuncParmNode));
    if (!newParmNode) {
        fprintf(stderr, "Error: Could not allocate memory for function parameter node.\n");
        return;
    }

    newParmNode->data = variable;
    newParmNode->next = funcParmStack;
    funcParmStack = newParmNode;
}

void createFunction(ObjectType variableType, char* funcName) {

    printf("func: %s\n", funcName);

    // FuncParmNode* current = funcParmStack;
    // while (current != NULL) {
    //     printf("> Function parameter: `%s` (type: %d, addr: %ld)\n", current->data->symbol->name, current->data->type, current->data->symbol->addr);
    //     current = current->next;
    // }

    // while (funcParmStack != NULL) {
    //     FuncParmNode* temp = funcParmStack;
    //     funcParmStack = funcParmStack->next;
    //     free(temp);
    // }

    Object* funcObject = (Object*)malloc(sizeof(Object));
    funcObject->type = variableType;
    funcObject->symbol = (SymbolData*)malloc(sizeof(SymbolData));
    funcObject->symbol->name = strdup(funcName);
    funcObject->symbol->addr = variableAddress++;
    funcObject->symbol->lineno = yylineno; 
    funcObject->symbol->func_sig = "-"; 
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = funcObject;
    newNode->next = symbolTableStack->symbolTable;
    symbolTableStack->symbolTable = newNode;

    printf("> Insert `%s` (addr: %ld) to scope level %d\n", funcName, funcObject->symbol->addr, scopeLevel);
}

void debugPrintInst(char instc, Object* a, Object* b, Object* out) {
}

bool objectExpression(char op, Object* dest, Object* val, Object* out) {
    return false;
}

bool objectExpBinary(char op, Object* a, Object* b, Object* out) {
    return false;
}

bool objectExpBoolean(char op, Object* a, Object* b, Object* out) {
    return false;
}

bool objectExpAssign(char op, Object* dest, Object* val, Object* out) {
    return false;
}

bool objectValueAssign(Object* dest, Object* val, Object* out) {
    return false;
}

bool objectNotBinaryExpression(Object* dest, Object* out) {
    return false;
}

bool objectNegExpression(Object* dest, Object* out) {
    return false;
}
bool objectNotExpression(Object* dest, Object* out) {
    return false;
}

bool objectIncAssign(Object* a, Object* out) {
    return false;
}

bool objectDecAssign(Object* a, Object* out) {
    return false;
}

bool objectCast(ObjectType variableType, Object* dest, Object* out) {
    return false;
}

Object* findVariable(char* variableName) {
    SymbolTableStackNode* currentScope = symbolTableStack;
    while (currentScope != NULL) {
        Node* current = currentScope->symbolTable;
        while (current != NULL) {
            if (strcmp(current->data->symbol->name, variableName) == 0) {
                return current->data;
            }
            current = current->next;
        }
        currentScope = currentScope->next;
    }
    Object* newVariable = (Object*)malloc(sizeof(Object));
    newVariable->symbol = (SymbolData*)malloc(sizeof(SymbolData));
    newVariable->symbol->name = strdup(variableName);
    newVariable->symbol->addr = -1;
    return newVariable;
}

void pushFunInParm(Object* variable) {
    if (!variable) {
        fprintf(stderr, "Error: NULL variable passed to pushFunInParm.\n");
        return;
    }
    FuncParmNode* newParmNode = (FuncParmNode*)malloc(sizeof(FuncParmNode));
    if (!newParmNode) {
        fprintf(stderr, "Error: Could not allocate memory for function parameter node.\n");
        return;
    }

    newParmNode->data = variable;
    newParmNode->next = funcParmStack;
    funcParmStack = newParmNode;

    //printf("> Pushed function parameter `%s` (type: %d, addr: %ld)\n", variable->symbol->name, variable->type, variable->symbol->addr);
}

void stdoutPrint() {
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        yyin = fopen(yyInputFileName = argv[1], "r");
    } else {
        yyin = stdin;
    }
    if (!yyin) {
        printf("file `%s` doesn't exists or cannot be opened\n", yyInputFileName);
        exit(1);
    }

    // Start parsing
    yyparse();
    printf("Total lines: %d\n", yylineno);
    fclose(yyin);

    yylex_destroy();
    return 0;
}