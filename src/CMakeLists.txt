# 1. Definisci i file sorgenti
set(SRCS
    main.c
    system_stm32f4xx.c
    stm32f4xx_it.c
    syscalls.c
    startup_stm32f446xx.S
)

# 2. CREA L'ESEGUIBILE (Questo deve venire PRIMA di ogni comando "target_")
add_executable(firmware_fsm.elf ${SRCS})

# 3. Ora puoi configurare il target creato
# Define del chip
target_compile_definitions(firmware_fsm.elf PRIVATE STM32F446xx)

# Percorsi di inclusione
target_include_directories(firmware_fsm.elf PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Opzioni di compilazione (Cortex-M4 + FPU)
target_compile_options(firmware_fsm.elf PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -Wall
    -fdata-sections 
    -ffunction-sections
)

# Opzioni del Linker
target_link_options(firmware_fsm.elf PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/stm32f446re.ld
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    --specs=nosys.specs
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_BINARY_DIR}/firmware_fsm.map
)

# Collegamento Librerie
target_link_libraries(firmware_fsm.elf 
    motor_controller 
    utils
)

# 4. Generazione del file .bin per lo flash
add_custom_command(TARGET firmware_fsm.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary firmware_fsm.elf firmware_fsm.bin
    COMMENT "Generazione del file binario firmware_fsm.bin..."
)