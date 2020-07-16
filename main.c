#include "core_api.h"
#include "tools_api.h"
int main() {
    cellulare ** main_table = load_data_llist();  // Load file data in memory

    //delete_cellulare(main_table, 0); WORKING

    // __SEARCH__
    //cellulare search_par;
    //search_par.ram = 6000;
    //int test = search_in_main_table((const cellulare **) main_table, &search_par); // TODO rewrite
    // EOF __SEARCH__

    //export_to_HTML(main_table); WORKING

    //export_to_TXT(main_table); WORKING

    //cell_quick_sort(main_table, sizeof(cellulare*), get_file_rows(open_file("cellulari.csv", "r")), "cpu"); WORKING
    free_main_table_p(main_table);  // Free loaded data WORKING
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/*
 * TODO 0) Visualizzazione db in console
 * 1) Caricamento da file cellulari.csv in vettore di “struct cellulare”
 * 2) Ordinamenti (almeno 2 diversi)
 * 3) Visualizzazione (su file cellulari.html / cellulari.txt)
 * TODO 4) Ricerca (per almeno due campi) e visualizzazione del cellulare cercato
 * 5) Cancellazione (in memoria) di un cellulare
 * TODO 6) Inserimento (da tastiera nel vettore in memoria) di un nuovo cellulare
 * TODO 7) Salvataggio (su file cellulari.csv) del vettore in memoria (Se modificato).
 * TODO 8) Facoltativo: immettere un campo “immagine” nella struct cellulare e fare in modo che dal file cellulari.html si “veda” l'immagine del cellulare
 */