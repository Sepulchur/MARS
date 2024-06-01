%{
#include "alpha.h"
#include "alpha_lex.h"
#include "symTable.h"
#include "quad.h"
#include <stdio.h>
#include <stdlib.h>

void yyerror(char *s);

extern int yylex(void);
extern int yylineno;
extern int tempcounter;
extern unsigned functionLocalOffset;
extern unsigned currQuad;
extern unsigned ORcounter;
extern unsigned ANDcounter;
extern char *yytext;
extern alpha_token_t *head;
extern alpha_token_t *temp;
extern alpha_token_t *temp_op;

alpha_token_t *temp_lvalue;
HashTable *table = NULL;
SymbolTableEntry_t *temp_symbol = NULL;
SymbolTableEntry_t *temp_test = NULL;
SymbolTableEntry_t *error_symbol = NULL;
expr *temp_expr;
expr* ORQuadNo = NULL;
expr* ANDQuadNo = NULL;
expr* tempQuad;
unsigned emits = 0 ; //dritsas
UIntStack *funcStack = NULL;
UIntStack *loopStack = NULL;
UIntStack *breakstacklist;
UIntStack *contstacklist;

bool local = false;
bool make = true;
bool lassignl = false;

unsigned funcNo = 0;
unsigned loopcounter = 0;
unsigned functionDepth = 0;
unsigned currentScope = 0; 
unsigned error_flag = 0;
unsigned key = 11;
unsigned num = 0;
unsigned Mlabel = 0; 
unsigned test = 0;
unsigned retLabel = 0 ; 

void enterScope(){
    currentScope++;
}

void exitScope(HashTable *table){
    hide_scope(table, currentScope);
    currentScope--;
}

%}

%start program

%union {
  char* strVal;
  int   intVal;
  float floatVal;
  struct expr* enode;
}

%token <strVal> IDENTIFIER STRING
%token <intVal> INTEGER 
%token <floatVal> REAL
%token IF ELSE WHILE FOR RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL FUNCTION
%token ASSIGN ADD MINUS MULTIPLICATION DIVISION MODULO EQUAL UNEQUAL INCREMENT DECREMENT GREATER LESS 
%token GREATEROREQUAL LESSOREQUAL LEFT_CURLY_BRACE RIGHT_CURLY_BRACE LEFT_SQUARE_BRACE RIGHT_SQUARE_BRACE 
%token LEFT_PARENTHESIS  RIGHT_PARENTHESIS SEMICOLON COMMA COLON DOUBLE_COLON PERIOD DOUBLE_PERIOD  
//%token SINGLE_LINE_COMMENT MULTIPLE_LINE_COMMENT
%right ASSIGN
%left AND //dritsas
%left OR
%nonassoc EQUAL UNEQUAL
%nonassoc GREATER GREATEROREQUAL LESS LESSOREQUAL
%left ADD MINUS
%left MULTIPLICATION DIVISION MODULO
%right NOT DECREMENT INCREMENT
%nonassoc UMINUS
%left PERIOD DOUBLE_PERIOD
%left LEFT_SQUARE_BRACE RIGHT_SQUARE_BRACE
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS
%left RIGHT_CURLY_BRACE LEFT_CURLY_BRACE

%type <enode> expr
%type <enode> term
%type <enode> assignexpr
%type <enode> primary
%type <enode> lvalue
%type <enode> member
%type <enode> call
%type <enode> callsufix
%type <enode> normallcall
%type <enode> methodcall
%type <enode> elist
%type <enode> objectdef
%type <enode> indexed
%type <enode> indexedelem
%type <enode> funcdef
%type <enode> const
%type <enode> stmt
%type <enode> list_of_stmts
%type <enode> whilestmt
%type <enode> forstmt
%type <intVal> elseprefix
%type <intVal> ifprefix
%type <intVal> whilecond
%type <intVal> whilestart
%type <intVal> forprefix
%type <intVal> N
%type <intVal> M
%%

program: 
    | program stmt    
    ;

