#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "vm.h"

void test_libfunc_cos(double input, avm_memcell_t inputType, double expected, avm_memcell_t expectedType) {
    stack[topsp + AVM_STACKENV_SIZE + 1].type = inputType;
    stack[topsp + AVM_STACKENV_SIZE + 1].data.numVal = input;

    libfunc_cos();

    if (retval.type != expectedType) {
        printf("Test failed: Incorrect type for return value. Expected %d, got %d.\n", expectedType, retval.type);
        return;
    }

    if (expectedType == number_m) {
        double result = retval.data.numVal;
        double epsilon = 0.000001; // Tolerance for floating point comparison

        if (fabs(result - expected) < epsilon) {
            printf("Test passed for input %f. Expected %f, got %f.\n", input, expected, result);
        } else {
            printf("Test failed for input %f. Expected %f, got %f.\n", input, expected, result);
        }
    } else {
        printf("Test passed: Return type correctly identified as %d.\n", expectedType);
    }
}

int main() {
    // Initialize stack pointer, assuming the current function frame is at the bottom
    topsp = 0;
    
    // Testing cosine function at various angles and types
    test_libfunc_cos(0, number_m, 1, number_m);       // cos(0 degrees)
    test_libfunc_cos(90, number_m, 0, number_m);      // cos(90 degrees)
    test_libfunc_cos(180, number_m, -1, number_m);    // cos(180 degrees)
    test_libfunc_cos(270, number_m, 0, number_m);     // cos(270 degrees)
    test_libfunc_cos(360, number_m, 1, number_m);     // cos(360 degrees)
    test_libfunc_cos(100, string_m, 0, undef_m);      // Incorrect type input

    return 0;
}
