#pragma once
#include "../core_api.h"

int prep_ante(FILE * analyt_html);
void prep_cont(cellulare ** main_table, FILE * analyt_html);
int prep_post(FILE * analyt_html);

int export_to_HTML(cellulare ** main_table);

int comp_cell(const cellulare * b_cell, const void * c_ag);
int search_in_main_table(const cellulare **main_table, const cellulare *search_p);