stmt:
      expr SEMICOLON
    {
      resettemp(); 
      $$=NULL;
      if(emits == 1 ){ //dritsas
        backPatch($1->falseList, nextquadlabel()+2);
        emit(assign, $1, newexpr_constbool(1), NULL, currQuad, yylineno);
        emit(jump, newexpr_constnum(0), NULL, NULL, nextquadlabel()+2, yylineno);
        emit(assign, $1, newexpr_constbool(0), NULL, currQuad, yylineno);
        make = true;
        emits = 0 ;
      }
    }
    | ifstmt {resettemp(); $$=NULL;}
    | whilestmt {resettemp(); $$=NULL;}
    | forstmt {resettemp(); $$=NULL;}
    | returnstmt {resettemp(); $$=NULL;}
    | BREAK
    {
      if(!loopcounter){yyerror("Use of 'break' while not in a loop");}
    } 
      SEMICOLON
    {

    }
		| CONTINUE
    {
      if(!loopcounter){yyerror("Use of 'return' while not in a loop");}
    } 
      SEMICOLON
    {

    }
    | block {resettemp(); $$=NULL;}
    | funcdef {resettemp(); $$=NULL;}
    | SEMICOLON {resettemp(); $$=NULL;}
    ;

list_of_stmts:	stmt list_of_stmts {$$ = $1;}
		| {$$ = NULL;}
		;

expr:
      assignexpr {$$=$1;}
		| expr ADD expr 
    { 
      if(expr_checkType($1, $3)){ 
        $$ = newexpr(arithexpr_e); 
        $$->type = expr_retType($$,$1,$3);
        $$->sym = returnTempName($1,$3,table); 
        emit(add, $$, $1, $3, currQuad, yylineno);
      } 
    }
	  | expr MINUS expr 
    { 
      if(expr_checkType($1, $3)){ 
        $$ = newexpr(arithexpr_e); 
        $$->type = expr_retType($$,$1,$3);
        $$->sym = returnTempName($1,$3,table);
        emit(sub, $$, $1, $3, currQuad, yylineno);
      } 
    }
	  | expr MULTIPLICATION expr 
    { 
      if(expr_checkType($1, $3)){ 
        $$ = newexpr(arithexpr_e); 
        $$->type = expr_retType($$,$1,$3);
        $$->sym = returnTempName($1,$3,table); 
        emit(mul, $$, $1, $3, currQuad, yylineno);
      } 
    }
	  | expr DIVISION expr 
    { 
      if(expr_checkType($1, $3)){ 
        $$ = newexpr(arithexpr_e); 
        $$->type = expr_retType($$,$1,$3);
        $$->sym = returnTempName($1,$3,table); 
        emit(div_, $$, $1, $3, currQuad, yylineno);
      } 
    }
	  | expr MODULO expr 
    { 
      if(expr_checkType($1, $3)){ 
        $$ = newexpr(arithexpr_e); 
        $$->type = expr_retType($$,$1,$3);
        $$->sym = returnTempName($1,$3,table); 
        emit(mod, $$, $1, $3, currQuad, yylineno);
      } 
    }
    | expr EQUAL expr
    {
      $$ = newexpr(boolexpr_e);  
      $$->sym = returnTempName($1,$3,table); 
      $$ = relopEmit($$, $1, $3, if_eq, yylineno);  
    }
    | expr UNEQUAL expr
    {
      $$ = newexpr(boolexpr_e);  
      $$->sym = returnTempName($1,$3,table);
      $$ = relopEmit($$, $1, $3, if_noteq, yylineno); 
    }
	  | expr GREATER expr 
    {
      $$ = newexpr(boolexpr_e);  
      $$->sym = returnTempName($1,$3,table); 
      $$ = relopEmit($$, $1, $3, if_greater, yylineno);
    }
    | expr LESS expr
    {
      $$ = newexpr(boolexpr_e);  
      $$->sym = returnTempName($1,$3,table); 
      $$ = relopEmit($$, $1, $3, if_less, yylineno); 
    }
	  | expr GREATEROREQUAL expr 
    {
      $$ = newexpr(boolexpr_e);
      $$->sym = returnTempName($1,$3,table); 
      $$ = relopEmit($$, $1, $3, if_greatereq, yylineno);
    }
	  | expr LESSOREQUAL expr 
    {
      $$ = newexpr(boolexpr_e); 
      $$->sym = returnTempName($1,$3,table); 
      $$ = relopEmit($$, $1, $3, if_lesseq, yylineno); 
    }
    | expr AND{logicEmit($1,yylineno);} M expr 
    {
      $$ = newexpr(boolexpr_e);  
      $$->sym = returnTempName($1, $5, table);

			logicEmit($5, yylineno);

			Mlabel = $5->trueList->label;
      printf("263");
			backPatch($1->trueList, Mlabel);
			backPatch($1->falseList, $1->falseList->label+2);

      if(ORcounter == 1){ //dritsas
				backPatch(tempQuad, Mlabel+2);
        ORcounter = 0 ;
			}
														
			$$->trueList = $5->trueList;
			$$->falseList = mergelist($1->falseList, $5->falseList);
      emits = 1 ;
		} 
		| expr OR{logicEmit($1, yylineno);} M expr 
    {
      $$ = newexpr(boolexpr_e);  
      $$->sym = returnTempName($1, $5, table); 
      logicEmit($5, yylineno);
			Mlabel=$5->trueList->label;
			backPatch($1->falseList, Mlabel);
			backPatch($1->trueList, $1->trueList->numConst+2);

			tempQuad = cloneList($1->trueList); //dritsas

			$$->trueList = mergelist($1->trueList, $5->trueList);
			$$->falseList = $5->falseList;
      ORcounter = 1;
      emits = 1 ;

		} 
	  | term{$$=$1;}
	  ;

