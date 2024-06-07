CC := gcc
CFLAGS := -g
FLEX := flex
BISON := bison
RM := rm -f
MATH := -lm

LEX_SOURCE := lex/alpha_lex.l
BISON_SOURCE := bison/parse.y
LEX_OUT := lex/alpha_lex.c
BISON_OUT_C := bison/parse.c
BISON_OUT_H := bison/parse.h 

SYM_TABLE := bison/symbolTable/symTable.c
QUAD := bison/quads/quad.c
VM := bison/instructions/vm.c

AVM_SRC := avm/alpha.c avm/avm.c avm/avm_table/avm_table.c avm/execute/execute.c avm/libfunc/libfunc.c
AVM_HEADERS := avm/avm.h avm/avm_table/avm_table.h avm//execute/execute.h avm/libfunc/libfunc.h

PARSER_TARGET := parser
AVM_TARGET := avm/avm_program

.PHONY: all clean

all: $(PARSER_TARGET) $(AVM_TARGET)

$(PARSER_TARGET): $(BISON_OUT_C) $(LEX_OUT) $(SYM_TABLE) $(QUAD) $(VM)
	$(CC) $(CFLAGS) -o $@ $(BISON_OUT_C) $(LEX_OUT) $(SYM_TABLE) $(QUAD) $(VM)

$(AVM_TARGET): $(AVM_SRC) $(AVM_HEADERS)
	$(CC) $(CFLAGS) -o $@ $(AVM_SRC) $(MATH)

$(LEX_OUT): $(LEX_SOURCE) $(BISON_OUT_C) $(BISON_OUT_H)
	$(FLEX) --outfile=$@ $(LEX_SOURCE)

$(BISON_OUT_C) $(BISON_OUT_H): $(BISON_SOURCE)
	$(BISON) -v --yacc --defines=$(BISON_OUT_H) --output=$(BISON_OUT_C) $<

clean:
	$(RM) $(PARSER_TARGET) $(AVM_TARGET) $(LEX_OUT) $(BISON_OUT_C) $(BISON_OUT_H) *.o *.out bison/parse.output lex/alpha_lex.h
