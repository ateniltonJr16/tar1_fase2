#ifndef OPCOES_ESCOLHIDAS_H
#define OPCOES_ESCOLHIDAS_H

#include "func/funcionalidades.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "lib/font.h"
#include "lib/matrixws.h"

extern uint pwm_wrap;
extern char buffer[100];

void quadrado();
void atualizar_matriz_led();
void condicoes();
void alternar_funcoes();

#endif