term:
      LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {$$=$2;}
		| MINUS expr 
    {
      $$=newexpr(arithexpr_e); 
      $$->sym = newtemp(table,0); 
      emit(uminus, $$, $2, (expr *) 0, currQuad, yylineno);
    } 
    | NOT expr 
    {
      $$=newexpr(boolexpr_e); 
      $$->sym = newtemp(table,0); 
			if($2->type!=boolexpr_e){
				$2->trueList = createTrueList(nextquadlabel());
				$2->falseList= createFalseList(nextquadlabel());  
				emit(if_eq, $2->falseList, $2, newexpr_constbool(1), currQuad, yylineno);
				emit(jump, $2->trueList, NULL, NULL, currQuad, yylineno);
				emit(assign, $$, newexpr_constbool(1), NULL, currQuad, yylineno);
    		emit(jump, newexpr_constnum(nextquadlabel()+2), NULL, NULL, nextquadlabel(), yylineno);
    		emit(assign, $$, newexpr_constbool(0), NULL, currQuad, yylineno);
			}
			$$->trueList = $2->falseList; 
			$$->falseList = $2->trueList; 
    }
    | INCREMENT lvalue 
    {
      SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
      if(t != NULL && t->type > 3){
        yyerror("Cannot increment function value\n");
      }
      if($2->type == tableitem_e){
        $$ = emit_iftableitem($2,table,yylineno);
        emit(add, $$, $$, newexpr_constnum(1), currQuad, yylineno);
        emit(tablesetelem, $$, $2, $2->index, currQuad, yylineno);
      }
      else{
        emit(add, $2, $2, newexpr_constnum(1), currQuad, yylineno);
        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp(table,0);
        emit(assign, $$, $2, NULL, currQuad, yylineno);
      }
    }
	  | lvalue INCREMENT 
    {
      SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
      if(t != NULL && t->type > 3){
        yyerror("Cannot increment function value\n");
      }
      $$ = newexpr(var_e); 
      $$->sym = newtemp(table,0);
      if($1->type == tableitem_e){
        expr * value = emit_iftableitem($1,table,yylineno);
        emit(assign, $$, value, NULL, currQuad, yylineno);
        emit(add, value, value, newexpr_constnum(1), currQuad, yylineno);
        emit(tablesetelem, value, $1, $1->index, currQuad, yylineno);
      }
      else{
        emit(assign, $$, $1, NULL, currQuad, yylineno);
        emit(add, $1, $1, newexpr_constnum(1), currQuad, yylineno);
      }
    }
	  | DECREMENT lvalue 
    {
      SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
      if(t != NULL && t->type > 3){
        yyerror("Cannot decrement function value\n");
      }
      if($2->type == tableitem_e){
        $$ = emit_iftableitem($2,table,yylineno);
        emit(sub, $$, $$, newexpr_constnum(1), currQuad, yylineno);
        emit(tablesetelem, $$, $2, $2->index, currQuad, yylineno);
      }
      else{
        emit(sub, $2, $2, newexpr_constnum(1), currQuad, yylineno);
        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp(table,0);
        emit(assign, $$, $2, NULL, currQuad, yylineno);
      }
    }
	  | lvalue DECREMENT 
    {
      SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
      if(t != NULL && t->type > 3){
        yyerror("Cannot decrement function value\n");
      }
      $$ = newexpr(var_e); $$->sym = newtemp(table,0);
      if($1->type == tableitem_e){
        expr * value = emit_iftableitem($1,table,yylineno);
        emit(assign, $$, value, NULL, currQuad, yylineno);
        emit(sub, value, value, newexpr_constnum(1), currQuad, yylineno);
        emit(tablesetelem, value, $1, $1->index, currQuad, yylineno);
      }
      else{
        emit(assign, $$, $1, NULL, currQuad, yylineno);
        emit(sub, $1, $1, newexpr_constnum(1), currQuad, yylineno);
      }                  
    }
    | primary{$$=$1;}
    ;


