add_library(motor_controller motor_fsm.c)

target_include_directories(motor_controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Questa libreria usa la funzione definita in utils
target_link_libraries(motor_controller PRIVATE utils)