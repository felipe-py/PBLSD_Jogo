#ifndef THREADS_H
#define THREADS_H

#include "utils.h"
#include <pthread.h>
#include <linux/input.h>

#define MOUSE_DEVICE "/dev/input/event0"

#define SENTIDO_PARA_DIREITA 1
#define SENTIDO_PARA_ESQUERDA 2
#define SENTIDO_PARA_CIMA 3
#define SENTIDO_PARA_BAIXO 4

#define VELOCIDADE_POLICIAIS_2_3_6_8 10000
#define VELOCIDADE_POLICIAIS_4_5_7 8000
#define VELOCIDADE_POLICIAIS_9_10 7000
#define VELOCIDADE_POLICIAIS_1 5000

int fd_mouse;
struct input_event ev;

pthread_mutex_t lock;

pthread_t thread_mouse, thread_policais_1, thread_policiais_2_3_6_8, thread_policiais_4_5_7, thread_policias_9_10;

volatile int x_ladrao = INICIO_LADRAO_X;
volatile int y_ladrao = INICIO_LADRAO_Y;

volatile int policia_1_x = INICIO_POLICIAL_1_X;
volatile int policia_2_x = INICIO_POLICIAL_2_X;
volatile int policia_3_x = INICIO_POLICIAL_3_X;
volatile int policia_4_x = INICIO_POLICIAL_4_X;
volatile int policia_5_x = INICIO_POLICIAL_5_X;
volatile int policia_6_x = INICIO_POLICIAL_6_X;
volatile int policia_7_x = INICIO_POLICIAL_7_X;
volatile int policia_8_x = INICIO_POLICIAL_8_X;
volatile int policia_9_x = INICIO_POLICIAL_9_X;
volatile int policia_10_x = INICIO_POLICIAL_10_X;

volatile int policia_1_y = INICIO_POLICIAL_1_Y;
volatile int policia_2_y = INICIO_FIM_POLICIAL_2_Y;
volatile int policia_3_y = INICIO_POLICIAL_3_Y;
volatile int policia_4_y = INICIO_FIM_POLICIAL_4_Y;
volatile int policia_5_y = INICIO_FIM_POLICIAL_5_Y;
volatile int policia_6_y = INICIO_FIM_POLICIAL_6_Y;
volatile int policia_7_y = INICIO_POLICIAL_7_Y;
volatile int policia_8_y = INICIO_FIM_POLICIAL_8_Y;
volatile int policia_9_y = INICIO_POLICIAL_9_Y;
volatile int policia_10_y = INICIO_POLICIAL_10_Y;

volatile int pause = 0;
volatile int start = 0;
volatile int sair = 0;
volatile int furtivo = 0;

volatile int habilidades = 0;

int cria_threads_jogo();

int cancela_threads_jogo();

int espera_cancelamento_threads_jogo();

void* movimenta_mouse(void* arg);

void* movimenta_policiais_2_3_6_8(void* arg);

void* movimenta_policiais_4_5_7(void* arg);

void* movimenta_policiais_9_10(void* arg);

void* movimenta_policiais_1(void* arg);

void* botao(void* arg);

#endif
