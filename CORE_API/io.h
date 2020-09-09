#pragma once

#include "globals.h"
#include <stdio.h>
/*
 * IO:
 * All the functions in this category are dedicated to the input/output from/to files
 * This header should be part of the CORE_API as it is essential for the rest of the application
 * The header also contains qol functions that abstract the i/o process
 */
/*
 * Counts the number of lines in a file
 * @r_d - A pointer to a file opened in read mode
 * @return - an unsigned int containing the number of lines in the file
 */
size_t get_file_rows(FILE * r_d);
/*
 * Wrapper for open_file that opens the csv file containing all the necessary data and returns it;
 * @mode - a string which is read and instructs the function on which mode the file should get openend
 *         can be [r, w, a]
 * @return - A file pointer to "cellulari.csv" or NULL if an IO error occoured
 */
FILE * open_cell_file(char * mode);
/*
 * Reads the data from <r_d> and stores it in <destination>
 * @r_d - this variable MUST point to a file that has the same dialect and structure as "cellulari.csv"
 */
void read_to_list(cellulare * destination, FILE * r_d);
/*
 * Reads the data from <r_d> and stores it in <destination>
 * @r_d - this variable MUST point to a file that has the same dialect and structure as "cellulari.csv"
 */
void read_to_plist(cellulare ** destination, FILE * r_d);
/*
 * Wrapper for read_to_list with memory allocation
 * @return - A cellulare * that must be free'd or NULL if the allocation fails
 */
cellulare * load_data_list();
/*
 * Wrapper for read_to_plist with memory allocation
 * This function differs from load_data_list because it allocates memory for an array of pointers then allocates
 * each struct in a separate region of memory thus allowing faster computation, data insertion and deletion
 * @return - A cellulare * that must be free'd or NULL if the allocation fails
 */
cellulare ** load_data_plist();
/*
 * Function that converts a list to pointed list
 */
cellulare ** pointer_list_flist(cellulare * list, size_t lsize);

void free_main_table();
void free_main_table_p();
void read_cellulare(FILE *r_d, cellulare * w_d);

uint32 write_str_to_file(const char * r_d, FILE * w_d);
uint32 write_cell_to_file(cellulare * r_d, FILE * w_d);

FILE * open_file(const char * file_name, const char * mode);

size_t main_table_len();

uint32 check_modified();

uint32 write_table_to_file();

void safe_quit();