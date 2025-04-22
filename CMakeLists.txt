# ==========================================================================================

# Generated CMake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Definir nome do projeto em uma variável para fácil substituição
set(NOME_PROJETO tar1_fase2) # Aqui você po~e o nome do projeto

# Escolher a placa usada (pico ou pico_w)
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Incluir o SDK do Pico (deve ser antes do projeto)
include(pico_sdk_import.cmake)

# Criar o projeto
project(${NOME_PROJETO} C CXX ASM)

# Inicializar o SDK
pico_sdk_init()

# Adicionar o executável
add_executable(${NOME_PROJETO}
    ${NOME_PROJETO}.c  # Arquivo principal
    # Pasta lib
    lib/rgb.c
    lib/ssd1306.c
    lib/buttons.c
    lib/display_init.c
    lib/matrixws.c
    lib/buzzer.c
    # Pasta func
    func/funcionalidades.c
    func/opcoes_escolhidas.c
)

# Nome e versão do programa
pico_set_program_name(${NOME_PROJETO} "${NOME_PROJETO}")
pico_set_program_version(${NOME_PROJETO} "0.1")

# Ativar saída via UART e USB
pico_enable_stdio_uart(${NOME_PROJETO} 1)
pico_enable_stdio_usb(${NOME_PROJETO} 1)

# Incluir diretórios padrão
target_include_directories(${NOME_PROJETO} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Bibliotecas utilizadas
target_link_libraries(${NOME_PROJETO}
    pico_stdlib
    hardware_pwm
    hardware_i2c
    hardware_adc
    hardware_pio
)