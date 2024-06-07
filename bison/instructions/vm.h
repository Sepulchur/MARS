#ifndef vm_h
#define vm_h

#include "../quads/quad.h"
#include "../../avm/avm.h"

typedef struct stackFunc {
    unsigned    top;
    int         capacity;
    SymbolTableEntry_t**  stack_array;
} stackFunc;

void initializeFuncStack(stackFunc *s);

void resizeFuncStack(stackFunc *s);

void pushf(stackFunc *s, SymbolTableEntry_t *sym);

SymbolTableEntry_t* topf(stackFunc* s);

SymbolTableEntry_t* popf(stackFunc *s);

unsigned consts_newstring(char* s);

unsigned consts_newnumber(double n);

unsigned libfuncts_newused(char* s);

unsigned userfuncts_newfunc(SymbolTableEntry_t* sym);

void make_operand(expr* e, vmarg* arg);

void make_numberoperand(vmarg* arg, double val);

void make_booloperand(vmarg* arg, unsigned val);

void make_retvaloperand(vmarg* arg);

typedef struct incomplete_jump {
    unsigned            instrNo;
    unsigned            iaddress;
    struct incomplete_jump*    next;
} incomplete_jump;

void add_incomplete_jump(unsigned instrNo, unsigned iaddress);

void patch_incomplete_jumps();

void generate(vmopcode op, quad* q);

void generate_ADD(quad* q);
void generate_SUB(quad* q);
void generate_MUL(quad* q);
void generate_DIV(quad* q);
void generate_MOD(quad* q);
void generate_NEWTABLE(quad* q);
void generate_TABLEGETELEM(quad* q);
void generate_TABLESETELEM(quad* q);
void generate_ASSIGN(quad* q);
void generate_NOP(quad* q);

void generate_relational(vmopcode op, quad* q);

void generate_JUMP(quad* q);
void generate_IF_EQ(quad* q);
void generate_IF_NOTEQ(quad* q);
void generate_IF_GREATER(quad* q);
void generate_IF_GREATEREQ(quad* q);
void generate_IF_LESS(quad* q);
void generate_IF_LESSEQ(quad* q);

void generate_NOT(quad* q);

void generate_OR(quad* q);

void generate_PARAM(quad* q);

void generate_CALL(quad* q);

void generate_GETRETVAL(quad* q);

void generate_AND(quad* q);

void generate_FUNCSTART(quad* q);

void generate_RETURN(quad* q);

void generate_FUNCEND(quad* q);

void generate_UMINUS(quad* q);

void generate_all(void);

unsigned nextinstructionlabel();

void expandNumberConstants();

void expandStringConstants();

void expandUserFunctions();

void expandLibraryFunctions();

void expandInstructions();

void emitInstruction(instruction* temp);

void resetOperand(vmarg* arg);

void printInstructionDetails(int index, instruction instr);

void printInstructions();

#endif
