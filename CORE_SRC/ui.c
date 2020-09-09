#include "../CORE_API/ui.h"
#include "../tools_api.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

typedef void(*functionPointerType)(cellulare **);

struct commandStruct {
    char const *name;
    functionPointerType execute;
    char const *help;
};

const struct commandStruct commands[] = {
        {"display", &cmd_display_table, "Prints the main_table onto the screen. Aliases: [list]"},
        {"list", &cmd_display_table, "ignore"},

        {"sort", &cmd_sort, "Enters the sorting menu."},

        {"html", &cmd_html, "Creates the file HTMl_output.html which contains the main table formatted in HTML"},

        {"txt", &cmd_txt, "Creates the file TXT_output.txt which contains the main table formatted in txt"},

        {"search", &cmd_search, "Search a cellulare in the table based on a series of parameters"},

        {"add", &cmd_add, "Asks the user all the data needed to generate a new cellualre and adds it to the main table"},

        {"delete", &cmd_del, "Asks the user the id of the element he wishes to delete and safely removes it from the main table. Aliases: [del]"},
        {"del", &cmd_del, "ignore"},

        {"view", &cmd_view, "Asks the user the id of an element and then prints all of its details."},

        {"quit", &cmd_safe_quit, "Safely exit the application. [saves changes]. Aliases: [exit, q]"},
        {"exit", &cmd_safe_quit, "ignore"},
        {"q", &cmd_safe_quit, "ignore"},

        {"!quit", &cmd_unsafe_quit, "Exits the application WITHOUT saving changes. Aliases: [!exit, !q]"},
        {"!exit", &cmd_unsafe_quit, "ignore"},
        {"!q", &cmd_unsafe_quit, "ignore"},

        {"help", &cmd_help, "Shows this menu. Aliases: [?, h]"},
        {"?", &cmd_help, "ignore"},
        {"h", &cmd_help, "ignore"},

        {"",0,""} //End of table indicator. MUST BE LAST!!!
};

/*
 * Manages and updates screen and handles user i/o
 */

_Noreturn void ui_loader(cellulare ** main_table) {
    // Boot up the CLI
    setbuf(stdout, 0); // sets stdout's buffer to NULL allowing it to work during debug
    while (1)
        get_user_command(main_table, ">");
}

/*
 * Core API & Tools API calls wrappers/executables
 * Used by the cmd handler in order to avoid user error
 * All wrappers should take as a parameter ONLY the main_table pointed list in the form of: cellulare ** main_table
 * All functions in this category should start with "cmd_"
 */

void cmd_display_table(cellulare ** main_table) {
    uint32 str_data_len = (main_table_len(main_table) * CELLULARE_STRING_LINE_SIZE + 1) * sizeof(char);
    char * str_data = malloc(str_data_len);
    str_data[0] = '\0';

    generate_string(main_table, str_data);
    printf("%s", str_data);
    free(str_data);
}

void cmd_list_fields() {
    puts("\n");
    for (size_t i = 0; fields[i].execute; i++)
        printf("%-21s --> %s\n", fields[i].name, fields[i].description);
}

void cmd_html(cellulare ** main_table) {
    if(export_to_HTML(main_table))
        puts("The html file could not be generated!");
    system("HTMl_output.html");
}

void cmd_txt(cellulare ** main_table) {
    if (export_to_TXT(main_table))
        puts("The txt file could not be generated!");
    system("TXT_output.txt");
}

void cmd_sort(cellulare ** main_table) {
    if (get_user_y_n("Would you like to view all fields available? [y/n] --> ", "That value isn't accepted!"))
        cmd_list_fields(); // todo test
    size_t m_t_len = main_table_len(main_table);
    fflush(stdin);
    char * field = get_user_str("\nSort by [field] --> ", "That value is not accepted!", 20);
    if (!cell_quick_sort(main_table, sizeof(cellulare *), m_t_len, field)) {
        printf("The field you provided does not exist! No changes were made.\n");
        return;
    }
    else
        printf("The table has been sorted by %s\n", field);
    free(field);
}

void cmd_search(cellulare ** main_table) {
    char * raw_parameters = get_user_str("Write search parameters separated by space [partial parameters are accepted] [parameters can be of any type] [search is NOT case sensitive]:\n",
                 "The data you inserted is not valid!", MAX_PARAM_DATA_SIZE);
    search_menu(main_table, raw_parameters);
    free(raw_parameters);
}

