#ifndef quad_h
#define quad_h

#include "symTable.h"
#include <stdbool.h>

#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE  (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

typedef struct {
    unsigned int *items;
    int capacity;
    int top;
} UIntStack;

/*
 * Data Structure: stmt_t
 * ----------------------
 * Stores control information for statements, especially used in managing
 * break and continue lists in loop and control structures.
 *
 * Members:
 *  - breakList: Identifier for break list.
 *  - contList: Identifier for continue list.
 */
typedef struct stmt_t{
    int breakList, contList;
} stmt_t;

/*
 * Enum: iopcode
 * -------------
 * Enumerates the types of intermediate opcodes used in the compilation or
 * interpretation process.
 *
 * Values include ASSIGN, ADD, SUB, etc., representing different operations.
 */
typedef enum iopcode{
    assign, add, sub, mul, div_, mod, uminus, and,
    or, not, if_eq, if_noteq, if_lesseq, if_greatereq, if_less, 
    if_greater, call_, param,  ret, getretval, funcstart, funcend,    
    tablecreate, tablegetelem, tablesetelem, jump    
}iopcode;

/*
 * Enum: expr_t
 * ------------
 * Enumerates types of expressions in the system.
 *
 * Values include var_e, tableitem_e, programfunc_e, etc., representing
 * different kinds of expressions.
 */
typedef enum expr_t{
    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constnum_e,
    constbool_e,
    conststring_e,

    nil_e
}expr_t;

/*
 * Data Structure: expr
 * --------------------
 * Represents an expression in the system.
 *
 * Members:
 *  - type: Type of the expression, determined by expr_t.
 *  - sym: Associated symbol.
 *  - index: Index expression for array access.
 *  - numConst: Numeric constant, if any.
 *  - strConst: String constant, if any.
 *  - next: Pointer to the next expression in a list.
 *  - boolConst: Boolean constant, if any.
 */
typedef struct expr{
    expr_t  type;
    SymbolTableEntry_t* sym;
    struct expr* index;
    double  numConst;
    char*   strConst;
    struct expr* next;
    struct expr* trueList;
    struct expr* falseList;
    unsigned label;
    unsigned char boolConst;
}expr;

/*
 * Union: value
 * ------------
 * Represents a general purpose value in expressions, which can be either
 * an expression or a symbol.
 *
 * Members:
 *  - e: Pointer to an expression.
 *  - s: Pointer to a symbol.
 */
typedef union value{
    expr* e;
    SymbolTableEntry_t* s;
}type;

/*
 * Data Structure: quad
 * --------------------
 * Represents a quadruple, used in generating intermediate code.
 *
 * Members:
 *  - op: The operation code, defined by iopcode.
 *  - result: The result of the operation.
 *  - arg1: The first argument of the operation.
 *  - arg2: The second argument of the operation.
 *  - label: Label for control flow.
 *  - line: Line number in the source code.
 */
typedef struct quad{
    iopcode op;
    expr*   result;
    expr*   arg1;
    expr*   arg2;
    unsigned    label;
    unsigned    line;
}quad;

/*
 * Data Structure: call
 * --------------------
 * Represents a function call in the system.
 *
 * Members:
 *  - elist: A pointer to the first expression in the list of arguments passed to the call.
 *  - method: Indicates if the call uses a method-like access (possibly non-zero for true).
 *  - name: The name of the function being called.
 */
typedef struct call{
    expr* elist;
    unsigned char method;
    char* name;
}call;

/*
 * Function: expand
 * ----------------
 * Dynamically increases the size of the memory block allocated for quads array.
 * Ensures the array size is increased by the EXPAND_SIZE each time it reaches its current capacity.
 *
 * Preconditions:
 *  - 'total' should equal 'currQuad' to ensure memory is expanded accurately.
 * Postconditions:
 *  - Memory for quads is reallocated with increased size.
 *  - The old memory block is freed after copying its content to the new block.
 */
void expand(void);

