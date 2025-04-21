# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# Definir nome do projeto em uma variável para fácil substituição
set(NOME_PROJETO tar1_fase2)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(${NOME_PROJETO} C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(${NOME_PROJETO} 
                ${NOME_PROJETO}.c # Principal
                #Pasta lib
                lib/rgb.c
                lib/ssd1306.c
                lib/buttons.c
                lib/display_init.c
                lib/matrixws.c
                lib/buzzer.c
                #Pasta func
                func/funcionalidades.c
                func/opcoes_escolhidas.c)

pico_set_program_name(${NOME_PROJETO} "${NOME_PROJETO}")
pico_set_program_version(${NOME_PROJETO} "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${NOME_PROJETO} 1)
pico_enable_stdio_usb(${NOME_PROJETO} 1)

# Add the standard library to the build
target_link_libraries(${NOME_PROJETO}
        pico_stdlib
        hardware_pwm
        hardware_i2c
        hardware_adc
        hardware_pio)

# Add the standard include files to the build
target_include_directories(${NOME_PROJETO} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(${NOME_PROJETO})

pico_add_extra_outputs(${NOME_PROJETO})