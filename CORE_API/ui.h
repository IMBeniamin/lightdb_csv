#pragma once
#include "globals.h"

_Noreturn void ui_loader(cellulare ** main_table);

char *get_user_str(const char *message, const char *help_line, int n_char);
int get_user_y_n(const char *message, const char *help_line);
int get_user_int(const char *message, const char *help_line);
cellulare * get_user_cellulare(cellulare ** main_table);
void get_user_command(cellulare ** main_table, const char * message);

void cmd_handler(cellulare ** main_table, const char * cmd);
void test_commands(cellulare ** main_table);

// Command wrappers
// All wrappers/executables should have the prefix "cmd_" at the beginning of the name

void cmd_display_table(cellulare ** main_table);
void cmd_list_fields();
void cmd_html(cellulare ** main_table);
void cmd_txt(cellulare ** main_table);
void cmd_sort(cellulare ** main_table);
void cmd_search(cellulare ** main_table);
void cmd_add(cellulare ** main_table);
void cmd_del(cellulare ** main_table);
void cmd_view(cellulare ** main_table);
void cmd_help();
void cmd_safe_quit(cellulare ** main_table);
void cmd_unsafe_quit();
