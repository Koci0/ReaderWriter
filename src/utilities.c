
#include "utilities.h"
#include "const.h"

void print_shared_memory(int *pam) {
    fprintf(stderr, "Memory: ");
    for (int i = 0; i < MAX_BUFFER; i++) {
        fprintf(stderr, "%d | ", pam[i]);
    }
    fprintf(stderr, "\n");
}
