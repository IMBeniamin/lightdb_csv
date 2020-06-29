cmake_minimum_required(VERSION 3.16)
project(csv_database C)

set(CMAKE_C_STANDARD 11)

add_executable(csv_database main.c CORE_API/globals.h CORE_SRC/UI.c CORE_API/UI.h CORE_SRC/IO.c CORE_SRC/IO.c CORE_API/IO.h CORE_API.h TOOLS_API.h TOOLS_SRC/sorting.c TOOLS_API/sorting.h)