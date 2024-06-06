#ifndef vm_h
#define vm_h

#include "quad.h"
#include <stdbool.h>
#include <stdio.h>

#define AVM_TABLE_HASHSIZE 211
#define AVM_STACKSIZE  4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_STACKENV_SIZE 4
#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v
#define AVM_NUMACTUALS_OFFSET   +4
#define AVM_SAVEDPC_OFFSET      +3
#define AVM_SAVEDTOP_OFFSET     +2
#define AVM_SAVEDTOPSP_OFFSET   +1

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic
/* #define execute_jle execute_relational
#define execute_jge execute_relational
#define execute_jlt execute_relational
#define execute_jgt execute_relational */


typedef enum vmopcode {
    assign_v,
    add_v,
    sub_v,
    mul_v,
    div_v,
    mod_v,
    uminus_v,
    and_v,
    or_v,
    not_v,
    jeq_v,
    jne_v,
    jle_v,
    jge_v,
    jlt_v,
    jgt_v,
    call_v,                         
    pusharg_v,
    ret_v,
    getret_v,
    funcenter_v,
    funcexit_v,
    newtable_v,
    tablegetelem_v,
    tablesetelem_v,
    jump_v,
    nop_v
} vmopcode;

typedef enum vmarg_t {
    label_a    = 0,
    global_a   = 1,
    formal_a   = 2,
    local_a    = 3,
    number_a   = 4,
    string_a   = 5,
    bool_a     = 6,
    nil_a      = 7,
    userfunc_a = 8,
    libfunc_a  = 9,
    retval_a   = 10
} vmarg_t;

typedef struct vmarg {
    vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instruction {
    vmopcode opcode;
    vmarg    result;
    vmarg    arg1;
    vmarg    arg2;
    unsigned srcLine;
} instruction;

typedef struct userfunc {
    unsigned       address;
    unsigned       localSize;
    unsigned       saved_index;/*den*/
    const char*    id;
} userfunc;

typedef enum avm_memcell_t {
    number_m   = 0,
    string_m   = 1,
    bool_m     = 2,
    table_m    = 3,
    userfunc_m = 4,
    libfunc_m  = 5,
    nil_m      = 6,
    undef_m    = 7
} avm_memcell_t;

typedef struct avm_memcell {
    avm_memcell_t type;
    union {
        double          numVal;
        char*           strVal;
        unsigned char   boolVal;
        struct avm_table* tableVal;  // Forward declaration
        unsigned        funcVal;
        char*           libfuncVal;
    } data;
} avm_memcell;

typedef struct avm_table_bucket {
    avm_memcell         key;
    avm_memcell         value;
    struct avm_table_bucket* next;  // Use 'struct' keyword for self-referential struct
} avm_table_bucket;

typedef struct avm_table {
    unsigned          refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
    unsigned          total;
} avm_table;

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

void num_expand();

void string_expand();

void userfunc_expand();

void libfunc_expand();

void instruction_expand();

void emitInstruction(instruction* temp);

void reset_operand(vmarg* arg);

void printInstructionDetails(int index, instruction instr);

void printInstructions();

static void avm_initstack(void);


//--------------------------------------------------------------phase 5-----------------------------------------------------------------------------


void avm_warning(char* format);

void avm_error(char* format);

void avm_dec_top(void);

void push_global(int i);

static void avm_initstack(void);

void avm_tableincrefcounter(avm_table* t);

void avm_tabledecrefcounter(avm_table* t);

void avm_tablebucketsinit(avm_table_bucket** p);

avm_table* avm_tablenew(void);

void avm_tabledestroy(avm_table* t);

void memclear_string(avm_memcell* m);

void memclear_table(avm_memcell* m);

void avm_memcellclear(avm_memcell* m);

void avm_tablebucketdestroy(avm_table_bucket** p);

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

void avm_assign(avm_memcell* lv, avm_memcell* rv);

void execute_assign(instruction* instr);

void avm_call_functor(avm_table* t);

void avm_push_envvalue(unsigned val);

void avm_callsaveenvironment();

unsigned avm_get_envvalue(unsigned i);

userfunc* avm_getfuncinfo(unsigned address);

void execute_call(instruction* instr);

void execute_funcenter(instruction* instr);

void execute_funcexit(instruction* instr);

void avm_calllibfunc(char* id);

unsigned avm_totalactuals();

avm_memcell* avm_getactual(unsigned i);

void avm_push_table_arg (avm_table* t);

void execute_pusharg(instruction* instr);

char* avm_tostring(avm_memcell* m);

double add_impl(double x, double y);

double sub_impl(double x, double y);

double mul_impl(double x, double y);

double div_impl(double x, double y);

double mod_impl(double x, double y);

void execute_arithmetic(instruction* instr);

void execute_uminus(instruction* instr);

void execute_and(instruction* instr);

void execute_or(instruction* instr);

void execute_not(instruction* instr);

unsigned char number_tobool(avm_memcell* m);

unsigned char string_tobool(avm_memcell* m);

unsigned char bool_tobool(avm_memcell* m);

unsigned char table_tobool(avm_memcell* m);

unsigned char userfunc_tobool(avm_memcell* m);

unsigned char libfunc_tobool(avm_memcell* m);

unsigned char nil_tobool(avm_memcell* m);

unsigned char undef_tobool(avm_memcell* m);

unsigned char avm_tobool(avm_memcell* m);

void execute_jeq(instruction* instr);

void libfunc_typeof();

void libfunc_totalarguments();

void libfunc_print();

void execute_newtable(instruction* instr);

void execute_tablegetelem(instruction* instr);

void execute_tablesetelem(instruction* instr);

void execute_nop(instruction* instr);

void execute_jump(instruction* instr);

void execute_cycle(void);

#endif
