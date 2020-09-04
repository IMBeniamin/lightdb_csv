#pragma once
#include "../CORE_API/globals.h"

#define MAX_PRINTED_RESULTS 5
#define MAX_PARAM_DATA_SIZE 200

// consider creating linked list template to be used multiple times

struct parameter {
    char * data;
    struct parameter * next;
};

int in_array(const int *array, uint32 array_len, uint32 value);
char * serialize_cellulare(cellulare * data);
uint32 get_occourences(const char * serialized_data, const char * parameter);
struct parameter * get_structured_parameters(char * raw_parameters);
void push(struct parameter * head_node, char * new_data, uint32 data_size);

void iterate_parameters(cellulare ** main_table, struct parameter * head_parameter, uint32 * search_table);
void iterate_main_table(cellulare ** main_table, const char * parameter, uint32 * search_table);
uint32 iterate_cellulare(cellulare * data, const char * paramter);

int find_max(const uint32 * array, uint32 len);
int * find_best(uint32 * search_table, uint32 search_table_len, int * search_results, uint32 search_results_n);
void out_search_result(cellulare ** main_table, const int * search_results);
void search_menu(cellulare ** main_table, char * raw_parameters);