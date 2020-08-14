#include "../TOOLS_API/search.h"
#include "../core_api.h"
#include "../TOOLS_API/analytics.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <shlwapi.h>

void push(struct parameter * head_node, char * new_data, uint32 data_size) {
    struct parameter * new_parameter = calloc(1, sizeof(struct parameter));
    new_parameter->data = calloc(data_size, sizeof(char));

    strcpy(new_parameter->data, new_data);
    new_parameter->next = NULL;

    if (head_node->next == NULL)
        head_node->next = new_parameter;
    else {
        struct parameter * current = head_node;
        while(current->next)
            current = current->next;
        current->next = new_parameter;
    }
}

struct parameter * get_structured_parameters(char * raw_parameters) {
    char * delim = " ";
    char * ptr = strtok(raw_parameters, "\n");
    ptr = strtok(ptr, delim);

    struct parameter * head = calloc(1, sizeof(struct parameter));
    head->data = calloc(strlen(ptr) + 1, sizeof(char));

    strcpy(head->data, ptr);
    head->next = NULL;

    while((ptr = strtok(NULL, delim)))
    {
        push(head, ptr, strlen(ptr)+1);
    }
    return head;
}

uint32 get_occourences(const char * serialized_data, const char * parameter) {
    int count = 0;
    const char *tmp = serialized_data;
    while((tmp = StrStrA(tmp, parameter))) { // using windows' version for non case sensitive comparison
        count++;
        tmp++;
    }
    return count;
}

char * serialize_cellulare(cellulare * data) {
    char * serialized_data = calloc(1, CELLULARE_STRING_LINE_SIZE);
    sprintf(serialized_data, "%d%u%d%u%d%f%s%s%s",
            data->weight,
            data->ram,
            data->display_ppi,
            data->id_os,
            data->id_manufacturer,
            data->display_size,
            data->display_resolution,
            data->cpu,
            data->name);
    return serialized_data;
}

uint32 iterate_cellulare(cellulare * data, const char * paramter) {
    char * serialized_data = serialize_cellulare(data);
    size_t occourences = get_occourences(serialized_data, paramter);
    free(serialized_data);
    return occourences;
}

void iterate_main_table(cellulare ** main_table, const char * parameter, uint32 * search_table) {
    size_t main_table_l = main_table_len(main_table);
    for (size_t i = 0; i < main_table_l; i++) {
        search_table[i] += iterate_cellulare(main_table[i], parameter);
    }
}

void iterate_parameters(cellulare ** main_table, struct parameter * head_parameter, uint32 * search_table) {
    for( struct parameter * current = head_parameter; current; current = current->next )
        iterate_main_table(main_table, current->data, search_table);
}

int in_array(const int * array, size_t array_len, size_t value) {
    for (int i = 0; i < array_len; i++)
        if (value == array[i])
            return 1;
    return 0;
}

int * find_best(const uint32 * search_table, uint32 search_table_len, uint32 search_results_n) {
    int * high_to_low = malloc(search_results_n * sizeof(uint32));

    for (size_t i = 0; i < search_results_n; i++) {
        high_to_low[i] = -1;
    }

    for (size_t pow_index = 0; pow_index < search_results_n; pow_index++) {
        high_to_low[pow_index] = (int)search_table[0];
        for (size_t i = 1; i < search_table_len; i++) {
            if (search_table[i] > high_to_low[pow_index] && !in_array(high_to_low, search_results_n, i))
                high_to_low[pow_index] = i;
        }
    }
    return high_to_low;
}

void out_search_result(cellulare ** main_table, const int * search_results) {
    puts("The following results have been found:");
    for (size_t i = 0; i < MAX_PRINTED_RESULTS; i++) {
        char buff[CELLULARE_STRING_LINE_SIZE] = {0};
        if (search_results[i] > 0) {
            sprintf(buff, "%d) ", i+1);
            concat_cellulare_string(main_table[search_results[i]], buff);
            printf("%s", buff);
        }
    }
}

void search_menu(cellulare ** main_table, char * raw_parameters) {
    // TODO consider allocating search_results beforehand and passing it into the function
    struct parameter * head_parameter = get_structured_parameters(raw_parameters);
    uint32 * search_table = calloc(main_table_len(main_table), sizeof(uint32));

    iterate_parameters(main_table, head_parameter, search_table);

    size_t search_table_len = main_table_len(main_table);
    int * search_results = find_best(search_table, search_table_len, MAX_PRINTED_RESULTS);

    out_search_result(main_table, search_results);
    free(search_results);
    free(search_table);

}