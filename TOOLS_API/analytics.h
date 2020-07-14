#pragma once
#include "../core_api.h"

int prep_ante(FILE * analyt_html);
void prep_cont(cellulare ** main_table, FILE * analyt_html);
int prep_post(FILE * analyt_html);

int export_to_HTML(cellulare ** main_table);
