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