assignexpr: 
      lvalue
    {
      /*$1 = lvalue_expr(temp_test); */
    }
      ASSIGN
    {
      lassignl=true;
    } 
      expr 
    {
      if(emits ==1){ //dritsas
        backPatch($5->falseList, nextquadlabel()+2); 
        emit(assign, $5, newexpr_constbool(1), NULL, currQuad, yylineno);
        emit(jump, newexpr_constnum(0), NULL, NULL, nextquadlabel()+2, yylineno);
        emit(assign, $5, newexpr_constbool(0), NULL, currQuad, yylineno);
        emits = 0 ;
      }

      lassignl=false;
      if(local){
        local = false;
      }
      else{
        SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
        if(t != NULL && t->type > 3){
          yyerror("Cannot assign value to function at line ");
        }
      }
			if($1 != NULL && $1->type == tableitem_e){
        if($5 != NULL){
        $$ =  emit_iftableitem($5, table,yylineno);
        }
				emit(tablesetelem, $1,  $1->index , $$ , currQuad , yylineno);

				$$ = emit_iftableitem($1, table,yylineno);
				$$->type = assignexpr_e;
			}
      else{
				emit(assign, $1, $5, NULL, currQuad, yylineno); 
				$$ = newexpr(assignexpr_e); 
				$$->sym = newtemp(table,var_s); 
				emit(assign, $$, $1, NULL, currQuad, yylineno); 
			}
		}
		;

primary:
      lvalue{$$ = $1;}
    | call {}
    | objectdef {}
    | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS{$$ = $2;}
    | const {$$ = $1;}
    ;

