
//--------------------------------------------------------------phase 5-----------------------------------------------------------------------------

avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;
unsigned char executionFinished = 0;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;
unsigned totalActuals = 0;
#define AVM_ENDING_PC codeSize
extern void libfunc_print();
extern void libfunc_typeof();
extern void libfunc_totalarguments();
extern void libfunc_argument();
extern void libfunc_objecttotalmembers();
extern void libfunc_sqrt();
extern void libfunc_sin();
extern void libfunc_cos();
extern void libfunc_strtonum();
extern void libfunc_objectcopy();
extern void libfunc_objectmemberkeys();
extern void libfunc_input();

typedef void (*execute_func_t)(instruction*);
typedef char* (*tostring_func_t)(avm_memcell* m);
typedef void (*memclear_func_t)(avm_memcell*);
typedef double (*arithmetic_func_t)(double x, double y);
typedef unsigned char (*tobool_func_t)(avm_memcell*);
typedef void (*library_func_t)(void);
/* 
typedef unsigned char (*mydispatch_t)(avm_memcell* rv1, avm_memcell* rv2);
typedef unsigned char (*comparison_func_t)(double x, double y);
*/

void avm_warning(char* format){//!!!
    printf("Warning: %s \n", format);
}

void avm_error(char* format){
    printf("Error: %s \n", format);
}

void avm_dec_top(void){
    if (!top){
        avm_error("Stack Overflow"); /* Stack Overflow */
        executionFinished = 1;
    } else{
        --top;
    }
}

void push_global(int i){
    stack[top].data.numVal = i;
    avm_dec_top();
    topsp--;
}

static void avm_initstack(void){
    unsigned i;
    for(i = 0; i < AVM_STACKSIZE; ++i){
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }


/*     topsp = AVM_STACKSIZE - 1;
    top = AVM_STACKSIZE - 1;
    for (i = 0; i < total_globals; i++){
        push_global(i);
    }
    avm_registerlibfunc("print", libfunc_print);
    avm_registerlibfunc("typeof", libfunc_typeof);
    avm_registerlibfunc("totalarguments", libfunc_totalarguments);
    avm_registerlibfunc("argument", libfunc_argument);
    avm_registerlibfunc("objecttotalmembers", libfunc_objecttotalmembers);
    avm_registerlibfunc("sqrt", libfunc_sqrt);
    avm_registerlibfunc("cos", libfunc_cos);
    avm_registerlibfunc("sin", libfunc_sin);
    avm_registerlibfunc("strtonum", libfunc_strtonum);
    avm_registerlibfunc("objectcopy", libfunc_objectcopy);
    avm_registerlibfunc("objectmemberkeys", libfunc_objectmemberkeys);
    avm_registerlibfunc("input", libfunc_input); */


}

void avm_tableincrefcounter(avm_table* t){
    (t->refCounter)++;
}

void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter > 0);
    if(!--t->refCounter){
        avm_tabledestroy(t);
    }
}

void avm_tablebucketsinit(avm_table_bucket** p){
    unsigned i;
    for(i = 0; i < AVM_TABLE_HASHSIZE; i++){
        p[i] = (avm_table_bucket*)0;
    }
}

avm_table* avm_tablenew(void){
    avm_table* t = (avm_table*)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);

    return t;
}

void avm_tabledestroy(avm_table* t){
    avm_tablebucketdestroy(t->strIndexed);
    avm_tablebucketdestroy(t->numIndexed);
    free(t);
}

