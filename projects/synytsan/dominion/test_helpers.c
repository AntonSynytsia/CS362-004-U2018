#include "test_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int custom_assert(int v_res, int v_exp, const char* msg) {
    if (v_res == v_exp) {
        #ifdef NDEBUG // if debug is defined, we don't want to print out success cases.
            printf("SUCCESS: %s\n", msg);
        #endif
        return 1;
    }
    else {
        printf("FAILURE: %s\n", msg);
        // Assert will interrupt if NDEBUG is not defined.
        assert(v_res == v_exp);
        return 0;
    }
}