/*
 * Function: emit
 * --------------
 * Emits a new quad to the quads array with the given opcode and operands.
 * Ensures memory is expanded if the current quads array is full.
 *
 * Parameters:
 *  - op: The opcode for the quad.
 *  - result: The result expression of the operation.
 *  - arg1: The first operand.
 *  - arg2: The second operand.
 *  - label: The control flow label associated with this quad.
 *  - line: The source line number associated with this operation.
 *
 * Postconditions:
 *  - A new quad is added to the quads array.
 */
void emit(iopcode op, expr* result, expr* arg1, expr* arg2, unsigned label, unsigned line);

/*
 * Function: newtempname
 * ---------------------
 * Generates a new temporary variable name.
 *
 * Returns:
 *  - A string representing a new unique temporary variable name.
 */
char* newtempname(void);

/*
 * Function: resettemp
 * -------------------
 * Resets the temporary variable counter to zero.
 * This function is typically called to reinitialize the counter for temporary variables.
 *
 * Postconditions:
 *  - The counter for temporary variable names is set to zero.
 */
void resettemp(void);

/*
 * Function: newtemp
 * -----------------
 * Creates a new temporary variable symbol.
 * If a symbol with the new temporary name does not exist, a new symbol is created.
 *
 * Parameters:
 *  - table: Pointer to the hashtable
 *  - sym: The type of symbol to be created.
 *  - name: Pointer to the variable where the new temporary name will be stored.
 *
 * Returns:
 *  - The newly created or existing symbol.
 */
SymbolTableEntry_t* newtemp(HashTable *table, symbol_t sym);

/*
 * Function: currscopespace
 * ------------------------
 * Determines the current scope space based on the value of the scope space counter.
 *
 * Returns:
 *  - The current scope space, which can be program variable, function local, or formal argument.
 */
scopespace_t currscopespace(void);

/*
 * Function: currscopeoffset
 * -------------------------
 * Returns the current offset in the current scope.
 * The offset is incremented after each new variable declaration.
 *
 * Returns:
 *  - The current offset in the scope space.
 */
unsigned currscopeoffset(void);

/*
 * Function: enterscopespace
 * -------------------------
 * Increments the scope space counter to transition to a new scope space.
 * This function is called when entering a new function or a new block of code.
 *
 * Postconditions:
 *  - The scope space counter is incremented.
 */
void enterscopespace(void);

/*
 * Function: exitscopespace
 * ------------------------
 * Decrements the scope space counter to return to the previous scope space.
 * This function is called when exiting a function or a block of code.
 *
 * Postconditions:
 *  - The scope space counter is decremented.
 */
void exitscopespace(void);

/*
 * Function: resetformalargsoffset
 * -------------------------------
 * Resets the offset for formal arguments.
 * This is used when starting to declare new formal arguments in a function.
 *
 * Postconditions:
 *  - The formal arguments offset is set to zero.
 */
void resetformalargsoffset(void);

/*
 * Function: resetfunctionlocalsoffset
 * -----------------------------------
 * Resets the offset for function locals.
 * This is used when starting to declare new local variables in a function scope.
 *
 * Postconditions:
 *  - The function locals offset is set to zero.
 */
void resetfunctionlocalsoffset(void);

/*
 * Function: restorecurrscopeoffset
 * --------------------------------
 * Restores the current scope offset to a specified value.
 * This function is typically used to roll back the scope offset after temporarily modifying it.
 *
 * Parameters:
 *  - n: The value to restore the current scope offset to.
 *
 * Postconditions:
 *  - The current scope offset is set to 'n'.
 */
void restorecurrscopeoffset(unsigned n);

/*
 * Function: nextquadlabel
 * -----------------------
 * Retrieves the next available label for a quad.
 * This function is useful for generating unique labels for control flow management.
 *
 * Returns:
 *  - The next available label.
 */
unsigned nextquadlabel(void);

/*
 * Function: patchlabel
 * --------------------
 * Assigns a label to a specific quad in the quads array.
 * This is used to update quads with correct jump targets after the targets are determined.
 *
 * Parameters:
 *  - quadNo: The index of the quad to patch.
 *  - label: The label to assign to the quad.
 *
 * Preconditions:
 *  - 'quadNo' must be a valid index in the quads array.
 *  - The quad at 'quadNo' should not already have a label assigned.
 *
 * Postconditions:
 *  - The specified quad is updated with the new label.
 */
