
#include "utilities.h"
#include "const.h"

void print_shared_memory(int *pam) {
    for (int i = 0; i < MAX_BUFFER; i++) {
        fprintf(stderr, "%5d | ", pam[i]);
    }
    fprintf(stderr, "\n");
}
