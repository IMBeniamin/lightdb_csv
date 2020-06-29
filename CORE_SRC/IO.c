#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../CORE_API/IO.h"

void read_cellulare(FILE *r_d, cellulare * w_d) {
    char buff[200];
    fgets(buff, 200, r_d);
    char * token = strtok(buff, ",");
    w_d->id = token ? atoi(token) : 0;
    token = strtok(NULL, ",");
    strcpy(w_d->name, token);
    token = strtok(NULL, ",");
    w_d->ram = token ? atoi(token) : 0;
    token = strtok(NULL, ",");
    strcpy(w_d->cpu, token);
    token = strtok(NULL, ",");
    w_d->display_ppi = token ? atoi(token) : 0;
    token = strtok(NULL, ",");
    w_d->display_size = token ? atoi(token) : 0;
    token = strtok(NULL, ",");
    strcpy(w_d->display_resolution, token);
}

int get_file_rows(FILE * r_d) {
    char buff[200];
    int res = 0;
    while (fgets(buff, 200, r_d)) {
       res++;
    }
    return res;
}

void read_file_data(cellulare * destination, size_t rows, FILE * r_d) {
    for (int i=0; i<rows; i++) {
        read_cellulare(r_d, &destination[i]);
    }
}

FILE * open_cell_file(char * mode) {
    if (strcmp(mode, "r") == 0 || strcmp(mode, "w") == 0)
        return fopen("cellulari.csv", mode);
    else
        return NULL;
}

cellulare * load_data() {
    size_t rows = get_file_rows(open_cell_file("r"));
    cellulare * main_table = calloc(sizeof(cellulare), rows);
    read_file_data(main_table, rows, open_cell_file("r"));
    return main_table;
}

//TODO implement linked list data loading

cellulare ** linked_list_flist(cellulare * list, size_t lsize) {
    // create linked list from normal array
    // used to perform various tests and check efficiency of both methods
    cellulare ** linked_list = calloc(sizeof(cellulare*), lsize);
    for (int i=0; i<lsize; i++) {
        linked_list[i] = &list[i];
    }
    return linked_list;
}

void free_main_table(cellulare * main_table) {
    free(main_table);
}

void free_main_table_p(cellulare **main_table) {
    // !! ONLY call this IF EACH struct was malloc'ed INDIVIDUALLY
    size_t rows = get_file_rows(open_cell_file("r"));
    for (;rows; rows--, main_table++) {
        free(main_table);
    }
}
