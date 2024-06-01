#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
char *strdup(const char *s);
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#include "symTable.h"
#include "quad.h"
extern void push_loopcounter (void);
extern void pop_loopcounter (void);

quad *  quads = (quad*) 0;
unsigned total = 0;
unsigned currQuad = 0;
unsigned tempcounter = 0;
unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;
unsigned ORcounter = 0;
unsigned ANDcounter = 0;
unsigned addone = 0 ; //dritsas
void comperror(char *format, ...) {
    va_list args;

    printf("\033[31m");

    va_start(args, format); 
    vprintf(format, args);  
    va_end(args);  

    printf("\033[0m");
}

void initializeStack(UIntStack *s) {
    s->capacity = sizeof(unsigned int);
    s->items = malloc(sizeof(unsigned int));
    s->top = -1;
}

bool isFull(UIntStack *s){
    return s->top == (s->capacity/4) - 1;
}

bool isEmpty(UIntStack *s){
    return s->top == -1;
}

void resize(UIntStack *s){
    s->capacity = s->capacity + 4;
    unsigned *newItem = (unsigned int *)realloc(s->items, (s->capacity/4)  *sizeof(unsigned int));
    s->items = newItem;
}

void push(UIntStack *s, unsigned int item){
    if(isFull(s)){
        resize(s);
    }
    s->items[++s->top] = item;
}

unsigned int pop(UIntStack *s){
    if(isEmpty(s)){
        fprintf(stderr, "Stack is empty\n");
        return -1; 
    } 
    else{
        return s->items[s->top--];
    }
}

unsigned int peek(UIntStack *s){
    if(!isEmpty(s)){
        return s->items[s->top];
    } 
    else{
        fprintf(stderr, "Stack is empty\n");
        return -1; 
    }
}

void freeStack(UIntStack *s){
    free(s->items);
    s->items = NULL;
    s->capacity = 0;
    s->top = -1;
}

void patchBreakContinue(UIntStack *s, unsigned label) {
    unsigned nextLabel;
    while(!isEmpty(s)){
        nextLabel = peek(s);
        patchlabel(nextLabel, label);
        pop(s);
    }
}

void expand(void){
    quad *p;
    assert(total==currQuad);
    p = (quad*)malloc(NEW_SIZE);
    if(quads){
        memcpy(p, quads, CURR_SIZE);
        free(quads);
    }
    quads = p;
    total += EXPAND_SIZE;
}

void emit(
    iopcode op,
    expr *  result,
    expr *  arg1,
    expr *  arg2,
    unsigned    label,
    unsigned    line
){
    quad *p;
    if(currQuad == total)
        expand();

    p = quads+currQuad++;
    p->op = op;
    p->arg1 = arg1;
    p->arg2 = arg2;
    p->result = result;
    p->label = label;
    p->line = line;
}

char *newtempname(void){
    char *nameBuffer = (char *)malloc(20  *sizeof(char));
    sprintf(nameBuffer, "_t%d", tempcounter++);
    return nameBuffer;
}

void resettemp(void){
    tempcounter = 0;
}

SymbolTableEntry_t *newtemp(HashTable *table, symbol_t sym){/*DANGER!!*/
    SymbolTableEntry_t *t;
    char *name = newtempname();
    t = H_Lookup(table, 0, name);
    if(t == NULL){/*was nil*/
        if(sym == var_s)
            t = H_Insert(&table, create_entry(0, LOCALVAR, createPassport(name, 0), 0));
        else if(sym == programfunc_s)
            t = H_Insert(&table, create_entry(0, USERFUNC, createPassport(name, 0), 0));        
        else if(sym == library_func_s)
            t = H_Insert(&table, create_entry(0, LIBFUNC, createPassport(name, 0), 0));
    }

    return t;
}

scopespace_t currscopespace(void){
    if(scopeSpaceCounter == 1)
        return programvar;
    else
        if(scopeSpaceCounter % 2 == 0)
            return formalarg;
        else   
            return functionlocal;
}

