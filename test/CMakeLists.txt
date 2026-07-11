include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        v2.5.2
)
FetchContent_MakeAvailable(unity)

# Test 1: Utils (già esistente)
add_executable(esegui_test test_utils.c)
target_link_libraries(esegui_test PRIVATE utils unity)
add_test(NAME test_funzionalita_utils COMMAND esegui_test)

# Test 2: Motor FSM (Nuovo)
add_executable(test_fsm test_motor_fsm.c)
target_link_libraries(test_fsm PRIVATE motor_controller unity)
add_test(NAME test_fsm_transizioni COMMAND test_fsm)