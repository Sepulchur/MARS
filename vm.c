#include "quad.h"
#include "vm.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "math.h"

unsigned fstart_flag = 0; 
unsigned fcounter = 0; 
unsigned currStringConst = 0;
char** namedLibfuncs;
unsigned currLibfunct = 0;
extern unsigned currQuad ; 
extern quad* quads;
unsigned counter = 0 ;

unsigned currUserfunct = 0;

unsigned currInstructions = 0;
unsigned totalInstructions = 0;

instruction* instructions = (instruction*)0;

unsigned  totalNumConsts    = 0;
unsigned  currNumConst      = 0;
unsigned  totalNameLibfuncs = 0;
unsigned  totalUserFuncs    = 0;
unsigned  totalStringConsts = 0;
double*   numConsts;
char**    stringConsts;
userfunc* userFuncs;



avm_memcell stack[AVM_STACKSIZE];

stackFunc* funcstack;

void initializeFuncStack(stackFunc *s) {
    if (funcstack == NULL) {
        fprintf(stderr, "Error: funcstack pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
    s->capacity = 1;
    s->stack_array = (SymbolTableEntry_t**)malloc(s->capacity * sizeof(SymbolTableEntry_t*));
    if (s->stack_array == NULL) {
        fprintf(stderr, "Error: Memory allocation for stack_array failed\n");
        exit(EXIT_FAILURE);
    }
    s->top = 0;
}

void resizeFuncStack(stackFunc *s) {
    int new_capacity = s->capacity * 2; 
    SymbolTableEntry_t** new_array = (SymbolTableEntry_t**)realloc(s->stack_array, new_capacity * sizeof(SymbolTableEntry_t*));
    if (new_array == NULL) {
        printf("Failed to allocate memory during resize!\n");
        return; 
    }
    s->stack_array = new_array;
    s->capacity = new_capacity;
}

void pushf(stackFunc *s, SymbolTableEntry_t *sym) {
    if (s->top == s->capacity) {
        resizeFuncStack(s);
    }
    s->stack_array[s->top] = sym;
    s->top++;
}

SymbolTableEntry_t* topf(stackFunc* s) {
    if (s->top == 0) {
        printf("ERROR, stack is empty!\n");
        return NULL;
    }
    return s->stack_array[s->top - 1];
}

SymbolTableEntry_t* popf(stackFunc *s) {
    if (s->top == 0) {
        printf("ERROR, stack is empty!\n");
        return NULL;
    }
    s->top--;
    return s->stack_array[s->top];
}

unsigned consts_newstring(char* s) {
    char** t;
    if(currStringConst == totalStringConsts){
        string_expand();
    }
    t = stringConsts + currStringConst++;
    *t = s;
    return currStringConst - 1;
}

unsigned consts_newnumber(double n){
    double* t;
    if(currNumConst == totalNumConsts){
        num_expand();
    }
    t = numConsts + currNumConst++;
    *t = n;
    return currNumConst - 1;
}

unsigned libfuncts_newused(char* s){
    char** t;
    if(currLibfunct == totalNameLibfuncs){
        libfunc_expand();
    }
    t = namedLibfuncs + currLibfunct++;
    *t = s;
    return currLibfunct - 1;
}

unsigned userfuncts_newfunc(SymbolTableEntry_t* sym){
    userfunc* t;
    unsigned  size = 0;
    if(currUserfunct == totalUserFuncs){
        userfunc_expand();
    }
    t = userFuncs + currUserfunct++;
    t->id = sym->passport.name;
    t->address = sym->address;
    ArgList* temp = sym->argList;
    while(temp != NULL){
        temp = temp->next;
        size++;
    }
    t->localSize = size;
    t->saved_index = fcounter++;

    return currUserfunct - 1;
}

void make_operand(expr* e, vmarg* arg){

    if(e != NULL){
        switch(e->type){
            case var_e:{                

                assert(e->sym);
                arg->val = e->sym->offset;
                if(e->sym->type == USERFUNC){
                    arg->type = userfunc_a;
                }
                else if(e->sym->type == LIBFUNC){
                    arg->type = libfunc_a;
                }
                else{
                    switch(e->sym->space){
                        case programvar:
                            arg->type = global_a;
                            break;
                        case functionlocal:
                            arg->type = local_a;
                            break;
                        case formalarg:
                            arg->type = formal_a;
                            break;
                        default:
                            assert(0);
                    }
                }
                break;
            }
            case tableitem_e:{               
                switch(e->sym->space){
                    case programvar:
                        arg->type = global_a;
                        break;
                    case functionlocal:
                        arg->type = local_a;
                        break;
                    case formalarg:
                        arg->type = formal_a;
                        break;
                    default:
                        assert(0);
                }
                break;
            }
            case arithexpr_e:{
                assert(e->sym);
                arg->val = e->sym->offset;
                switch(e->sym->space){
                    case programvar:
                        arg->type = global_a;
                        break;
                    case functionlocal:
                        arg->type = local_a;
                        break;
                    case formalarg:
                        arg->type = formal_a;
                        break;
                    default:
                        assert(0);
                }
                break;
            }
            case boolexpr_e:{
                if(e->sym->passport.name[0] == '_'){
                    arg->type=global_a;
                    arg->val = e->sym->offset;               
                }
                break;
            }
            case assignexpr_e:{
                assert(e->sym);
                arg->val = e->sym->offset;
                switch(e->sym->space){
                    case programvar:
                        arg->type = global_a;
                        break;
                    case functionlocal:
                        arg->type = local_a;
                        break;
                    case formalarg:
                        arg->type = formal_a;
                        break;
                    default:
                        assert(0);
                }
                break;
            }
            case newtable_e:{
                assert(e->sym);
                arg->val = e->sym->offset;
                switch(e->sym->space){
                    case programvar:
                        arg->type = global_a;
                        break;
                    case functionlocal:
                        arg->type = local_a;
                        break;
                    case formalarg:
                        arg->type = formal_a;
                        break;
                    default:
                        assert(0);
                }
                break;
            }
            case constbool_e:{
                arg->val = e->boolConst;
                arg->type = bool_a;
                break;
            }
            case conststring_e:{
                arg->val = consts_newstring(e->strConst);
                arg->type = string_a;
                break;
            }
            case constnum_e:{
                arg->val = consts_newnumber(e->numConst);
                arg->type = number_a;
                break;
            }
            case nil_e:{
                arg->type = nil_a;
                break;
            }
            case programfunc_e:{
                arg->type = userfunc_a;
                if(fstart_flag){
                    e->sym->address = nextinstructionlabel();
                    arg->val = userfuncts_newfunc(e->sym);
                    fstart_flag = 0;
                }else{
                    int i;
                    for(i = currUserfunct; i>=0; i--){
                        if((fcounter - userFuncs[i].saved_index < 2) && userFuncs[i].id == e->sym->passport.name){
                            arg->val = i;
                            break;
                        }
                    }
                }

                break; 
            }
            case libraryfunc_e:{
                arg->type = libfunc_a;
                arg->val = libfuncts_newused(strdup(e->sym->passport.name));//strdup
                break;
            }
            default:
                assert(0);
        }
    }
}

void make_numberoperand(vmarg* arg, double val) {
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}

void make_booloperand(vmarg* arg, unsigned val) {
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg) {
    arg->type = retval_a;
}

struct incomplete_jump*    ij_head  = (incomplete_jump*)0;
unsigned                   ij_total = 0;

void add_incomplete_jump(unsigned instrNo, unsigned iaddress) {
    incomplete_jump* ij = (incomplete_jump*)malloc(sizeof(incomplete_jump));
    ij->instrNo = instrNo;
    ij->iaddress = iaddress;
    if(ij_head == (incomplete_jump*) 0){
        ij_head = ij;
        ij_head->next = NULL;
        return;
    }
    ij->next = ij_head;
    ij_head = ij;
    ij_total++;
}

void patch_incomplete_jumps() {
    incomplete_jump* ij = ij_head;
    printf("%d " , ij->instrNo);
    while(ij != NULL){
        if(ij->iaddress == nextquadlabel()){
            instructions[ij->instrNo].result.val = nextinstructionlabel(); 
        } 
        else{
            instructions[ij->instrNo].result.val = quads[ij->iaddress].taddress;
        }
        ij = ij->next;
    }  
}

void generate(vmopcode op, quad* q) {
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = op;

    make_operand(q->result, &(t->result));
    make_operand(q->arg1, &(t->arg1));
    make_operand(q->arg2, &(t->arg2));

    t->srcLine = q->line;
    q->taddress = nextinstructionlabel();

    emitInstruction(t);
}

void generate_ADD(quad* q) { generate(add_v, q); }
void generate_SUB(quad* q) { generate(sub_v, q); }
void generate_MUL(quad* q) { generate(mul_v, q); }
void generate_DIV(quad* q) { generate(div_v, q); }
void generate_MOD(quad* q) { generate(mod_v, q); }
void generate_NEWTABLE(quad* q)     { generate(newtable_v, q); }
void generate_TABLEGETELEM(quad* q) { generate(tablegetelem_v, q); }
void generate_TABLESETELEM(quad* q) { generate(tablesetelem_v, q); }
void generate_ASSIGN(quad* q)       { generate(assign_v, q); }
void generate_NOP(quad* q) {
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = nop_v;
    emitInstruction(t);
}

void generate_relational(vmopcode op, quad *q){
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = op;
    make_operand(q->arg1, &(t->arg1));
    make_operand(q->arg2, &(t->arg2));

    t->result.type = label_a;
    if (q->result->numConst < q->label) {
        t->result.val = quads[q->label].result->numConst; /* ???t->result.val = quads[q->label].taddress;?? To taddress exei to rolo tou result numconst se jumps (target adress) */
    } else {
        add_incomplete_jump(nextinstructionlabel(), q->label);
    }
    q->taddress = nextinstructionlabel();
    emitInstruction(t);
}

void generate_JUMP(quad* q)         { generate_relational(jump_v, q); }
void generate_IF_EQ(quad* q)        { generate_relational(jeq_v, q);  }
void generate_IF_NOTEQ(quad* q)     { generate_relational(jne_v, q);  }
void generate_IF_GREATER(quad* q)   { generate_relational(jgt_v, q);  }
void generate_IF_GREATEREQ(quad* q) { generate_relational(jge_v, q);  }
void generate_IF_LESS(quad* q)      { generate_relational(jlt_v, q);  }
void generate_IF_LESSEQ(quad* q)    { generate_relational(jle_v, q);  }

void generate_NOT(quad* q){
    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = jeq_v;

    make_operand(q->arg1, &(t->arg1));
    make_booloperand(&(t->arg2), false);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel() + 3;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(&(t->arg1), false);
    reset_operand(&(t->arg2));
    make_operand(q->result, &(t->result));
    emitInstruction(t);

    t->opcode = jump_v;
    reset_operand(&(t->arg1));
    reset_operand(&(t->arg2));
    t->result.type = label_a;
    t->result.val = nextinstructionlabel() + 2;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(&(t->arg1), true);
    reset_operand(&(t->arg2));
    make_operand(q->result, &(t->result));
    emitInstruction(t);
}

void generate_OR(quad* q){
    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));

    t->opcode = jeq_v;
    make_operand(q->arg1, &(t->arg1));
    make_booloperand(&(t->arg2), true);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel() + 4;
    emitInstruction(t);

    make_operand(q->arg2, &(t->arg1));
    t->result.val = nextinstructionlabel() + 3;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(&(t->arg1), false);
    reset_operand(&(t->arg2));
    make_operand(q->result, &(t->result));
    emitInstruction(t);

    t->opcode = jump_v;
    reset_operand(&(t->arg1));
    reset_operand(&(t->arg2));
    t->result.type = label_a;
    t->result.val = nextinstructionlabel() + 2;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(&(t->arg1), true);
    reset_operand(&(t->arg2));
    make_operand(q->result, &(t->result));
    emitInstruction(t);
}

