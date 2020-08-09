#include <stdlib.h>
#include "../TOOLS_API/memedit.h"

void add_cellulare(cellulare ** main_table, cellulare * r_d) {
    /*
     * This function takes a cellulare * and adds it to the main_table
     * The r_d cellulare's id is automatically calculated based on preexisting data
     */
    //TODO validate r_d
    //int last_id = main_table_len(main_table);
    unsigned int new_table_len = main_table_len(main_table) + 1;
    unsigned int last_id = new_table_len - 1;
    r_d->id = last_id + 1;
    realloc(main_table, new_table_len*sizeof(cellulare*));
    main_table[new_table_len-1] = calloc(1, sizeof(cellulare));
    *(main_table[new_table_len-1]) = *r_d;
    main_table[new_table_len] = NULL;
}

void delete_cellulare(cellulare ** main_table, int del_i) {
    int m_t_len = main_table_len(main_table);
    free(main_table[del_i]);

    for (; del_i < m_t_len; del_i++){
        main_table[del_i] = main_table[del_i+1];
        if (main_table[del_i])
            main_table[del_i]->id--;
    }
    // TODO consider doing a realloc to reduce main_table's size after deletion
    //main_table = realloc(main_table, del_i* sizeof(cellulare*));
}