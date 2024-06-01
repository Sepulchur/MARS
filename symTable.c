#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "symTable.h"

const char* map_enum(enum SymbolType type){
    switch(type){
        case GLOBAL: return "GLOBAL";
        case LOCALVAR: return "LOCALVAR";
        case FORMAL: return "FORMAL";
        case CONST: return "CONST";
        case USERFUNC: return "USERFUNC";
        case LIBFUNC: return "LIBFUNC";
        default: return "UNKNOWN";
    }
}

passport_t createFuncName(unsigned int scope, unsigned int index){
    char *nameBuffer = (char *)malloc(20 * sizeof(char));

    sprintf(nameBuffer, "_function_%d", index);

    return createPassport(nameBuffer, scope);
}

passport_t createPassport(const char* name, unsigned int scope){
    passport_t p;
    p.scope = scope;
    p.name = name;
    return p;
}

unsigned int hash(int key){
    return key % TABLE_SIZE;
}

HashTable* createHashTable(){
    int i;
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    if(!table){
        return NULL;
    }
    for(i = 0; i < TABLE_SIZE; i++){
        table->buckets[i] = NULL;
    }
    table->len = 0;
    table->heads = NULL;
    H_Initlib(table);
    return table;
}

void freeHashTable(HashTable *table){
    int i;
    SymbolTableEntry_t *temp, *entry;
    ArgList *atemp, *atemp2;
    if (!table) return;
    for (i = 0; i < TABLE_SIZE; i++){
        entry = table->buckets[i];
        while(entry){
            temp = entry;
            entry = entry->next_entry;
            if(temp->type == USERFUNC){
                if(strncmp(temp->passport.name, "_", 1) == 0){
                    free((char *)temp->passport.name);
                }
                atemp = temp->argList;
                while(atemp){
                    atemp2 = atemp;
                    atemp = atemp->next;
                    free(atemp2);
                }
            }
            free(temp);
        }
    }
    free(table->heads);
    free(table);
}

SymbolTableEntry_t *create_entry(unsigned int key, enum SymbolType s, passport_t p, unsigned int line){
    SymbolTableEntry_t *newEntry;
    newEntry = (SymbolTableEntry_t*)malloc(sizeof(SymbolTableEntry_t));
    newEntry->key = key;
    newEntry->line = line;
    newEntry->passport = p;
    newEntry->type = s;
    newEntry->isActive = true;
    newEntry->next_entry = NULL;
    newEntry->next_scope = NULL;
    newEntry->argList = NULL;
    newEntry->address = 0;

    if(s <= 3){
        newEntry->generaltype = var_s;
    }
    else if(s == 4){
        newEntry->generaltype = programfunc_s;
    }
    else if(s == 5){
        newEntry->generaltype = library_func_s;
    }
    newEntry->space = 0;
    newEntry->offset = 0;
}

SymbolTableEntry_t * H_Insert(HashTable **table, SymbolTableEntry_t *newEntry){
    unsigned int slot;
    SymbolTableEntry_t *last = NULL;
    slot = hash(newEntry->key);

    last = Scope_LookUp(*table,&newEntry->passport,newEntry->type);
    SL_Insert(&(*table)->buckets[slot], newEntry);
    if(last != NULL){
        last->next_scope = newEntry;
    }
    else{
        (*table)->heads = realloc((*table)->heads, sizeof(SymbolTableEntry_t*)*((*table)->len+1));
        (*table)->heads[(*table)->len] = newEntry;
        (*table)->len = (*table)->len + 1;
    }

    return newEntry;
}

SymbolTableEntry_t * SL_Insert(SymbolTableEntry_t **h, SymbolTableEntry_t *new_entry){
    SymbolTableEntry_t *current_entry = *h;

    while(current_entry != NULL && current_entry->next_entry != NULL){
        current_entry = current_entry->next_entry;
    }

    if(current_entry == NULL) 
        *h = new_entry;
    else
        current_entry->next_entry = new_entry; 

    return EXIT_SUCCESS;
}

SymbolTableEntry_t * Scope_LookUp(HashTable *table, passport_t *p, enum SymbolType type){
    int i;
    SymbolTableEntry_t *temp;
    for(i = 0; i < table->len; i++){
        temp = table->heads[i];
        if(temp != NULL){/*den xriazetai*/
            if(type > 3 && temp->type > 3){
                if(temp->passport.scope == p->scope){
                    while(temp->next_scope!=NULL){
                        temp = temp->next_scope;
                    }
                    return temp;
                }  
            } else if(type <= 3){
                if(temp->passport.scope == p->scope){
                    while(temp->next_scope!=NULL){
                        temp = temp->next_scope;
                    }
                    return temp;
                }
            }
        }
    }
    return NULL;
}

void L_entry_print(HashTable *h){
    printf("entries = <"); int i;
    SymbolTableEntry_t *entry = NULL;
    for ( i = 0; i < TABLE_SIZE; i++){    
        entry = h->buckets[i];
        while(entry != NULL){
            printf(" %s ", entry->passport.name);
            entry = entry->next_entry;
        }
    }
    printf(">\n");
}

