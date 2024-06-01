#ifndef symTable_h
#define symTable_h

#include <stdbool.h>
#define TABLE_SIZE 10

/*
 * Enum: scopespace_t
 * ------------------
 * Enumerates the types of variable scope spaces within a program.
 *
 * Values:
 *  - programvar: Global variables accessible throughout the program.
 *  - functionlocal: Local variables defined within a function.
 *  - formalarg: Function formal arguments.
 */
typedef enum scopespace_t{
    programvar,
    functionlocal,
    formalarg
}scopespace_t;

/*
 * Enum: symbol_t
 * --------------
 * Enumerates the types of symbols that can exist in a program.
 *
 * Values:
 *  - var_s: Represents a variable symbol.
 *  - programfunc_s: Represents a program-defined function.
 *  - library_func_s: Represents a function provided by a library.
 */
typedef enum symbol_t{
    var_s, 
    programfunc_s, 
    library_func_s
}symbol_t;

/*
 * Enumeration: SymbolType
 * ------------------------
 *   Enumerates the types of symbols that can exist in the symbol table.
 */
enum SymbolType {
    GLOBAL, LOCALVAR, FORMAL, CONST, USERFUNC, LIBFUNC
};

/*
 * Union: value
 * ------------
 *   Can hold either a Variable or a Function, for use in the symbol table.
 */
typedef struct passport{
    unsigned int scope;
    const char *name;
} passport_t;

/*
 * Structure: ArgList
 * ------------------
 *   Represents a list of arguments for functions, forming a linked list.
 *
 *   name: Name of the variable.
 *   scope: Scope level where the variable is defined.
 *   next: Pointer to the next argument in the list.
 */
typedef struct ArgList{
    passport_t p;
    struct ArgList *next;
} ArgList;

/*
 * Structure: SymbolTableEntry_t
 * -----------------------------
 *   Represents an entry in the symbol table with key, type, value, and pointers for linked list.
 *
 *  - key: Hash key for the entry.
 *  - isActive: Indicates if the symbol is currently active.
 *  - val: The value of the symbol, either a variable or a function.
 *  - type: The type of symbol.
 *  - next_entry: Pointer to the next entry in case of hash collision.
 *  - next_scope: Pointer to the next symbol within the same scope.
 *  - name: The name of the symbol.
 *  - space: The scope space of the symbol.
 *  - offset: The offset of the symbol within its scope.
 */
typedef struct SymbolTableEntry {
    ArgList *argList;
    symbol_t generaltype;
    scopespace_t space;
    passport_t passport;
    unsigned offset;
    unsigned key;
    unsigned line;
    unsigned address;
    bool isActive;
    enum SymbolType type;
    struct SymbolTableEntry *next_entry;
    struct SymbolTableEntry *next_scope;
} SymbolTableEntry_t;

/*
 * Structure: HashTable
 * --------------------
 *   Represents the symbol table itself, implemented as a hash table.
 *
 *   buckets: Array of bucket pointers for the hash table.
 *   heads: Dynamic array of pointers to the head of the list for each scope.
 *   len: Number of elements in the heads array.
 */
typedef struct HashTable {
    SymbolTableEntry_t *buckets[TABLE_SIZE];
    SymbolTableEntry_t **heads;
    unsigned int len;
} HashTable;

/*
 * Function: createHashTable
 * -------------------------
 *   Initializes and returns a new hash table for the symbol table.
 *
 *   returns: Pointer to the newly created hash table.
 */
HashTable* createHashTable();

/*
 * Function: freeHashTable
 * -----------------------
 *   Frees all memory associated with a hash table.
 *
 *   table: Pointer to the hash table to be freed.
 */
void freeHashTable(HashTable *table);

/*
 * Function: hash
 * --------------
 *   Calculates the hash value for a given key.
 *
 *   key: The key to hash.
 *
 *   returns: The calculated hash value.
 */
unsigned int hash(int key);

/*
 * Function: H_Insert
 * ------------------
 *   Inserts a new symbol table entry into the hash table.
 *
 *   table: Double pointer to the hash table.
 *   new_entry: Pointer to the new entry to be inserted.
 *
 *   returns: Pointer to the inserted symbol table entry.
 */
SymbolTableEntry_t * H_Insert(HashTable **table, SymbolTableEntry_t *new_entry);

/*
 * Function: printHashTable
 * ------------------------
 *   Prints the contents of the hash table.
 *
 *   table: Pointer to the hash table to print.
 */
void printHashTable(HashTable *table);

/*
 * Function: AL_Insert
 * -------------------
 *   Inserts a new argument into an argument list for a function.
 *
 *   h: Double pointer to the head of the argument list.
 *   v: The value to insert into the list.
 *
 *   returns: Pointer to the newly inserted argument in the list.
 */
ArgList * AL_Insert(ArgList **h, passport_t p);

/*
 * Function: hide_scope
 * --------------------
 *   Deactivates all symbols in a given scope within the hash table.
 *
 *   table: Pointer to the hash table.
 *   scope: The scope whose symbols should be deactivated.
 */
void hide_scope(HashTable *table, unsigned int scope);

