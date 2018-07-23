#include "test_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int custom_assert(int v_res, int v_exp, const char* msg) {
    if (v_res == v_exp) {
        printf("SUCCESS: %s\n", msg);
        return 1;
    }
    else {
        printf("FAILURE: %s\n", msg);
        return 0;
    }
}
