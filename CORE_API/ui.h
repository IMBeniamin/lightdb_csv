#pragma once
#include "globals.h"
_Noreturn void ui_loader();

char *get_user_str(const char *message, const char *help_line, int n_char);
int get_user_y_n(const char *message, const char *help_line);
int get_user_int(const char *message, const char *help_line, int ROOF_VAL, int FLOOR_VAL);
double get_user_double(const char *message, const char *help_line, double ROOF_VAL, double FLOOR_VAL);
cellulare *get_user_cellulare();
void get_user_command(const char *message);

void cmd_handler(const char *cmd);
void test_commands();

// Command wrappers
// All wrappers/executables should have the prefix "cmd_" at the beginning of the name

void cmd_display_table();
void cmd_list_fields();
void cmd_html();
void cmd_txt();
void cmd_sort();
void cmd_search();
void cmd_add();
void cmd_del();
void cmd_view();
void cmd_help();
void cmd_safe_quit();
void cmd_unsafe_quit();