void generate_PARAM(quad* q){
    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));

    t->opcode = pusharg_v;
    make_operand(q->arg1, &(t->arg1));//result
    emitInstruction(t);
}

void generate_CALL(quad* q){
    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    
    t->opcode = call_v;
    make_operand(q->arg1, &(t->arg1));//result
    emitInstruction(t);
}

void generate_GETRETVAL(quad* q){
    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));

    t->opcode = assign_v;
    make_operand(q->result, &(t->result));
    make_retvaloperand(&(t->arg1));
    emitInstruction(t);
}

void generate_AND(quad* q){
    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));

    t->opcode = jeq_v;
    make_operand(q->arg1, &(t->arg1));
    make_booloperand(&(t->arg2), 0);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel() + 4;
    emitInstruction(t);

    make_operand(q->arg2, &(t->arg1));
    t->result.val = nextinstructionlabel() + 3;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(&(t->arg1), 1);
    reset_operand(&(t->arg2));
    make_operand(q->result, &(t->result));
    emitInstruction(t);

    t->opcode = jump_v;
    reset_operand(&(t->arg1));
    reset_operand(&(t->arg2));
    t->result.type = label_a;
    t->result.val = nextinstructionlabel() + 2;
    emitInstruction(t);

    t->opcode = assign_v;
    make_booloperand(&(t->arg1), 0);
    reset_operand(&(t->arg2));
    make_operand(q->result, &(t->result));
    emitInstruction(t);
}

