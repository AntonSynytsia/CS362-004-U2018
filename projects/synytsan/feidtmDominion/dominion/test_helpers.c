#include "test_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int custom_assert(int v_res, int v_exp, const char* msg) {
    int state;
    if (v_res == v_exp) {
        printf("SUCCESS: %s\n", msg);
        state = 1;
    }
    else {
        printf("FAILURE: %s\n", msg);
        state = 0;
    }
    // Assert will interrupt if NDEBUG is not defined.
    assert(v_res == v_exp);
    return state;
}
