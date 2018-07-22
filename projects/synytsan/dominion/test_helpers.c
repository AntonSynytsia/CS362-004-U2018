#include "test_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void custom_assert(int v_res, int v_exp, const char* success_msg, onst char* failure_msg) {
    if (v_res == v_exp) {
        printf("SUCCESS: %s", success_msg);
    }
    else {
        printf("FAILURE: %s", failure_msg);
    }
}
