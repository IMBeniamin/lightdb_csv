#include "../TOOLS_API/analytics.h"
#include <string.h>

/*
 * This section adresses data output in various formats.
 * This section is not part of the gui which manipulates data in real time and displays it, but it allows conversions
 * between formats in which data is stored, thus giving the user analytic capabilites.
 */


/*
 * HTML SECTION
 * This section controls how data in memory gets processed and transcribed in an html document
 */

int prep_ante(FILE * analyt_html) {
    char * prep_ante_app = "<style>\n"
                           "table, th, td {\n"
                           "border: 1px solid black;\n"
                           "}\n"
                           "</style>\n"
                           "<body style=\"text-align:center;\">\n"
                           "    <table style=\"height: 100%; width:70%\">\n"
                           "        <tr>\n"
                           "            <th>ID</th>\n"
                           "            <th>NAME</th>\n"
                           "            <th>RAM</th>\n"
                           "            <th>PROCESSOR</th>\n"
                           "            <th>DISPALY_PPI</th>\n"
                           "            <th>DISPLAY_SIZE</th>\n"
                           "            <th>DISPLAY_RESOLUTION</th>\n"
                           "        </tr>\n";
    int res = write_str_to_file(prep_ante_app, analyt_html);

    if (res == strlen(prep_ante_app)) return 0;
    else return 1;
}

void prep_cont(cellulare ** main_table, FILE * analyt_html) {
    for (; *main_table; main_table++) {
        char _tbw[500];
        sprintf(_tbw, "        <tr>\n"
                      "            <th>%d</th>\n"
                      "            <th>%s</th>\n"
                      "            <th>%d</th>\n"
                      "            <th>%s</th>\n"
                      "            <th>%d</th>\n"
                      "            <th>%f</th>\n"
                      "            <th>%s</th>\n"
                      "        </tr>\n",(*main_table)->id,
                (*main_table)->name,
                (*main_table)->ram,
                (*main_table)->cpu,
                (*main_table)->display_ppi,
                (*main_table)->display_size,
                (*main_table)->display_resolution);
        write_str_to_file(_tbw, analyt_html);
    }
}

int prep_post(FILE * analyt_html) {
    char * prep_post_app = "    </table>\n"
                           "</body>\n";
    int res = write_str_to_file(prep_post_app, analyt_html);

    if (res == strlen(prep_post_app)) return 0;
    else return 1;
}

int export_to_HTML(cellulare ** main_table) {
    FILE * analyt_html = open_file("HTMl_output.html", "w");
    if (prep_ante(analyt_html)) return 1;
    prep_cont(main_table, analyt_html);
    if (prep_post(analyt_html)) return 1;
    return 0; // ret 0 if everything went well
}

void export_to_TXT(cellulare ** main_table) {
    FILE * analyt_txt = open_file("TXT_output.txt", "w");
    write_str_to_file("| ID | NAME               | RAM | PROCESSOR           | DISPALY_PPI | DISPLAY_SIZE | DISPLAY_RESOLUTION |\n", analyt_txt);
    char _t_gen[200];
    for (; *main_table; main_table++) {
        sprintf(_t_gen, "|%4d|%20s|%5d|%21s|%13d|%14f|%20s|\n",
                                                (*main_table)->id,
                                                (*main_table)->name,
                                                (*main_table)->ram,
                                                (*main_table)->cpu,
                                                (*main_table)->display_ppi,
                                                (*main_table)->display_size,
                                                (*main_table)->display_resolution);
        write_str_to_file(_t_gen, analyt_txt);
    }
}

int valid_str(char * str) { // TODO going out of boundary for str
    int c = 0;
    for (;str; str++)
        if (*str)
            c++;
    return c;
}

int comp_cell(const cellulare * b_cell, const void * c_ag) {
    /*
     * b_cell = base cellulare // parameter to compare against
     * c_ag = comparation against // parameter to be compared
     */
    int checks = 0;
    cellulare *c_cell = (cellulare *) c_ag;
    if(c_cell->id && b_cell->id == c_cell->id)
        checks++;
    if (c_cell->weight && b_cell->weight == c_cell->weight)
        checks++;;
    if (c_cell->ram && b_cell->ram == c_cell->ram)
        checks++;
    if (c_cell->display_ppi && b_cell->display_ppi == c_cell->display_ppi)
        checks++;
    if (c_cell->id_os && b_cell->id_os == c_cell->id_os)
        checks++;
    if (c_cell->id_manufacturer && b_cell->id_manufacturer == c_cell->id_manufacturer)
        checks++;
    if (c_cell->display_size && b_cell->display_size == c_cell->display_size)
        checks++;
    if (valid_str(c_cell->display_resolution) && strcmp(c_cell->display_resolution, b_cell->display_resolution) == 0)
        checks++;
    if (valid_str(c_cell->size) && strcmp(c_cell->size, b_cell->size) == 0)
        checks++;
    if (valid_str(c_cell->cpu) && strcmp(c_cell->cpu, b_cell->cpu) == 0)
        checks++;
    if (valid_str(c_cell->name) && strcmp(c_cell->name, b_cell->name) == 0)
        checks++;
    if (valid_str(c_cell->notes) && strcmp(c_cell->notes, b_cell->notes) == 0)
        checks++;
    return checks;
}

// TODO redo search with auto completition
int search_in_main_table(const cellulare **main_table, const cellulare *search_p) {
    int len = main_table_len(main_table);
    for (int i = 0; i < len; i++) {
        if (comp_cell(main_table[i], search_p)) {
            return i;
        }
    }
    return -1;
}