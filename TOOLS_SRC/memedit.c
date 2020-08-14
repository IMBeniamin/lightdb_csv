#include <stdlib.h>
#include "../TOOLS_API/memedit.h"

int add_cellulare(cellulare ** main_table, cellulare * r_d) {
    /*
     * This function takes a cellulare * and adds it to the main_table
     * The r_d cellulare's id is automatically calculated based on preexisting data
     */
    unsigned int new_table_len = main_table_len(main_table) + 1;
    unsigned int last_id = new_table_len - 1;
    r_d->id = last_id + 1u;
    cellulare ** main_table_safeguard = realloc(main_table, new_table_len*sizeof(cellulare*));
    cellulare * cellulare_safeguard = calloc(1, sizeof(cellulare));
    if (!main_table_safeguard)
        return 1;
    else
        main_table = main_table_safeguard;
    if (!cellulare_safeguard)
        return 1;
    else
        main_table[new_table_len-1] = cellulare_safeguard;
    *(main_table[new_table_len-1]) = *r_d;
    main_table[new_table_len] = NULL;
    return 0;
}

int delete_cellulare(cellulare ** main_table, unsigned int delete_index) {
    int m_t_len = main_table_len(main_table);
    cellulare ** main_table_safeguard = realloc(main_table, (m_t_len-1) * sizeof(cellulare*));
    if (!main_table_safeguard)
        return 1;

    main_table = main_table_safeguard;

    free(main_table[delete_index]);

    for (; delete_index < m_t_len; delete_index++){
        main_table[delete_index] = main_table[delete_index + 1];
        if (main_table[delete_index])
            main_table[delete_index]->id--;
    }
    return 0;
}