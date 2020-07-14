#pragma once

#include "../core_api.h"
#include <stdlib.h>

int cell_quick_sort(cellulare ** main_table, size_t element_size, size_t nitems, char * member);
void export_to_TXT(cellulare ** main_table);
