cmake_minimum_required(VERSION 3.16)
project(csv_database C)

set(CMAKE_C_STANDARD 11)
add_executable(csv_database main.c CORE_API/globals.h CORE_SRC/ui.c CORE_API/ui.h CORE_SRC/io.c CORE_SRC/io.c CORE_API/io.h core_api.h tools_api.h TOOLS_SRC/sorting.c TOOLS_API/sorting.h TOOLS_SRC/analytics.c TOOLS_API/analytics.h TOOLS_SRC/memedit.c TOOLS_API/memedit.h TOOLS_SRC/search.c TOOLS_API/search.h)