void generate_FUNCSTART(quad* q){
    SymbolTableEntry_t* f;
    f = q->result->sym;
    f->address = nextinstructionlabel();
    q->taddress = nextinstructionlabel();

    /* userfunc.add(f->passport.name, f->taddress, f->totallocals); */
    pushf(funcstack, f);

    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = funcenter_v;
    fstart_flag = 1;
    make_operand(q->result, &(t->result));
    emitInstruction(t);
}
void generate_RETURN(quad* q){
    SymbolTableEntry_t* f;
    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));

    t->opcode = assign_v;
    make_retvaloperand(&(t->result));
    make_operand(q->arg1, &(t->arg1));
    emitInstruction(t);

    f = topf(funcstack);
    //pushf(f.returnList, nextinstructionlabel());

    t->opcode = jump_v;
    reset_operand(&(t->arg1));
    reset_operand(&(t->arg2));
    t->result.type = label_a;
    emitInstruction(t);
}

void generate_FUNCEND(quad* q){
    SymbolTableEntry_t* f;
    f = popf(funcstack);
    //backPatch(f.returnList, nextinstructionlabel());

    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = funcexit_v;
    fcounter--;
    make_operand(q->result, &(t->result));
    
    emitInstruction(t);
}

void generate_UMINUS(quad* q){

}

