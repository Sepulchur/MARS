#include "avm_table.h"

#define F_HASH_MULTIPLIER 31U

typedef struct nest_stack{
    avm_table* table;
    struct nest_stack* next;
} nest_stack;

nest_stack* nest_stack_top = NULL;

static inline bool nest_stack_lookup(avm_table* t){
    nest_stack* current = nest_stack_top;
    while(current){
        if(current->table == t){
            return true;
        }
        current = current->next;
    }
    return false;
}

static inline void nest_stack_push(avm_table* t){
    nest_stack* new_elem = (nest_stack*)malloc(sizeof(nest_stack));
    new_elem->table = t;
    new_elem->next = nest_stack_top;
    nest_stack_top = new_elem;
}

static inline void nest_stack_pop(void){
    nest_stack* temp;
    if(nest_stack_top){
        temp = nest_stack_top;
        nest_stack_top = nest_stack_top->next;
        free(temp);
    }
}

static inline unsigned compute_hash(unsigned capacity, avm_memcell* key){
	const char* id;
	unsigned len;
    unsigned hashValue = 0;
    unsigned i = 0;

	if(key->type == string_m){
		id = key->data.strVal;
		len = strlen(id);
	}
	else{
		id = (const char*)key;
		len = sizeof(avm_memcell);
	}
	
    for(i = 0; i < len; ++i){
        hashValue = hashValue * F_HASH_MULTIPLIER + (unsigned char)id[i];
    }

	return hashValue % capacity;
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

void avm_tabledestroy(avm_table* t){
    avm_tablebucketdestroy(t->strIndexed);
    avm_tablebucketdestroy(t->numIndexed);
    free(t);
}

void avm_tablebucketdestroy(avm_table_bucket** p){
    avm_table_bucket* b, *del;
    unsigned i = 0;
    for(i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p){
        for(b = *p; b;){
            del = b;
            b = b->next;
            avm_memcellclear(&(del->key));
            avm_memcellclear(&(del->value));
            free(del);
        }
        p[i] = (avm_table_bucket*)0;
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

void avm_tablesetelem(avm_table* table, avm_memcell* key, avm_memcell* value){
    bool deleteElem;
    unsigned capacity, hashIndex;
    avm_table_bucket** buckets;
    avm_table_bucket* bucket, *prev;

    assert(table);
    assert(key);
    assert(value);

    deleteElem = (value->type == nil_m);
    capacity = AVM_TABLE_HASHSIZE;
    buckets = (key->type == number_m) ? table->numIndexed : table->strIndexed;

    hashIndex = compute_hash(capacity, key);
    bucket = buckets[hashIndex];
    prev = NULL;

    while(bucket != NULL){
        if(avm_compare_memcell(&bucket->key, key) == 0){
            if(deleteElem){
                avm_memcellclear(&bucket->key);
                avm_memcellclear(&bucket->value);
                if(prev == NULL){
                    buckets[hashIndex] = bucket->next;
                } else{
                    prev->next = bucket->next;
                }
                free(bucket);
                table->total--;
            } 
            else{
                avm_assign(&bucket->value, value);
            }
            return;
        }
        prev = bucket;
        bucket = bucket->next;
    }

    if(deleteElem){
        return;
    }

    bucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
    avm_assign(&bucket->key, key);
    avm_assign(&bucket->value, value);
    bucket->next = buckets[hashIndex];
    buckets[hashIndex] = bucket;
    table->total++;
}

int avm_compare_memcell(avm_memcell* m1, avm_memcell* m2){
    if(m1->type != m2->type){
        return -1;
    }

    switch(m1->type){
        case number_m:
            return (m1->data.numVal == m2->data.numVal) ? 0 : -1;
        case string_m:
            return strcmp(m1->data.strVal, m2->data.strVal);
        case bool_m:
            return (m1->data.boolVal == m2->data.boolVal) ? 0 : -1;
        case nil_m:
            return 0;
        case userfunc_m:
            return (m1->data.funcVal == m2->data.funcVal) ? 0 : -1;
        case libfunc_m:
            return (m1->data.libfuncVal == m2->data.libfuncVal) ? 0 : -1;
        case table_m:
            return (m1->data.tableVal == m2->data.tableVal) ? 0 : -1;
        default:
            assert(0);
            return -1;
    }
}

avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* key){
    unsigned index;
    avm_table_bucket* bucket;

    assert(table);
    assert(key);
    
    if(key->type == number_m){
        index = compute_hash(AVM_TABLE_HASHSIZE, key);
        bucket = table->numIndexed[index];
    } 
    else if(key->type == string_m){
        index = compute_hash(AVM_TABLE_HASHSIZE, key);
        bucket = table->strIndexed[index];
    } 
    else{
        avm_error("Unsupported key type passed to avm_tablegetelem.\n");
        return NULL;
    }

    while(bucket != NULL){
        if(avm_compare_memcell(&bucket->key, key) == 0){
            return &bucket->value;
        }
        bucket = bucket->next;
    }

    return NULL;
}

char* avm_getable(avm_table* table){
    avm_table_bucket* bucket;
    char* buffer;
    unsigned buffLen = 60, buffIndex = 0, newIndex, size, i, transferred_elems = 0;

    assert(table);
    
    nest_stack_push(table);

    
    buffer = malloc(buffLen);
    size = table->total;
    strcpy(buffer, "[ ");
    buffIndex = 2;

    // Traverse strIndexed array
    for(i = 0; i < AVM_TABLE_HASHSIZE; ++i){
        bucket = table->strIndexed[i];
        while (bucket){
            char* k = avm_tostring(&bucket->key);
            char* v = avm_tostring(&bucket->value);
            newIndex = 9 + strlen(k) + strlen(v) + buffIndex;
            if(newIndex >= buffLen){
                buffLen = newIndex + 60;
                buffer = realloc(buffer, buffLen);
            }
            strcat(buffer, "{ ");
            strcat(buffer, k);
            free(k);
            strcat(buffer, " : ");
            strcat(buffer, v);
            free(v);

            if(transferred_elems == size - 1){
                buffIndex = newIndex - 1;
                strcat(buffer, " } ");
                break;
            }
            buffIndex = newIndex;
            strcat(buffer, " }, ");
            transferred_elems++;
            bucket = bucket->next;
        }
    }

    // Traverse numIndexed array
    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i){
        bucket = table->numIndexed[i];
        while (bucket){
            char* k = avm_tostring(&bucket->key);
            char* v = avm_tostring(&bucket->value);
            newIndex = 9 + strlen(k) + strlen(v) + buffIndex;
            if(newIndex >= buffLen){
                buffLen = newIndex + 60;
                buffer = realloc(buffer, buffLen);
            }
            strcat(buffer, "{ ");
            strcat(buffer, k);
            free(k);
            strcat(buffer, " : ");
            strcat(buffer, v);
            free(v);

            if(transferred_elems == size - 1){
                buffIndex = newIndex - 1;
                strcat(buffer, " } ");
                break;
            }
            buffIndex = newIndex;
            strcat(buffer, " }, ");
            transferred_elems++;
            bucket = bucket->next;
        }
    }

    buffIndex++;
    strcat(buffer, "]");
    assert(strlen(buffer) == buffIndex);
    nest_stack_pop();
    return buffer;
}

unsigned table_getTotal(avm_table* table){
	assert(table);
	return table->total;
}