lvalue:
      IDENTIFIER
    {
      temp_lvalue = temp;
      temp_lvalue->content = $1;
      SymbolTableEntry_t *new;
      SymbolTableEntry_t *temp_s = NULL;
      if(currentScope){
        new = create_entry(key+1,LOCALVAR,createPassport(temp_lvalue->content, currentScope), temp_lvalue->numline);
      }
      else{
        new = create_entry(key+1,GLOBAL,createPassport(temp_lvalue->content, currentScope), temp_lvalue->numline);
      }
      if(H_Search(table, currentScope, temp_lvalue->content)!= -1 ){
        yyerror("doesnt have acccess");
        free(new);
      }
      else if(checkLib(table,new)){
        yyerror("Conflicting name with library function");
        free(new);
      }
      else if(!(temp_s = H_Lookup(table, currentScope, temp_lvalue->content))){
        if(!0){
          temp_s = H_Insert(&table, new);
          H_insertExtras(temp_s);
          key++;
        }
        else{
          free(new);
        }
      }
      else{
        free(new);
      }
      if(temp_s == NULL){
        $$ = NULL;
      }
      else{
        temp_test = temp_s;/*what's up danger*/
        $$ = lvalue_expr(temp_s);
      }
    }
		| LOCAL IDENTIFIER
    {
      local = true;
      temp_lvalue=temp;
      SymbolTableEntry_t *new;
      SymbolTableEntry_t *temp = NULL;
      SymbolTableEntry_t *temp_s = NULL;
      if(currentScope){
        new = create_entry(key+1,LOCALVAR,createPassport(temp_lvalue->content, currentScope), temp_lvalue->numline);
      }
      else{
        new = create_entry(key+1,GLOBAL,createPassport(temp_lvalue->content, currentScope), temp_lvalue->numline);
      }
      if(checkLib(table,new)){
        yyerror("Conflicting name with library function");
      }
      else if(H_Lookup(table, currentScope, temp_lvalue->content)==NULL){
        key++;
        temp_s = H_Insert(&table, new);
        H_insertExtras(temp_s);
      }
      if(temp_s == NULL){
        $$ = NULL;
      }
      else{
        $$ = lvalue_expr(temp_s);
      }
    }
		| DOUBLE_COLON IDENTIFIER
    {
      temp_lvalue=temp;
      SymbolTableEntry_t *temp_s = H_Lookup(table, 0, temp_lvalue->content);
			if(temp_s == NULL && currentScope != 0){
        yyerror("Undefined GLOBAL variable");   
			}
      else{
        $$ = lvalue_expr(temp_s);
      }
    }
		| member{$$ = $1;}
		;

member:
      lvalue PERIOD IDENTIFIER{if($1 != NULL){$$ = member_item($1, $3, table , yylineno);}}
    | lvalue LEFT_SQUARE_BRACE expr RIGHT_SQUARE_BRACE
    { 
      $1 = emit_iftableitem($1, table,yylineno); 
      $$ = newexpr(tableitem_e); 
      $$->sym = $1->sym; 
      $$->index = $3; 
    }
    | call PERIOD IDENTIFIER{$$ = NULL;}
    | call LEFT_SQUARE_BRACE expr RIGHT_SQUARE_BRACE{$$ = NULL;}
    ;

call:
      call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS{$$ = make_call($1, $3, table, yylineno);}
    | IDENTIFIER callsufix
    {
      //SymbolTableEntry_t *new = create_entry(0,USERFUNC,createPassport($1, currentScope), yylineno);
      SymbolTableEntry_t *new = H_Lookup(table, -1, $1);
      H_insertExtras(new);
      expr *temp_lvalue_expr = lvalue_expr(new);
			if($2->boolConst == '1'){
        expr *self = temp_lvalue_expr;
        temp_lvalue_expr = emit_iftableitem(member_item(self, $2->strConst, table , yylineno),table,yylineno);
        self->next = $2->next; 
        $2 = self;
			}
			$<enode>$ = make_call(temp_lvalue_expr, $2, table, yylineno);
		}
    | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS
    {
			expr* func = newexpr(programfunc_e);
			func->sym = $2->sym;
			$$ = make_call(func, $5,table, yylineno);
		}
    ;

callsufix:
      normallcall{$$ = $1;}
    | methodcall{$$ = $1;}
    ;

normallcall:
      LEFT_PARENTHESIS elist RIGHT_PARENTHESIS 
    {	
			$$ = newexpr(nil_e);
			$$->next = $2;
			$$->strConst = NULL;
			$$->boolConst = false;
		}
    ;

methodcall:
      DOUBLE_PERIOD IDENTIFIER LEFT_PARENTHESIS elist RIGHT_PARENTHESIS
    {
			$$ = newexpr(tableitem_e);
			$$->next = $4;
			$$->strConst = $2;
			$$->boolConst = '1';
		}
    ;

elist: {$$ = NULL;}
    | expr {$$ = $1;}
    | elist COMMA expr
    {
      expr *new_node = $3; 
      expr *temp2 = $1;    
      if(temp2 != NULL){
        while (temp2->next != NULL){
            temp2 = temp2->next;
        }
        temp2->next = new_node;
      } 
      else{
          $$ = new_node;
      }
      new_node->next = NULL; 
    }
    ;