typedef void (*generator_func_t)(quad*);

generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,    
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP,
    generate_NOP
};


void generate_all(void){
    unsigned i;
    funcstack = (stackFunc*)malloc(sizeof(stackFunc));
    initializeFuncStack(funcstack);

    for(i = 0; i < nextquadlabel(); ++i){ 
        (*generators[quads[i].op])(quads + i);
        counter ++;
    }
    if(ij_head!= NULL){
        patch_incomplete_jumps();
    }
}

unsigned nextinstructionlabel(){
    return currInstructions;
}

void num_expand(){
    assert(totalNumConsts == currNumConst);
    double* p = (double*)malloc(EXPAND_SIZE * sizeof(double) + totalNumConsts * sizeof(double));
    if(numConsts){
        memcpy(p, numConsts, totalNumConsts * sizeof(double));
        free(numConsts);
    }
    numConsts = p;
    totalNumConsts += EXPAND_SIZE;
}

void string_expand(){
    assert(totalStringConsts == currStringConst);
    char** p = (char**)malloc(EXPAND_SIZE * sizeof + totalStringConsts * sizeof(char*));
    if(stringConsts){
        memcpy(p, stringConsts, totalStringConsts * sizeof(char*));
        free(stringConsts);
    }
    stringConsts = p;
    totalStringConsts += EXPAND_SIZE;
}

void userfunc_expand(){
    assert(totalUserFuncs == currUserfunct);
    userfunc* p = (userfunc*)malloc(EXPAND_SIZE * sizeof(userfunc) + totalUserFuncs * sizeof(userfunc));
    if(userFuncs){
        memcpy(p, userFuncs, totalUserFuncs * sizeof(userfunc));
        free(userFuncs);
    }
    userFuncs = p;
    totalUserFuncs += EXPAND_SIZE;
}

