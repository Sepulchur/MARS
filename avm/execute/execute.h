#ifndef EXECUTE_H
#define EXECUTE_H

#include "../avm.h"

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

typedef void (*execute_func_t)(instruction*);
typedef double (*arithmetic_func_t)(double x, double y);
typedef unsigned char (*tobool_func_t)(avm_memcell*);

static double add_impl(double x, double y) {return x+y;}
static double sub_impl(double x, double y) {return x-y;}
static double mul_impl(double x, double y) {return x*y;}
static double div_impl(double x, double y){
    if(y != 0){
        return x / y;
    } 
	else{
        avm_error("Division by 0");
		executionFinished = 1;
    }
}
static double mod_impl(double x, double y){
    if(y != 0){
        return ((unsigned)x) % ((unsigned)y);
    } 
	else{
        avm_error("Division by 0");
		executionFinished = 1;
    }
}

extern unsigned totalActuals;

void execute_assign(instruction *instr);

void execute_arithmetic(instruction *instr);

void execute_jeq(instruction *instr);

void execute_jne(instruction *instr);

void execute_jle(instruction *instr);

void execute_jge(instruction *instr);

void execute_jlt(instruction *instr);

void execute_jgt(instruction *instr);

void execute_call(instruction *instr);

void execute_pusharg(instruction *instr);

void execute_funcenter(instruction *instr);

void execute_funcexit(instruction *instr);

void execute_newtable(instruction *instr);

void execute_tablegetelem(instruction *instr);

void execute_tablesetelem(instruction *instr);

void execute_jump(instruction *instr);

void execute_uminus(instruction* instr);

void execute_and(instruction* instr);

void execute_or(instruction* instr);

void execute_not(instruction* instr);

static inline void execute_nop(instruction *instr){
	perror("NO OP");
}

#endif
