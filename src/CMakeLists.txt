# Questo file viene incluso solo se CMAKE_SYSTEM_NAME STREQUAL "Generic" (vedi CMakeLists.txt principale)

# ==========================================
# 1. SCARICA I DRIVER HAL DI STM32 E CMSIS
# ==========================================
include(FetchContent)

# Definizione per CMSIS Core (contiene core_cm4.h)
FetchContent_Declare(
    cmsis_core
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_core.git
    GIT_TAG        v5.6.0
)
FetchContent_MakeAvailable(cmsis_core)

# Definizione per CMSIS Device stm32f4
FetchContent_Declare(
    cmsis_device_stm32f4
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_device_f4.git
    GIT_TAG        v2.6.10
)
FetchContent_MakeAvailable(cmsis_device_stm32f4)

# Definizione per la libreria HAL di STM32F4
FetchContent_Declare(
    stm32f4_hal_driver
    GIT_REPOSITORY https://github.com/STMicroelectronics/stm32f4xx_hal_driver.git
    GIT_TAG        v1.8.0
)
FetchContent_MakeAvailable(stm32f4_hal_driver)

# ==========================================
# 2. GESTIONE DEI SORGENTI DEL FIRMWARE
# ==========================================

# Raccogli tutti i file .c del driver HAL ufficiale (escludendo i template)
file(GLOB STM32_HAL_SRCS "${stm32f4_hal_driver_SOURCE_DIR}/Src/stm32f4xx_hal*.c")
list(FILTER STM32_HAL_SRCS EXCLUDE REGEX ".*_template\\.c")

# Sorgenti del tuo applicativo + file di sistema CMSIS
set(STM32_FIRMWARE_SRCS
    main.c
    stm32f4xx_it.c
    ${cmsis_device_stm32f4_SOURCE_DIR}/Source/Templates/system_stm32f4xx.c
)

# File di startup ufficiale recuperato da CMSIS
set(STM32_FIRMWARE_ASM_SRCS
    ${cmsis_device_stm32f4_SOURCE_DIR}/Source/Templates/gcc/startup_stm32f446xx.s
)

# ==========================================
# 3. DEFINIZIONE DELL'ESEGUIBILE
# ==========================================
add_executable(firmware_fsm 
    ${STM32_FIRMWARE_SRCS} 
    ${STM32_FIRMWARE_ASM_SRCS}
    ${STM32_HAL_SRCS}
)

# DISATTIVA I WARNING SOLO SUI FILE DEL HAL DI ST (terze parti)  # <<< AGGIUNTO
set_source_files_properties(${STM32_HAL_SRCS} PROPERTIES COMPILE_FLAGS "-w")

# ==========================================
# 5. COLLEGAMENTO LIBRERIE E CONFIGURAZIONI COMPILATORE
# ==========================================

# Collega la logica hardware-agnostic (motor_controller)
target_link_libraries(firmware_fsm PRIVATE
    motor_controller
)

# Collega il linker script che si trova fisicamente in src/
target_link_options(firmware_fsm PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/stm32f446re.ld
)

# Definizioni globali per il preprocessore
target_compile_definitions(firmware_fsm PRIVATE
    STM32F446xx
    USE_HAL_DRIVER
)

# ==========================================
# 6. POST-COMPILAZIONE (Generazione .hex e .bin)
# ==========================================
add_custom_command(TARGET firmware_fsm POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:firmware_fsm> ${CMAKE_CURRENT_BINARY_DIR}/firmware_fsm.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:firmware_fsm> ${CMAKE_CURRENT_BINARY_DIR}/firmware_fsm.bin
    COMMENT "Generating .hex and .bin files for firmware_fsm"
)

# ==========================================
# 7. CONFIGURAZIONE DEI PERCORSI DI INCLUSIONE (Header)
# ==========================================

# I tuoi file di progetto (vogliamo vedere tutti i warning qui)
target_include_directories(firmware_fsm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# File delle librerie ST (usiamo SYSTEM per silenziare i loro warning interni)
target_include_directories(firmware_fsm SYSTEM PRIVATE
    ${cmsis_core_SOURCE_DIR}/Include
    ${cmsis_device_stm32f4_SOURCE_DIR}/Include
    ${cmsis_device_stm32f4_SOURCE_DIR}/Include/stm32f4xx
    ${cmsis_device_stm32f4_SOURCE_DIR}/Source/Templates
    ${stm32f4_hal_driver_SOURCE_DIR}/Inc
)