#pragma once

#include "../core_api.h"
#include <stdlib.h>

typedef int (*comparator_func)(const void *, const void *);
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
int size_compare(const void* a, const void* b);
int cpu_compare(const void* a, const void* b);
int name_compare(const void* a, const void* b);
int notes_compare(const void* a, const void* b);

struct field {
    char * name;
    comparator_func execute;
    char * description;
};

const struct field fields[] = {
        {"id", &id_compare, "ID of the product"},
        {"weight", &weight_compare, "Weight of the product"},
        {"ram", &ram_compare, "Ram of the product"},
        {"display_ppi", &d_ppi_compare, "Pixel per Inch capabilities of the display"},
        {"id_os", &id_os_compare, "Operatig system's ID"},
        {"id_manufacturer", &id_man_compare, "Manufacturer's ID"},
        {"display_size", &disp_size_compare, "Size of the display in inches"},
        {"display_resolution", &disp_res_compare, "Resolution of the display [AAAAxAAAA]"},
        {"size", &size_compare, "Size of the device"}, // TODO nani??
        {"cpu", &cpu_compare, "CPU's model"},
        {"name", &name_compare, "Name of the device"},
        {"notes", &notes_compare, "Aditional information about the device"},
        {"", 0, ""} // END OF TABLE INDICATOR, MUST BE LAST
};

int cell_quick_sort(cellulare ** main_table, size_t element_size, size_t nitems, char * member);