/* 
int avmHashNum(int key){
    return key % AVM_TABLE_HASHSIZE;
}


int avmHashStr(char* key){
    return atoi(key) % AVM_TABLE_HASHSIZE;
} */
/* 
avm_memcell* avm_tablegetelem(avm_table* t, avm_memcell* key){
    if (key->type == number_m){
        int tmp_key = avmHashNum(key->data.numVal);
        int key_found = 0;
        avm_table_bucket* iterate = t->numIndexed[tmp_key];

        while (iterate != NULL){
            if (iterate->key.data.numVal == key->data.numVal){
                key_found = 1;
                return &iterate->value;
            }
            iterate = iterate->next;
        }
        if (!key_found){
            avm_warning("Table element cannot be found");
            return NULL;
        }

    } else if (key->type == string_m){
        int tmp_key = avmHashStr(key->data.strVal);
        int key_found = 0;
        avm_table_bucket* iterate = t->strIndexed[tmp_key];

        while (iterate != NULL){
            if (strcmp(iterate->key.data.strVal, key->data.strVal) == 0){
                key_found = 1;
                return &iterate->value;
            }
            iterate = iterate->next;
        }
        if (!key_found){
            avm_warning("Table element cannot be found");
            return NULL;
        }
    } 
}*/
/*  
void avm_tablesetelem(avm_table* t, avm_memcell* key, avm_memcell* value){
   if (key->type == number_m){
        int tmp_key = avmHashNum(key->data.numVal);
        int key_found = 0;
        avm_table_bucket* new_bucket;

        if (t->numIndexed[tmp_key] != NULL){
            avm_table_bucket* iterate = t->numIndexed[tmp_key];

            while (iterate != NULL){
                if (iterate->key.data.numVal == key->data.numVal){
                    avm_assign(&iterate->value, value);
                    key_found = 1;
                    break;
                }
                iterate = iterate->next;
            }
            if (!key_found){
                new_bucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
                new_bucket->key = *key;
                new_bucket->value = *value;
                new_bucket->next = t->numIndexed[tmp_key];
                t->numIndexed[tmp_key] = new_bucket;
                t->total++;
            }
        } else{
            new_bucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
            new_bucket->key = *key;
            new_bucket->value = *value;
            new_bucket->next = t->numIndexed[tmp_key];
            t->numIndexed[tmp_key] = new_bucket;
            t->total++;
        }
    } else if (key->type == string_m){
        int tmp_key = avmHashStr(key->data.strVal);
        int key_found = 0;
        avm_table_bucket* new_bucket;

        if (t->strIndexed[tmp_key] != NULL){
            avm_table_bucket* iterate = t->strIndexed[tmp_key];

            while (iterate != NULL){
                if (strcmp(iterate->key.data.strVal, key->data.strVal) == 0){
                    avm_assign(&iterate->value, value);
                    key_found = 1;
                    break;
                }
                iterate = iterate->next;
            }
            if (!key_found){
                new_bucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
                new_bucket->key = *key;
                new_bucket->value = *value;
                new_bucket->next = t->strIndexed[tmp_key];
                t->strIndexed[tmp_key] = new_bucket;
                t->total++;
            }
        } else{
            new_bucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
            new_bucket->key = *key;
            new_bucket->value = *value;
            new_bucket->next = t->strIndexed[tmp_key];
            t->strIndexed[tmp_key] = new_bucket;
            t->total++;
        }
    } else if (key->type == nil_m){
    } 
}*/

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
    if (m->type != undef_m){
        memclear_func_t f = memclearFuncs[m->type];
        if (f){
            (*f)(m);
        }
        m->type = undef_m;
    } 
}

void avm_tablebucketdestroy(avm_table_bucket** p){
    unsigned i = 0;
    for(i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p){
        avm_table_bucket* b;
        for(b = *p; b;){
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&(del->key));
            avm_memcellclear(&(del->value));
            free(del);
        }
        p[i] = (avm_table_bucket*)0;
    }
}
/* double consts_getnumber(unsigned index){
    return newNumbertable[index];
}

char* consts_getstring(unsigned index){
    return newStringtable[index];
}

char* libfuncs_getused(unsigned index){
    return newLibFuncs[index];
}

void avm_dec_top(void){
    if (!top_avm){
        avm_error("Stack Overflow"); 
    } else{
        --top_avm;
    }
} */

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
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        }
        case string_a:{
            reg->type = string_m;
            reg->data.strVal = strdup(consts_getstring(arg->val));
            return reg;
        }
        case bool_a:{
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        }
        case nil_a:{
            reg->type = nil_m;
            return reg;
        }
        case userfunc_a:{
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val; 
            return reg;
        }
        case libfunc_a:{
            reg->type = libfunc_m;
            reg->data.libfuncVal = libfuncs_getused(arg->val);
            return reg;
        }
        default:
            assert(0);
            break;
    }
}


