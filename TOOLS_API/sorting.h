#pragma once

#include "../core_api.h"
#include <stdlib.h>

/*
 * Because reflection is not supported in C it is impossible to iterate or find members' names at run-time, thus making
 * it impossible to define pointers/types to a member of a struct.
 * To overcome this problem I have decided to make a comparator function for each member of the structure;
 */
int id_compare(const void* a, const void* b);
int weight_compare(const void* a, const void* b);
int ram_compare(const void* a, const void* b);
int d_ppi_compare(const void* a, const void* b);
int id_os_compare(const void* a, const void* b);
int id_man_compare(const void* a, const void* b);
int disp_size_compare(const void* a, const void* b);
int disp_res_compare(const void* a, const void* b);
int cpu_compare(const void* a, const void* b);
int name_compare(const void* a, const void* b);
int notes_compare(const void* a, const void* b);

typedef int (*comparator_func)(const void *, const void *);
struct field {
    char * name;
    comparator_func execute;
    char * description;
};

int strcicmp(char const *a, char const *b);

extern const struct field fields[];

int cell_quick_sort(cellulare ** main_table, size_t element_size, size_t nitems, char * member);