unsigned currscopeoffset(void){
    switch (currscopespace()){
        case programvar : return programVarOffset;
        case functionlocal : return functionLocalOffset;
        case formalarg : return formalArgOffset;
        default : assert(0);
    }
}

void incurrscopeoffset(void){
    switch (currscopespace()){
        case programvar : ++programVarOffset; break;
        case functionlocal : ++functionLocalOffset; break;
        case formalarg : ++formalArgOffset; break;
        default : assert(0);
    }
}


void enterscopespace(void){
    ++scopeSpaceCounter;
}

void exitscopespace(void){
    assert(scopeSpaceCounter>1);
    --scopeSpaceCounter;
}

void resetformalargsoffset(void){
    formalArgOffset = 0;
}

void resetfunctionlocalsoffset(void){
    functionLocalOffset = 0;
}

void restorecurrscopeoffset(unsigned n){
    switch(currscopespace()){
        case programvar : programVarOffset = n; break;
        case functionlocal : functionLocalOffset = n; break;
        case formalarg : formalArgOffset = n; break;
        default : assert(0);
    }
}

unsigned nextquadlabel(void){
    return currQuad;
}

expr *lvalue_expr(SymbolTableEntry_t *sym){
    expr *e;
    assert(sym);
    e = (expr*)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));

    e->next = NULL;
    e->sym  = sym;

    switch(sym->generaltype){
        case var_s : e->type = var_e; break;
        case programfunc_s : e->type = programfunc_e; break;
        case library_func_s : e->type = libraryfunc_e; break;
        default : assert(0);
    }

    return e;
}

expr *member_item(expr *lv, char *name, HashTable *table, unsigned line){
    expr *ti;
    lv = emit_iftableitem(lv, table, line); 
    ti = newexpr(tableitem_e); 
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name); 
    return ti;
}

expr *newexpr(expr_t t){
    expr *e = (expr*) malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->type = t;
    return e;
}

expr *newexpr_conststring(char *s){
    expr *e = newexpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}

expr *emit_iftableitem(expr *e, HashTable *table, unsigned line){
    if(e->type != tableitem_e)
        return e;
    else{
        expr *result = newexpr(var_e);
        result->sym = newtemp(table,0);
        emit(
            tablegetelem,
            result,
            e,
            e->index,
            currQuad,
            line
        );
        return result;
    }
}

expr *make_call(expr *lv, expr *reversed_elist, HashTable *table, unsigned line){
    expr *result, *func;
    func = emit_iftableitem(lv,table,line);
    while(reversed_elist){
        if(reversed_elist->type != nil_e){
            emit(param, reversed_elist, NULL, NULL, currQuad, line);
        }
        reversed_elist = reversed_elist->next;
    }
    emit(call_, func, NULL, NULL, currQuad, line);
    result = newexpr(var_e);
    result->sym = newtemp(table,0);
    emit(getretval, result, NULL, NULL, currQuad, line);
    return result;
}

expr *newexpr_constnum(double i){
    expr *e = newexpr(constnum_e);
    e->numConst = i;
    e->label = (int)i ;
    return e;
}

void check_arith(expr *e, const char *context){
    if(e->type == constbool_e   ||
       e->type == conststring_e ||
       e->type == nil_e         ||
       e->type == newtable_e    ||
       e->type == programfunc_e ||
       e->type == libraryfunc_e ||
       e->type == boolexpr_e)
       comperror("Illegal expr used in %s!", context);
}

unsigned int istempname(const char *s){
    return *s == '_';
}

unsigned int istempexpr(expr *e){
    return e->sym && (e->sym->type == LOCALVAR ||  e->sym->type == GLOBAL) && istempname(e->sym->passport.name);
}

void patchlabel(unsigned quadNo, unsigned label){
    printf("    %d  %d\n" , quadNo ,label);
    quads[quadNo].label = label;
    quads[quadNo].result->numConst=label;
}

