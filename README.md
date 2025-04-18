Projeto Integrador - BitDogLab
Sistemas Embarcados com RP2040
📌 Sumário
📹 Vídeo de Demonstração

🎯 Objetivo do Projeto

🛠️ Funcionalidades Implementadas

📦 Hardware Utilizado

⚙️ Compilação e Instalação

📂 Estrutura do Projeto

👨‍💻 Autor

📹 Vídeo de Demonstração
Assistir no YouTube

Conteúdo do vídeo:

Apresentação pessoal

Explicação das funcionalidades

Demonstração ao vivo na placa BitDogLab

(Substitua pelo link real do seu vídeo)

🎯 Objetivo do Projeto
Desenvolver um sistema embarcado completo utilizando:

Leitura analógica do joystick via ADC

Controle de matriz LED 5x5 e LED RGB com PWM

Exibição gráfica no display OLED SSD1306 (I2C)

Comunicação serial via UART para depuração

Tratamento de interrupções para botões com debounce

🛠️ Funcionalidades Implementadas
Funcionalidades Obrigatórias
✅ Controle de um cursor 8x8 no display OLED via joystick
✅ Leitura precisa dos eixos X/Y do joystick (ADC)
✅ Tratamento de botões com debounce em hardware
✅ Saída de depuração via UART (115200 baud)

Funcionalidades Adicionais
✨ Controle de matriz LED WS2812B 5x5
✨ Ajuste de cor RGB via PWM
✨ Feedback sonoro com buzzer
✨ Multiplos modos de operação

📦 Hardware Utilizado
Componente	Especificações
Microcontrolador	RP2040 (BitDogLab)
Display	OLED SSD1306 128x64 (I2C)
Joystick	Analógico + Botão
Matriz LED	WS2812B 5x5
LED RGB	PWM controlado
Buzzer	Ativo 5V
⚙️ Compilação e Instalação
Pré-requisitos
SDK do Raspberry Pi Pico

Toolchain ARM (gcc-arm-none-eabi)

CMake (versão 3.13+)

Passo a Passo
# Clone o repositório
git clone https://github.com/ateniltonJr16/tar1_fase2.git
cd tar1_fase2

# Configure o projeto
mkdir build && cd build
cmake ..

# Compile
make -j4

# Grave no RP2040 (modo BOOTSEL)
cp tar1_fase2.uf2 /media/$USER/RPI-RP2/
📂 Estrutura do Projeto
tar1_fase2/
├── lib/                  # Drivers de hardware
│   ├── ssd1306.[ch]      # Driver do display OLED
│   ├── buttons.[ch]      # Tratamento de botões
│   ├── rgb.[ch]          # Controle LED RGB
│   ├── display_init.[ch] # Inicialização do display
│   ├── matrixws.[ch]     # Controle matriz LED
│   └── buzzer.[ch]       # Driver do buzzer
│
├── func/                 # Lógica principal
│   ├── funcionalidades.[ch] # Configurações gerais
│   └── opcoes_escolhas.[ch] # Lógica de controle
│
├── CMakeLists.txt        # Configuração de build
├── tar1_fase2.c          # Ponto de entrada
└── README.md             # Documentação
👨‍💻 Autor
Nome: Atenilton Santos de Souza Júnior
GitHub: ateniltonJr16