void cmd_view(cellulare ** main_table) {
    uint32 id;
    uint32 m_t_len = main_table_len(main_table);
    id = get_user_int("Id of the cellulare --> ", "Invalid id!\n", (int)m_t_len+1, 0);
    if (!id) {
        puts("Exiting..");
        return;
    }
    char data[CELLULARE_STRING_LINE_SIZE]; data[0] = '\0';
    concat_cellulare_string(main_table[id-1], data);
    printf("%s", data);
    if (get_user_y_n("Do you want to see more details [y/n] --> ", "That value isn't valid!\n"))
        print_hidden(main_table[id-1]);
}

void cmd_add(cellulare ** main_table) {
    //**********DEBUG**********
    char _debug_str[CELLULARE_STRING_LINE_SIZE] = {0};
    //**********DEBUG**********

    cellulare * r_d = get_user_cellulare(main_table);

    //**********DEBUG**********
    concat_cellulare_string(r_d, _debug_str);
    puts("**********DEBUG**********");
    puts(_debug_str);
    puts("**********DEBUG**********");
    //**********DEBUG**********

    if(add_cellulare(main_table, r_d))
        puts("Phone hasn't been added, nothing has changed.");
    else
        puts("Successfuly added cellulare.");
    free(r_d);
}

void cmd_del(cellulare ** main_table) {
    int last_id = main_table_len(main_table);
    char * help_line = "Id non valido!";
    // -1 because of the id to index conversion
    int delete_index = get_user_int("Id of the element to be deleted --> ", help_line, (int)last_id+1, 0)-1;

    if(delete_cellulare(main_table, delete_index))
        puts("The phone hasn't been deleted, nothing has changed!");
    else
        puts("Successfuly deleted cellulare.");
}

void cmd_help() {
    printf("-----------------\n| Help Section! |\n-----------------\nThe following commands are available:\n----------------------------------\n");
    puts("While the application is asking for input, to cancel an operation write [!] and press [enter]");
    for (size_t i = 0; commands[i].execute; i++)
        if (strcmp(commands[i].help, "ignore") != 0)
            printf("%s -- %s\n", commands[i].name, commands[i].help);
}

void cmd_unsafe_quit() {
    exit(0);
}

void cmd_safe_quit(cellulare ** main_table) {
    safe_quit(main_table);
}

/*
 * Getters and handlers + tests
 */

char *get_user_str(const char *message, const char *help_line, int n_char) {
    /*
     * @n_char - this parameter is "optional" If the user passes 0 it's considered to be 21 by default
     * Returns NULL if the user exits the function
     * Remember to FREE the result
     */
    int chars_to_read = 21;
    char terminated = 0;
    if (n_char > 1)
         chars_to_read = n_char+2;
    char * _str = calloc(chars_to_read, sizeof(char));

    while (1) {
        fputs(message, stdout);
        fgets(_str, chars_to_read, stdin);
        fflush(stdin);
        if (!strcmp(_str, "\n")) {
            strcpy(_str, "");
            return _str;
        }
        if (strstr(_str, "\n")) {
            strncpy(_str, strtok(_str, "\n"), chars_to_read - 1);
            terminated = 1;
        }

        // validation check
        if (!_str[0])
            puts(help_line);
        else {
            if (!terminated)
                printf("More characters than necessary have been provided, everything after ...%c%c%c%c[...] has been ignored\n",
                        _str[chars_to_read-5],_str[chars_to_read-4],_str[chars_to_read-3],_str[chars_to_read-2]);
            return _str;
        }
    }
}

int get_user_y_n(const char *message, const char *help_line) {
    char * u_choice = NULL;
    while (1) {
        u_choice = get_user_str(message, help_line, 2);
        if (!strcmp(u_choice, "y")) {
            free(u_choice);
            return 1;
        }
        else if (!strcmp(u_choice, "n")){
            free(u_choice);
            return 0;
        }
        else {
            free(u_choice);
            continue;
        }
    }
}

/*int get_user_int(const char *message, const char *help_line, int ROOF_VAL, int FLOOR_VAL) {
    #define CHARED_INT_MAX_SIZE 15
    // Returns NULL if the user exits the function
    char buffer[CHARED_INT_MAX_SIZE] = {0};

    while (1) {
        fputs(message, stdout);
        fgets(buffer, CHARED_INT_MAX_SIZE, stdin);
        fflush(stdin);
        if (!strcmp(buffer, "\n")) // checks if the buffer is not empty
            return 0;
        strncpy(buffer, strtok(buffer, "\n"), CHARED_INT_MAX_SIZE - 1);

        // validation check
        char *p = buffer;
        int val = 0;
        while (*p) {
            if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1))))
                val = strtol(p, &p, 10);
            else
                break;
            if (val && (val > FLOOR_VAL && val < ROOF_VAL))
                return val; // the result is implicitely cast from a long to an int
        }
        puts(help_line);
    }
}
*/

