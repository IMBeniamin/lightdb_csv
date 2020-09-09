#include "../TOOLS_API/search.h"
#include "../core_api.h"
#include "../TOOLS_API/analytics.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

extern cellulare ** main_table;

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

    size_t MAX_LEN_serialized_data = strlen(serialized_data) + 1;
    char * tmp_serialized_data = alloca(MAX_LEN_serialized_data);
    tolowerstring(serialized_data, tmp_serialized_data, MAX_LEN_serialized_data);

    size_t MAX_LEN_parameter = strlen(parameter) + 1;
    char * tmp_parameter = alloca(MAX_LEN_parameter);
    tolowerstring(parameter, tmp_parameter, MAX_LEN_parameter);


    while((tmp_serialized_data = strstr(tmp_serialized_data, parameter))) {
        count++;
        tmp_serialized_data++;
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

void iterate_main_table(const char *parameter, uint32 *search_table) {
    size_t main_table_l = main_table_len();
    for (size_t i = 0; i < main_table_l; i++) {
        search_table[i] += iterate_cellulare(main_table[i], parameter);
    }
}

void iterate_parameters(struct parameter *head_parameter, uint32 *search_table) {
    for( struct parameter * current = head_parameter; current; current = current->next )
        iterate_main_table(current->data, search_table);
}

int in_array(const int *array, uint32 array_len, uint32 value) {
    for (int i = 0; i < array_len; i++)
        if (value == array[i])
            return 1;
    return 0;
}

int find_max(const uint32 * array, const uint32 len) {
    int max = 0, second_max = 0;
    for (int i = 1; i < len; i++) {
        if(array[i] > array[second_max] && array[i] > array[max])
            max = i;
        else if (array[i] > array[second_max] && array[i] <= array[max])
            second_max = i;
    }
    if (second_max != max)
        return max;
    else
        return -1;
}

int * find_best(uint32 * search_table, uint32 search_table_len, int * search_results, uint32 search_results_n) {
//    DEBUG===
//    puts("--------------------------------------------------------");
//    for (int i = 0; i < search_table_len; i++) {
//        printf("%d, ", search_table[i]);
//    }
//    puts("\n--------------------------------------------------------");
//
//    puts("--------------------------------------------------------");
//    for (int i = 0; i < search_results_n; i++) {
//        printf("%d, ", search_results[i]);
//    }
//    puts("\n--------------------------------------------------------");
//    !DEBUG===

    uint32 max_index;
    for ( uint32 i = 0; i < search_results_n; i++) {
        max_index = find_max(search_table, search_table_len);
        if (in_array(search_results, search_results_n, max_index))
            break;
        search_results[i] = (int)max_index;
        search_table[max_index] = 0;
    }
    return search_results;
}

void out_search_result(const int *search_results) {
    puts("The following results have been found:");
    for (size_t i = 0; i < MAX_PRINTED_RESULTS; i++) {
        char buff[CELLULARE_STRING_LINE_SIZE] = {0};
        if (search_results[i] >= 0) {
            sprintf(buff, "%u) ", i+1);
            concat_cellulare_string(main_table[search_results[i]], buff);
            printf("%s", buff);
        }
    }
}
void free_node(struct parameter * node) {
    free(node->data);
    free(node);
}
void free_ll (struct parameter * head) {
    struct parameter * current = head;
    struct parameter * next = NULL;
    while (current->next) {
        next = current->next;
        free_node(current);
        current = next;
    }
}

void search_menu(char *raw_parameters) {
    size_t search_table_len = main_table_len();
    if (!strcmp(raw_parameters, "")) {
        puts("You have not given any parameters, the function will now exit!");
        return;
    }
    struct parameter * head_parameter = get_structured_parameters(raw_parameters);
    uint32 * search_table = calloc(search_table_len, sizeof(uint32));
    if (!search_table) {
        puts("Errore nell'allocazione di memoria! Non e' stata fatta nessuna modifica.");
        return;
    }
    int * search_results = calloc(MAX_PRINTED_RESULTS, sizeof(int));
    if (!search_results) {
        puts("Errore nell'allocazione di memoria! Non e' stata fatta nessuna modifica.");
        return;
    }
    for (uint32 i = 0; i < MAX_PRINTED_RESULTS; i++) // consider refactoring to function
        search_results[i] = -1;

    iterate_parameters(head_parameter, search_table);
//    puts("search table:");
//    for (int i = 0; i < search_table_len; i++) {
//        printf("id: %d -- %d\n",i+1, search_table[i]);
//    }

    find_best(search_table, search_table_len, search_results, MAX_PRINTED_RESULTS);
//    puts("search results:");
//    for (int i = 0; i < MAX_PRINTED_RESULTS; i++)
//        printf("%d) %d\n",i+1, search_results[i]);

    out_search_result(search_results);

    free(search_results);
    free(search_table);
    free_ll(head_parameter);

}