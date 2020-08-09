#include "core_api.h"
#include "tools_api.h"
#include <string.h>
int main(int argc, char *argv[]) {
    cellulare ** main_table = load_data_plist();  // Load file data in memory

    if(argc == 2) // if 2 arguments are passed (name + command)
        cmd_handler(main_table, argv[1]); // execute the command
    else
        //test_commands();
        //cmd_handler("help");
        ui_loader(main_table);

    // __ADD/DELETE CELL__ WORKING
    //cellulare *mycell = calloc(1, sizeof(cellulare));
    //strcpy(mycell->name, "test device");
    //strcpy(mycell->cpu, "super duper cpu");
    //strcpy(mycell->display_resolution, "1234x1234");
    //mycell->ram = 1234;
    //mycell->display_size = 1.1;
    //mycell->display_ppi = 123;

    //add_cellulare(main_table, mycell); WORKING
    //printf("%d", write_table_to_file(main_table));

    //delete_cellulare(main_table, 0); WORKING
    // EOF __ADD/DELETE CELL__

    // __SEARCH__
//    cellulare search_par;
//    search_par.ram = 6000;
//    int test = search_in_main_table((const cellulare **) main_table, &search_par);
    // EOF __SEARCH__

    //export_to_HTML(main_table); WORKING

    //export_to_TXT(main_table); WORKING

    //cell_quick_sort(main_table, sizeof(cellulare*), get_file_rows(open_file("cellulari.csv", "r")), "cpu"); WORKING
    free_main_table_p(main_table);  // Free loaded data WORKING
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/*
 * 0) Visualizzazione db in console
 * 1) Caricamento da file cellulari.csv in vettore di “struct cellulare”
 * TODO [only UI] 2) Ordinamenti (almeno 2 diversi)
 * TODO [only UI] 3) Visualizzazione (su file cellulari.html / cellulari.txt)
 * TODO 4) Ricerca (per almeno due campi) e visualizzazione del cellulare cercato
 * TODO [only UI] 5) Cancellazione (in memoria) di un cellulare
 * TODO [only UI] 6) Inserimento (da tastiera nel vettore in memoria) di un nuovo cellulare
 * TODO [only UI] 7) Salvataggio (su file cellulari.csv) del vettore in memoria (Se modificato).
 *
 * TODO 8) Facoltativo: immettere un campo “immagine” nella struct cellulare e fare in modo che dal file cellulari.html si “veda” l'immagine del cellulare
 * TODO 9) Aggiungi funzione undo/redo
 * TODO 10) Add debugging/timing functions
 */