int get_user_int(const char *message, const char *help_line, int ROOF_VAL, int FLOOR_VAL) {
    return (int)get_user_double(message, help_line, ROOF_VAL, FLOOR_VAL);
}

double get_user_double(const char *message, const char *help_line, double ROOF_VAL, double FLOOR_VAL) {
    #define CHARED_INT_MAX_SIZE 311 // char occupati da: (1,8 * 10^308)
    char buffer[CHARED_INT_MAX_SIZE] = {0};
    while (1) {
        fputs(message, stdout);
        fgets(buffer, CHARED_INT_MAX_SIZE, stdin);
        fflush(stdin);
        if (!strcmp(buffer, "\n") || !strcmp(buffer, "!\n")) // checks if the buffer is not empty
            return 0;
        strncpy(buffer, strtok(buffer, "\n"), CHARED_INT_MAX_SIZE - 1);

        // validation check
        char *p = buffer;
        double val = 0;

        if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1))))
            val = strtod(p, &p);
        if (val && (val > FLOOR_VAL && val < ROOF_VAL)) {
            // check if string has alpha after number
            while (*p)
                if (!isdigit(*p)){
                    puts("All non digit characters have been ignored!");
                    break;
                }
            return val;
        }

        puts(help_line);
    }
}

cellulare * get_user_cellulare(cellulare ** main_table) {
    /*
     * This function asks the user all the data necessary to build a cellulare
     * The memory is allocated on the heap so REMEMBER TO FREE IT
     * return NULL pointer if a cellulare could not be generated
     */
    cellulare * ret_cell = calloc(1, sizeof(cellulare));
    if (!ret_cell)
        return NULL;

    printf("Input the requested data and press 'enter' to continue.\nIf you want to leave a field blank "
           "press enter without entering any data.\n");

    char * buffer = NULL;
    char * help_line = "The value you have provided is not valid";

    buffer = get_user_str("Phone's name --> ",help_line, MAX_NAME);
    strcpy(ret_cell->name, buffer);
    free(buffer); buffer = NULL;

    ret_cell->weight = get_user_int("Weight of the phone --> ",help_line, 2000, 0);
    ret_cell->ram = get_user_int("Ram of the phone --> ",help_line, 100000, 0);
    ret_cell->display_ppi = get_user_int("Pixel per inch of the display --> ",help_line, 1000, 0);
    ret_cell->id_os = get_user_int("OS's id --> ",help_line, 20, 0);
    ret_cell->id_manufacturer = get_user_int("Manufacturer's id --> ",help_line, 20, 0);
    ret_cell->display_size = get_user_double("Display size (inch) --> ",help_line,15, 0);

    buffer = get_user_str("Display resolution (AAAAxAAAA) --> ",help_line, MAX_DISPLAY_RESOLUTION);
    strcpy(ret_cell->display_resolution, buffer);
    free(buffer);
    buffer = NULL;

    buffer = get_user_str("CPU (A core Aghz) --> ",help_line, MAX_CPU);
    strcpy(ret_cell->cpu, buffer);
    free(buffer);
    buffer = NULL;

    buffer = get_user_str("Notes [max 500 char]:\n",help_line, MAX_NOTES);
    strcpy(ret_cell->notes, buffer);
    free(buffer);

    // test if struct is empty
    cellulare * test_cell = alloca(sizeof(cellulare));
    memset(test_cell, 0, sizeof(cellulare));
    if (!memcmp(ret_cell, test_cell, sizeof(cellulare))) {
        puts("The phone was empty, ignoring");
        return NULL;
    }
    ret_cell->id = main_table_len(main_table);
    return ret_cell;
}

void get_user_command(cellulare ** main_table, const char * message) {
    char * cmd = get_user_str(message, "The value you have provided is not a string!", 0);
    cmd_handler(main_table, cmd);
    free(cmd);
}

void cmd_handler(cellulare ** main_table, const char * cmd) {
    for (size_t i = 0; commands[i].execute; i++) {
        if(!strcmp(commands[i].name, cmd)) {
            (*commands[i].execute)(main_table);
            return;
        }
    }
    printf("WARNING: No matching command for %s\n", cmd);
}

void test_commands(cellulare ** main_table) {
    for (size_t i = 0; commands[i].execute; i++) {
        printf("%s : ", commands[i].name);
        (*commands[i].execute)(main_table);
    }
}
