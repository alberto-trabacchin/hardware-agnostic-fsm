cmake_minimum_required(VERSION 3.19)
project(ProgettoFSM C ASM) # Abilitiamo anche il supporto all'Assembly per lo startup file

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Condizione: stiamo compilando per STM32 (Cross-compilazione)?
if(CMAKE_SYSTEM_NAME STREQUAL "Generic")
    message(STATUS "Build target rilevato: STM32F446RE")
    
    # Includiamo la libreria FSM
    add_subdirectory(lib/utils)
    add_subdirectory(lib/motor_controller)
    
    # Includiamo l'applicazione firmware specifica
    add_subdirectory(src)

else()
    message(STATUS "Build target rilevato: PC Locale (Host)")
    
    # Abilitiamo i test sul PC
    enable_testing()
    add_subdirectory(lib/utils)
    add_subdirectory(lib/motor_controller)
    add_subdirectory(test)
endif()