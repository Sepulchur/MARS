#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "avm.h"
char** string_array;
double* number_array;
userfunc* userfunc_array;
char** libfunc_array;
instruction* instructions;

avm_memcell* create_number_memcell(double num) {
    avm_memcell* cell = (avm_memcell*)malloc(sizeof(avm_memcell));
    cell->type = number_m;
    cell->data.numVal = num;
    return cell;
}

avm_memcell* create_string_memcell(const char* str) {
    avm_memcell* cell = (avm_memcell*)malloc(sizeof(avm_memcell));
    cell->type = string_m;
    cell->data.strVal = strdup(str);
    return cell;
}

void print_memcell(avm_memcell* cell) {
    switch (cell->type) {
        case number_m:
            printf("Number: %lf\n", cell->data.numVal);
            break;
        case string_m:
            printf("String: %s\n", cell->data.strVal);
            break;
        case bool_m:
            printf("Bool: %d\n", cell->data.boolVal);
            break;
        case nil_m:
            printf("Nil\n");
            break;
        default:
            printf("Unknown type\n");
    }
}

void test_avm_tablesetelem() {
    avm_table* table = avm_tablenew();

    avm_memcell* key1 = create_string_memcell("key1");
    avm_memcell* value1 = create_number_memcell(42);

    avm_memcell* key2 = create_number_memcell(13);
    avm_memcell* value2 = create_string_memcell("value2");

    avm_memcell* key3 = create_string_memcell("key3");
    avm_memcell* value3 = create_number_memcell(84);

    avm_tablesetelem(table, key1, value1);
    avm_tablesetelem(table, key2, value2);
    avm_tablesetelem(table, key3, value3);

    printf("Testing insertions...\n");

    avm_memcell* found_value1 = avm_tablegetelem(table, key1);
    assert(found_value1 != NULL && found_value1->type == number_m && found_value1->data.numVal == 42);
    print_memcell(found_value1);

    avm_memcell* found_value2 = avm_tablegetelem(table, key2);
    assert(found_value2 != NULL && found_value2->type == string_m && strcmp(found_value2->data.strVal, "value2") == 0);
    print_memcell(found_value2);

    avm_memcell* found_value3 = avm_tablegetelem(table, key3);
    assert(found_value3 != NULL && found_value3->type == number_m && found_value3->data.numVal == 84);
    print_memcell(found_value3);

    avm_memcell* new_value1 = create_number_memcell(99);
    avm_tablesetelem(table, key1, new_value1);

    printf("Testing update...\n");
    found_value1 = avm_tablegetelem(table, key1);
    assert(found_value1 != NULL && found_value1->type == number_m && found_value1->data.numVal == 99);
    print_memcell(found_value1);

    avm_memcell* nil_value = (avm_memcell*)malloc(sizeof(avm_memcell));
    nil_value->type = nil_m;
    avm_tablesetelem(table, key1, nil_value);

    printf("Testing deletion...\n");
    found_value1 = avm_tablegetelem(table, key1);
    assert(found_value1 == NULL);

    avm_memcellclear(key1);
    avm_memcellclear(value1);
    avm_memcellclear(key2);
    avm_memcellclear(value2);
    avm_memcellclear(key3);
    avm_memcellclear(value3);
    avm_memcellclear(new_value1);
    avm_memcellclear(nil_value);
    avm_tabledestroy(table);

    printf("All tests passed.\n");
}

void test_avm_getable() {
    avm_table* table = avm_tablenew();

    avm_memcell* key1 = create_string_memcell("key1");
    avm_memcell* value1 = create_number_memcell(42);

    avm_memcell* key2 = create_number_memcell(13);
    avm_memcell* value2 = create_string_memcell("value2");

    avm_memcell* key3 = create_string_memcell("key3");
    avm_memcell* value3 = create_number_memcell(84);

    avm_tablesetelem(table, key1, value1);
    avm_tablesetelem(table, key2, value2);
    avm_tablesetelem(table, key3, value3);

    char* table_str = avm_getable(table);
    printf("Table: %s\n", table_str);
    free(table_str);

    avm_memcellclear(key1);
    avm_memcellclear(value1);
    avm_memcellclear(key2);
    avm_memcellclear(value2);
    avm_memcellclear(key3);
    avm_memcellclear(value3);
    avm_tabledestroy(table);
}


int main() {
    test_avm_tablesetelem();
    test_avm_getable();
    return 0;
}
