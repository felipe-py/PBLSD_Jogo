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

extern int fd_mouse;
extern struct input_event ev;

extern pthread_mutex_t lock;

extern pthread_t thread_mouse, thread_policais_1, thread_policiais_2_3_6_8, thread_policiais_4_5_7, thread_policias_9_10;

extern volatile int x_ladrao;
extern volatile int y_ladrao;

extern volatile int policia_1_x;
extern volatile int policia_2_x;
extern volatile int policia_3_x;
extern volatile int policia_4_x;
extern volatile int policia_5_x;
extern volatile int policia_6_x;
extern volatile int policia_7_x;
extern volatile int policia_8_x;
extern volatile int policia_9_x;
extern volatile int policia_10_x;

extern volatile int policia_1_y;
extern volatile int policia_2_y;
extern volatile int policia_3_y;
extern volatile int policia_4_y;
extern volatile int policia_5_y;
extern volatile int policia_6_y;
extern volatile int policia_7_y;
extern volatile int policia_8_y;
extern volatile int policia_9_y;
extern volatile int policia_10_y;

extern volatile int cancela_threads_policiais;
extern volatile int cancela_thread_botoes;

extern volatile int pausar;
extern volatile int start;
extern volatile int sair;
extern volatile int furtivo;

extern volatile int jogando;

extern volatile int habilidades;

int cria_threads_jogo();

int espera_cancelamento_threads_policias();

int cancela_thread_mouse();

void* movimenta_mouse(void* arg);

void* movimenta_policiais_2_3_6_8(void* arg);

void* movimenta_policiais_4_5_7(void* arg);

void* movimenta_policiais_9_10(void* arg);

void* movimenta_policiais_1(void* arg);

void* botao(void* arg);

#endif
