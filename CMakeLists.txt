cmake_minimum_required(VERSION 3.16)
project(ProgettoFSM C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Abilita il motore di test interno di CMake (CTest)
enable_testing()

# Aggiunge le sotto-cartelle al processo di build
add_subdirectory(lib/utils)
add_subdirectory(src)
add_subdirectory(test)