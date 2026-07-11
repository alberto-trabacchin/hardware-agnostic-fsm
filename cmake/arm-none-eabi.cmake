set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Forza l'uso del compilatore incrociato per ARM
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# Flag hardware specifici per STM32F446RE (Cortex-M4 con Floating Point Unit hardware)
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# Flag di compilazione e ottimizzazione
set(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall -Wextra -O0 -g3 -fdata-sections -ffunction-sections" CACHE INTERNAL "C compiler flags")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -g -x assembler-with-cpp" CACHE INTERNAL "ASM compiler flags")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -Wl,--gc-sections --specs=nano.specs" CACHE INTERNAL "Linker flags")
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")