#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "lib/buttons.h"
#include <stdio.h>
#include "lib/font.h"
#include "lib/rgb.h"
#include "lib/display_init.h"
#include "lib/buzzer.h"
#include "lib/matrixws.h"

#define VRX_PIN 26
#define VRY_PIN 27

// Variáveis globais
uint16_t x_value = 0, y_value = 0;
uint16_t pwm_red = 0, pwm_blue = 0;

void init_adc_joy() {
    adc_init();
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);
}

uint pwm_init_gpio(uint gpio, uint wrap) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_enabled(slice_num, true);
    return slice_num;
}

void debounce_botao(uint pino, volatile uint32_t *last_irq_time, bool *estado_LED) {
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

    if (tempo_atual - *last_irq_time > DEBOUNCE_DELAY) {
        *last_irq_time = tempo_atual;
        *estado_LED = !(*estado_LED);

        if (pino == BOTAO_A) {
            if (*estado_LED) {
                pwm_set_gpio_level(red, 4095);
                pwm_set_gpio_level(blue, 4095);
                buzzer_play_A = true;
            } else {
                pwm_set_gpio_level(red, 0);
                pwm_set_gpio_level(blue, 0);
                buzzer_play_A = true;
            }
        } else if (pino == BOTAO_J) {
            gpio_put(green, *estado_LED);
            borda_estado = (borda_estado + 1) % 3;
            buzzer_play_J = true;
        }
    }
}

void botao_callback(uint gpio, uint32_t eventos) {
    if (gpio == BOTAO_A) {
        debounce_botao(BOTAO_A, &last_irq_time_A, &estado_LED_A);
    } else if (gpio == BOTAO_J) {
        debounce_botao(BOTAO_J, &last_irq_time_J, &estado_LED_B);
    }
}

uint16_t joystick_to_pwm(uint16_t joystick_value) {
    int32_t offset = (int32_t)joystick_value - 2048;
    if (offset < 0) offset = -offset;
    return (uint16_t)(offset * 2);
}

void quadrado() {
    adc_select_input(0);
    x_value = adc_read();

    adc_select_input(1);
    y_value = adc_read();

    pwm_red = joystick_to_pwm(y_value);
    pwm_blue = joystick_to_pwm(x_value);

    int pos_x = centro_x + ((2048 - (int)x_value) * centro_x) / 2048;
    int pos_y = centro_y - ((2048 - (int)y_value) * centro_y) / 2048;

    ssd1306_fill(&ssd, false);
    desenhar_borda();
    ssd1306_rect(&ssd, pos_x, pos_y, square_size, square_size, true, true);
    ssd1306_send_data(&ssd);
}

#define DEADZONE 200  // Zona morta para considerar o joystick centralizado

// Variáveis globais
int led_x = 2, led_y = 2;  // Posição inicial do LED (centro da matriz 5x5)

void atualizar_matriz_led() {
    int mat[5][5][3] = {0};  // Inicializa toda a matriz com LEDs apagados
    
    // Verifica se estamos na zona morta (joystick centralizado)
    if (abs((int)x_value - 2048) < DEADZONE && abs((int)y_value - 2048) < DEADZONE) {
        // Centraliza o LED
        led_x = 2;
        led_y = 2;
    } else {
        // Mapeia os valores do joystick para posições na matriz 5x5
        led_x = ((int)y_value * 5) / 4096;
        led_y = 4 - ((int)x_value * 5) / 4096;  // Inverte o eixo Y
        
        // Garante que os valores estejam dentro dos limites da matriz
        led_x = (led_x < 0) ? 0 : (led_x > 4) ? 4 : led_x;
        led_y = (led_y < 0) ? 0 : (led_y > 4) ? 4 : led_y;
    }
    
    // Acende o LED na posição calculada (vermelho)
    mat[led_y][led_x][1] = 10;  // LED vermelho
    
    desenhaMatriz(mat);
}

uint pwm_wrap = 4095;
char buffer[100];

void condicoes() {
    if (estado_LED_A) {
        pwm_set_gpio_level(red, pwm_red);
        pwm_set_gpio_level(blue, pwm_blue);
        sprintf(buffer, "(x, y) = (%u%%, %u%%)  ", x_value * 100 / 4096, y_value * 100 / 4096);
        uart_puts(uart0, buffer);
        sprintf(buffer, "Brilho(led azul, led vermelho) = (%u%%, %u%%)\r\n", pwm_blue * 100 / 4096, pwm_red * 100 / 4096);
        uart_puts(uart0, buffer);
    } else {
        sprintf(buffer, "(x, y) = (%u%%, %u%%) \r\n", x_value * 100 / 4096, y_value * 100 / 4096);
        uart_puts(uart0, buffer);
    }
    if (buzzer_play_A) {
        buzzer_play_A = false; // limpa a flag
        buzzer_set_freq(buzzer, 500);
        sleep_ms(100); // aqui pode usar sleep
        buzzer_stop(buzzer);
    }
    if (buzzer_play_J) {
        buzzer_play_J = false; // limpa a flag
        buzzer_set_freq(buzzer, 100);
        sleep_ms(100); // aqui pode usar sleep
        buzzer_stop(buzzer);
    }
}

int main() {
    stdio_init_all();
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

    while (true) {
        quadrado();
        atualizar_matriz_led();  // Atualiza a matriz de LEDs baseado no joystick
        condicoes();
        sleep_ms(100);
    }

    return 0;
}