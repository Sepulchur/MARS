#include "libfunc.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define PI 3.14159265358979323846

library_func_t executeLibFuncs[] = {
    {"print", libfunc_print},
    {"sqrt", libfunc_sqrt},
    {"input", libfunc_input},
    {"argument", libfunc_argument},
    {"objecttotalmembers", libfunc_objecttotalmembers},
    {"sin", libfunc_sin},
    {"strtonum", libfunc_strtonum},
    {"objectcopy", libfunc_objectcopy},
    {"objectmemberkeys", libfunc_objectmemberkeys},
    {"typeof", libfunc_typeof},
    {"cos", libfunc_cos},
    {"totalarguments", libfunc_totalarguments}
};

void invalid_libfunc(char* id){
    avm_error("error: invalid library function: %s\n", id);
	executionFinished = 1;
}

void libfunc_sqrt(char* id){
	avm_memcell* arg;
	unsigned n = avm_totalactuals();
	arg = avm_getactual(0);

	if(n != 1){
		avm_error("error: library function 'sqrt' expected 1 argument but got %u.\n", n);
		executionFinished = 1;
		return;
	}
	if(arg->type != number_m){
		avm_error("error: incompatible type for argument 1 of 'sqrt'.\n");
		executionFinished = 1;
		return;
	}

	avm_memcellclear(&retval);

	if(arg->data.numVal < 0){
		retval.type = nil_m;
		return;
	}
	retval.type = number_m;
	retval.data.numVal = sqrt(arg->data.numVal);
}

void libfunc_sin(char* id){
	avm_memcell* arg;
	unsigned n = avm_totalactuals();
	arg = avm_getactual(0);

	if(n != 1){
		avm_error("error: library function 'sin' expected 1 argument but got %u.\n", n);
		executionFinished = 1;
		return;
	}
	if(arg->type != number_m){
		avm_error("error: incompatible type for argument 1 of 'sin'.\n");
		executionFinished = 1;
		return;
	}

	avm_memcellclear(&retval);

	retval.type = number_m;
	retval.data.numVal = sin(arg->data.numVal * PI / 180.0);
}

void libfunc_cos(char* id){
	avm_memcell* arg;
	unsigned n = avm_totalactuals();
	arg = avm_getactual(0);

	if(n != 1){
		avm_error("error: library function 'cos' expected 1 argument but got %u.\n", n);
		executionFinished = 1;
		return;
	}
	if(arg->type != number_m){
		avm_error("error: incompatible type for argument 1 of 'cos'.\n");
		executionFinished = 1;
		return;
	}

	avm_memcellclear(&retval);

	retval.type = number_m;
	retval.data.numVal = cos(arg->data.numVal * PI / 180.0);
}

void libfunc_typeof(char* id){
	unsigned n = avm_totalactuals();

	if(n != 1){
		avm_error("error: library function 'typeof' expected 1 argument but got %u\n", n);
		executionFinished = 1;
		return;
	}

	avm_memcellclear(&retval);

	retval.type = string_m;
	retval.data.strVal = strdup(memcell_typeToString[avm_getactual(0)->type]);
}

void libfunc_strtonum(char* id){
	avm_memcell* arg;
	char* str;
	unsigned n = avm_totalactuals();
	arg = avm_getactual(0);

	if(n != 1){
		avm_error("error: library function 'strtonum' expected 1 argument but got %u\n", n);
		executionFinished = 1;
		return;
	}
	
	if(arg->type != string_m){
		avm_error("error: incompatible type for argument 1 of 'strtonum'.\n");
		executionFinished = 1;
		return;
	}

	avm_memcellclear(&retval);
	
	str = arg->data.strVal;
    if(arg->type != string_m ||(str != 0 && atof(str) == 0)){
        retval.type = nil_m;
    } 
	else{
        retval.data.numVal = atof(str);
        retval.type = number_m;
    }
}

void libfunc_argument(char* id){
	avm_memcell* arg;
	unsigned n, total;
	unsigned p = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	if(!p){
		avm_warning("warning: library function 'argument' called outside function.\n");
		retval.type = nil_m;
		return;
	}
		
	n = avm_totalactuals();
	if(n != 1){
		avm_error("error: library function 'argument' expected 1 argument but got %u\n", n);
		executionFinished = 1;
		return;
	}

	total = avm_get_envvalue(p + AVM_NUMACTUALS_OFFSET);
	arg = avm_getactual(0); 
	if(arg->type != number_m){
		avm_error("error: incompatible type for argument 1 of 'argument'.\n");
		executionFinished = 1;
		return;
	}

	avm_assign(&retval, &stack[p + AVM_NUMACTUALS_OFFSET + 1 +(int)arg->data.numVal]);	
}

void libfunc_totalarguments(char* id){
	unsigned p = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	if(!p){
		avm_warning("warning: library function 'totalarguments' called outside function.\n");
		retval.type = nil_m;
		return;
	}
	
	retval.type = number_m;
	retval.data.numVal = avm_get_envvalue(p + AVM_NUMACTUALS_OFFSET);
}