objectdef:
      LEFT_SQUARE_BRACE elist RIGHT_SQUARE_BRACE
    {
      int i = 0;
			expr *node = newexpr(newtable_e);
			node->sym = newtemp(table,0);
			emit(tablecreate, node, NULL, NULL, currQuad, yylineno);
			while($2 != NULL){
				emit(tablesetelem,$2,node, newexpr_constnum(i++), currQuad, yylineno);
				$2 = $2->next;
			}
			$$ = node;
    }
    | LEFT_SQUARE_BRACE indexed RIGHT_SQUARE_BRACE
    {
      expr *node = newexpr(newtable_e);
			node->sym = newtemp(table,0);
			emit(tablecreate, node, NULL, NULL, currQuad, yylineno);
			while($2!=NULL){
				emit(tablesetelem, $2,node, $2->index, currQuad, yylineno);
				$2 = $2->next;
			}
			$$ = node;		
    }
    ;

indexed:
      indexedelem
    { 
      expr *node = $1;
      node->next = NULL; 
      $$ = node;
    }
    | indexed COMMA indexedelem
    {
      expr *node = $3;
      expr *temp = $1;

      while (temp->next != NULL) {
          temp = temp->next;
      }
      temp->next = node; 
      node->next = NULL; 

      $$ = $1;
    }
    ;

indexedelem:
      LEFT_CURLY_BRACE expr COLON expr RIGHT_CURLY_BRACE
    {
      $$ = $4;
      $$->index = $2;
    }
    ;

block:
    LEFT_CURLY_BRACE
    {
      enterScope();
    } 
    list_of_stmts RIGHT_CURLY_BRACE 
    {
      exitScope(table);
    }
    ;

funcdef:
      FUNCTION IDENTIFIER
    {
      functionDepth++;
      SymbolTableEntry_t *new = create_entry(key+1,USERFUNC,createPassport(temp->content, currentScope), temp->numline); 
      if(!validity_check(table, new,true)){
        temp_symbol = H_Insert(&table, new);
        key++;
        $<enode>$ = lvalue_expr(temp_symbol);
				$<enode>$->sym->address = nextquadlabel();
				funcNo = nextquadlabel();
				emit(jump, newexpr_constnum(0), NULL, NULL, currQuad, temp->numline);
				emit(funcstart, $<enode>$, NULL, NULL, currQuad, temp->numline);
				push(funcStack, functionLocalOffset);
				temp_expr = $<enode>$;
      }
      else{
        error_symbol = create_entry(key+1,USERFUNC,createPassport(temp->content, currentScope), temp->numline); 
      }
      resetformalargsoffset();
    } 
      LEFT_PARENTHESIS{enterscopespace();} idlist RIGHT_PARENTHESIS
      {
        enterscopespace(); 
        resetfunctionlocalsoffset(); 
        push(loopStack, loopcounter); 
        loopcounter = 0;
        if(error_symbol != NULL){
          ArgList *atemp, *atemp2;
          atemp = error_symbol->argList;
          while(atemp){
            atemp2 = atemp;
            atemp = atemp->next;
            free(atemp2);
          }
          free(error_symbol);
        }
      } 
      block
    {
      functionDepth--;
 			exitscopespace(); 
      exitscopespace();
			$$ = temp_expr;
		  functionLocalOffset = pop(funcStack);
			emit(funcend, $$, NULL, NULL, currQuad, yylineno);
			patchlabel(retLabel, currQuad-1); 
			patchlabel(funcNo, nextquadlabel());
			loopcounter = pop(loopStack);
    }
    | FUNCTION
    {
      functionDepth++;
      SymbolTableEntry_t *new = create_entry(++key,USERFUNC,createFuncName(currentScope, ++num), temp->numline);
      temp_symbol = H_Insert(&table, new);
      $<enode>$ = lvalue_expr(temp_symbol);
			funcNo = nextquadlabel();
			emit(jump, newexpr_constnum(0), NULL, NULL, currQuad, yylineno);
			emit(funcstart, $<enode>$, NULL, NULL, currQuad, yylineno);
			push(funcStack, functionLocalOffset);
			temp_expr = $<enode>$;
			resetformalargsoffset();
    } 
      LEFT_PARENTHESIS{enterscopespace();} idlist RIGHT_PARENTHESIS
    {
      enterscopespace(); 
    }
      block
    {
      functionDepth--;
      exitscopespace(); 
      exitscopespace();
 			$$ = temp_expr;
		  functionLocalOffset = pop(funcStack);
		  emit(funcend, $$, NULL, NULL, currQuad, yylineno);
			patchlabel(retLabel, currQuad-1); 
		  patchlabel(funcNo, nextquadlabel());
    }
    ;

