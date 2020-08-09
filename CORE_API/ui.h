#pragma once
#include "globals.h"

_Noreturn void ui_loader(cellulare ** main_table);

char * get_user_str(const char * message);
int get_user_int(const char * message);
cellulare * get_user_cellulare(cellulare ** main_table);
void get_user_command(cellulare ** main_table, const char * message);

void cmd_handler(cellulare ** main_table, char * cmd);
void test_commands(cellulare ** main_table);

// Command wrappers
// All wrappers/executables should have the prefix "cmd_" at the beginning of the name

void cmd_help();
void cmd_display_table(cellulare ** main_table);

