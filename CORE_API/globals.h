#ifndef CSV_DATABASE_GLOBALS_H
#define CSV_DATABASE_GLOBALS_H
/*
 * Global conventions:
 * Abbreviations:
 * w_d = write_data (data to be written [might be used with an appended (f) which means that the data is formatted]
 * r_d = read_data (data to be read) (usually is passed to a w_d)
 * qol = quality of life
 * Naming:
 * All function names follow the Snakecase convention
 * Defined compile-time constants also follow the Snakecase convention, but should be uppercase
 */

/*
 * These definitions should be put under CORE_API as they must be included in all project files
 * Global definitions:
 * Fixed size definitions for various elements of the csv data and comodity names
 */

#define CELLULARE_STRING_LINE_SIZE 200
#define MAX_DISPLAY_RESOLUTION 15
#define MAX_CPU 20
#define MAX_NAME 40
#define MAX_NOTES 500
#define uint32 unsigned int

/*
 * Main struct for reading csv data
 * Each phone is stored in a telefono_cellulare struct.
 */

typedef struct telefono_cellulare {
    unsigned int id;
    unsigned int weight;
    unsigned int ram;
    unsigned int display_ppi;
    unsigned int id_os;
    unsigned int id_manufacturer;
    double display_size;
    char display_resolution[MAX_DISPLAY_RESOLUTION];
//    char size[15];
    char cpu[MAX_CPU];
    char name[MAX_NAME];
    char notes[MAX_NOTES];
}cellulare;
/*
 * Basic wrapper for a fixed size char array
 */
typedef struct String {
    char data[100];
    uint32 length;
}string;
/*
 * Global extern flags implemented in main.c for various purposes
 * Each flag should have its own getter and setter
 *
 * Usage convention:
 * 0 and 1 should be used for all true/false flags
 * Flags with error tables should have corresponding documentation
 */
extern uint32 MODIFIED_FILE_DATA_FLAG;

#endif //CSV_DATABASE_GLOBALS_H
