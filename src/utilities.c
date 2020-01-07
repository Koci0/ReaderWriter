
#include "utilities.h"
#include "const.h"

void print_shared_memory(int *pam) {
    for (int i = 0; i < BUFFER; i++) {
        fprintf(stderr, "%5d | ", pam[i]);
    }
    fprintf(stderr, "\n");
}

void write_num_to_file(char filename[], int num) {
    FILE *file;
    file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error: fopen@write_num_to_file (file)");
        exit(2);
    }
    
    fprintf(file, "%d\n", num);
    fclose(file);
}

void read_num_from_file(char filename[]) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error: fopen@read_from_file (file)");
        exit(2);
    }
    
    int pid = 0;
    while (fscanf(file, "%d", &pid) > 0) {
        fprintf(stderr, "%d\n", pid);
    }

    if (pid == 0) {
        fprintf(stderr, "File empty!\n");
    }
    fclose(file);
}

void clean_file(char filename[]) {
    FILE *file;
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error: fopen@clean_file (file)");
        exit(2);
    }
    fclose(file);
}