void libfunc_expand(){
    assert(totalNameLibfuncs == currLibfunct);
    char** p = (char**)malloc(EXPAND_SIZE * sizeof(char*) + totalNameLibfuncs * sizeof(char*));
    if(namedLibfuncs){
        memcpy(p, namedLibfuncs, totalNameLibfuncs * sizeof(char*));
        free(namedLibfuncs);
    }
    namedLibfuncs = p;
    totalNameLibfuncs += EXPAND_SIZE;
}

void instruction_expand(){
    assert(totalInstructions == currInstructions);
    instruction* p = (instruction*)malloc(EXPAND_SIZE * sizeof(instruction) + totalInstructions * sizeof(instruction));
    if(instructions){
        memcpy(p, instructions, totalInstructions * sizeof(instruction));
        free(instructions);
    }
    instructions = p;
    totalInstructions += EXPAND_SIZE;
}

void emitInstruction(instruction* temp){
    if(currInstructions == totalInstructions){
        instruction_expand();
    }

    instruction* i = instructions + currInstructions++;

    i->opcode = temp->opcode;
    i->result = temp->result;
    i->arg1 = temp->arg1;
    i->arg2 = temp->arg2;
    i->srcLine = temp->srcLine;
}

void reset_operand(vmarg* arg){
    arg = NULL;
}

void printInstructionDetails(int index, instruction instr) {
    char* opcodeNames[] = {
    "assign", "add", "sub", "mul", "div_", "mod", "uminus", "and",
    "or", "not", "if_eq", "if_noteq", "if_lesseq", "if_greatereq", "if_less", 
    "if_greater", "call_", "param",  "ret", "getretval", "funcstart", "funcend",    
    "tablecreate", "tablegetelem", "tablesetelem", "jump","nop" };
    printf("%d | %s | Result: Type %d Value %d ", index+1, opcodeNames[instr.opcode], instr.result.type, instr.result.val);

    if(instr.opcode == ret_v || instr.opcode== jump_v ||
    instr.opcode == funcenter_v || instr.opcode == funcexit_v ){

    }else{
        printf("| Arg1: Type %d Value %d", instr.arg1.type, instr.arg1.val);
        switch (instr.arg1.type) {
            case number_a:
                printf(" Number: %d", (int)numConsts[instructions[index].arg1.val]);
                break;
            case string_a:
                printf(" | String: \"%s\"", stringConsts[instr.arg1.val]);
                break;
            case userfunc_a:
                printf(" | User Function: %s", userFuncs[instructions[index].arg1.val].id);
                break;
            case libfunc_a:
                printf(" | Library Function: %s", namedLibfuncs[instructions[index].arg1.val]);
                break;
            default:
                break;
        }
    }


    if (instr.opcode == add_v || instr.opcode == sub_v || instr.opcode == mul_v || instr.opcode == div_v || instr.opcode == mod_v ||
        instr.opcode == jeq_v || instr.opcode == jne_v || instr.opcode == jle_v || instr.opcode == jge_v || instr.opcode == jlt_v ||
        instr.opcode == jgt_v || instr.opcode == tablegetelem_v || instr.opcode == tablesetelem_v) {
        printf(" | Arg2: Type %d Value %d\n", instr.arg2.type, instr.arg2.val);
        switch (instr.arg2.type) {
            case number_a:
                printf(" Number: %d", (int)numConsts[instructions[index].arg2.val]);
                break;
            case string_a:
                printf(" | String: \"%s\"", stringConsts[instr.arg2.val]);
                break;
            case userfunc_a:
                printf(" | User Function: %s", userFuncs[instructions[index].arg2.val].id);
                break;
            case libfunc_a:
                printf(" | Library Function: %s", namedLibfuncs[instructions[index].arg2.val]);
                break;
            default:
                break;
        }
    }
    printf("\n");
}

void printInstructions() {
    int nextInstructionCount = nextinstructionlabel(); 
    printf("\nInstruction Details:\n\n");
    for (int i = 0; i < nextInstructionCount; i++) {
        printInstructionDetails(i, instructions[i]);
    }
}   
