#include "avm.h"
#include "execute/execute.h"

char** string_array;
double* number_array;
userfunc* userfunc_array;
char** libfunc_array;

int main(int argc, char** argv){
	if(argc != 2){
		printf("No input file. Exiting ..\n");
		return 1;
	}

	return 0;
}