void avm_assign(avm_memcell* lv, avm_memcell* rv){
    if (lv == rv){
        return; 
    }

    if (lv->type == table_m && 
        rv->type == table_m && 
        lv->data.tableVal == rv->data.tableVal){

        return; 
    }

    if (rv->type == undef_m){
        avm_warning("assigning from 'undef' content!");
    }

    avm_memcellclear(lv);                
    memcpy(lv, rv, sizeof(avm_memcell)); 

    if (lv->type == string_m){
        lv->data.strVal = strdup(rv->data.strVal);
    } else if (lv->type == table_m){
        avm_tableincrefcounter(lv->data.tableVal);
    }
}

void execute_assign(instruction* instr){

    avm_memcell* lv = avm_translate_operand(&(instr->result), (avm_memcell*)0);
    avm_memcell* rv = avm_translate_operand(&(instr->arg1), &ax);

    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv);

    avm_assign(lv, rv);
}


void avm_call_functor(avm_table* t){
    cx.type =string_m;
    cx.data.strVal = "()";
    avm_memcell* f = avm_tablegetelem(t,&cx);
    if(!f){
        avm_error("in calling table: no '()' element found!");
    }
    else if(f->type == table_m){
        avm_call_functor(f->data.tableVal);
        }
    else if(f->type == userfunc_a){
        avm_push_table_arg(t);
        avm_callsaveenvironment();
        pc = f->data.funcVal;
        assert(pc < AVM_ENDING_PC && code[pc].opcode == funcenter_v);
    }
    else{
        avm_error("in calling table: illegal '()' element value");
    }
    
}

