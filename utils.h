#ifndef UTILS_H
#define UTILS_H

#define ESQ_SPRITE_LADRAO 5
#define DIR_SPRITE_LADRAO 5

#define ESQ_SPRITE_POLICIA 3
#define DIR_SPRITE_POLICIA 4

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
#define FIM_POLICIAL_10_X 20 - ESQ_SPRITE_POLICIA

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

#define FIM_POLICIAL_1_Y 96
#define FIM_POLICIAL_3_Y 184
#define FIM_POLICIAL_7_Y 288
#define FIM_POLICIAL_9_Y 448
#define FIM_POLICIAL_10_Y 200

#define INICIO_LADRAO_X 456
#define INICIO_LADRAO_Y 32

#define PORTA_X 456
#define PORTA_Y 0

#define TROFEU_ESQ_X 24
#define TROFEU_ESQ_Y 16

#define TROFEU_DIR_X 96
#define TROFEU_DIR_Y 104

#define PAUSE_X 608
#define PAUSE_Y 0

int verifica_colisao_parede(int x_ladrao, int y_ladrao, int verificar, char x_y);

int verifica_colisao_policia(int x_ladrao, int y_ladrao, int policia_x, int policia_y);

#endif
