#include "func/funcionalidades.h"

// Variáveis globais
uint16_t x_value = 0, y_value = 0;
uint16_t pwm_red = 0, pwm_blue = 0;

int led_x = 2, led_y = 2;  // Posição inicial do LED (centro da matriz 5x5)
int estado_B = 0; // 0 = quadrado, 1 = matriz LED
int cor_atual = 0; // 0 = Vermelho, 1 = Verde, 2 = Azul

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

        if (pino == BOTAO_A) {
            *estado_LED = !(*estado_LED);
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
            *estado_LED = !(*estado_LED);
            gpio_put(green, *estado_LED);
            borda_estado = (borda_estado + 1) % 3;
            buzzer_play_J = true;
        } else if (pino == BOTAO_B) {
            estado_B = (estado_B + 1) % 2; // Alterna entre 0 e 1
            if (estado_B == 1) { // Se mudou para modo matriz
                cor_atual = (cor_atual + 1) % 6; // Cicla entre 0, 1 e 2
            }
            buzzer_play_B = true;
        }
    }
}

void botao_callback(uint gpio, uint32_t eventos) {
    if (gpio == BOTAO_A) {
        debounce_botao(BOTAO_A, &last_irq_time_A, &estado_LED_A);
    } else if (gpio == BOTAO_J) {
        debounce_botao(BOTAO_J, &last_irq_time_J, &estado_LED_B);
    } else if (gpio == BOTAO_B) {
        debounce_botao(BOTAO_B, &last_irq_time_B, &estado_LED_B);
    }
}

uint16_t joystick_to_pwm(uint16_t joystick_value) {
    int32_t offset = (int32_t)joystick_value - 2048;
    if (offset < 0) offset = -offset;
    return (uint16_t)(offset * 2);
}