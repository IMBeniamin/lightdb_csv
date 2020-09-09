#include <stdlib.h>
#include "../TOOLS_API/memedit.h"

int add_cellulare(cellulare ** main_table, cellulare * r_d) {
    /*
     * This function takes a cellulare * and adds it to the main_table
     * The r_d cellulare's id is automatically calculated based on preexisting data
     */
    // 10 + NULL -- 11 + NULL
    if (!r_d)
        return 2;
    unsigned int new_table_len = main_table_len(main_table) + 2; // NULL termination + new element
    unsigned int new_id = new_table_len - 1;

//    puts("**********DEBUG**********");
//    printf("new table len -- %d\nnew_id -- %d\n", new_table_len, new_id);
//    puts("**********DEBUG**********");

    r_d->id = new_id;
    cellulare ** main_table_safeguard = realloc(main_table, new_table_len*sizeof(cellulare*));

//    puts("**********DEBUG**********");
//    cmd_display_table(main_table_safeguard);
//    puts("**********DEBUG**********");

    if (!main_table_safeguard) {
        puts("Allocation error!");
        return 1;
    }
    else {
        main_table = main_table_safeguard;
        main_table[new_table_len-1] = NULL;
    }

    cellulare * cellulare_safeguard = calloc(1, sizeof(cellulare));
    if (!cellulare_safeguard) {
        puts("Allocation error!");
        return 1;
    }
    else {
        main_table[new_id-1] = cellulare_safeguard;
        *(main_table[new_id-1]) = *r_d;
    }

//    puts("**********DEBUG**********");
//    cmd_display_table(main_table);
//    puts("**********DEBUG**********");

    MODIFIED_FILE_DATA_FLAG = 1;
    return 0;
}

int delete_cellulare(cellulare ** main_table, int delete_index) {
    size_t m_t_len = main_table_len(main_table) + 1; // +1 because of the NULL termination
    if (m_t_len < 2)
        return 1;
    if (delete_index < 0 || delete_index > m_t_len-2) // the last index should be the last id -1 + -1 // NULL termination)
        return 2;

    unsigned int new_m_t_len = m_t_len - 1;
    cellulare ** main_table_safeguard = realloc(main_table, new_m_t_len * sizeof(cellulare*));
    if (!main_table_safeguard)
        return 3;

    main_table = main_table_safeguard;

    free(main_table[delete_index]);

    for (; delete_index < new_m_t_len-1; delete_index++){
        main_table[delete_index] = main_table[delete_index + 1];
        if (main_table[delete_index])
            main_table[delete_index]->id--;
    }
    main_table[new_m_t_len-1] = NULL;
    MODIFIED_FILE_DATA_FLAG = 1;
    return 0;
}