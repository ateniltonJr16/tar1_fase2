![image](https://github.com/user-attachments/assets/f2a5c9b8-6208-4723-8f46-1d74be421827)
# Projeto de Revisão - BitDogLab (Sistemas Embarcados)

📌 Sumário
📹 Demonstração

🎯 Objetivo

🛠️ Funcionalidades Obrigatórias

✨ Funcionalidades Adicionais

📦 Componentes Utilizados

⚙️ Compilação e Gravação

📂 Estrutura do Código

👨‍💻 Autor


## 📹 Demonstração

[clique aqui para acessar o vídeo](link#)

Conteúdo do vídeo:
Apresentação pessoal do autor.
Explicação das funcionalidades implementadas.
Demonstração ao vivo na placa BitDogLab.

🎯 Objetivo
Desenvolver um sistema embarcado na placa BitDogLab utilizando o RP2040, integrando:

Leitura analógica do joystick (ADC).

Controle de matriz LED, LED RGB e buzzer.

Exibição de informações no display SSD1306 (I2C).

Comunicação serial via UART para depuração.

Tratamento de interrupções e debounce de botões.

## 🛠️ Funcionalidades Obrigatórias
✅ Display SSD1306: Exibe um quadrado 8x8 pixels centralizado, movendo-se proporcionalmente ao joystick.

✅ Joystick: Leitura analógica dos eixos X/Y (ADC) para controle do quadrado.

✅ Botões: Tratamento com debounce e interrupções.

✅ UART: Envio de dados para monitoramento em terminal serial.

## ✨ Funcionalidades Adicionais
🔹 Matriz LED 5x5: Feedback visual complementar.

🔹 LED RGB: Cores controladas por PWM.

🔹 Buzzer: Alertas sonoros para eventos.

🔹 Modos de Operação: Alternância entre matriz LED e controle RGB.

## 📦 Componentes Utilizados
Microcontrolador: RP2040 (BitDogLab).

Display: OLED SSD1306 (128x64, I2C).

Joystick: Eixos analógicos + botão.

Matriz LED: 5x5 (WS2812B).

LED RGB: PWM (Vermelho, Verde, Azul).

Buzzer: Feedback sonoro.

# ⚙️ Compilação e Gravação
Pré-requisitos
SDK do Raspberry Pi Pico.

Toolchain CMake (sudo apt install cmake gcc-arm-none-eabi).

Passos
bash
git clone https://github.com/ateniltonJr16/tar1_fase2.git
cd projeto-integrador
mkdir build && cd build
cmake ..
make -j4
Gravação: Copie o arquivo .uf2 para a placa no modo BOOTSEL.

## 📂 Estrutura do Código
plaintext
projeto-integrador/  
├── lib/  
│   ├── font.h           # Possui os caractéres do display 

│   ├── ssd1306.c,h      # Display OLED 

│   ├── buttons.c,h      # Configura os botões

│   └── rgb.c,h          # Controle LED RGB

│   └── display_init.c,h # INicializa e desenha no display 

│   └── matrixws.c,h     # Configua a matriz de leds 5x5

│   └── ws2818b.pio.h    # biblioteca da matriz leds ws2812

│   └── buzzer.c,h       # Inicializa e configura o pwm do buzzer

│   └── ws2818b.pio.h    # biblioteca da matriz leds ws2812  

├── func/  

│   ├── funcionalidades.c,h #Contém as configurações das funções principais

│   └── opcoes_escolhas.c,h #Funções principais do projeto

├── CMakeLists.txt # 

├── tar1_fase2.c   # Código fonte

├── diagram.json   # Simulador interativo

├── wokwi.toml     # Para simular no wokwi

├── ...            # Outos arquivos padrões

└── README.md  

## 👨‍💻 Autor
Nome: Atenilton Santos de Souza Júnior

GitHub: ateniltonJr16
