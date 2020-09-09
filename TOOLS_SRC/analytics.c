#include "../TOOLS_API/analytics.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

extern cellulare ** main_table;

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
                           "            <th>IMAGE</th>\n"
                           "        </tr>\n";
    size_t res = write_str_to_file(prep_ante_app, analyt_html);

    if (res == strlen(prep_ante_app)) return 0;
    else return 1;
}

void prep_cont(FILE *analyt_html) {
    for (int i = 0; main_table[i]; main_table++) {
        char _tbw[500];
        sprintf(_tbw, "        <tr>\n"
                      "            <th>%d</th>\n"
                      "            <th>%s</th>\n"
                      "            <th>%d</th>\n"
                      "            <th>%s</th>\n"
                      "            <th>%d</th>\n"
                      "            <th>%f</th>\n"
                      "            <th>%s</th>\n"
                      "            <th><img style=\"width: 80px; height: 80px;\" src=\"res\\%s.jpg\"></th>\n"
                      "        </tr>\n",
                                main_table[i]->id,
                                main_table[i]->name,
                                main_table[i]->ram,
                                main_table[i]->cpu,
                                main_table[i]->display_ppi,
                                main_table[i]->display_size,
                                main_table[i]->display_resolution,
                                main_table[i]->name);
        write_str_to_file(_tbw, analyt_html);
    }
}

int prep_post(FILE * analyt_html) {
    char * prep_post_app = "    </table>\n"
                           "</body>\n";
    size_t res = write_str_to_file(prep_post_app, analyt_html);

    if (res == strlen(prep_post_app)) return 0;
    else return 1;
}

void concat_cellulare_string(cellulare * data, char * w_d) {
    char _generated_line[CELLULARE_STRING_LINE_SIZE] = {0};
    sprintf(_generated_line, "|%4d|%20s|%5d|%21s|%13d|%14f|%20s|\n",
            data->id,
            data->name,
            data->ram,
            data->cpu,
            data->display_ppi,
            data->display_size,
            data->display_resolution);
    // **********DEBUG**********
//    puts("**********DEBUG**********");
//    puts(_generated_line);
//    puts("**********DEBUG**********");
    // **********DEBUG**********
    strcat(w_d, _generated_line);
}

void generate_string(char *w_d) {
    strcpy(w_d, "| ID | NAME               | RAM | PROCESSOR           | DISPALY_PPI | DISPLAY_SIZE | DISPLAY_RESOLUTION |\n");
    for (int i = 0; main_table[i]; i++)
        concat_cellulare_string(main_table[i], w_d);
}

int export_to_HTML() {
    FILE * analyt_html = open_file("HTMl_output.html", "w");
    if (prep_ante(analyt_html)) return 1;
    prep_cont(analyt_html);
    if (prep_post(analyt_html)) return 1;
    fclose(analyt_html);
    return 0; // ret 0 if everything went well
}

int export_to_TXT() {
    FILE * analyt_txt = open_file("TXT_output.txt", "w");
    if (!analyt_txt) return 1;
    char * formatted_data = calloc(main_table_len() * CELLULARE_STRING_LINE_SIZE + 1, sizeof(char));
    if (!formatted_data) return 1;

    generate_string(formatted_data);
    write_str_to_file(formatted_data, analyt_txt);

    free(formatted_data);
    fclose(analyt_txt);
    return 0;
}

int valid_str(char * str) { // TODO going out of boundary for str
    int c = 0;
    for (;str; str++)
        if (*str)
            c++;
    return c;
}

int comp_cell(cellulare * b_cell, const void * c_ag) {
    /*
     * b_cell = base cellulare // parameter to compare against
     * c_ag = comparation against // parameter to be compared
     */
    int checks = 0;
    cellulare *c_cell = (cellulare *) c_ag;
    if(c_cell->id && b_cell->id == c_cell->id)
        checks++;
    if (c_cell->weight && b_cell->weight == c_cell->weight)
        checks++;
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
    if (valid_str(c_cell->cpu) && strcmp(c_cell->cpu, b_cell->cpu) == 0)
        checks++;
    if (valid_str(c_cell->name) && strcmp(c_cell->name, b_cell->name) == 0)
        checks++;
    if (valid_str(c_cell->notes) && strcmp(c_cell->notes, b_cell->notes) == 0)
        checks++;
    return checks;
}

void print_hidden(cellulare * cell) {
    printf("Manufacturer id: %d\n", cell->id_manufacturer);
    printf("Operating System's id: %d\n", cell->id_os);
    printf("Weight: %d\n", cell->weight);
    printf("Notes:\n%s\n", cell->notes);
}

void tolowerstring(const char * mixed_str, char * res_string, const size_t MAX) {
    const char * p = mixed_str;
    unsigned int i = 0;
    while (*p && i <= MAX) {
        if (isalpha(*p) && isupper(*p))
            *res_string = *p + ' ';
        else
            *res_string = *p;
        p++; res_string++; i++;
    }
}
