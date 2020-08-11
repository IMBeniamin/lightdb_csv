#pragma once

/*
 * Global naming conventions:
 * w_d = write_data (data to be written [might be used with an appended (f) which means that the data is formatted]
 * r_d = read_data (data to be read) (usually is passed to a w_d)
 */
#define CELLULARE_STRING_LINE_SIZE 200
#define MAX_DISPLAY_RESOLUTION 15
#define MAX_CPU 20
#define MAX_NAME 40
#define MAX_NOTES 500

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

typedef struct String {
    char data[100];
}string;