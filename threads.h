#ifndef THREADS_H
#define THREADS_H

#include "utils.h"
#include <pthread.h>

/* Caminho para acesso ao dispositivo do mouse para captura de eventos */
#define MOUSE_DEVICE "/dev/input/event0"

/* Definições para movimentações dos sprites dos policiais */
#define SENTIDO_PARA_DIREITA 1
#define SENTIDO_PARA_ESQUERDA 2
#define SENTIDO_PARA_CIMA 3
#define SENTIDO_PARA_BAIXO 4

/* Tempo do "usleep" que define velocidade de movimentação dos sprites dos policiais */
#define VELOCIDADE_POLICIAIS 4250

/* Usando para abrir /dev/input/event0 */
extern int fd_mouse;

/* Mutex para sincronização entre as threads */
extern pthread_mutex_t lock;

/* IDs das threads do jogo */
extern pthread_t thread_mouse, thread_policais_1_2_3, thread_policiais_4_5_6, thread_policiais_7_8_9_10;

/* Variáveis para as coordenadas X e Y do sprite ladrão */
extern volatile int x_ladrao;
extern volatile int y_ladrao;

/* Variáveis para as coordenadas X dos sprites policiais */
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

/* Variáveis para as coordenadas Y dos sprites policiais */
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

/* Variáveis de controle responsáveis por cancelar as threads do jogo */
extern volatile int cancela_threads_policiais;
extern volatile int cancela_thread_botoes;

/* Variáveis responsáveis pelo controle do jogo */
extern volatile int pausar;
extern volatile int start;
extern volatile int sair;

/* Variável usada para habilitar botões de pause e despause apenas quando o jogador estiver jogando */
extern volatile int jogando;

/* Variável que indica a quantidade de habilidades restantes do jogador */
extern volatile int habilidades;

/* Variável que indica se o jogador está utilizando a habilidade ou não */
extern volatile int furtivo;

/* Função para setar posição inicial do jogador (sprite ladrão) */
void 
inicia_ladrao();

/* Função para criar as threads do jogo (mouse e policiais) */
int 
cria_threads_jogo();

/* Função para esperar o encerramento das threads dos policiais */
int 
espera_cancelamento_threads_policias();

/* Função para cancelar a thread do mouse */
int 
cancela_thread_mouse();

/* Função referente a thread para captação dos eventos do mouse */
void* 
movimenta_mouse(void* arg);

/* Função referente a thread para movimentação dos policiais 1, 2 e 3 */
void* 
movimenta_policiais_1_2_3(void* arg);

/* Função referente a thread para movimentação dos policiais 4, 5 e 6 */
void* 
movimenta_policiais_4_5_6(void* arg);

/* Função referente a thread para movimentação dos policiais 7, 8, 9 e 10 */
void* 
movimenta_policiais_7_8_9_10(void* arg);

/* Função referente a thread para captação dos eventos dos botões da FPGA */
void* 
botao(void* arg);

#endif
