#include "../CORE_API/ui.h"
#include "../tools_api.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// TODO remember to add all funcs to the header

typedef void(*functionPointerType)(cellulare **);
#define HELP_LINE "The data you have inserted is not valid! Please use the command 'help' if you need assistance\n"

struct commandStruct {
    char const *name;
    functionPointerType execute;
    char const *help;
};

const struct commandStruct commands[] = {
        {"display", &cmd_display_table, "Prints the main_table onto the screen."},
        {"sort", &cmd_sort, "Enters the sorting menu."},
        {"quit", &safe_quit, "Safely exit the application. [saves changes]"},
        {"exit", &safe_quit, "Alias for 'quit'"},
        {"help", &cmd_help, "Shows this menu."},
        {"",0,""} //End of table indicator. MUST BE LAST!!!
};

/*
 * Manages and updates screen and handles user i/o
 */

_Noreturn void ui_loader(cellulare ** main_table) {
    // Boot up the CLI
    setbuf(stdout, 0); // sets stdout buffer to 0 allowing it to also work in debug mode
    while (1)
        get_user_command(main_table, ">");
}

/*
 * Core API & Tools API calls wrappers/executables
 * Used by the cmd handler in order to avoid user error
 * !IMPORTANT! All wrappers MUST take as a parameter ONLY the main_table pointed list in the form of: cellulare ** main_table +
 * All functions in this category should start with "cmd_"
 *
 * +: The only function which makes an exception in this category is cmd_help, which has an unspecified number (and type) of params.
 */

void cmd_display_table(cellulare ** main_table) {
    char * str_data = calloc(main_table_len(main_table) * CELLULARE_STRING_LINE_SIZE + 1, sizeof(char));
    generate_string(main_table, str_data);
    printf("%s", str_data);
}

void cmd_list_fields(cellulare ** main_table) {
    for (size_t i = 0; fields[i].execute; i++)
        printf("%s --> %s\n", fields[i].name, fields[i].description);
}

void cmd_sort(cellulare ** main_table) {
    printf("Would you like to view all fields available? [y/n]");
    char buff[200];
    while (fgets(buff, 200, stdin)) {
        if (!strcmp(buff, "y\n")) {
            cmd_list_fields(main_table);
            break;
        }
        else if (!strcmp(buff, "n\n"))
            break;
        else
            continue;
    }

    size_t m_t_len = main_table_len(main_table);
    //todo add option to show available fields
    char *field = get_user_str("\nSort by [field] -->");
    if (!cell_quick_sort(main_table, sizeof(cellulare *), m_t_len, field)) {
        printf("The field you provided does not exist! No changes were made.\n");
        return;
    }
    else
        printf("The table has been sorted by %s\n", field);
    free(field);
}

void cmd_help() {
    printf("-----------------\n| Help Section! |\n-----------------\nThe following commands are available:\n----------------------------------\n");
    for (size_t i = 0; commands[i].execute; i++)
        printf("%s -- %s\n\n", commands[i].name, commands[i].help);
}

/*
 * Getters and handlers + tests
 */

char * get_user_str(const char * message) {
    /*
     * Returns NULL if the user exits the function
     * Remember to FREE the result
     */
    fputs(message, stdout);
    char buffer[100] = {0};
    char * _str = calloc(20, sizeof(char));

    while (1) {
        fgets(buffer, 20, stdin);
        _str = strtok(buffer, "\n");

        // validation check
        if (strchr(_str, ' ') || !_str[0])
            printf(HELP_LINE);
        else
            return _str;
    }
}

int get_user_int(const char * message) {
    /*
     * Returns NULL if the user exits the function
     */
    fputs(message, stdout);
    char buffer[100] = {0};
    char * _str = calloc(20, sizeof(char));

    while (1) {
        fgets(buffer, 20, stdin);
        _str = strtok(buffer, "\n");

        // validation check
        char *p = _str;
        long val = 0;
        while (*p) {
            if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1))))
                val = strtol(p, &p, 10);
            else
                p++;
            if (!val)
                printf(HELP_LINE);
            else
                return val; // the result is implicitely cast from a long to an int
        }
    }
}

cellulare * get_user_cellulare(cellulare ** main_table) {
    //TODO not tested
    /*
     * This function asks the user all the data necessary to build a cellulare
     * The memory is allocated on the heap so REMEMBER TO FREE IT
     */
    __int8 is_valid = 0;
    cellulare * ret_cell = calloc(sizeof(cellulare), 1);
    ret_cell->id = main_table_len(main_table);
    printf("Input the requested data and press 'enter' to continue.\n If you want to leave a field blank "
           "press enter without entering any data.\n");

    strcpy(ret_cell->name, get_user_str("Phone's name -->"));
    ret_cell->weight = get_user_int("Weight of the phone -->");
    ret_cell->ram = get_user_int("Ram of the phone -->");
    ret_cell->display_ppi = get_user_int("Pixel per inch of the display -->");
    ret_cell->id_os = get_user_int("Operating System's id -->");
    ret_cell->id_manufacturer = get_user_int("Manufacturer's id -->");
    ret_cell->display_size = get_user_int("Display size (inch) -->");
    strcpy(ret_cell->display_resolution, get_user_str("Display resolution (AAAAxAAAA) -->"));
    // strcpy(ret_cell->size, ) todo what is size?
    strcpy(ret_cell->cpu, get_user_str("CPU (Snapdragon xxx)"));
    strcpy(ret_cell->notes, get_user_str("Notes [max 500 char]:\n"));
    return ret_cell;
}

void get_user_command(cellulare ** main_table, const char * message) {
    char * cmd = get_user_str(message);
    cmd_handler(main_table, cmd);
    free(cmd);
}

void cmd_handler(cellulare ** main_table, char * cmd) {
    for (size_t i = 0; commands[i].execute; i++) {
        if(!strcmp(commands[i].name, cmd)) {
            if (cmd) {
                (*commands[i].execute)(main_table);
                return;
            }
        }
    }
    printf("WARNING: No matching command for %s.\n", cmd);
}

void test_commands(cellulare ** main_table) {
    for (size_t i = 0; commands[i].execute; i++) {
        printf("%s : ", commands[i].name);
        (*commands[i].execute)(main_table);
    }
}
