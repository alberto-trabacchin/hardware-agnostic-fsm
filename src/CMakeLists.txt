# DISATTIVA TUTTO IL RESTO PER QUESTO TEST
add_executable(firmware_fsm 
    main.c
    syscalls.c
)

# Flag minimi per far capire al compilatore che è un Cortex-M4
target_compile_options(firmware_fsm PRIVATE 
    -mcpu=cortex-m4 
    -mthumb
)

target_link_options(firmware_fsm PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/stm32f446re.ld
    -mcpu=cortex-m4 
    -mthumb
    --specs=nosys.specs
)

# Genera .bin
add_custom_command(TARGET firmware_fsm POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:firmware_fsm> ${CMAKE_CURRENT_BINARY_DIR}/firmware_fsm.bin
)