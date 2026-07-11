include(FetchContent)

# Scarica automaticamente il framework Unity da GitHub
FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        v2.5.2
)
FetchContent_MakeAvailable(unity)

# Crea l'eseguibile del test
add_executable(run_test test_utils.c)

# Collega la nostra libreria "utils" e la libreria "unity" appena scaricata
target_link_libraries(run_test PRIVATE utils unity)

# Registra il test all'interno del sistema di test di CMake (CTest)
add_test(NAME test_temperature COMMAND run_test)