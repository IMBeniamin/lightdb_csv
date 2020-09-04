#pragma once
#include "../core_api.h"

int prep_ante(FILE * analyt_html);
void prep_cont(cellulare ** main_table, FILE * analyt_html);
int prep_post(FILE * analyt_html);

void concat_cellulare_string(cellulare * data, char * w_d);
void generate_string (cellulare ** main_table, char * w_d);

int export_to_HTML(cellulare ** main_table);
int export_to_TXT(cellulare ** main_table);

int comp_cell(cellulare * b_cell, const void * c_ag);
void print_hidden(cellulare * cell);
void tolowerstring(const char * mixed_str, char * res_string, size_t MAX);