/*
 * Function: SL_Insert
 * -------------------
 *   Inserts a new symbol table entry into the scope list.
 *
 *   h: Double pointer to the head of the list.
 *   new_entry: Pointer to the new entry to be inserted.
 *
 *   returns: Status code of the operation (e.g., EXIT_SUCCESS).
 */
SymbolTableEntry_t * SL_Insert(SymbolTableEntry_t **h, SymbolTableEntry_t *new_entry);

/*
 * Function: L_LookUp
 * ------------------
 *   Looks up a symbol in the hash table by its identifier.
 *
 *   h: Pointer to the head of the list where the lookup should start.
 *   id: The identifier of the symbol to look up.
 *
 *   returns: Pointer to the found symbol table entry, or NULL if not found.
 */
SymbolTableEntry_t * L_LookUp(SymbolTableEntry_t *h, int id);

/*
 * Function: createFuncVal
 * -----------------------
 *   Creates a value union with the function type, initialized with given attributes.
 *
 *   name: Name of the function.
 *   scope: Scope level of the function.
 *   line: Line number where the function is declared.
 *
 *   returns: The created function value.
 */
passport_t createPassport(const char *name, unsigned int scope);

/*
 * Function: L_entry_print
 * -----------------------
 *   Prints entries of the hash table.
 *
 *   h: Pointer to the hash table to be printed.
 */
void L_entry_print(HashTable *h);

/*
 * Function: L_heads_print
 * -----------------------
 *   Prints the heads of each scope in the hash table.
 *
 *   h: Pointer to the hash table.
 */
void L_heads_print(HashTable *h);

/*
 * Function: Scope_LookUp
 * ----------------------
 *   Looks up the last entry in a given scope that matches a given value and symbol type.
 *
 *   table: Pointer to the hash table.
 *   v: Pointer to the value to match.
 *   type: The type of symbol to match.
 *
 *   returns: Pointer to the found symbol table entry, or NULL if not found.
 */
SymbolTableEntry_t * Scope_LookUp(HashTable *table, passport_t *p, enum SymbolType type);

/*
 * Function: PrintHashTable
 * ------------------------
 *   Prints the entire hash table, scope by scope.
 *
 *   table: Pointer to the hash table to be printed.
 */
void PrintHashTable(HashTable *table);

/*
 * Function: PrintScope
 * --------------------
 *   Prints all entries within a specific scope of the hash table.
 *
 *   table: Pointer to the hash table.
 *   scope: The scope to print.
 */
void PrintScope(const HashTable *table, unsigned int scope);

/*
 * Function: H_Initlib
 * -------------------
 *   Initializes the hash table with predefined library functions.
 *
 *   table: Pointer to the hash table.
 */
void H_Initlib(HashTable *table);

/*
 * Function: validity_check
 * ------------------------
 *   Checks if a symbol table entry is valid and does not conflict with existing entries.
 *
 *   table: Pointer to the hash table.
 *   entry: Pointer to the symbol table entry to check.
 *   b: Boolean flag to indicate whether to print error messages.
 *
 *   returns: true if the entry is valid, false otherwise.
 */
bool validity_check(HashTable *table, SymbolTableEntry_t *entry, bool b);

/*
 * Function: H_Lookup
 * ------------------
 *   Looks up a symbol by name and (if scope > 0) scope in the hash table.
 *
 *   table: Pointer to the hash table.
 *   scope: Scope level to search within.
 *   name: Name of the symbol to look up.
 *
 *   returns: Pointer to the found symbol table entry, or NULL if not found.
 */
SymbolTableEntry_t *H_Lookup(HashTable *table, int scope, const char *name);

/*
 * Function: create_entry
 * ----------------------
 *   Creates a new symbol table entry.
 *
 *   key: Key for the new entry.
 *   s: Symbol type of the new entry.
 *   v: Value of the new entry.
 *
 *   returns: Pointer to the newly created symbol table entry.
 */
SymbolTableEntry_t *create_entry(unsigned int key, enum SymbolType s, passport_t p, unsigned int line);

/*
 * Function: print_red
 * -------------------
 *   Prints an error message in red text to stderr.
 *
 *   s: The error message to print.
 *   line: Line number where the error occurred.
 */
void print_red(char *s, int line);

/*
 * Function: createFuncName
 * ------------------------
 *   Generates a unique name for a function.
 *
 *   scope: Scope level of the function.
 *   line: Line number of the function declaration.
 *   index: An index to ensure uniqueness.
 *
 *   returns: The created function name as a value.
 */
passport_t createFuncName(unsigned int scope, unsigned int index);

/*
 * Function: map_enum
 * ------------------
 *   Maps the SymbolType enumeration to its string representation.
 *
 *   type: The SymbolType enumeration value.
 *
 *   returns: The string representation of the SymbolType.
 */
const char* map_enum(enum SymbolType type);

/*
 * Function: checkLib
 * ------------------
 *   Checks if a symbol name conflicts with a predefined library function name.
 *
 *   table: Pointer to the hash table.
 *   new: Pointer to the new symbol table entry being checked.
 *
 *   returns: true if there is no conflict, false if there is a conflict.
 */
bool checkLib(HashTable *table, SymbolTableEntry_t *new);

int H_Search(HashTable *table, unsigned int scope, char *name);

#endif /* symTable_h */