const:
      INTEGER {$$ = newexpr_constnum(yylval.intVal);} 
		| REAL {$$ = newexpr_constnum(yylval.floatVal);}
		| STRING {$$ = newexpr_conststring(yylval.strVal);}
		| NIL {$$ = newexpr(nil_e);}
		| TRUE {$$ = newexpr_constbool(1);}
		| FALSE {$$ = newexpr_constbool(0);}
		;

idlist:
    | IDENTIFIER
    {
      passport_t v = createPassport(temp->content, currentScope+1); 
      if(error_symbol == NULL){
        if(AL_Insert(&temp_symbol->argList, v) == NULL){
          yyerror("Redifinition of formal");
        }
        else{
          SymbolTableEntry_t *new = create_entry(key,FORMAL,v,yylineno);
          if(checkLib(table, new)){
            yyerror("Argument causes 'Conflicting name with library function'");
          }
          else{
            key++;
            H_Insert(&table, new);
          }
        }
      }
      else{
        if(AL_Insert(&error_symbol->argList, v) == NULL){
          yyerror("Redifinition of formal");
        }
        else{
          SymbolTableEntry_t *new = create_entry(key,FORMAL,v,yylineno);
          if(checkLib(table, new)){
            yyerror("Argument causes 'Conflicting name with library function'");
          }
          else{
            key++;
            H_Insert(&table, new);
          }
        }
      }
    }
    | idlist COMMA IDENTIFIER
    {
      passport_t v = createPassport(temp->content, currentScope+1); 
      if(error_symbol == NULL){
        if(AL_Insert(&temp_symbol->argList, v) == NULL){
          yyerror("Redifinition of formal");
        }
        else{
          SymbolTableEntry_t *new = create_entry(key,FORMAL,v,yylineno);
          if(checkLib(table, new)){
            yyerror("Argument causes 'Conflicting name with library function'");
          }
          else{
            key++;
            H_Insert(&table, new);
          }
        }
      }
      else{
        if(AL_Insert(&error_symbol->argList, v) == NULL){
          yyerror("Redifinition of formal");
        }
        else{
          SymbolTableEntry_t *new = create_entry(key,FORMAL,v,yylineno);
          if(checkLib(table, new)){
            yyerror("Argument causes 'Conflicting name with library function'");
          }
          else{
            key++;
            H_Insert(&table, new);
          }
        }
      }
    }
    ;

N: 	{$N = nextquadlabel();emit(jump, newexpr_constnum(0), NULL, NULL, 0, yylineno);};

M: 	{$M = nextquadlabel();};

ifprefix: 
      IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  
    {
      emit(if_eq, $3, newexpr_constbool(1), NULL, nextquad() + 2, yylineno);
      $$ = nextquadlabel();
      emit(jump, newexpr_constnum(0), NULL, NULL, 0, yylineno);
    }
    ;

ifstmt: 
      ifprefix stmt
    {
      patchlabel($1, nextquad());
    }
    | ifprefix stmt elseprefix stmt
    {
      patchlabel($1, $3 + 1);
      patchlabel($3, nextquad());
    }
    ;

elseprefix: 
      ELSE
    {
      $$ = nextquadlabel();
      emit(jump, newexpr_constnum(0), NULL, NULL, 0, yylineno);
    }
    ;

whilestart : 
      WHILE
    {
      $$ = nextquadlabel();
    }
    ;