void patchlabel(unsigned quadNo, unsigned label);

/*
 * Function: lvalue_expr
 * ---------------------
 * Creates an expression that represents an lvalue, typically used for variable access.
 *
 * Parameters:
 *  - sym: The symbol associated with the lvalue.
 *
 * Returns:
 *  - An expression pointer that represents the lvalue.
 */
expr* lvalue_expr(SymbolTableEntry_t* sym);

/*
 * Function: member_item
 * ---------------------
 * Creates an expression for accessing a member item of a structure or an array.
 *
 * Parameters:
 *  - lv: The expression representing the left value from which to access the member.
 *  - name: The name of the member to access.
 *
 * Returns:
 *  - An expression that represents the member item access.
 */
expr* member_item(expr* lv, char* name, HashTable *table, unsigned line);

/*
 * Function: newexpr
 * -----------------
 * Constructs a new expression of a specified type.
 *
 * Parameters:
 *  - t: The type of the expression to create.
 *
 * Returns:
 *  - A pointer to the newly created expression of type expr.
 */
expr* newexpr(expr_t t);

/*
 * Function: newexpr_conststring
 * -----------------------------
 * Constructs a new expression representing a constant string.
 *
 * Parameters:
 *  - s: The string value to embed in the expression.
 *
 * Returns:
 *  - A pointer to the newly created expression containing the string.
 */
expr* newexpr_conststring(char *s);

/*
 * Function: emit_iftableitem
 * --------------------------
 * Checks if the given expression is a table item expression and emits the necessary intermediate code
 * to handle table item access if required.
 *
 * Parameters:
 *  - e: The expression to check and process.
 *
 * Returns:
 *  - An expression that potentially modifies the original expression to handle table item access.
 */
expr* emit_iftableitem(expr* e, HashTable *table, unsigned line);

/*
 * Function: make_call
 * -------------------
 * Constructs a call expression to a function with a list of arguments.
 * This function generates intermediate quads for the call and argument passing.
 *
 * Parameters:
 *  - lv: The expression representing the function to call.
 *  - reversed_elist: The list of expressions representing the arguments, in reversed order.
 *
 * Returns:
 *  - An expression representing the result of the function call.
 */
expr* make_call(expr* lv, expr* reversed_elist, HashTable *table, unsigned line);

/*
 * Function: newexpr_constbool
 * ---------------------------
 * Constructs a new expression representing a constant boolean value.
 *
 * Parameters:
 *  - b: The boolean value (either 0 or 1) to embed in the expression.
 *
 * Returns:
 *  - A pointer to the newly created expression containing the boolean constant.
 */
expr* newexpr_constbool(unsigned int b);

/*
 * Function: comperror
 * -------------------
 * Prints an error message to the standard error stream.
 * This function is used for compiler error reporting.
 *
 * Parameters:
 *  - format: A format string as used in printf.
 *  - ...: A variable number of arguments matching the format string.
 *
 * Behavior:
 *  - The error message is formatted and printed to stderr.
 */
void comperror(char* format, ...);

/*
 * Function: check_arith
 * ---------------------
 * Checks if an expression is valid for arithmetic operations.
 * Reports an error if the expression is not suitable.
 *
 * Parameters:
 *  - e: The expression to check.
 *  - context: The context string describing where the check occurs.
 *
 * Postconditions:
 *  - If the expression is not suitable for arithmetic, an error message is reported.
 */
void check_arith(expr* e, const char* context);

/*
 * Function: istempname
 * --------------------
 * Checks if the provided string represents a temporary variable name.
 *
 * Parameters:
 *  - s: A string representing the name to check.
 *
 * Returns:
 *  - Non-zero if the name is a temporary variable name; otherwise, zero.
 */
unsigned int istempname(const char* s);

/*
 * Function: istempexpr
 * --------------------
 * Determines if the given expression represents a temporary variable.
 *
 * Parameters:
 *  - e: Pointer to the expression to check.
 *
 * Returns:
 *  - Non-zero if the expression represents a temporary variable; otherwise, zero.
 */