void libfunc_objectcopy(char* id){
	avm_table_bucket* temp;
	avm_table* t, *t_new;
	avm_memcell* arg;
	unsigned i, n = avm_totalactuals();
	if(n != 1){
		avm_error("error: library function 'objectcopy' expected 1 argument but got %u\n", n);
		executionFinished = 1;
		return;
	}

	arg = avm_getactual(0);
	if(arg->type != table_m){
		avm_error("error: incompatible type for argument 1 of 'objectcopy'.\n");
		executionFinished = 1;
		return;
	}

	t = arg->data.tableVal;
	t_new = avm_tablenew();

	avm_memcellclear(&retval);

	for(i = 0; i < AVM_TABLE_HASHSIZE; i++){

        temp = t->strIndexed[i];
        while (temp != NULL) {
            avm_tablesetelem(t_new, &temp->key, avm_tablegetelem(t, &temp->key));
            temp = temp->next;
        }

        temp = t->numIndexed[i];
        while (temp != NULL) {
            avm_tablesetelem(t_new, &temp->key, avm_tablegetelem(t, &temp->key));
            temp = temp->next;
        }

    }

	retval.type = table_m;
	retval.data.tableVal = t_new;
	avm_tableincrefcounter(retval.data.tableVal);
}

void libfunc_objecttotalmembers(char* id){
	avm_memcell* arg;
	unsigned n = avm_totalactuals();
	if(n != 1){
		avm_error("error: library function 'objecttotalmembers' expected 1 argument but got %u\n", n);
		executionFinished = 1;
		return;		
	}

	arg = avm_getactual(0);
	if(arg->type != table_m){
		avm_error("error: incompatible type for argument 1 of 'objecttotalmembers'.\n");
		executionFinished = 1;
		return;
	}

	avm_memcellclear(&retval);

	retval.type = number_m;
	retval.data.numVal = table_getTotal(arg->data.tableVal);
}

void libfunc_objectmemberkeys(char* id){
	avm_table_bucket* temp, *new_bucket; 
	avm_memcell* arg;
	avm_table* t, *t_new;
	avm_memcell new_key;
    unsigned i, z, t_size;
	unsigned n = avm_totalactuals();
	if(n != 1){
		avm_error("error: library function 'objectmemberkeys' expected 1 argument but got %u\n", n);
		executionFinished = 1;
		return;		
	}

	arg = avm_getactual(0);
	if(arg->type != table_m){
		avm_error("error: incompatible type for argument 1 of 'objectmemberkeys'.\n");
		executionFinished = 1;
		return;
	}

	t = arg->data.tableVal;
	t_new = avm_tablenew();
	t_size = t->total;

	avm_memcellclear(&retval);

	for (i = 0; i < AVM_TABLE_HASHSIZE; i++) {

        temp = t->strIndexed[i];
        while (temp != NULL) {
            new_key.data.numVal = z;
            new_bucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
            new_bucket->key = new_key;
            new_bucket->value = temp->key;
            new_bucket->next = t_new->strIndexed[z];
            t_new->numIndexed[z] = new_bucket;
            t_new->total++;
            z++;
            temp = temp->next;
        }

        temp = t->numIndexed[i];
        while (temp != NULL) {
            new_key.data.numVal = z;
            new_bucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
            new_bucket->key = new_key;
            new_bucket->value = temp->key;
            new_bucket->next = t_new->numIndexed[z];
            t_new->numIndexed[z] = new_bucket;
            t_new->total++;
            z++;
            temp = temp->next;
        }

    }
    
	retval.type = table_m;
	retval.data.tableVal = t_new;
	avm_tableincrefcounter(retval.data.tableVal);
}

void libfunc_print(char* id){
	unsigned i;
	char* s;
    unsigned n = avm_totalactuals();
    for(i = 0; i < n; i++){
        s = avm_tostring(avm_getactual(i));
        fputs(s, stdout);
        free(s);/*whats up danger*/
    }

    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = n;
}

static inline bool isNumber(char c){
	if(c >= '0' && c <= '9'){
		return 1;
    }
	return 0;
}

void libfunc_input(char* id){
    avm_memcellclear(&retval);

	unsigned periodIndex, index;
    size_t len, bufferSize = 0;
    char *str;
    char *line = NULL; 
    len = getline(&line, &bufferSize, stdin);

    if(len <= 0){
        retval.type = nil_m;
        free(line);
        return;
    }

    line[--len] = '\0';

    if(len == 0 || strcmp(line, "nil") == 0){
        retval.type = nil_m;
        free(line);
        return;
    }

    if(strcmp(line, "true") == 0){
        retval.type = bool_m;
        retval.data.boolVal = 1;
        free(line);
        return;
    }

    if(strcmp(line, "false") == 0){
        retval.type = bool_m;
        retval.data.boolVal = 0;
        free(line);
        return;
    }

    index = 0;
    if(line[index] == '-' || line[index] == '+'){
        index++;
    }

    if(len - index <= 16){
        periodIndex;
        while(isNumber(line[index])){
            index++;
        }

        if(index == len){
            retval.type = number_m;
            sscanf(line, "%lf", &retval.data.numVal);
            free(line);
            return;
        }

        if(line[index] == '.'){
            periodIndex = ++index;
            while(isNumber(line[index])){
                index++;
            }

            if(index == len && index != periodIndex){
                retval.type = number_m;
                sscanf(line, "%lf", &retval.data.numVal);
                free(line);
                return;
            }
        }
    }

    if(len > 1 && line[0] == '"' && line[len - 1] == '"'){
        line[len - 1] = '\0';
        str = malloc(len - 1);
        strcpy(str, &line[1]);
        free(line);
        line = str;
    }

    retval.type = string_m;
    retval.data.strVal = line;
}
