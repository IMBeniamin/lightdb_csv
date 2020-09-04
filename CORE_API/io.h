#pragma once

#include "globals.h"
#include <stdio.h>

size_t get_file_rows(FILE * r_d);
FILE * open_cell_file(char * mode);

void read_to_list(cellulare * destination, FILE * r_d);
void read_to_llist(cellulare ** destination, FILE * r_d);

cellulare * load_data_list();
cellulare ** load_data_plist();
cellulare ** pointer_list_flist(cellulare * list, size_t lsize);

void free_main_table(cellulare * main_table);
void free_main_table_p(cellulare ** main_table);
void read_cellulare(FILE *r_d, cellulare * w_d);

uint32 write_str_to_file(const char * r_d, FILE * w_d);
uint32 write_cell_to_file(cellulare * r_d, FILE * w_d);

FILE * open_file(const char * file_name, const char * mode);

size_t main_table_len(cellulare ** main_table);

uint32 check_modified(cellulare ** main_table);

uint32 write_table_to_file(cellulare ** main_table);

void safe_quit(cellulare ** main_table);