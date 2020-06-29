#pragma once

#include <stdio.h>
#include "globals.h"

int get_file_rows(FILE * r_d);
void read_file_data(cellulare * destination, size_t rows, FILE * r_d);
FILE * open_cell_file(char * mode);
cellulare * load_data();
void free_main_table(cellulare * main_table);
void free_main_table_p(cellulare ** main_table);
cellulare ** linked_list_flist(cellulare * list, size_t lsize);
