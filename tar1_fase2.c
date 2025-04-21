/*
*             ___________________________________________
*            |                                           |
*            |  PROJETO: DualControl Matrix              |
*            |                                           |
*            |  ► Controle simultâneo de:                |
*            |    - Matriz LED 5x5 (WS2812B)             |
*            |    - Display OLED 128x64 (SSD1306)        |
*            |                                           |
*            |  ► Funcionalidades:                       |
*            |    - Joystick analógico para navegação    |
*            |    - Modos RGB com ajuste PWM             |
*            |    - Feedback sonoro via buzzer           |
*            |                                           |
*            |  ► Tecnologias:                           |
*            |    - RP2040 (BitDogLab)                   |
*            |    - Protocolos: I2C, UART, ADC, PWM, PIO |
*            |                                           |
*            |  AUTOR: Atenilton Santos de Souza Júnior  |
*            |___________________________________________|
*/

#include "func/opcoes_escolhidas.h"

int main() {  
    stdio_init_all(); // Inicializa a comunicação serial para depuração
    iniciar_botoes();//Iniicaliza os botões
    init_adc_joy(); //Inicializa o adc do joystick
    iniciar_rgb(); // Inicializa os leds RGB
    display();    // Inicializa o display OLED
    controle(PINO_MATRIZ); // Inicializa a matriz 5x5 ws2812

    pwm_init_gpio(red, pwm_wrap); // PWM do led RGB vermelho
    pwm_init_gpio(blue, pwm_wrap); // PWM do led RGB azul

    // Inicializa o buzzer com beep de 1 kHz durante 0,5 seg
    buzzer_init(buzzer, 1000);
    sleep_ms(500);
    buzzer_stop(buzzer);

    // Mensagem inicial para confirmar que a UART está funcionando
    printf("Sistema inicializado. Pronto para receber comandos.\n");

    while (true) {
        // Altera entre o controle da matriz e do cursor do display
        // Interrupções foram aplicadas dentro dessa função
        alternar_funcoes(); 
        beeps(); //Ativa o beep do buzzer quando um botão é pressionado
        //Mensagens de depuração
        printf("PWM joystick (X, Y) = (%.0f%%, %.0f%%)\n", (float) y_value / 4095 *100, (float) x_value / 4095 *100);
        sleep_ms(100); // Revisão a cada 100 ms
    }

    return 0;
}