void L_heads_print(HashTable *h){
    int i = 0; 
    printf("kefalia len=%d: <", h->len);
    for(i=0;i<h->len;i++){
        if(h->heads[i]->isActive)
            printf(" %d ", h->heads[i]->key);
    }
    printf(">\n");
}

void PrintScope(const HashTable *table, unsigned int scope){
    unsigned int i;
    const char* typeStr;
    SymbolTableEntry_t *entry;
    bool foundScope = false;

    printf("------------\tScope #%u\t------------\n", scope);

    for(i = 0; i < table->len; ++i){
        for(entry = table->heads[i]; entry != NULL; entry = entry->next_scope){
            if(((entry->type == USERFUNC || entry->type == LIBFUNC) && entry->passport.scope == scope) ||
                ((entry->type != USERFUNC && entry->type != LIBFUNC) && entry->passport.scope == scope)){
                
                foundScope = true;
                typeStr = map_enum(entry->type);
                if(entry->type == USERFUNC || entry->type == LIBFUNC){
                    printf("%s\t[%s]\t(line %u) (scope %u)\n", entry->passport.name, typeStr, entry->line, entry->passport.scope);
                } else{
                    printf("%s\t[%s]\t(line %u) (scope %u)\n", entry->passport.name, typeStr, entry->line, entry->passport.scope);
                }
            }
        }
    }

    if(!foundScope){
        printf("No symbols found in this scope.\n");
    }
}

void PrintHashTable(HashTable *table){
    unsigned int i, scope, maxScope = 0;
    SymbolTableEntry_t *entry;

    /* Determine the maximum scope */
    for(i = 0; i < table->len; ++i){
        for(entry = table->heads[i]; entry != NULL; entry = entry->next_scope){
            unsigned int currentScope =(entry->type == USERFUNC || entry->type == LIBFUNC) ? entry->passport.scope : entry->passport.scope;
            if(currentScope > maxScope){
                maxScope = currentScope;
            }
        }
    }

    /* Display scopes from 0 to maxScope */
    for(scope = 0; scope <= maxScope; ++scope){
        PrintScope(table, scope);
    }
}

void hide_scope(HashTable *table, unsigned int scope){
    int i;
    SymbolTableEntry_t *temp = NULL;
    for(i=0;i<table->len;i++){
        if(table->heads[i]->type == USERFUNC || table->heads[i]->type == LIBFUNC){
            if(table->heads[i]->passport.scope == scope)
                temp = table->heads[i];
        } 
        else{
            if(table->heads[i]->passport.scope == scope)
                temp = table->heads[i];
        }
    }
    while(temp!=NULL){
        temp->isActive = false;
        temp = temp->next_scope;
    }
}

SymbolTableEntry_t *H_Lookup(HashTable *table, int scope, const char *name){
    int i;
    SymbolTableEntry_t *temp = NULL;
    if(scope>=0){
        for(i = 0; i < table->len; i++){
            temp = table->heads[i];
            while(temp != NULL){
                if((temp->type > 3 && temp->passport.scope == scope) || (temp->type <= 3 && temp->passport.scope == scope)){
                    if(temp->type > 3 && strcmp(temp->passport.name, name) == 0){
                        return temp;
                    }
                    else if(temp->type <= 3 && strcmp(temp->passport.name, name) == 0){
                        return temp;
                    }
                }
                temp = temp->next_scope;
            }
        }
    }
    else{
        for(i=0;i<TABLE_SIZE;i++){
            temp = table->buckets[i];
            while(temp!=NULL){
                if(temp->type > 3){
                    if(strcmp(temp->passport.name, name) == 0){
                        return temp;
                    }
                }
                else if(temp->type <= 3){    
                    if(strcmp(temp->passport.name, name) == 0){
                        return temp;
                    }
                }
                temp = temp->next_entry;
            }
        }
    }

    return NULL;
}

ArgList * AL_Insert(ArgList **h, passport_t p){
    int i;
    ArgList *current_arg = *h;
    ArgList *prev_arg = NULL;
    ArgList *new_arg = (ArgList *) malloc(sizeof(ArgList));
    
    while(current_arg != NULL){
        if(strcmp(current_arg->p.name, p.name) == 0){
            free(new_arg);
            return NULL;
        }
        prev_arg = current_arg; 
        current_arg = current_arg->next;
    }

    new_arg->p.name = p.name;
    new_arg->next = NULL;

    if(prev_arg == NULL) 
        *h = new_arg;
    else 
        prev_arg->next = new_arg;

    return new_arg; 
}

