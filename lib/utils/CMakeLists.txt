add_library(utils utils.c)

# Espone la cartella corrente per i file che includeranno "utils.h"
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})