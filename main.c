#include "CORE_API.h"

int main() {
    cellulare * main_table = load_data();  // Load file data in memory
//    cellulare ** pp_main_table = linked_list_flist(main_table, get_file_rows(open_cell_file("r")));

    free_main_table(main_table);  // Free loaded data
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

/*
 * 1) Caricamento da file cellulari.csv in vettore di “struct cellulare”
 * 2) Ordinamenti (almeno 2 diversi)
 * TODO 3) Visualizzazione (su file cellulari.html / cellulari.txt)
 * TODO 4) Ricerca (per almeno due campi) e visualizzazione del cellulare cercato
 * TODO 5) Cancellazione (in memoria) di un cellulare
 * TODO 6) Inserimento (da tastiera nel vettore in memoria) di un nuovo cellulare
 * TODO 7) Salvataggio (su file cellulari.csv) del vettore in memoria (Se modificato).
 * TODO 8) Facoltativo: immettere un campo “immagine” nella struct cellulare e fare in modo che dal file cellulari.html si “veda” l'immagine del cellulare
 */