unsigned int istempexpr(expr* e);

/*
 * Function: patchlabel
 * --------------------
 * Assigns a specific label to a quad at a given index.
 *
 * Parameters:
 *  - quadNo: The index of the quad to modify.
 *  - label: The label to assign to the quad.
 *
 * Preconditions:
 *  - 'quadNo' must be less than the total number of quads currently managed.
 *  - The quad at the specified index should not have a label assigned.
 *
 * Postconditions:
 *  - The quad at the specified index is updated with the new label.
 */
void patchlabel(unsigned quadNo, unsigned label);

/*
 * Function: newexpr_constbool
 * ---------------------------
 * Creates a new expression that holds a constant boolean value.
 *
 * Parameters:
 *  - b: The boolean value (0 or 1) to be stored in the expression.
 *
 * Returns:
 *  - A pointer to the newly created boolean expression.
 */
expr* newexpr_constbool(unsigned int b);

/*
 * Function: nextquad
 * ------------------
 * Retrieves the next available index for creating a new quad.
 *
 * Returns:
 *  - The index where the next quad will be placed.
 */
unsigned nextquad(void);

/*
 * Function: make_stmt
 * -------------------
 * Initializes a statement control structure used for managing break and continue lists.
 *
 * Parameters:
 *  - s: A pointer to the statement structure to initialize.
 *
 * Postconditions:
 *  - The provided statement structure is initialized with zeroed break and continue lists.
 */
void make_stmt(stmt_t* s);

/*
 * Function: newlist
 * -----------------
 * Initializes a new list for label management, typically used in control structures.
 *
 * Parameters:
 *  - i: The initial index to start the list.
 *
 * Returns:
 *  - The starting index of the new list.
 */
int newlist(int i);


/*
 * Function: patchlist
 * -------------------
 * Assigns a label to all elements of a list, typically used to backpatch jumps in control structures.
 *
 * Parameters:
 *  - list: The list of quads to patch.
 *  - label: The label to assign to all quads in the list.
 *
 * Postconditions:
 *  - All quads in the specified list are updated with the provided label.
 */
void patchlist(int list, int label);

/*
 * Function: newexpr_constnum
 * --------------------------
 * Creates a new expression that holds a constant numeric value.
 *
 * Parameters:
 *  - i: The numeric value to be stored in the expression.
 *
 * Returns:
 *  - A pointer to the newly created numeric expression.
 */
expr* newexpr_constnum(double i);

SymbolTableEntry_t* returnTempName(expr *expr1, expr *expr3, HashTable *h);

int expr_checkType(expr *e, expr *e1);

expr_t expr_retType(expr *temp, expr *a, expr *b);

void incurrscopeoffset(void);

void initializeStack(UIntStack *s);

bool isFull(UIntStack *s);

bool isEmpty(UIntStack *s);

void resize(UIntStack *s);

void push(UIntStack *s, unsigned int item);

unsigned int pop(UIntStack *s);

unsigned int peek(UIntStack *s);

void freeStack(UIntStack *s);

void H_insertExtras(SymbolTableEntry_t *s);

int expr_checkType(expr *e, expr *e1);

expr_t expr_retType(expr *temp, expr *a, expr *b);

SymbolTableEntry_t* returnTempName(expr *expr1, expr *expr3, HashTable *h);

expr* mergelist(expr* list1, expr* list2);

void backPatch(expr* list, unsigned label);

expr* createTrueList(unsigned label);

expr* createFalseList(unsigned label);

const char* opcodeToString(iopcode op);

char *exprToString(expr *e);

void printQuad(FILE *f, int index);

void printQuads(FILE *f);

void freeQuads(void);

void freeExpr(expr* e);

expr *relopEmit(expr *E, expr *arg1, expr  *arg2, iopcode op, int line);

expr *logicEmit(expr *E, int line);

void patchBreakContinue(UIntStack *s, unsigned label);

expr* cloneList(expr* head); //dritsas

#endif /* quad_h */