expr *newexpr_constbool(unsigned int b){
    expr *e = newexpr(constbool_e);
    e->boolConst = !!b;
    if(b == 1){
        e->strConst = "\'true\'";
    }else{
        e->strConst = "\'false\'";
    }
    return e;
}

unsigned nextquad(void){ 
    return currQuad; 
}

void make_stmt(stmt_t *s){ 
    s->breakList = s->contList = 0; 
}

int newlist(int i){ 
    quads[i].label = 0; 
    return i; 
}

void patchlist(int list, int label){
    while(list){
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
}

void H_insertExtras(SymbolTableEntry_t *s){
    s->space = currscopespace();
    s->offset = currscopeoffset();
    incurrscopeoffset();
}

int expr_checkType(expr *e, expr *e1){
    if(e->type == programfunc_e || e->type == libraryfunc_e || 
        e->type == conststring_e || e->type == nil_e ||
        e->type == newtable_e || e->type == constbool_e || 
        e1->type == constbool_e || e1->type == conststring_e || 
        e1->type == programfunc_e || e1->type == libraryfunc_e || 
        e1->type == nil_e || e->type == boolexpr_e ||
        e1->type == boolexpr_e || e1->type == newtable_e){
        comperror("invalid arithmetic expresion");
        return 0;
    }
    return 1;
}

expr_t expr_retType(expr *temp, expr *a, expr *b){
    if(a->type == constnum_e && a->type == constnum_e){
        return constnum_e;
    }
    return temp->type;
}

SymbolTableEntry_t *returnTempName(expr *expr1, expr *expr3, HashTable *h){
    if(expr1 != NULL && istempexpr(expr1)){
		return expr1->sym;
	}else if(expr3 != NULL && istempexpr(expr3)){
		return expr3->sym;
	}else{
		return newtemp(h, var_s);
	}
}

expr *mergelist(expr *list1, expr *list2){
    if(!list1)
        return list2;
    else
        if(!list2)
            return list1;
        else{
            expr *iter = list1;
            while(iter->next){ 
                iter = iter->next;
            }
            iter->next = list2; 
            return list1; 
        }
}

void backPatch(expr *list, unsigned label){
    expr *temp = list;
    while(temp != NULL){
        patchlabel((int)(temp->label), label);
        temp = temp->next;
    }
}

expr *createTrueList(unsigned label){
    expr *list = newexpr_constnum(label+2);
    list->label = label;
    return list;
}

expr *createFalseList(unsigned label){
    expr *list = newexpr_constnum(label);
    list->label = label;
    return list;
}

expr *relopEmit(expr *E, expr *arg1, expr  *arg2, iopcode op, int line){
    E->trueList = createTrueList(nextquadlabel()); 
    E->falseList= createFalseList(nextquadlabel()+1); 
    emit(op, E->trueList, arg1, arg2, currQuad, line);
    emit(jump, E->falseList, NULL, NULL, currQuad, line);
    return E;
}

expr *logicEmit(expr *E, int line){
    if(E->type != boolexpr_e){
        E->trueList = createTrueList(nextquadlabel()); 
        E->falseList= createFalseList(nextquadlabel()+1); 
        emit(if_eq, E->trueList, E, newexpr_constbool('1'), currQuad, line);
        emit(jump, E->falseList, NULL, NULL, currQuad, line);
    }
    return E;
}

expr* cloneList(expr* head){ //dritsas
    expr* current=head;
    expr * newList = NULL;
    expr* temp=NULL;

    while(current != NULL){
        if(newList == NULL){
            newList=(expr*)malloc(sizeof(struct expr));
            newList->label = current->label;
            newList->next = NULL;
            temp=newList;
        }else{
            temp->next = (expr*)malloc(sizeof(struct expr));
            temp=temp->next;
            temp->label = current->label;
            temp->next = NULL;
        }
        current=current->next;
    }
    return newList;
}

const char *opcodeToString(iopcode op){
    switch(op){
        case assign: return "ASSIGN";
        case add: return "ADD";
        case sub: return "SUB";
        case mul: return "MUL";
        case div_: return "DIV";
        case mod: return "MOD";
        case uminus: return "UMINUS";
        case and: return "AND";
        case or: return "OR";
        case not: return "NOT";
        case if_eq: return "IF_EQ";
        case if_noteq: return "IF_NOTEQ";
        case if_lesseq: return "IF_LESS_EQUAL";
        case if_greatereq: return "IF_GREATER_EQUAL";
        case if_less: return "IF_LESS";
        case if_greater: return "IF_GREATER";
        case call_: return "CALL";
        case param: return "PARAM";
        case ret: return "RETURN";
        case getretval: return "GETRETVAL";
        case funcstart: return "FUNC_START";
        case funcend: return "FUNC_END";
        case tablecreate: return "TABLE_CREATE";
        case tablegetelem: return "TABLE_GET_ELEM";
        case tablesetelem: return "TABLE_SET_ELEM";
        case jump: return "JUMP";
        default: return "UNKNOWN";
    }
}


char *exprToString(expr *e){
    if(!e) 
        return "";

    char *result = malloc(256  *sizeof(char)); 
    if(!result) 
        return "";

    *result = '\0';

    switch (e->type) {
        case var_e:
            if(e->sym && e->sym->passport.name){
                strcpy(result, e->sym->passport.name);
            }
            break;
        case arithexpr_e:
            if(e->sym && e->sym->passport.name){
                strcpy(result, e->sym->passport.name);
            }
            break;
        case constnum_e:
            if(istempexpr(e)){
                strcpy(result, e->sym->passport.name);
            } 
            else{
                if(addone == 0 ){//dritsas
                    sprintf(result, "%f", e->numConst ); 
                }
                else {
                    sprintf(result, "%f", e->numConst +1 );                     
                }
            }
            break;
        case constbool_e:
            strcpy(result, e->boolConst ? "true" : "false");
            break;
        case conststring_e:
            if(e->strConst){
                sprintf(result, "\"%s\"", e->strConst);
            }
            break;
        case nil_e:
            strcpy(result, "nil");
            break;
/*         case boolexpr_e:
            sprintf(result, "%d", e->label);
            break; */
        default:
            if(e->sym && e->sym->passport.name){
                strcpy(result, e->sym->passport.name);
            }
            break;
    }

    return result;
}

void printQuad(FILE *f, int index) {
    char *result;
    fprintf(f, "%d: %s", index +1, opcodeToString(quads[index].op));//dritsas
    if(quads[index].op ==10 || quads[index].op ==11 ||
    quads[index].op ==12 || quads[index].op ==13 ||
    quads[index].op ==14 ||quads[index].op ==15){
        addone = 1 ;
    }
    if(quads[index].op == jump) {
        if(quads[index].result) {
            result = exprToString(quads[index].result); 
            fprintf(f, " %d", (int)(quads[index].label +1)); 
            free(result);
        }
    } 
    else {
        if(quads[index].result) {
            result = exprToString(quads[index].result );
            fprintf(f, " %s", result);
            free(result);
        }
        if(quads[index].arg1) {
            result = exprToString(quads[index].arg1);
            fprintf(f, " %s", result);
            free(result);     
        }
        if(quads[index].arg2) {
            result = exprToString(quads[index].arg2);
            fprintf(f, " %s", result);
            free(result);      
        }
    }
    fprintf(f, " [line: %d]\n", quads[index].line);
    addone = 0 ; //dritsas
}

void printQuads(FILE *f){
    int i;
    fprintf(f, "\n----------Intermediate code----------\n");

    for(i = 0; i < currQuad; i++){
        printQuad(f, i);
    }
}
 