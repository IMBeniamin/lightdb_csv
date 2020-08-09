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
    if (strcmp(mode, "r") == 0 || strcmp(mode, "w") == 0 || strcmp(mode, "a") == 0) {
        FILE * _opened = fopen(file_name, mode);
        if (_opened)
            return _opened;
        else
            return NULL;
    }
    else
        return NULL;
}

unsigned int write_str_to_file(const char * r_d, FILE * w_d) {
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

size_t get_file_rows(FILE * r_d) {
    char buff[200];
    int res = 0;
    while (fgets(buff, 200, r_d))
       res++;
    return res;
}

void read_to_list(cellulare * destination, FILE * r_d) {
    size_t rows = get_file_rows(r_d);
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
    FILE * cell_file = open_cell_file("r");
    size_t rows = get_file_rows(cell_file);
    fclose(cell_file);

    cellulare * main_table = calloc(rows, sizeof(cellulare));

    cell_file = open_cell_file("r");
    read_to_list(main_table, cell_file);
    fclose(cell_file);

    return main_table;

}

cellulare ** load_data_plist() {
    // Generates a pointer list containing data read from the csv flie
    FILE * cell_file = open_cell_file("r");
    size_t rows = get_file_rows(cell_file);
    fclose(cell_file);
    cellulare ** main_table = calloc(rows + 1, sizeof(cellulare*));
    for (int i = 0; i < rows; i++) {
        main_table[i] = calloc(1, sizeof(cellulare)); // allocate each struct
    }
    main_table[rows] = NULL;
    cell_file = open_cell_file("r");
    read_to_llist(main_table, cell_file);
    return main_table;
}

cellulare ** pointer_list_flist(cellulare * list, size_t lsize) {
    // create pointer list from normal array
    // used to perform various tests and check efficiency of both methods
    cellulare ** pointer_list = calloc(lsize, sizeof(cellulare*));
    for (int i=0; i<lsize; i++) {
        pointer_list[i] = &list[i];
    }
    return pointer_list;
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

size_t main_table_len(cellulare ** main_table) {
    int i = 0;
    while(*main_table) {
        i++;
        main_table++;
    }
    return i;
}

int check_modified(cellulare ** main_table) {
    FILE * csv_table = open_cell_file("r");
    size_t file_table_size = get_file_rows(csv_table);
    size_t main_table_size = main_table_len(main_table);
    /*
     * if len is not enough do 1 on 1 comparison
     * cellulare * file_table = calloc(file_table_size, sizeof(cellulare));
     * read_to_list(file_table, csv_table);
     */
    if (main_table_size != file_table_size)
        return 1;
    return 0;
}

unsigned int write_cell_to_file(cellulare * r_d, FILE * w_d) {
    char w_d_f[700] = {0};
    sprintf(w_d_f, "%d,%s,%d,%s,%d,%f,%s\n", r_d->id, r_d->name, r_d->ram, r_d->cpu, r_d->display_ppi, r_d->display_size, r_d->display_resolution); // TODO add rest of parameters
    return write_str_to_file(w_d_f, w_d);
}

unsigned int write_table_to_file(cellulare ** main_table) {
    /*
     * Returns the bytes written to the file
     */
    size_t elem_written = 0;
    size_t tot_written = 0;
    if (check_modified(main_table)) {
        FILE * w_d = open_cell_file("w");
        while (*main_table) {
            elem_written = write_cell_to_file(*main_table, w_d);
            tot_written += elem_written;
            if (elem_written)
                main_table++;
            else {
                fprintf(stderr, "Error writing to the file!");
                w_d = open_cell_file("a");
            }
        }
        fclose(w_d);
    }
    return tot_written;
}

void safe_quit(cellulare ** main_table) {
    write_table_to_file(main_table);
    exit(0);
}