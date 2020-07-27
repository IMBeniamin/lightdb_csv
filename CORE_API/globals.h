#pragma once

/*
 * Global naming conventions:
 * w_d = write_data (data to be written [might be used with an appended (f) which means that the data is formatted]
 * r_d = read_data (data to be read) (usually is passed to a w_d)
 */

typedef struct telefono_cellulare {
    int id;
    int weight;
    int ram;
    int display_ppi;
    int id_os;
    int id_manufacturer;
    double display_size;
    char display_resolution[10];
    char size[15];
    char cpu[20];
    char name[40];
    char notes[500];
}cellulare;
