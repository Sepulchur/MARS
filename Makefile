CC := gcc
CFLAGS := -g
FLEX := flex
BISON := bison
RM := rm -f

LEX_SOURCE := alpha_lex.l
BISON_SOURCE := parse.y
LEX_OUT := alpha_lex.c
BISON_OUT_C := parse.c
BISON_OUT_H := parse.h 
SYM_TABLE := symTable.c
QUAD := quad.c
TARGET := parser

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(BISON_OUT_C) $(LEX_OUT) $(SYM_TABLE) $(QUAD)
	$(CC) $(CFLAGS) -o $@ $(BISON_OUT_C) $(LEX_OUT) $(SYM_TABLE) $(QUAD)

$(LEX_OUT): $(LEX_SOURCE) $(BISON_OUT_C) $(BISON_OUT_H)
	$(FLEX) --outfile=$@ $(LEX_SOURCE)

$(BISON_OUT_C) $(BISON_OUT_H): $(BISON_SOURCE)
	$(BISON) -v --yacc --defines=$(BISON_OUT_H) --output=$(BISON_OUT_C) $<

clean:
	$(RM) $(TARGET) $(LEX_OUT) $(BISON_OUT_C) $(BISON_OUT_H) *.o *.out parse.output
