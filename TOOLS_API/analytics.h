#pragma once
#include "../core_api.h"

int prep_ante(FILE * analyt_html);
void prep_cont(FILE *analyt_html);
int prep_post(FILE * analyt_html);

void concat_cellulare_string(cellulare * data, char * w_d);
void generate_string(char *w_d);

int export_to_HTML();
int export_to_TXT();

int comp_cell(cellulare * b_cell, const void * c_ag);
void print_hidden(cellulare * cell);
void tolowerstring(const char * mixed_str, char * res_string, size_t MAX);
