#ifndef AVM_TABLE_H
#define AVM_TABLE_H

#define AVM_TABLE_HASHSIZE 211

#include "../avm.h"

typedef struct avm_table avm_table;
typedef struct avm_memcell avm_memcell;
typedef struct avm_table_bucket avm_table_bucket;

void avm_tableincrefcounter(avm_table* t);

void avm_tabledecrefcounter(avm_table* t);

void avm_tabledestroy(avm_table* t);

void avm_tablebucketdestroy(avm_table_bucket** p);

void avm_tablebucketsinit(avm_table_bucket** p);

avm_table* avm_tablenew(void);

static inline unsigned compute_hash(unsigned capacity, avm_memcell* key);

int avm_compare_memcell(avm_memcell* m1, avm_memcell* m2);

void avm_tablesetelem(avm_table* table, avm_memcell* key, avm_memcell* value);

avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* key);

void avm_tabledestroy(avm_table* t);

char* avm_getable(avm_table* table);

unsigned table_getTotal(avm_table* table);

#endif
