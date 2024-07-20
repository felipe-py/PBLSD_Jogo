#ifndef UTILS_H
#define UTILS_H

/**Desconsidera 5 pixels à esquerda e á direita do sprite ladrão 
 * Usado para melhor determinação das posições do sprite em tela e colisões 
 */
#define ESQ_SPRITE_LADRAO 5
#define DIR_SPRITE_LADRAO 5

/**Desconsidera 3 pixels à esquerda e 4 pixels á direita do sprite policial
 * Usado para melhor determinação das posições do sprite em tela e colisões 
 */
#define ESQ_SPRITE_POLICIA 3
#define DIR_SPRITE_POLICIA 4

/* Posições iniciais da coordenada X dos sprites policiais - Movimentação */
#define INICIO_POLICIAL_1_X 160 - ESQ_SPRITE_POLICIA
#define INICIO_POLICIAL_2_X 600 + DIR_SPRITE_POLICIA
#define INICIO_POLICIAL_3_X 456 - ESQ_SPRITE_POLICIA
#define INICIO_POLICIAL_4_X 400 + DIR_SPRITE_POLICIA
#define INICIO_POLICIAL_5_X 88 - ESQ_SPRITE_POLICIA
#define INICIO_POLICIAL_6_X 608 + ESQ_SPRITE_POLICIA
#define INICIO_POLICIAL_7_X 392
#define INICIO_POLICIAL_8_X 96 - ESQ_SPRITE_POLICIA
#define INICIO_POLICIAL_9_X 456 - ESQ_SPRITE_POLICIA
#define INICIO_POLICIAL_10_X 208 + DIR_SPRITE_POLICIA

/* Posições finais da coordenada X dos sprites policiais - Movimentação */
#define FIM_POLICIAL_1_X 400 + DIR_SPRITE_POLICIA
#define FIM_POLICIAL_2_X 456 - ESQ_SPRITE_POLICIA
#define FIM_POLICIAL_3_X 608 + DIR_SPRITE_POLICIA
#define FIM_POLICIAL_4_X 88 - ESQ_SPRITE_POLICIA
#define FIM_POLICIAL_5_X 400 + DIR_SPRITE_POLICIA
#define FIM_POLICIAL_6_X 456 - ESQ_SPRITE_POLICIA
#define FIM_POLICIAL_7_X 96 - ESQ_SPRITE_POLICIA
#define FIM_POLICIAL_8_X 208 + DIR_SPRITE_POLICIA
#define FIM_POLICIAL_9_X 600 + DIR_SPRITE_POLICIA
#define FIM_2_POLICIAL_9_X 392 - ESQ_SPRITE_POLICIA
#define FIM_POLICIAL_10_X 24 - ESQ_SPRITE_POLICIA

/* Posições iniciais da coordenada Y (e finais) dos sprites policiais - Movimentação */
#define INICIO_POLICIAL_1_Y 8
#define INICIO_FIM_POLICIAL_2_Y 72
#define INICIO_POLICIAL_3_Y 128
#define INICIO_FIM_POLICIAL_4_Y 160
#define INICIO_FIM_POLICIAL_5_Y 216
#define INICIO_FIM_POLICIAL_6_Y 296
#define INICIO_POLICIAL_7_Y 336
#define INICIO_FIM_POLICIAL_8_Y 384
#define INICIO_POLICIAL_9_Y 368
#define INICIO_POLICIAL_10_Y 448

/* Posições finais da coordenada Y dos sprites policiais - Movimentação */
#define FIM_POLICIAL_1_Y 96
#define FIM_POLICIAL_3_Y 184
#define FIM_POLICIAL_7_Y 288
#define FIM_POLICIAL_9_Y 448
#define FIM_POLICIAL_10_Y 200

/* Quantidade de pixels que policiais 1, 2 e 3 deslocam a cada tempo determinado */
#define DESLOCAMENTO_POLICIAL_1 3
#define DESLOCAMENTO_POLICIAL_2 2
#define DESLOCAMENTO_POLICIAL_3 2

/* Quantidade de pixels que policiais 4, 5 e 6 deslocam a cada tempo determinado */
#define DESLOCAMENTO_POLICIAL_4 3
#define DESLOCAMENTO_POLICIAL_5 3
#define DESLOCAMENTO_POLICIAL_6 2

/* Quantidade de pixels que policiais 7, 8, 9 e 10 deslocam a cada tempo determinado */
#define DESLOCAMENTO_POLICIAL_7 3
#define DESLOCAMENTO_POLICIAL_8 2
#define DESLOCAMENTO_POLICIAL_9 2
#define DESLOCAMENTO_POLICIAL_10 2

/* Posição inicial da coordenada X e Y do sprite ladrão */
#define INICIO_LADRAO_X 456
#define INICIO_LADRAO_Y 32

/* Posição da coordenada X e Y do sprite porta */
#define PORTA_X 456
#define PORTA_Y 0

/* Posição da coordenada X e Y do sprite troféu esquerdo */
#define TROFEU_ESQ_X 24
#define TROFEU_ESQ_Y 16

/* Posição da coordenada X e Y do sprite troféu direito */
#define TROFEU_DIR_X 96
#define TROFEU_DIR_Y 104

/* Posição da coordenada X e Y do sprite pause */
#define PAUSE_X 608
#define PAUSE_Y 0

/* Função para verificar colisão do sprite ladrão com estruturas do mapa do jogo e evitar atravessá-las */
int 
verifica_colisao_parede(int x_ladrao, int y_ladrao, int verificar, char x_y);

/* Função para verificar colisão do sprite ladrão com sprites policiais e sprites troféus */
int 
verifica_colisao_policia(int x_ladrao, int y_ladrao, int policia_x, int policia_y);

#endif