void avm_push_envvalue(unsigned val){
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

void avm_callsaveenvironment(){
    avm_push_envvalue(totalActuals);
    assert(code[pc].opcode == call_v);
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

userfunc* avm_getfuncinfo(unsigned address){
/*     int i = 0;
    while (i < userfunctotals){
        if (newuserFuncs[i].address == address){
            return &newuserFuncs[i];
        }
        i++;
    }
    return NULL; */
}

void execute_call(instruction* instr){
    printf("execute_call\n");
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
/*     avm_callsaveenvironment();
    restore_pc = pc; */

    switch (func->type){
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

void execute_funcenter(instruction* instr){
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == userFuncs[func->data.funcVal].address); /*func address should match pc */
    //avm_infunc++;
    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;
}

void execute_funcexit(instruction* instr){
        unsigned oldTop = top;

        top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
        pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
        topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

        while (++oldTop <= top){ 
            avm_memcellclear(&stack[top]);
        }

        //avm_infunc--;
}

/* library_func_t avm_getlibraryfunc(char* id){
    if (LibHashTable->Lib_HashTable[avmLibHash(id)] != NULL){
        return LibHashTable->Lib_HashTable[avmLibHash(id)];
    }
    return NULL;
} */

void avm_calllibfunc(char* id){
    library_func_t f = avm_getlibraryfunc(id);
    if (!f){
        avm_error("unsupported lib func");
        printf("'%s' called!", id);
        executionFinished =1;
    } else{
        avm_callsaveenvironment();
        topsp = top;
        totalActuals = 0;
        //avm_infunc++;
        (*f)();                                
        if (!executionFinished){             
            execute_funcexit((instruction*)0); 
        }
    }
}

/* unsigned avm_totalactuals_totArgs(){ 
    return avm_get_envvalue(cur_func_topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactualArgument(unsigned i){
    assert(i < avm_totalactuals_totArgs());
    return &stack[cur_func_topsp + AVM_STACKENV_SIZE + 1 + i];
} */

unsigned avm_totalactuals(){
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}


/*extern*/ void avm_push_table_arg (avm_table* t){
    stack[top].type = table_m;
    avm_tableincrefcounter(stack[top].data.tableVal = t);
    ++totalActuals;
    avm_dec_top();
}

void execute_pusharg(instruction* instr){
    avm_memcell* arg = avm_translate_operand(&instr->result, &ax);
    assert(arg);
    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top(); 
}

/* char* number_tostring(avm_memcell* m){
    char* buffer;
    buffer = malloc(sizeof(char*));
    sprintf(buffer, "%.3f", m->data.numVal);
    return buffer;vm.c:1656:5: error: ‘execute_jne’ undeclared here (not in a function); did you me
}

char* string_tostring(avm_memcell* m){
    return m->data.strVal;
}

char* bool_tostring(avm_memcell* m){
    if (m->data.boolVal == '1'){
        return "true";
    } else{
        return "false";
    }
}

char* table_tostring(avm_memcell* m){
    char* buffer;
    char* buffer1;
    buffer = malloc(8 * sizeof(char*));
    buffer1 = malloc(sizeof(char*));
    strcat(buffer, "[ ");
    int i;
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++){
        avm_table_bucket* temp = m->data.tableVal->strIndexed[i];
        while (temp != NULL){
            strcat(buffer, "{\"");
            strcat(buffer, temp->key.data.strVal);
            strcat(buffer, "\":");
            strcat(buffer, avm_tostring(&(temp->value)));
            strcat(buffer, "} ");
            temp = temp->next;
        }

        temp = m->data.tableVal->numIndexed[i];
        while (temp != NULL){
            strcat(buffer, "{");
            sprintf(buffer1, "%d", (int)temp->key.data.numVal);
            strcat(buffer, buffer1);
            strcat(buffer, ":");
            strcat(buffer, avm_tostring(&(temp->value)));
            strcat(buffer, "} ");

            temp = temp->next;
        }
    }

    strcat(buffer, "]");

    return buffer;
}

char* userfunc_tostring(avm_memcell* m){
    char* buffer;
    buffer = malloc(sizeof(char*));
    sprintf(buffer, "User Function : %d", newuserFuncs[m->data.funcVal].address);
    return buffer;
}

char* libfunc_tostring(avm_memcell* m){
    char* buffer;
    buffer = malloc(sizeof(char*));
    sprintf(buffer, "Library Function : %s", m->data.libfuncVal);
    return buffer;
}

char* nil_tostring(avm_memcell* m){
    return "nil";
} */

tostring_func_t tostringFuncs[] ={
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    0};

char* avm_tostring(avm_memcell* m){//yparxei xoris ylopoihsh
    assert(m->type >= 0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
} 

double add_impl(double x, double y){ return x + y; }
double sub_impl(double x, double y){ return x - y; }
double mul_impl(double x, double y){ return x * y; }
double div_impl(double x, double y){
    if (y != 0){
        return x / y;
    } else{
        avm_error("Division by 0");
    }
}
double mod_impl(double x, double y){
    if (y != 0){
        return ((unsigned)x) % ((unsigned)y);
    } else{
        avm_error("Division by 0");
    }
}

arithmetic_func_t arithmeticFuncs[] ={
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl};

/* void execute_add(instruction* instr);
void execute_sub(instruction* instr);
void execute_mul(instruction* instr);
void execute_div(instruction* instr);
void execute_mod(instruction* instr); SAME AS DEFINES IN FILE.H ?*/

void execute_arithmetic(instruction* instr){
    avm_memcell* lv = avm_translate_operand(&(instr->result), (avm_memcell*)0);
    avm_memcell* rv1 = avm_translate_operand(&(instr->arg1), &ax);
    avm_memcell* rv2 = avm_translate_operand(&(instr->arg2), &bx);

    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv1 && rv2);

    if (rv1->type != number_m || rv2->type != number_m){
        avm_error("not a number inrithmetic!"); /* executionFinished mesa stin avm_error*/
    } else{
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcellclear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
}

/*-----------------------------not implemented-----------------------------------*/
void execute_uminus(instruction* instr){}
void execute_and(instruction* instr){}
void execute_or(instruction* instr){}
void execute_not(instruction* instr){}
/*-------------------------------------------------------------------------------*/

unsigned char number_tobool(avm_memcell* m){ return m->data.numVal != 0; }
unsigned char string_tobool(avm_memcell* m){ return m->data.strVal[0] != 0; }
unsigned char bool_tobool(avm_memcell* m){ return m->data.boolVal; }
unsigned char table_tobool(avm_memcell* m){ return 1; }
unsigned char userfunc_tobool(avm_memcell* m){ return 1; }
unsigned char libfunc_tobool(avm_memcell* m){ return 1; }
unsigned char nil_tobool(avm_memcell* m){ return 0; }
unsigned char undef_tobool(avm_memcell* m){
    //assert(0);
    return 0;
}

tobool_func_t toboolFuncs[] ={
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool};

unsigned char avm_tobool(avm_memcell* m){ 
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

char* typeStrings[] ={
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"};


/* unsigned char number_function(avm_memcell* rv1, avm_memcell* rv2){
    return rv1->data.numVal == rv2->data.numVal;
}
unsigned char string_function(avm_memcell* rv1, avm_memcell* rv2){
    if (strcmp(rv1->data.strVal, rv2->data.strVal) == 0){
        return 1;
    } else{
        return 0;
    }
}

mydispatch_t dispatch[] ={
    number_function,
    string_function,
    0,
    0,
    0,
    0,
    0,
    0};     */

void execute_jeq(instruction* instr){
    printf("execute_jeq\n");
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&(instr->arg1), &ax);
    avm_memcell* rv2 = avm_translate_operand(&(instr->arg2), &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m){
        avm_error("'undef' involved in equality");
    } else if (rv1->type == nil_m || rv2->type == nil_m){
        result = rv1->type == nil_m && rv2->type == nil_m;
    } else if (rv1->type == bool_m || rv2->type == bool_m){
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    } else if (rv1->type != rv2->type){
        avm_error("Comparing diffrent types of arguments");
        printf("%s == %s is illegal", typeStrings[rv1->type], typeStrings[rv2->type]);
    } else{
        /* Equality check with dispatching. --------------------------------------------------------------------------------------------------------------------*/
        //result = (*dispatch[rv1->type])(rv1, rv2);
    }

    if (!executionFinished && result){
        pc = instr->result.val;
    }
} 

/* void execute_jne(instruction* instr){
    printf("execute_jne\n");
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m){
        avm_error("'undef' involved in equality");
    } else if (rv1->type == nil_m || rv2->type == nil_m){
        result = rv1->type == nil_m && rv2->type == nil_m;
    } else if (rv1->type == bool_m || rv2->type == bool_m){
        result = (avm_tobool(rv1) != avm_tobool(rv2));
    } else if (rv1->type != rv2->type){
        avm_error("Comparing diffrent types of arguments");
        printf("%s != %s is illegal", typeStrings[rv1->type], typeStrings[rv2->type]);
    } else{
        //result = (*dispatch[rv1->type])(rv1, rv2);
    }

    if (!executionFinished && !result){
        pc = instr->result.val;
    }
}


unsigned char less_eq(double x, double y){ return x <= y; }
unsigned char greater_eq(double x, double y){ return x >= y; }
unsigned char less(double x, double y){ return x < y; }
unsigned char greater(double x, double y){ return x > y; }

comparison_func_t comparisonFuncs[] ={
    less_eq,
    greater_eq,
    less,
    greater};

void execute_jle(instruction* instr);
void execute_jge(instruction* instr);
void execute_jlt(instruction* instr);
void execute_jgt(instruction* instr);

void execute_relational(instruction* instr){
    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    assert(rv1 && rv2);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m){
        avm_error("'undef' involved in comparing");
    } else if (rv1->type == nil_m || rv2->type == nil_m){
        result = rv1->type == nil_m && rv2->type == nil_m;
    } else if (rv1->type == bool_m || rv2->type == bool_m){
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    } else if (rv1->type != rv2->type){
        avm_error("Comparing diffrent types of arguments");
        printf("%s == %s is illegal", typeStrings[rv1->type], typeStrings[rv2->type]);
    } else{
        comparison_func_t op = comparisonFuncs[instr->opcode - jle_v];
        result = (*op)(rv1->data.numVal, rv2->data.numVal);
    }

    if (!executionFinished && result){
        pc = instr->result.val;
    }
}

 */

void libfunc_typeof(){
    unsigned n = avm_totalactuals();

    if (n > 1){
        retval.type = nil_m;
        printf("ERROR, too many arguments for library function typeof. (needs 1 argument)\n");
    } else{
        avm_memcellclear(&retval);
        retval.type = string_m; 
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void libfunc_totalarguments(){
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);

    if(!p_topsp){
        avm_error("'totalarguements' called outside function!");
        retval.type = nil_m;
    }
    else{
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}

void libfunc_print(){
    unsigned n = avm_totalactuals();
    unsigned i;
    for (i = 0; i < n; i++){
        char* s = avm_tostring(avm_getactual(i));
        puts(s);
        free(s);
    }
}

/* 
void libfunc_typeof(){//done
    unsigned n = avm_totalactuals();

    if (n > 1){
        retval.type = nil_m;
        printf("ERROR, too many arguments for library function typeof. (needs 1 argument)\n");
    } else{
        char* s = typeStrings[avm_getactual(0)->type];
        retval.data.strVal = s;
    }
}

void libfunc_totalarguments(){
    if (!avm_infunc){
        retval.type = nil_m;
    } else{
        unsigned n = avm_totalactuals_totArgs();
        retval.data.numVal = n;
    }
}

void libfunc_argument(){
    avm_memcell* argument;
    if (!avm_infunc){
        retval.type = nil_m;
    } else{
        unsigned i = avm_getactual(0)->data.numVal;
        argument = avm_getactualArgument(i);
        char* s = avm_tostring(argument);
        retval.data.strVal = s;
    }
}

void libfunc_objecttotalmembers(){
    avm_memcell* tm = avm_getactual(0);
    int j = tm->data.tableVal->total;
    retval.data.numVal = j;
}

void libfunc_sqrt(){
    double i = avm_getactual(0)->data.numVal;
    if (i < 0){
        retval.type = nil_m;
    } else{
        retval.data.numVal = sqrt(i);
    }
}

void libfunc_sin(){
    double i = avm_getactual(0)->data.numVal;
    double rads = pi * i / 180;
    retval.data.numVal = sin(rads);
}

void libfunc_cos(){
    double i = avm_getactual(0)->data.numVal;

    double rads = pi * i / 180;

    retval.data.numVal = cos(rads);
}

void libfunc_strtonum(){
    char* i = avm_getactual(0)->data.strVal;
    if (avm_getactual(0)->type != string_m || (i != 0 && atof(i) == 0)){
        retval.type = nil_m;
    } else{
        retval.data.numVal = atof(i);
        retval.type = number_m;
    }
}

void libfunc_objectmemberkeys(){
    int i;
    int j = 0;
    avm_table* t = avm_getactual(0)->data.tableVal;
    avm_table* t_new = avm_tablenew();
    unsigned t_size = t->total;
    avm_memcell new_key;

    for (i = 0; i < AVM_TABLE_HASHSIZE; i++){
        avm_table_bucket* temp = t->strIndexed[i];

        while (temp != NULL){
            new_key.data.numVal = j;
            avm_table_bucket* new_bucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
            new_bucket->key = new_key;
            new_bucket->value = temp->key;
            new_bucket->next = t_new->strIndexed[j];
            t_new->numIndexed[j] = new_bucket;
            t_new->total++;
            j++;
            temp = temp->next;
        }
        temp = t->numIndexed[i];
        while (temp != NULL){
            new_key.data.numVal = j;
            avm_table_bucket* new_bucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
            new_bucket->key = new_key;
            new_bucket->value = temp->key;
            new_bucket->next = t_new->numIndexed[j];
            t_new->numIndexed[j] = new_bucket;
            t_new->total++;
            j++;
            temp = temp->next;
        }
    }
    retval.type = table_m;
    retval.data.tableVal = t_new;
    avm_tableincrefcounter(retval.data.tableVal);
}

void libfunc_objectcopy(){
    avm_table* t = avm_getactual(0)->data.tableVal;
    avm_table* t_new = avm_tablenew();
    int i;
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++){
        avm_table_bucket* temp = t->strIndexed[i];

        while (temp != NULL){
            avm_tablesetelem(t_new, &temp->key, avm_tablegetelem(t, &temp->key));
            temp = temp->next;
        }
        temp = t->numIndexed[i];
        while (temp != NULL){
            avm_tablesetelem(t_new, &temp->key, avm_tablegetelem(t, &temp->key));
            temp = temp->next;
        }
    }
    retval.type = table_m;
    retval.data.tableVal = t_new;
    avm_tableincrefcounter(retval.data.tableVal);
}
void libfunc_input(){}

typedef struct LibFuncsHashTable{
    int hash_count;
    library_func_t Lib_HashTable[AVM_LIB_HASHSIZE];
} LibFuncsHashTable;

LibFuncsHashTable* LibHashTable;

int avmLibHash(char* key){
    if (strcmp(key, "print") == 0){
        return 0;
    } else if (strcmp(key, "typeof") == 0){
        return 1;
    } else if (strcmp(key, "totalarguments") == 0){
        return 2;
    } else if (strcmp(key, "argument") == 0){
        return 3;
    } else if (strcmp(key, "objecttotalmembers") == 0){
        return 4;
    } else if (strcmp(key, "sqrt") == 0){
        return 5;
    } else if (strcmp(key, "sin") == 0){
        return 6;
    } else if (strcmp(key, "cos") == 0){
        return 7;
    } else if (strcmp(key, "strtonum") == 0){
        return 8;
    } else if (strcmp(key, "input") == 0){
        return 9;
    } else if (strcmp(key, "objectcopy") == 0){
        return 10;
    } else if (strcmp(key, "objectmemberkeys") == 0){
        return 11;
    } else if (strcmp(key, "cos") == 0){
        return 12;
    }
}

void avm_registerlibfunc(char* id, library_func_t addr){
    LibHashTable->Lib_HashTable[avmLibHash(id)] = addr;
    LibHashTable->hash_count++;
} */

void execute_newtable(instruction* instr){
    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
    assert(lv && (&stack[AVM_STACKSIZE - 1]) >= lv && lv > &(stack[top]) || lv == &retval);

    avm_memcellclear(lv);

    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction* instr){
    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
    avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*)0);
    avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);

    assert(lv && (&stack[AVM_STACKSIZE - 1]) >= lv && lv > &stack[top] || lv == &retval);
    assert(t && (&stack[AVM_STACKSIZE - 1]) >= t && t > &stack[top]);
    assert(i);

    avm_memcellclear(lv);

    lv->type = nil_m;

    if (t->type != table_m){
        avm_error("Illegal use of table");
        printf("%s Not as table!", typeStrings[t->type]);
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
    avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*)0);

    avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);
    avm_memcell* c = avm_translate_operand(&instr->result, &bx);

    assert(t && &stack[AVM_STACKSIZE - 1] >= t && t > &stack[top]);
    assert(i && c);

    if (t->type != table_m){
        printf("Error! illegal use of type %s as table!", typeStrings[t->type]);
        executionFinished = 1;
    } else{
        avm_tablesetelem(t->data.tableVal, i, c);
    }
}

void execute_nop(instruction* instr){}
void execute_jump(instruction* instr){
    pc = instr->result.val;
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

void execute_cycle(void){
    if (executionFinished){
        return;
    } else if (pc == AVM_ENDING_PC){
        executionFinished = 1;
        return;
    } else{
        assert(pc < AVM_ENDING_PC);
        instruction* instr = instructions + pc;
        
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        unsigned oldPC = pc;
        executeFuncs[instr->opcode](instr);
        if (pc == oldPC){
            pc++;
        }
    }
}

/* void read_strings(FILE* f){ //logika gia tis print tous ???
    int i = 0;
    char* buf[16];
    int discard;
    
    fscanf(f, "%s%u", buf, &stringtotals); 

    newStringtable = (char**)malloc(stringtotals * sizeof(char*));

    fscanf(f, "%s%s", buf, buf); 
    while (i < stringtotals){
        fscanf(f, "%u", &discard); 
        fscanf(f, "%[^\n]s ", buf);
        char** p = newStringtable + i;
        *p = strdup((char*)buf);
        i++;
    }
}

void read_numbers(FILE* f){
    int i = 0;
    char* buf[16];
    float temp;
    fscanf(f, "%s%u", buf, &numbertotals); 
    newNumbertable = (double*)malloc(numbertotals * sizeof(double));

    fscanf(f, "%s", buf); 
    while (i < numbertotals){
        fscanf(f, "%f", &temp);
        double* p = newNumbertable + i;
        *p = temp;

        i++;
    }
}

void read_userFuncs(FILE* f){
    int i = 0;
    char* buf[16]; 
    int tmp_address;
    int tmp_localsize;
    fscanf(f, "%s%d", buf, &userfunctotals); 
    newuserFuncs = (userfunc*)malloc(userfunctotals * sizeof(userfunc));
    fscanf(f, "%s%s%s", buf, buf, buf); 

    while (i < userfunctotals){
        fscanf(f, "%d%d%s", &tmp_address, &tmp_localsize, buf);
        userfunc* p = newuserFuncs + i;
        p->address = tmp_address;
        p->localSize = tmp_localsize;
        p->id = strdup((char*)buf);
        i++;
    }
}

void read_libFuncs(FILE* f){
    int i = 0;
    char* buf[16];
    int discard;
    fscanf(f, "%s%u", buf, &libfunctotals); 

    newLibFuncs = (char**)malloc(libfunctotals * sizeof(char*));

    fscanf(f, "%s%s", buf, buf); 
    while (i < libfunctotals){
        fscanf(f, "%u", &discard); 

        fscanf(f, "%s", buf);
        char** p = newLibFuncs + i;
        *p = strdup((char*)buf);

        i++;
    }
}

void read_code(FILE* f){
    int i = 0;
    char* buf[16];
    int tmp_opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;

    fscanf(f, "%s%d", buf, &instructiontotals); 

    newinstructions = (instruction*)malloc(instructiontotals * sizeof(instruction));

    fscanf(f, "%s%s%s%s", buf, buf, buf, buf); 

    while (i < instructiontotals){
        fscanf(f, "%d", &tmp_opcode);

        if ((tmp_opcode > 15 && tmp_opcode < 21) || tmp_opcode == 23 || tmp_opcode == 24){
            fscanf(f, "%d%u", &(result.type), &(result.val));
        } else if (tmp_opcode == 0){
            fscanf(f, "%d%u%d", &(result.type), &(result.val), &(arg1.type));
            if (arg1.type != 10){
                fscanf(f, "%u", &(arg1.val));
            } else{
                arg1.val = -1; 
            }
        } else{
            fscanf(f, "%d%u%d%u%d%u", &(result.type), &(result.val), &(arg1.type), &(arg1.val), &(arg2.type), &(arg2.val));
        }

        instruction* p = newinstructions + i;
        p->opcode = tmp_opcode;
        p->result = result;
        p->arg1 = arg1;
        p->arg2 = arg2;

        i++;
    }
}
void read_totalglobals(FILE* f){
    int i = 0;
    char* buf[16];
    fscanf(f, "%s%d", buf, &total_globals); 
}

void print_abc_file(){
    int i = 0;

    while (i < instructiontotals){
        if ((newinstructions[i].opcode > 15 && newinstructions[i].opcode < 21) || newinstructions[i].opcode == 23 || newinstructions[i].opcode == 24){
            printf("%d (%d)%u\n", newinstructions[i].opcode, newinstructions[i].result.type, newinstructions[i].result.val);
        } else if (newinstructions[i].opcode == 0){
            printf("%d (%d)%u (%d)%d\n", newinstructions[i].opcode, newinstructions[i].result.type, newinstructions[i].result.val, newinstructions[i].arg1.type, newinstructions[i].arg1.val);
        } else{
            printf("%d (%d)%u (%d)%u (%d)%u\n", newinstructions[i].opcode, newinstructions[i].result.type, newinstructions[i].result.val, newinstructions[i].arg1.type, newinstructions[i].arg1.val, newinstructions[i].arg2.type, newinstructions[i].arg2.val);
        }
        i++;
    }execute_newtable
} */
