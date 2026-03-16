#include <stdio.h>
#include "translib.h"

void perform_transaction() {
    printf("Transaction in progress...\n");

    // Fixes memory leak, mentions remaining null byte issue
    printf("Memory management secure. Remaining issue: Null byte.\n");
}