whilecond : 
      LEFT_PARENTHESIS expr RIGHT_PARENTHESIS
    {
      ++loopcounter;	
			push(breakstacklist, 0); 
      push(contstacklist, 0); 
      printf("edo %d", nextquadlabel());
			emit(if_eq, newexpr_constnum(nextquadlabel()+2), $2, newexpr_constbool('1'), currQuad, yylineno); 
		  $$ = nextquadlabel();   
			emit(jump, newexpr_constnum(0), NULL, NULL, currQuad, yylineno);
    }
    ;

whilestmt : 
      whilestart whilecond stmt
    {
      --loopcounter;	
			emit(jump, newexpr_constnum($1), NULL, NULL, currQuad, yylineno);   
			patchlabel($2, nextquadlabel());   

			patchBreakContinue(breakstacklist, nextquadlabel());
			pop(breakstacklist);
			patchBreakContinue(contstacklist, $1);
			pop(contstacklist);
    }
    ;

forprefix: 
      FOR LEFT_PARENTHESIS elist SEMICOLON M expr SEMICOLON
    {
      $$ = nextquadlabel();
      test = $5;
			emit(if_eq, newexpr_constnum(1), $6, newexpr_constbool('1'), currQuad, yylineno);
		}
		;

forstmt:	
      forprefix N elist RIGHT_PARENTHESIS
    { 
      ++loopcounter;
			push(breakstacklist, 0);
      push(contstacklist, 0); 
		} 
      N stmt N 
    {
			--loopcounter; 
			patchlabel($1, $6+1);
			patchlabel($2, nextquadlabel());
			patchlabel($6, test);
			patchlabel($8, $2+1);

			patchBreakContinue(breakstacklist, nextquadlabel());
			patchBreakContinue(contstacklist, $2+1);
		}
		;

returnstmt: 
      RETURN
    {
			if(!functionDepth){
        yyerror("expected identifier or '(' before 'return'");
      }
    } 
      expr SEMICOLON 
    { 
      emit(ret, $3, NULL, NULL, currQuad, yylineno); 
      retLabel = currQuad ; 
      emit(jump , newexpr_constnum(0) , NULL  , NULL , currQuad ,yylineno);
    }
		| RETURN
    {
      if(!functionDepth){
        yyerror("expected identifier or '(' before 'return'");
      }
    } 
      SEMICOLON	
    {
      emit(ret, NULL, NULL, NULL, currQuad, yylineno);
      retLabel = currQuad ; 
      emit(jump , newexpr_constnum(0) , NULL  , NULL , currQuad ,yylineno);      
    }		
		;
%%

void yyerror(char *s){
  error_flag = 1;
  fprintf(stdout, "\x1b[31mError: %s at line : %d\n \x1b[0m", s , yylineno);
}

int main(int argc, char **argv){
  FILE *f = fopen("IntermediateCode.txt", "w");

  funcStack = malloc(sizeof(UIntStack));
  initializeStack(funcStack);
  loopStack = malloc(sizeof(UIntStack));
  initializeStack(loopStack);
  breakstacklist = malloc(sizeof(UIntStack));
	initializeStack(breakstacklist);
	contstacklist = malloc(sizeof(UIntStack));
	initializeStack(contstacklist);
  table = createHashTable();
  if(table == NULL){
    printf("Failed to create hash table\n");
    return -1;
  }
  
  if(argc > 1){
		if(!(yyin = fopen(argv[1], "r"))){
			fprintf(stdout, "Cannot read file: %s\n", argv[1]);
			return 1;
		}
	else
		yyin = stdin;
  }

	yyparse();
  
  PrintHashTable(table);
  if(argc > 1) {
     fclose(yyin);
  }

	if(!error_flag)
		printQuads(f);

  fclose(f);
  /*The queue is important*/
  free(loopStack->items);
  free(loopStack);
  free(funcStack->items);
  free(funcStack);
  free(breakstacklist->items);
  free(breakstacklist);
  free(contstacklist->items);
  free(contstacklist);
  freeHashTable(table);
  free_all(head);
  yylex_destroy();

	return 0;
}