void H_Initlib(HashTable *table){
    H_Insert(&table, create_entry(0, LIBFUNC, createPassport("print", 0), 0));
    H_Insert(&table, create_entry(1, LIBFUNC, createPassport("input", 0), 0));
    H_Insert(&table, create_entry(2, LIBFUNC, createPassport("objectmemberkeys", 0), 0));
    H_Insert(&table, create_entry(3, LIBFUNC, createPassport("objecttotalmembers", 0), 0));
    H_Insert(&table, create_entry(4, LIBFUNC, createPassport("objectcopy", 0), 0));
    H_Insert(&table, create_entry(5, LIBFUNC, createPassport("totalarguments", 0), 0));
    H_Insert(&table, create_entry(6, LIBFUNC, createPassport("argument", 0), 0));
    H_Insert(&table, create_entry(7, LIBFUNC, createPassport("typeof", 0), 0));    
    H_Insert(&table, create_entry(8, LIBFUNC, createPassport("strtonum", 0), 0));    
    H_Insert(&table, create_entry(9, LIBFUNC, createPassport("sqrt", 0), 0));    
    H_Insert(&table, create_entry(10, LIBFUNC, createPassport("cos", 0), 0));    
    H_Insert(&table, create_entry(11, LIBFUNC, createPassport("sin", 0), 0));    
}

void print_red(char *s, int line){
    fprintf(stdout, "\x1b[31mValidity error: %s at line %d\n\x1b[0m", s, line);
}

bool validity_check(HashTable *table, SymbolTableEntry_t *entry, bool b){
    int i, type, s, scope;
    SymbolTableEntry_t *temp = NULL;
    temp = table->heads[0];
    for(i = 0; i < 12; i++){ 
        if((entry->type == USERFUNC || entry->type == LIBFUNC)){
            if(strcmp(temp->passport.name, entry->passport.name) == 0){
                if(b)print_red("Conflicting name with library function", entry->line);
                return 0;
            }
            type = 1;
        }
        else if(entry->type > 0 && entry->type <= 3){
            if(strcmp(temp->passport.name, entry->passport.name) == 0){
                if(b)print_red("Conflicting name with library function", entry->line);
                return 0;
            }
            type = 0;
        }
        temp = temp->next_scope;
    }

    if(type)
        scope = entry->passport.scope;
    else
        scope = entry->passport.scope;

    /*MONO GIA VAR, CHECK IF YOU HAVE THE SAME NAME WITH FUNCT temp->type > 3 SUSPICIOUS*/
    if(!type){
        for(s = scope; s >= 0; s--){
            temp = H_Lookup(table, s, entry->passport.name);
            if(temp != NULL)
                if(temp->isActive && (temp->type > 3)){
                    if(b)print_red("Conflicting name with user function", entry->line);
                    free(entry);
                    return EXIT_FAILURE;
                }
        }

        /*MONO GIA VAR mikrotero function scope*/
        for(s = scope - 1; s > 0; s--){
            temp = H_Lookup(table, s, entry->passport.name);
            if(temp != NULL)
                if(temp->isActive && (temp->type <= 3)){
                    if(b)print_red("Conflicting name with user function", entry->line);
                    free(entry);return EXIT_FAILURE;
                }
        }
    }
    
    /*enan gia scope = 0 kai enan gia scope toy entry*/
    if(type){
        temp = H_Lookup(table, 0, entry->passport.name);
        if(temp != NULL){
            if(b)print_red("Conflicting name with GLOBAL function/variable", entry->line);
            free(entry);return EXIT_FAILURE;
        }
        temp = H_Lookup(table, scope, entry->passport.name);   
        if(temp != NULL){
            if(b)print_red("Conflicting name REDIFINITION of function", entry->line);
            free(entry);return EXIT_FAILURE;
        }    
    }
    else{
        temp = H_Lookup(table, 0, entry->passport.name);
        if(temp != NULL){
            if(b)print_red("Conflicting name with GLOBAL function/variable", entry->line);
            free(entry);return EXIT_FAILURE;
        }
        temp = H_Lookup(table, scope, entry->passport.name);   
        /*YACC ARG TO CHECK EAN EINAI DILOSI */
        if(temp != NULL){
            if(b)print_red("Conflicting name REDIFINITION of variable", entry->line);
            free(entry);return EXIT_FAILURE;
        }    
    }
    
    return EXIT_SUCCESS;
}

bool checkLib(HashTable *table, SymbolTableEntry_t *new){
    int i;
    SymbolTableEntry_t *entry = table->heads[0];
    for(i = 0; i < 12; i++){ 
        if(strcmp(entry->passport.name, new->passport.name) == 0){
            free(new);
            return EXIT_FAILURE;
        }
      entry = entry->next_scope;
    }
    return EXIT_SUCCESS;
}

int H_Search(HashTable *table, unsigned int scope, char *name){
    int i ;
    bool func;
    SymbolTableEntry_t *target = NULL;
    if(scope == 0 ){
        return -1;
    }
    for(i = scope - 1; i > 0 ; i--){
        target = H_Lookup(table,i,name);
        if(target != NULL ){
            return i; 
        }
    }
    return -1; 
}
