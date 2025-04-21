#include "func/opcoes_escolhidas.h"

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

void atualizar_matriz_led() {
    int mat[5][5][3] = {0};  // Inicializa toda a matriz com LEDs apagados
    
    adc_select_input(0);
    x_value = adc_read();
    adc_select_input(1);
    y_value = adc_read();
    
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
    
    // Acende o LED na posição calculada com a cor atual
    switch(cor_atual) {
        case 0: // Vermelho
            mat[led_y][led_x][0] = 20; // "=20": intensidade do led
            break;
        case 1: // Verde
            mat[led_y][led_x][1] = 20;
            break;
        case 2: // Azul
            mat[led_y][led_x][2] = 20;
            break;
        case 3: // 
            mat[led_y][led_x][0] = 20;
            mat[led_y][led_x][1] = 20;
            break;
        case 4: // 
            mat[led_y][led_x][0] = 20;
            mat[led_y][led_x][2] = 20;
            break;
        case 5: // 
            mat[led_y][led_x][1] = 20;
            mat[led_y][led_x][2] = 20;
            break;
    }
    
    desenhaMatriz(mat);
}

uint pwm_wrap = 4095;
char buffer[100];

void beeps() {
    if (estado_LED_A) {
        pwm_set_gpio_level(red, pwm_red);
        pwm_set_gpio_level(blue, pwm_blue);
    } else {}

    if (buzzer_play_A) {
        buzzer_play_A = false;
        buzzer_set_freq(buzzer, 500);
        sleep_ms(100);
        buzzer_stop(buzzer);
    }
    if (buzzer_play_B) {
        buzzer_play_B = false;
        buzzer_set_freq(buzzer, 50);
        sleep_ms(100);
        buzzer_stop(buzzer);
    }
    if (buzzer_play_J) {
        buzzer_play_J = false;
        buzzer_set_freq(buzzer, 100);
        sleep_ms(100);
        buzzer_stop(buzzer);
    }
}

void alternar_funcoes() {
    // Chama a função apropriada baseada no estado_B
    if (estado_B == 0) {
        quadrado();
        desliga(); 
    } else {
        // Limpa o display
        ssd1306_fill(&ssd, false);

        // Exibe os textos fixos
        ssd1306_draw_string(&ssd, "PWM Joystick", 16, 20);

        // Adiciona os valores do joystick na parte inferior
        char joy_values[32];
        snprintf(joy_values, sizeof(joy_values), "X:%3.0f%% Y:%3.0f%%", 
                (float)x_value / 4095 * 100, 
                (float)y_value / 4095 * 100);
        ssd1306_draw_string(&ssd, joy_values, 20, 40);  // Posiciona na linha inferior

        // Atualiza o display
        ssd1306_send_data(&ssd);

        atualizar_matriz_led();
    }
}