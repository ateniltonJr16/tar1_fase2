#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdint.h>
#include "lib/rgb.h"
#include "lib/buttons.h"
#include "lib/buzzer.h"
#include "lib/display_init.h"

#define VRX_PIN 26
#define VRY_PIN 27
#define DEADZONE 200  // Zona morta para considerar o joystick centralizado

// Variáveis globais
extern uint16_t x_value, y_value;
extern uint16_t pwm_red, pwm_blue;
extern int led_x, led_y; 
extern int estado_B; 
extern int cor_atual; 

void init_adc_joy();
uint pwm_init_gpio(uint gpio, uint wrap);
void debounce_botao(uint pino, volatile uint32_t *last_irq_time, bool *estado_LED);
void botao_callback(uint gpio, uint32_t eventos);
uint16_t joystick_to_pwm(uint16_t joystick_value);

#endif