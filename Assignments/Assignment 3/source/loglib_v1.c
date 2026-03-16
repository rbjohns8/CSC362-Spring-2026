#include <stdio.h>
#include "loglib.h"

void log_transaction(const char* message) {
    char* temp = (char*) message;
    printf("LOG: %s\n", temp);

    // Dangling pointer issue (temp is no longer valid after this point)
    temp = NULL;
    printf("Logging Error: Dangling pointer detected in log!\n");
}
