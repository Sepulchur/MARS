#ifndef _LIBFUNC_H_
#define _LIBFUNC_H_

#include "avm.h"

#define F_ARRAY_SIZE 12

typedef struct {
    char* id;
    void (*func)(char*);
} library_func_t;

extern library_func_t executeLibFuncs[];

void invalid_libfunc(char* id);

void libfunc_print(char* id);

void libfunc_input(char* id);

void libfunc_objectmemberkeys(char* id);

void libfunc_objecttotalmembers(char* id);

void libfunc_objectcopy(char* id);

void libfunc_totalarguments(char* id);

void libfunc_argument(char* id);

void libfunc_typeof(char* id);

void libfunc_strtonum(char* id);

void libfunc_sqrt(char* id);

void libfunc_cos(char* id);

void libfunc_sin(char* id);

#endif