cmake_minimum_required(VERSION 3.16)
project(ProgettoFSM C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_testing()

# Cartelle delle librerie
add_subdirectory(lib/utils)
add_subdirectory(lib/motor_controller) # Aggiunto

add_subdirectory(src)
add_subdirectory(test)