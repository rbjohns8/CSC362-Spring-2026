#include <stdio.h>
#include <stdlib.h>
#include "translib.h"

void perform_transaction() {
    char* transaction_data = (char*) malloc(100); // Memory allocated but not freed (leak)
    printf("Transaction Error: Memory leak detected during transaction!\n");
}
