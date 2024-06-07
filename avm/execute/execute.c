#include "execute.h"

char* typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"
};

arithmetic_func_t arithmeticFuncs [] = {
	add_impl,
	sub_impl,
	mul_impl,
	div_impl,
	mod_impl
};

unsigned char number_tobool(avm_memcell* m){ return m->data.numVal != 0; }
unsigned char string_tobool(avm_memcell* m){ return m->data.strVal[0] != 0; }
unsigned char bool_tobool(avm_memcell* m){ return m->data.boolVal; }
unsigned char table_tobool(avm_memcell* m){ return 1; }
unsigned char userfunc_tobool(avm_memcell* m){ return 1; }
unsigned char libfunc_tobool(avm_memcell* m){ return 1; }
unsigned char nil_tobool(avm_memcell* m){ return 0; }
unsigned char undef_tobool(avm_memcell* m){ return 0;}

tobool_func_t toboolFuncs[] ={
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool};


void execute_assign(instruction* instr){
    pc++;

    avm_memcell* lv = avm_translate_operand(&(instr->result), NULL);
    avm_memcell* rv = avm_translate_operand(&(instr->arg1), &ax);

    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));

    avm_assign(lv, rv);
}

static inline userfunc* avm_getfuncinfo(unsigned address){
	for(unsigned i = 0; i < userfuncs; i++){
		if(address == userfunc_array[i].address){
			return &userfunc_array[i];
        }
	}
	return NULL;
}

void execute_funcenter(instruction* instr){
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == func->data.funcVal); 

    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;
    pc++;
    avm_memcellclear(&retval);
}

void execute_funcexit(instruction* instr){
    unsigned oldTop = top;

    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while(++oldTop <= top){ 
        avm_memcellclear(&stack[top]);
    }
}

void execute_pusharg(instruction* instr){
    avm_memcell* arg = avm_translate_operand(&instr->result, &ax);
    assert(arg);
    avm_assign(&stack[top], arg);
    ++totalActuals;
    pc++;
    avm_dec_top(); 
}

void execute_arithmetic(instruction* instr){
    avm_memcell* lv = avm_translate_operand(&(instr->result), NULL);
    avm_memcell* rv1 = avm_translate_operand(&(instr->arg1), &ax);
    avm_memcell* rv2 = avm_translate_operand(&(instr->arg2), &bx);

    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv1 && rv2);

    if(rv1->type != number_m || rv2->type != number_m){
        avm_error("not a number inrithmetic!"); 
        executionFinished = 1;
    } 
    else{
	    double (*op)(double, double) = arithmeticFuncs[instr->opcode - 1];
        avm_memcellclear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }

    pc++;
}

static bool avm_tobool(avm_memcell* m){
	assert(m->type >= 0 && m->type < undef_m);
	return toboolFuncs[m->type](m);
}

void execute_jeq(instruction* instr){
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&(instr->arg1), &ax);
    avm_memcell* rv2 = avm_translate_operand(&(instr->arg2), &bx);

    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m){
        avm_error("'undef' involved in equality");
    } 
    else if (rv1->type == nil_m || rv2->type == nil_m){
        result = rv1->type == nil_m && rv2->type == nil_m;
    } 
    else if (rv1->type == bool_m || rv2->type == bool_m){
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    } 
    else if (rv1->type != rv2->type){
        avm_error("Comparing diffrent types of arguments");
        printf("%s == %s is illegal", typeStrings[rv1->type], typeStrings[rv2->type]);
    } 
    else{
    }

    if(!executionFinished && result){
        pc = instr->result.val;
    }
    else{
        pc++;
    }
} 

void execute_newtable(instruction* instr){
    pc++;
    avm_memcell* lv = avm_translate_operand(&instr->result, NULL);
    assert(lv && (&stack[AVM_STACKSIZE - 1]) >= lv && lv > &(stack[top]) || lv == &retval);

    avm_memcellclear(lv);

    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}


void execute_tablegetelem(instruction* instr){
    pc++;
    avm_memcell* lv = avm_translate_operand(&instr->result, NULL);
    avm_memcell* t = avm_translate_operand(&instr->arg1, NULL);
    avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);

    assert(lv && (&stack[AVM_STACKSIZE - 1]) >= lv && lv > &stack[top] || lv == &retval);
    assert(t && (&stack[AVM_STACKSIZE - 1]) >= t && t > &stack[top]);
    assert(i);

    avm_memcellclear(lv);

    lv->type = nil_m;

    if (t->type != table_m){
        avm_error("Illegal use of table");
        executionFinished = 1;
    } else{
        avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
        if (content){
            avm_assign(lv, content);
        } else{
            char* ts = avm_tostring(t);
            char* is = avm_tostring(i);
            avm_warning(" Cannot be found!");
            printf("%s [%s] not found!", ts, is);
            free(ts);
            free(is);
        }
    }
}

void execute_tablesetelem(instruction* instr){
    pc++;
    avm_memcell* t = avm_translate_operand(&instr->arg1, NULL);
    avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);
    avm_memcell* c = avm_translate_operand(&instr->result, &bx);

    assert(t && &stack[AVM_STACKSIZE - 1] >= t && t > &stack[top]);
    assert(i && c);

    if (t->type != table_m){
        avm_error("Error! illegal use of type %s as table!", typeStrings[t->type]);
        executionFinished = 1;
    } else{
        avm_tablesetelem(t->data.tableVal, i, c);
    }
}

void execute_jump(instruction* instr){
    pc = instr->result.val;
}

void execute_jne(instruction* instr){}

void execute_jge(instruction* instr){}

void execute_jlt(instruction* instr){}

void execute_jgt(instruction* instr){}

void execute_jle(instruction* instr){}

void execute_call(instruction* instr){
    printf("execute_call\n");
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);

    switch (func->type){
        case userfunc_m:{
            avm_callsaveenvironment();
            pc = func->data.funcVal;
            assert(pc < AVM_ENDING_PC);
            //assert(instructions[pc].opcode == funcenter_v);
            break;
        }
        case string_m:
            //avm_calllibfunc(func->data.strVal);
            break;
        case libfunc_m:
            //avm_calllibfunc(func->data.libfuncVal);
            break;
        case table_m: 
            //avm_call_functor(func->data.tableVal);
            break;
        default:{
            char* s = avm_tostring(func);
            avm_error(s);
            free(s);
            executionFinished = 1;
        }
    }
}

execute_func_t executeFuncs[] ={
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop,
    execute_jump
}; 

static inline void execute_cycle(void){
    if (executionFinished){
        return;
    } else if (pc == AVM_ENDING_PC){
        executionFinished = 1;
        return;
    } else{
        instruction* instr = instructions + pc;
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        unsigned oldPC = pc;
        currLine = instr->srcLine;
        executeFuncs[instr->opcode](instr);
        if (pc == oldPC){
            pc++;
        }
    }
}

void execute_uminus(instruction* instr){}

void execute_and(instruction* instr){}

void execute_or(instruction* instr){}

void execute_not(instruction* instr){}
