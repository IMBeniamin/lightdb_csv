#include "../CORE_API/io.h"

#include <stdlib.h>
#include <string.h>

/*
 * INPUT SECTION
 * This part deals with all data reading and importing into memory.
 * The API allows various types of memory management and provides ways to "convert" stored data to other
 * storing patterns, allowing faster operations when necessary.
 *
 * I have decided to also include the low level functions even if it could potentially
 * allow bad code to be written because it gives more freedom in accessing the API and allows partial utilisation.
 */

FILE * open_file(const char * file_name, const char * mode) {
    if (strcmp(mode, "r") == 0 || strcmp(mode, "w") == 0) {
        FILE * _opened = fopen(file_name, mode);
        if (_opened)
            return _opened;
        else
            return NULL;
    }
    else
        return NULL;
}

int write_str_to_file(const char * r_d, FILE * w_d) {
    return fwrite(r_d, 1, strlen(r_d), w_d);
}

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
    token[strlen(token) - 1] = 0;
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

void read_to_list(cellulare * destination, size_t rows, FILE * r_d) {
    for (; rows; rows--, destination++) {
        read_cellulare(r_d, destination);
    }
}

void read_to_llist(cellulare ** destination, FILE * r_d) {
    for (; *destination; destination++) {
        read_cellulare(r_d, *destination);
    }
}

FILE * open_cell_file(char * mode) {
    return open_file("cellulari.csv", mode);
}

cellulare * load_data_list() {
    size_t rows = get_file_rows(open_cell_file("r"));
    cellulare * main_table = calloc(rows, sizeof(cellulare));
    read_to_list(main_table, rows, open_cell_file("r"));
    return main_table;

}

cellulare ** load_data_llist() {
    // Generates a linked list containing data read from the csv flie
    size_t rows = get_file_rows(open_cell_file("r"));
    cellulare ** main_table = calloc(rows + 1, sizeof(cellulare*));
    for (int i = 0; i < rows; i++) {
        main_table[i] = calloc(1, sizeof(cellulare)); // allocate each struct
    }
    main_table[rows] = NULL;
    read_to_llist(main_table, open_cell_file("r"));
    return main_table;
}

cellulare ** linked_list_flist(cellulare * list, size_t lsize) {
    // create linked list from normal array
    // used to perform various tests and check efficiency of both methods
    cellulare ** linked_list = calloc(lsize, sizeof(cellulare*));
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
    //size_t rows = get_file_rows(open_cell_file("r")); legacy data counting function
    for (;*main_table; main_table++) {
        free(*main_table);
    }
    free(main_table);
}

int main_table_len(const cellulare ** main_table) {
    int i = 0;
    while(*main_table) {
        i++;
        main_table++;
    }
    return i;
}

void delete_cellulare(cellulare ** main_table, int del_i) {
    int m_t_len = main_table_len(main_table);
    free(main_table[del_i]);

    for (; del_i < m_t_len; del_i++){
        main_table[del_i] = main_table[del_i+1];
        if (main_table[del_i])
            main_table[del_i]->id--;
    }
    // TODO consider doing a realloc to reduce main_table's size after deletion
    //main_table = realloc(main_table, del_i* sizeof(cellulare*));
}
