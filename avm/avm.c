#include "avm.h"

#define AMV_ENV_SIZE 4

const char* memcell_typeToString[] = {
	"number", 
    "string", 
    "bool", 
    "table", 
    "userfunc", 
    "libfunc", 
    "nil", 
    "undef"
};

avm_memcell stack[AVM_STACKSIZE];
avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;
unsigned glob_mem;
unsigned totalActuals;
unsigned pc = 0;
unsigned char executionFinished = 0;

static inline void (*avm_getlibraryfunc(char* id))(char*) {
    unsigned i;
    for(i = 0; i < F_ARRAY_SIZE; ++i){
        if(strcmp(executeLibFuncs[i].id, id) == 0){
            return executeLibFuncs[i].func;
        }
    }
    return NULL;
}

static inline void avm_calllibfunc(char* id) {
    void (*f)(char*) = avm_getlibraryfunc(id);
    if(!f){
        invalid_libfunc(id);
        executionFinished =1;
    } 
    else{
        avm_callsaveenvironment();
        topsp = top;
        totalActuals = 0;
        f(id);                              
        if(!executionFinished){             
            //execute_funcexit(NULL); 
        }
    }
}

void avm_initstack(unsigned globals_a){
    unsigned i;
	for(i = 0; i < AVM_STACKSIZE; ++i){
		stack[i].type = undef_m;
	}
	ax.type = undef_m;
	bx.type = undef_m;
	cx.type = undef_m;
	retval.type = undef_m;
	glob_mem = AVM_STACKSIZE -1 - globals_a;
	top = glob_mem;
}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
    switch (arg->type){
        case global_a:
            return &stack[AVM_STACKSIZE - 1 - (arg->val)];
        case local_a:
            return &stack[topsp - (arg->val)];
        case formal_a:
            return &stack[topsp + AVM_STACKENV_SIZE + 1 + (arg->val)];
        case retval_a:
            return &retval;
        case number_a:{
            avm_memcellclear(reg);
            reg->type = number_m;
            reg->data.numVal = num_array[arg->val];
            return reg;
        }
        case string_a:{
            avm_memcellclear(reg);
            reg->type = string_m;
            reg->data.strVal = strdup(string_array[arg->val]);
            return reg;
        }
        case bool_a:{
            avm_memcellclear(reg);
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        }
        case nil_a:{
            avm_memcellclear(reg);
            reg->type = nil_m;
            return reg;
        }
        case userfunc_a:{
            avm_memcellclear(reg);
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val; 
            return reg;
        }
        case libfunc_a:{
            avm_memcellclear(reg);
            reg->type = libfunc_m;
            reg->data.libfuncVal = libfunc_array[arg->val];
            return reg;
        }
        default:
            assert(0);
            break;
    }
}

void avm_assign(avm_memcell* lv, avm_memcell* rv){
    if(lv == rv){
        return; 
    }

    if(lv->type == table_m && 
        rv->type == table_m && 
        lv->data.tableVal == rv->data.tableVal){

        return; 
    }

    if(rv->type == undef_m){
        avm_warning("assigning from 'undef' content!");
    }

    avm_memcellclear(lv);                
    memcpy(lv, rv, sizeof(avm_memcell)); 

    if(lv->type == string_m){
        lv->data.strVal = strdup(rv->data.strVal);
    } 
    else if(lv->type == table_m){
        avm_tableincrefcounter(lv->data.tableVal);
    }
}

void memclear_string(avm_memcell* m){
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell* m){
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}

memclear_func_t memclearFuncs[] ={
    0,               /* number */
    memclear_string, /* string */
    0,               /* bool */
    memclear_table,  /* table */
    0,               /* userfunc */
    0,               /* libfunc */
    0,               /* nil */
    0,               /* undef */
};

void avm_memcellclear(avm_memcell* m){
    if(m->type != undef_m){
        memclear_func_t f = memclearFuncs[m->type];
        if(f){
            (*f)(m);
        }
        m->type = undef_m;
    } 
}

void avm_dec_top(void){
    if(!top){
        avm_error("Stack Overflow.\n");
        executionFinished = 1;
    } 
    else{
        --top;
    }
}

void avm_push_envvalue(unsigned val){
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

void avm_callsaveenvironment(){
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc + 1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}

unsigned avm_get_envvalue(unsigned i){
    assert(stack[i].type == number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double)val));
    return val;
}

unsigned avm_totalactuals(){
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
	assert(i < avm_totalactuals());
	return &stack[topsp + AMV_ENV_SIZE + 1 + i];
}

void avm_error(char *format, ...) {
    va_list args;

    printf("\033[31m");

    va_start(args, format); 
    vprintf(format, args);  
    va_end(args);  

    printf("\033[0m");
}

void avm_warning(char *format, ...) {
    va_list args;

    printf("\033[33m");

    va_start(args, format); 
    vprintf(format, args);  
    va_end(args);  

    printf("\033[0m");
}

static inline bool isInt(double num){
	return num == (int)num;
}
static inline bool isWholeNumber(double num) {
    double intPart;
    return modf(num, &intPart) == 0.0;
}

char* avm_tostring(avm_memcell* memcell){
	char *buffer;
	switch(memcell->type){
		case number_m:{
			buffer = malloc(25);
			if(isWholeNumber(memcell->data.numVal)){
				sprintf(buffer, "%.0lf", memcell->data.numVal);
            }
			else{
				sprintf(buffer, "%.3lf", memcell->data.numVal);
            }
			return buffer;
		}
		case string_m:{
			buffer = strdup(memcell->data.strVal);
			return buffer;
		}
		case bool_m:{
			buffer = malloc(6);
			memcell->data.boolVal == 0 ? strcpy(buffer,"false") : strcpy(buffer,"true");
			return buffer;
		}
		case table_m:{
			return avm_getable(memcell->data.tableVal);
		}
		case userfunc_m:{
			buffer = malloc(20);
			sprintf(buffer, "userfunc %u", memcell->data.funcVal);
			return buffer;
		}
		case libfunc_m:{
			buffer = malloc(27);
			sprintf(buffer, "libfunc %s", memcell->data.libfuncVal);
			return buffer;
		}
		case nil_m:{
			buffer = malloc(4);
			strcpy(buffer, "nil");
			return buffer;
		}
		case undef_m:{
			avm_error("Cannot print undefined.\n");
		}

		default:assert(0);
	}
	return NULL;
}
