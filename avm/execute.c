#include "execute.h"

void execute_call(instruction* instr){
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
/*     avm_callsaveenvironment();
    restore_pc = pc; */

    switch(func->type){
        case userfunc_m:{
            avm_callsaveenvironment();
            pc = userFuncs[func->data.funcVal].address;
            assert(pc < AVM_ENDING_PC);
            assert(instructions[pc].opcode == funcenter_v);
            break;
        }
        case string_m:
            avm_calllibfunc(func->data.strVal);
            break;
        case libfunc_m:
            avm_calllibfunc(func->data.libfuncVal);
            break;
        case table_m: 
            avm_call_functor(func->data.tableVal);
            break;
        default:{
            char* s = avm_tostring(func);
/*             char buffer[50];
            sprintf(buffer, "call: cannot bind '%s' to function!", s); */
            avm_error(s);
            free(s);
            executionFinished = 1;
        }
    }
}

void execute_call(instruction *instr){
	avm_memcell* func = avm_translate_operand(instr->res_type, instr->res_val, &ax);
	assert(func);
	
	switch(func->type){

		case userfunc_m:
			avm_callsaveenvironment();
			pc = func->data.funcVal;
			assert(instructions[pc].op == 20);/* funcenter */
			break;

		case string_m:
			avm_callsaveenvironment();
			avm_calllibfunc(func->data.strVal);
			break;

		case libfunc_m:
			avm_callsaveenvironment();
			avm_calllibfunc(func->data.libfuncVal);
			break;
		
		case table_m:{
			avm_memcell call;
			call.type = string_m;
			call.data.strVal = "()";
			avm_memcell* fvalue = Atable_get_elem(func->data.tableVal, &call);
			if(!fvalue){
				avm_error("Table has no functor.\n");
			} 
			else {
				if(fvalue->type != userfunc_m){
					avm_error("Not a function at key: '()' of table.\n");
				}
				avm_assign(&stack[top], func);
				totalActuals++;
				avm_dec_top();
				avm_callsaveenvironment();
				pc = fvalue->data.funcVal;
				assert(instructions[pc].op == 20);
			}
			break;
		}

		default: {
			avm_error("call: cannot bind %s to function", memcell_typeToString[func->type]);
		}
	}
}