#include <stdio.h>
#include "loglib.h"

void log_transaction(const char* message) {
    printf("LOG: %s\n", message);

    // Fix: No dangling pointer, but mention remaining null byte issue
    printf("Logging secure. Remaining issue: Null byte.\n");
}
