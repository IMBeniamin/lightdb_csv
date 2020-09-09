#include "core_api.h"
uint32 MODIFIED_FILE_DATA_FLAG = 0;
cellulare ** main_table;

int main(int argc, char *argv[]) {
    setbuf(stdout, 0); // sets stdout's buffer to NULL allowing it to work during debug
//    char * test = get_user_str("Input stuff --> ", "Wrong stuff\n", 10);
//    printf("\n\n%s\n\n", test);
//    free(test);
    main_table = load_data_plist();  // Load file data in memory;
    if (!main_table) {
        puts("An error occoured in load the file in memory!");
        return 1;
    }
    if(argc == 2) // if 2 arguments are passed (name + command)
        cmd_handler(argv[1]); // execute the command
    else
    {
        //test_commands();
        cmd_handler("help");
        ui_loader();
    }
    free_main_table_p();  // Free loaded data*/
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/*
 * 0) Visualizzazione db in console
 * 1) Caricamento da file cellulari.csv in vettore di “struct cellulare”
 * 2) Ordinamenti (almeno 2 diversi)
 * 3) Visualizzazione (su file cellulari.html / cellulari.txt)
 * 4) Ricerca (per almeno due campi) e visualizzazione del cellulare cercato
 * 5) Cancellazione (in memoria) di un cellulare
 * 6) Inserimento (da tastiera nel vettore in memoria) di un nuovo cellulare
 * 7) Salvataggio (su file cellulari.csv) del vettore in memoria (Se modificato).
 * 8) Crea comando view
 * 9) Immettere un campo “immagine” nella struct cellulare e fare in modo che dal file cellulari.html si “veda” l'immagine del cellulare
 * FACOLTATIVO 10) Add undo/redo
 * FACOLTATIVO 11) Add debugging/timing functions
 */
