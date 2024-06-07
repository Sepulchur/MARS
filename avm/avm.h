#ifndef AVM_H
#define AVM_H

#define AVM_STACKSIZE  4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_STACKENV_SIZE 4
#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v
#define AVM_NUMACTUALS_OFFSET   +4
#define AVM_SAVEDPC_OFFSET      +3
#define AVM_SAVEDTOP_OFFSET     +2
#define AVM_SAVEDTOPSP_OFFSET   +1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "avm_table/avm_table.h"
#include "libfunc/libfunc.h"

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

typedef struct avm_table avm_table;

typedef struct avm_memcell {
    avm_memcell_t type;
    union {
        double          numVal;
        char*           strVal;
        unsigned char   boolVal;
        avm_table* tableVal;
        unsigned        funcVal;
        char*           libfuncVal;
    } data;
} avm_memcell;

typedef struct userfunc {
    unsigned    address;
    unsigned    localSize;
    char*       id;
} userfunc;

typedef struct instruction {
    vmopcode opcode;
    vmarg    result;
    vmarg    arg1;
    vmarg    arg2;
    unsigned srcLine;
} instruction;

typedef struct avm_table_bucket {
    avm_memcell         key;
    avm_memcell         value;
    struct avm_table_bucket* next;  
} avm_table_bucket;

struct avm_table {
    unsigned          refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
    unsigned          total;
};

typedef void (*memclear_func_t)(avm_memcell*);

extern avm_memcell stack[];
extern avm_memcell ax, bx, cx;
extern avm_memcell retval;

extern unsigned currLine;
extern unsigned top, topsp;
extern unsigned glob_mem;
extern unsigned pc;
extern unsigned totalActuals;
extern unsigned char executionFinished;

//elenxos
extern char** string_array;
extern double* number_array;
extern userfunc* userfunc_array;
extern char** libfunc_array;
extern unsigned userfuncs_a;
extern const char* memcell_typeToString[];
extern instruction* instructions; //tmp

static void avm_initstack(unsigned globals_a);

void avm_memcellclear(avm_memcell* m);

char* avm_tostring(avm_memcell* m);

avm_memcell* avm_getactual(unsigned i);

unsigned avm_totalactuals();

unsigned avm_get_envvalue(unsigned i);

void avm_callsaveenvironment();

void avm_dec_top(void);

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

void avm_assign(avm_memcell* lv, avm_memcell* rv);

void avm_error(char *format, ...);

void avm_warning(char *format, ...);

#endif
