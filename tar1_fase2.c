#include "func/opcoes_escolhidas.h"

int main() {  
    stdio_init_all(); // Inicializa também a stdio para printf
    iniciar_botoes();
    iniciar_rgb();
    display();
    init_adc_joy();
    controle(PINO_MATRIZ);

    pwm_init_gpio(red, pwm_wrap);
    pwm_init_gpio(blue, pwm_wrap);

    buzzer_init(buzzer, 200);
    sleep_ms(500);
    buzzer_stop(buzzer);

    // Mensagem inicial para confirmar que a UART está funcionando
    printf("Sistema inicializado. Pronto para receber comandos.\n");

    while (true) {
        alternar_funcoes();
        condicoes();
        sleep_ms(100);
    }

    return 0;
}