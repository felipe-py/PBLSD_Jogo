#include "biblioteca_gpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/input.h>

#define MOUSE_DEVICE "/dev/input/event0"

#define ESQ_SPRITE_POLICIA 3
#define DIR_SPRITE_POLICIA 4

#define ESQ_SPRITE_LADRAO 5
#define DIR_SPRITE_LADRAO 5

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
#define FIM_POLICIAL_10_X 24 - ESQ_SPRITE_POLICIA

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

#define SENTIDO_PARA_DIREITA 1
#define SENTIDO_PARA_ESQUERDA 2
#define SENTIDO_PARA_CIMA 3
#define SENTIDO_PARA_BAIXO 4

#define VELOCIDADE_POLICIAIS_2_3_6_8 10000
#define VELOCIDADE_POLICIAIS_4_5_7 8000
#define VELOCIDADE_POLICIAIS_9_10 7000
#define VELOCIDADE_POLICIAIS_1 5000

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

volatile int clicou = 0;

int fd_mouse;
struct input_event ev;

pthread_mutex_t lock; 

void* movimenta_mouse(void* arg) {
    ssize_t n;

    int verificar;

    while(1){
        n = read(fd_mouse, &ev, sizeof(ev));
            
        if (n == (ssize_t)-1) {
            fprintf(stderr, "Erro de leitura\n");
            break;
        } 
        
        if (n != sizeof(ev)) {
            fprintf(stderr, "Erro ao ler %ld bytes, o esperado era %ld\n", n, sizeof(ev));
            break;
        }

        pthread_mutex_lock(&lock);

        if (ev.type == EV_REL) {
            if (ev.code == REL_X) {
                verificar = x_ladrao + ev.value;
                    
                if(
                    //AREA 1, 2, 3, 4 - COLUNA ESQUERDA
                    (x_ladrao >= 448 - ESQ_SPRITE_LADRAO && (y_ladrao >= 0 && y_ladrao < 432) && verificar < 448 - ESQ_SPRITE_LADRAO) ||
                    
                    //PASSAGEM 1
                    ((x_ladrao >= 568 - ESQ_SPRITE_LADRAO && x_ladrao < 608) && (y_ladrao > 35 && y_ladrao < 64) && (verificar < 568 - ESQ_SPRITE_LADRAO || verificar > 587 + DIR_SPRITE_LADRAO)) ||

                    //PASSAGEM 2
                    ((x_ladrao >= 520 - ESQ_SPRITE_LADRAO && x_ladrao < 560) && (y_ladrao > 91 && y_ladrao < 120) && (verificar < 520 - ESQ_SPRITE_LADRAO || verificar > 539 + DIR_SPRITE_LADRAO)) ||

                    
                    //AREA 3 MEIO DIREITA (LADO DIREITO DO QUADRADO SUPERIOR)
                    (x_ladrao >= 592 - ESQ_SPRITE_LADRAO && (y_ladrao >= 163 && y_ladrao < 196) && verificar < 592 - ESQ_SPRITE_LADRAO) ||

                    
                    //AREA 3 MEIO DIREITA (LADO ESQUERDO DO QUADRADO)
                   ((x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 512) && (y_ladrao > 163 && y_ladrao < 264) && verificar > 491 + DIR_SPRITE_LADRAO) ||

                    
                    //AREA 3 MEIO DIREITA (LADO DIREITO DO QUADRADO INFERIOR)
                    (x_ladrao >= 592 - ESQ_SPRITE_LADRAO && (y_ladrao >= 224 && y_ladrao < 264) && verificar < 592 - ESQ_SPRITE_LADRAO) ||


                    //PASSAGEM 3
                    (x_ladrao >= 592 - ESQ_SPRITE_LADRAO && (y_ladrao > 331 && y_ladrao < 360) && verificar < 592 - ESQ_SPRITE_LADRAO) ||


                    //AREA 5 E 7 - COLUNA DIREITA
                    (x_ladrao <= 419 + DIR_SPRITE_LADRAO && (y_ladrao >= 0 && y_ladrao < 432) && verificar > 419 + DIR_SPRITE_LADRAO) ||

                    //AREA 5 E 7 E 8 - COLUNA ESQUERDA
                    (x_ladrao >= 80 - ESQ_SPRITE_LADRAO && (y_ladrao >= 0 && y_ladrao < 432) && verificar < 80 - ESQ_SPRITE_LADRAO) ||


                    //AREA 5 INFERIOR CENTRAL - DIREITA DO QUADRADO
                    (x_ladrao >= 368 - ESQ_SPRITE_LADRAO && y_ladrao > 339 && verificar < 368 - ESQ_SPRITE_LADRAO) ||

                    //AREA 5 INFERIOR CENTRAL - ESQUERDA DO QUADRADO
                    (x_ladrao <= 227 + DIR_SPRITE_LADRAO && y_ladrao > 339 && verificar > 227 + DIR_SPRITE_LADRAO) ||


                    //AREA 5 INFERIOR CENTRAL - PASSAGEM CIMA
                    ((x_ladrao >= 80 - ESQ_SPRITE_LADRAO && x_ladrao < 120) && (y_ladrao > 243 && y_ladrao < 272) && (verificar < 80 - ESQ_SPRITE_LADRAO || verificar > 99 + DIR_SPRITE_LADRAO)) ||


                    //AREA 6 ESQUERDA TOTAL
                    (x_ladrao <= 51 + DIR_SPRITE_LADRAO && (y_ladrao >= 0 && y_ladrao < 432) && verificar > 51 + DIR_SPRITE_LADRAO) ||


                    //AREA 7 CENTRO SUPERIOR - MOLDURA
                    (x_ladrao >= 144 - ESQ_SPRITE_LADRAO && (y_ladrao >= 27 && y_ladrao < 144) && verificar < 144 - ESQ_SPRITE_LADRAO) ||


                    //AREA 8 TAÇA DIREITA
                    (x_ladrao <= 115 + DIR_SPRITE_LADRAO && (y_ladrao > 27 && y_ladrao < 136) && verificar > 115 + DIR_SPRITE_LADRAO)
                    
                    ){}

                else
                    x_ladrao += ev.value;
            } 
            
            else if (ev.code == REL_Y) {
                verificar = y_ladrao + ev.value;

                if(
                    //AREA 1 CIMA DIREITA  - VERIFICA BAIXO
                    (y_ladrao <= 35 && ((x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 568 - ESQ_SPRITE_LADRAO) || (x_ladrao > 587 + DIR_SPRITE_LADRAO)) && verificar > 35) ||


                    //AREA 2 CIMA DIREITA - VERIFICA BAIXO
                    (y_ladrao <= 91 && ((x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 520 - ESQ_SPRITE_LADRAO) || (x_ladrao > 539 + DIR_SPRITE_LADRAO)) && verificar > 91) ||

                    //AREA 2 CIMA DIREITA - VERIFICA CIMA
                    (y_ladrao >= 64 && ((x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 568 - ESQ_SPRITE_LADRAO) || (x_ladrao > 587 + DIR_SPRITE_LADRAO)) && verificar < 64) ||


                    //AREA 3 MEIO DIREITA - VERIFICA CIMA
                    (y_ladrao >= 120 && ((x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 520 - ESQ_SPRITE_LADRAO) || x_ladrao > 539 + DIR_SPRITE_LADRAO) && verificar < 120) ||


                    //AREA 3 MEIO DIREITA (TOPO QUADRADO SUPERIOR) - VERIFICA BAIXO
                    (y_ladrao <= 163 && (x_ladrao > 491 + DIR_SPRITE_LADRAO && x_ladrao < 592 - ESQ_SPRITE_LADRAO) && verificar > 163) ||

                    //AREA 3 MEIO DIREITA (DIREITA DO QUADRADO SUPERIOR) - VERIFICA BAIXO
                    (y_ladrao <= 195 && x_ladrao >= 592 - ESQ_SPRITE_LADRAO && verificar > 195) ||

                    
                    //AREA 3 MEIO DIREITA - VERIFICA BAIXO
                    (y_ladrao <= 331 && (x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 592 - ESQ_SPRITE_LADRAO) && verificar > 331) ||


                    //AREA 3 MEIO DIREITA (QUADRADO INFERIOR) - VERIFICA CIMA
                    (y_ladrao >= 264 && (x_ladrao > 491 + DIR_SPRITE_LADRAO && x_ladrao < 592 - ESQ_SPRITE_LADRAO) && verificar < 264) ||

                    //AREA 3 MEIO DIREITA (DIREITA DO QUADRADO INFERIOR) - VERIFICA CIMA
                    (y_ladrao >= 224 && x_ladrao >= 592 - ESQ_SPRITE_LADRAO && verificar < 224) ||


                    //AREA 4 INFERIOR DIREITA - VERIFICA CIMA
                    (y_ladrao >= 360 && (x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 592 - ESQ_SPRITE_LADRAO) && verificar < 360) ||

                    //AREA 4 INFERIOR DIREITA - PASSAGEM - VERIFICA CIMA
                    (y_ladrao >= 432 && (x_ladrao > 419 + DIR_SPRITE_LADRAO && x_ladrao < 448 - ESQ_SPRITE_LADRAO) && verificar < 432) ||


                    //AREA 5 INFERIOR CENTRO - VERIFICA CIMA
                    (y_ladrao >= 272 && (x_ladrao > 99 + DIR_SPRITE_LADRAO && x_ladrao < 440 - ESQ_SPRITE_LADRAO) && verificar < 272) ||


                    //AREA 5 INFERIOR CENTRO - VERIFICA BAIXO (TOPO DO QUADRADO)
                    (y_ladrao <= 339 && (x_ladrao > 227 + DIR_SPRITE_LADRAO && x_ladrao < 368 - ESQ_SPRITE_LADRAO) && verificar > 339) ||


                    //AREA 5 INFERIOR CENTRO - PASSAGEM ESQUERDA - VERIFICA CIMA
                    (y_ladrao >= 432 && (x_ladrao > 51 + DIR_SPRITE_LADRAO && x_ladrao < 80 - ESQ_SPRITE_LADRAO) && verificar < 432) ||


                    //AREA 7 SUPERIOR CENTRO - VERIFICA CIMA MOLDURA
                    (y_ladrao >= 144 && (x_ladrao >= 80 - ESQ_SPRITE_LADRAO && x_ladrao < 144 - ESQ_SPRITE_LADRAO) && verificar < 144) ||

                    
                    //AREA 7 SUPERIOR CENTRO - VERIFICA BAIXO
                    (y_ladrao <= 243 && (x_ladrao > 99 + DIR_SPRITE_LADRAO && x_ladrao < 440) && verificar > 243) ||


                    //AREA 8 TAÇA - VERIFICA BAIXO
                    (y_ladrao <= 115 && (x_ladrao >= 80 - ESQ_SPRITE_LADRAO && x_ladrao < 136 - ESQ_SPRITE_LADRAO) && verificar > 115) ||

                    //AREA 8 TAÇA - PASSAGEM
                    (y_ladrao <= 27 && (x_ladrao > 115 + DIR_SPRITE_LADRAO && x_ladrao < 144 - ESQ_SPRITE_LADRAO) && verificar > 27)
                ){}

                else
                    y_ladrao += ev.value;
            }
        }
        
        //Limitar as coordenadas acumuladas
        if (x_ladrao < 0) x_ladrao = 0;
        if (x_ladrao > 619) x_ladrao = 619;
        if (y_ladrao < 0) y_ladrao = 0;
        if (y_ladrao > 459) y_ladrao = 459;

        //LADRAO
        set_sprite_wbr(1, x_ladrao, y_ladrao, 25, 15);

        pthread_mutex_unlock(&lock);
        
        if (ev.type == EV_KEY && ev.code == BTN_LEFT) {
            if (ev.value == 1) {
                pthread_mutex_lock(&lock);
                clicou = 1;
                pthread_mutex_unlock(&lock);
            } 
        }
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* movimenta_policiais_2_3_6_8(void* arg) {
    int sentido_policial_2 = SENTIDO_PARA_ESQUERDA;
    int sentido_policial_3 = SENTIDO_PARA_DIREITA;
    int sentido_policial_6 = SENTIDO_PARA_ESQUERDA;
    int sentido_policial_8 = SENTIDO_PARA_DIREITA;

    while(1){
        //7 segundos / 619 (7 000 000 dividido pelo total de pixels) -> Tempo para um pixel ir de 0 a 619
        usleep(VELOCIDADE_POLICIAIS_2_3_6_8);

        pthread_mutex_lock(&lock);
        
        //POLICIA 2
            if(sentido_policial_2 == SENTIDO_PARA_ESQUERDA){
                policia_2_x -= 1;     
                if(policia_2_x == FIM_POLICIAL_2_X){
                    sentido_policial_2 = SENTIDO_PARA_DIREITA;
                }
            }

            else if(sentido_policial_2 == SENTIDO_PARA_DIREITA){
                policia_2_x += 1;       
                if(policia_2_x == INICIO_POLICIAL_2_X){
                    sentido_policial_2 = SENTIDO_PARA_ESQUERDA;
                }
            }

        //POLICIA 3
            if(sentido_policial_3 == SENTIDO_PARA_DIREITA){
                policia_3_x += 1;     
                if(policia_3_x == FIM_POLICIAL_3_X){
                    sentido_policial_3 = SENTIDO_PARA_BAIXO;
                }
            }

            else if(sentido_policial_3 == SENTIDO_PARA_BAIXO){
                policia_3_y += 1;       
                if(policia_3_y == FIM_POLICIAL_3_Y){
                    sentido_policial_3 = SENTIDO_PARA_CIMA;
                }
            }

            else if(sentido_policial_3 == SENTIDO_PARA_CIMA){
                policia_3_y -= 1;       
                if(policia_3_y == INICIO_POLICIAL_3_Y){
                    sentido_policial_3 = SENTIDO_PARA_ESQUERDA;
                }
            }

            else if(sentido_policial_3 == SENTIDO_PARA_ESQUERDA){
                policia_3_x -= 1;       
                if(policia_3_x == INICIO_POLICIAL_3_X){
                    sentido_policial_3 = SENTIDO_PARA_DIREITA;
                }
            }

        //POLICIA 6
            if(sentido_policial_6 == SENTIDO_PARA_ESQUERDA){
                policia_6_x -= 1;     
                if(policia_6_x == FIM_POLICIAL_6_X){
                    sentido_policial_6 = SENTIDO_PARA_DIREITA;
                }
            }

            else if(sentido_policial_6 == SENTIDO_PARA_DIREITA){
                policia_6_x += 1;       
                if(policia_6_x == INICIO_POLICIAL_6_X){
                    sentido_policial_6 = SENTIDO_PARA_ESQUERDA;
                }
            }

        //POLICIA 8
            if(sentido_policial_8 == SENTIDO_PARA_DIREITA){
                policia_8_x += 1;     
                if(policia_8_x == FIM_POLICIAL_8_X){
                    sentido_policial_8 = SENTIDO_PARA_ESQUERDA;
                }
            }

            else if(sentido_policial_8 == SENTIDO_PARA_ESQUERDA){
                policia_8_x -= 1;       
                if(policia_8_x == INICIO_POLICIAL_8_X){
                    sentido_policial_8 = SENTIDO_PARA_DIREITA;
                }
            }
        
        //atualizando posições

        //POLICIA 2
        set_sprite_wbr(1, policia_2_x, policia_2_y, 30, 6);
        //POLICIA 3
        set_sprite_wbr(1, policia_3_x, policia_3_y, 30, 7);
        //POLICIA 6
        set_sprite_wbr(1, policia_6_x, policia_6_y, 30, 10);
        //POLICIA 8
        set_sprite_wbr(1, policia_8_x, policia_8_y, 30, 12);

        pthread_mutex_unlock(&lock);
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* movimenta_policiais_4_5_7(void* arg) {
    int sentido_policial_4 = SENTIDO_PARA_ESQUERDA;
    int sentido_policial_5 = SENTIDO_PARA_DIREITA;
    int sentido_policial_7 = SENTIDO_PARA_CIMA;

    while(1){
        //7 segundos / 619 (7 000 000 dividido pelo total de pixels) -> Tempo para um pixel ir de 0 a 619
        usleep(VELOCIDADE_POLICIAIS_4_5_7);

        pthread_mutex_lock(&lock);

        //POLICIA 4
            if(sentido_policial_4 == SENTIDO_PARA_ESQUERDA){
                policia_4_x -= 1;       
                if(policia_4_x == FIM_POLICIAL_4_X){
                    sentido_policial_4 = SENTIDO_PARA_DIREITA;
                }
            }

            else if(sentido_policial_4 == SENTIDO_PARA_DIREITA){
                policia_4_x += 1;     
                if(policia_4_x == INICIO_POLICIAL_4_X){
                    sentido_policial_4 = SENTIDO_PARA_ESQUERDA;
                }
            }

        //POLICIA 5
            if(sentido_policial_5 == SENTIDO_PARA_DIREITA){
                policia_5_x += 1;     
                if(policia_5_x == FIM_POLICIAL_5_X){
                    sentido_policial_5 = SENTIDO_PARA_ESQUERDA;
                }
            }

            else if(sentido_policial_5 == SENTIDO_PARA_ESQUERDA){
                policia_5_x -= 1;       
                if(policia_5_x == INICIO_POLICIAL_5_X){
                    sentido_policial_5 = SENTIDO_PARA_DIREITA;
                }
            }

        //POLICIA 7
            if(sentido_policial_7 == SENTIDO_PARA_CIMA){
                policia_7_y -= 1;       
                if(policia_7_y == FIM_POLICIAL_1_Y){
                    sentido_policial_7 = SENTIDO_PARA_ESQUERDA;
                }
            }

            else if(sentido_policial_7 == SENTIDO_PARA_ESQUERDA){
                policia_7_x -= 1;       
                if(policia_7_x == FIM_POLICIAL_7_X){
                    sentido_policial_7 = SENTIDO_PARA_DIREITA;
                }
            }

            else if(sentido_policial_7 == SENTIDO_PARA_DIREITA){
                policia_7_x += 1;     
                if(policia_7_x == INICIO_POLICIAL_7_X){
                    sentido_policial_7 = SENTIDO_PARA_BAIXO;
                }
            }

            else if(sentido_policial_7 == SENTIDO_PARA_BAIXO){
                policia_7_y += 1;       
                if(policia_7_y == INICIO_POLICIAL_7_Y){
                    sentido_policial_7 = SENTIDO_PARA_CIMA;
                }
            }
        
        //atualizando posições

        //POLICIA 4
        set_sprite_wbr(1, policia_4_x, policia_4_y, 30, 8);
        //POLICIA 5
        set_sprite_wbr(1, policia_5_x, policia_5_y, 30, 9);
        //POLICIA 7
        set_sprite_wbr(1, policia_7_x, policia_7_y, 30, 11);

        pthread_mutex_unlock(&lock);
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* movimenta_policiais_9_10(void* arg) {
    int sentido_policial_9 = SENTIDO_PARA_DIREITA;
    int sentido_policial_10 = SENTIDO_PARA_ESQUERDA;

    while(1){
        //7 segundos / 619 (7 000 000 dividido pelo total de pixels) -> Tempo para um pixel ir de 0 a 619
        usleep(VELOCIDADE_POLICIAIS_9_10);

        pthread_mutex_lock(&lock);

        //POLICIA 9
            if(sentido_policial_9 == SENTIDO_PARA_DIREITA){
                policia_9_x += 1;     
                if(policia_9_x == FIM_POLICIAL_9_X && policia_9_y == INICIO_POLICIAL_9_Y){
                    sentido_policial_9 = SENTIDO_PARA_BAIXO;
                }

                else if(policia_9_x == FIM_POLICIAL_9_X && policia_9_y == FIM_POLICIAL_9_Y){
                    sentido_policial_9 = SENTIDO_PARA_CIMA;
                }
            }

            else if(sentido_policial_9 == SENTIDO_PARA_BAIXO){
                policia_9_y += 1;       
                if(policia_9_y == FIM_POLICIAL_9_Y){
                    sentido_policial_9 = SENTIDO_PARA_ESQUERDA;
                }
            }

            else if(sentido_policial_9 == SENTIDO_PARA_ESQUERDA){
                policia_9_x -= 1;       
                if((policia_9_x == FIM_2_POLICIAL_9_X && policia_9_y == FIM_POLICIAL_9_Y) || policia_9_x == INICIO_POLICIAL_9_X && policia_9_y == INICIO_POLICIAL_9_Y){
                    sentido_policial_9 = SENTIDO_PARA_DIREITA;
                }
            }

            else if(sentido_policial_9 == SENTIDO_PARA_CIMA){
                policia_9_y -= 1;       
                if(policia_9_y == INICIO_POLICIAL_9_Y){
                    sentido_policial_9 = SENTIDO_PARA_ESQUERDA;
                }
            }

        //POLICIA 10
            if(sentido_policial_10 == SENTIDO_PARA_ESQUERDA){
                policia_10_x -= 1;       
                if(policia_10_x == FIM_POLICIAL_10_X){
                    sentido_policial_10 = SENTIDO_PARA_CIMA;
                }
            }

            else if(sentido_policial_10 == SENTIDO_PARA_CIMA){
                policia_10_y -= 1;       
                if(policia_10_y == FIM_POLICIAL_10_Y){
                    sentido_policial_10 = SENTIDO_PARA_BAIXO;
                }
            }

            else if(sentido_policial_10 == SENTIDO_PARA_BAIXO){
                policia_10_y += 1;       
                if(policia_10_y == INICIO_POLICIAL_10_Y){
                    sentido_policial_10 = SENTIDO_PARA_DIREITA;
                }
            }

            else if(sentido_policial_10 == SENTIDO_PARA_DIREITA){
                policia_10_x += 1;     
                if(policia_10_x == INICIO_POLICIAL_10_X){
                    sentido_policial_10 = SENTIDO_PARA_ESQUERDA;
                }
            }
        
        //atualizando posições

        //POLICIA 9
        set_sprite_wbr(1, policia_9_x, policia_9_y, 30, 13);
        //POLICIA 10
        set_sprite_wbr(1, policia_10_x, policia_10_y, 30, 14);

        pthread_mutex_unlock(&lock);
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* movimenta_policiais_1(void* arg) {
    int sentido_policial_1 = SENTIDO_PARA_DIREITA;

    while(1){
        //7 segundos / 619 (7 000 000 dividido pelo total de pixels) -> Tempo para um pixel ir de 0 a 619
        usleep(VELOCIDADE_POLICIAIS_1);

        pthread_mutex_lock(&lock);
        
        //POLICIA 1
            if(sentido_policial_1 == SENTIDO_PARA_DIREITA){
                policia_1_x += 1;     
                if(policia_1_x == FIM_POLICIAL_1_X){
                    sentido_policial_1 = SENTIDO_PARA_BAIXO;
                }
            }

            else if(sentido_policial_1 == SENTIDO_PARA_BAIXO){
                policia_1_y += 1;       
                if(policia_1_y == FIM_POLICIAL_1_Y){
                    sentido_policial_1 = SENTIDO_PARA_ESQUERDA;
                }
            }

            else if(sentido_policial_1 == SENTIDO_PARA_ESQUERDA){
                policia_1_x -= 1;       
                if(policia_1_x == INICIO_POLICIAL_1_X){
                    sentido_policial_1 = SENTIDO_PARA_CIMA;
                }
            }

            else if(sentido_policial_1 == SENTIDO_PARA_CIMA){
                policia_1_y -= 1;       
                if(policia_1_y == INICIO_POLICIAL_1_Y){
                    sentido_policial_1 = SENTIDO_PARA_DIREITA;
                }
            }
        
        //atualizando posições

        //POLICIA 1
        set_sprite_wbr(1, policia_1_x, policia_1_y, 30, 5);

        pthread_mutex_unlock(&lock);
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

int main() {
    pthread_t thread_id, thread_id2, thread_id3, thread_id4, thread_id5;

    //Abre arquivo de comunicação com o driver
    if (open_driver( ) == -1){
        return -1;
    }

    // Abrir o dispositivo do mouse
    fd_mouse = open(MOUSE_DEVICE, O_RDONLY);
    if (fd_mouse == -1) {
        fprintf(stderr, "Erro ao abrir o mouse\n");
        return 1;
    }

    //LADRAO
    set_sprite_wbr(1, x_ladrao, y_ladrao, 25, 15);

    //POLICIA 1
    set_sprite_wbr(1, INICIO_POLICIAL_1_X, FIM_POLICIAL_1_Y, 30, 5);
    //POLICIA 2
    set_sprite_wbr(1, INICIO_POLICIAL_2_X, INICIO_FIM_POLICIAL_2_Y, 30, 6);
    //POLICIA 3
    set_sprite_wbr(1, INICIO_POLICIAL_3_X, FIM_POLICIAL_3_Y, 30, 7);
    //POLICIA 4
    set_sprite_wbr(1, INICIO_POLICIAL_4_X, INICIO_FIM_POLICIAL_4_Y, 30, 8);
    //POLICIA 5
    set_sprite_wbr(1, INICIO_POLICIAL_5_X, INICIO_FIM_POLICIAL_5_Y, 30, 9);
    //POLICIA 6
    set_sprite_wbr(1, INICIO_POLICIAL_6_X, INICIO_FIM_POLICIAL_6_Y, 30, 10);
    //POLICIA 7
    set_sprite_wbr(1, INICIO_POLICIAL_7_X, FIM_POLICIAL_7_Y, 30, 11);
    //POLICIA 8
    set_sprite_wbr(1, INICIO_POLICIAL_8_X, INICIO_FIM_POLICIAL_8_Y, 30, 12);
    //POLICIA 9
    set_sprite_wbr(1, INICIO_POLICIAL_9_X, FIM_POLICIAL_9_Y, 30, 13);
    //POLICIA 10
    set_sprite_wbr(1, INICIO_POLICIAL_10_X, FIM_POLICIAL_10_Y, 30, 14);

    //Inicializa o mutex de LOCK
    pthread_mutex_init(&lock, NULL);
    
    if (pthread_create(&thread_id, NULL, movimenta_mouse, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_create(&thread_id2, NULL, movimenta_policiais_2_3_6_8, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_create(&thread_id3, NULL, movimenta_policiais_4_5_7, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_create(&thread_id4, NULL, movimenta_policiais_9_10, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_create(&thread_id5, NULL, movimenta_policiais_1, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }
    
    while(1){
        pthread_mutex_lock(&lock);

        if((x_ladrao >= 96 && x_ladrao < 440) && y_ladrao < 144){

            //COLISÃO COM POLICIA 1
            if (x_ladrao <= policia_1_x + 15 &&        //esquerda
                x_ladrao + 15 >= policia_1_x &&        //direita
                y_ladrao <= policia_1_y + 19 &&        //baixo
                y_ladrao + 18 >= policia_1_y) {           //cima
                
                pthread_mutex_unlock(&lock);
        
                printf("COLIDIU\n");
                break;
            }
        }

        else if(x_ladrao > 440 && y_ladrao < 120){

            //COLISÃO COM POLICIA 2
            if (x_ladrao <= policia_2_x + 15 &&        //esquerda
                x_ladrao + 15 >= policia_2_x &&        //direita
                y_ladrao <= policia_2_y + 19 &&        //baixo
                y_ladrao + 18 >= policia_2_y) {           //cima
                
                pthread_mutex_unlock(&lock);
        
                printf("COLIDIU\n");
                break;
            }
        }

        else if(x_ladrao > 440 && (y_ladrao > 96 && y_ladrao < 336)){
            
            //COLISÃO COM POLICIA 3
            if (x_ladrao <= policia_3_x + 15 &&        //esquerda
                x_ladrao + 15 >= policia_3_x &&        //direita
                y_ladrao <= policia_3_y + 19 &&        //baixo
                y_ladrao + 18 >= policia_3_y) {           //cima
                
                pthread_mutex_unlock(&lock);
        
                printf("COLIDIU\n");
                break;
            }

            //COLISÃO COM POLICIA 6 - aqui é else if
            if (x_ladrao <= policia_6_x + 15 &&        //esquerda
                x_ladrao + 15 >= policia_6_x &&        //direita
                y_ladrao <= policia_6_y + 19 &&        //baixo
                y_ladrao + 18 >= policia_6_y) {           //cima
                
                pthread_mutex_unlock(&lock);
        
                printf("COLIDIU\n");
                break;
            }
        }

        else if((x_ladrao >= 80 && x_ladrao < 440) && (y_ladrao > 120 && y_ladrao < 256)){

            //COLISÃO COM POLICIA 4
            if (x_ladrao <= policia_4_x + 15 &&        //esquerda
                x_ladrao + 15 >= policia_4_x &&        //direita
                y_ladrao <= policia_4_y + 19 &&        //baixo
                y_ladrao + 18 >= policia_4_y) {           //cima
                
                pthread_mutex_unlock(&lock);
        
                printf("COLIDIU\n");
                break;
            }

            //COLISÃO COM POLICIA 5 - aqui é else if
            if (x_ladrao <= policia_5_x + 15 &&        //esquerda
                x_ladrao + 15 >= policia_5_x &&        //direita
                y_ladrao <= policia_5_y + 19 &&        //baixo
                y_ladrao + 18 >= policia_5_y) {           //cima
                
                pthread_mutex_unlock(&lock);
        
                printf("COLIDIU\n");
                break;
            }
        }

        else if((x_ladrao >= 80 && x_ladrao < 440) && (y_ladrao > 248 && y_ladrao < 424)){

            //COLISÃO COM POLICIA 7
            if (x_ladrao <= policia_7_x + 15 &&        //esquerda
                x_ladrao + 15 >= policia_7_x &&        //direita
                y_ladrao <= policia_7_y + 19 &&        //baixo
                y_ladrao + 18 >= policia_7_y) {           //cima
                
                pthread_mutex_unlock(&lock);
        
                printf("COLIDIU\n");
                break;
            }

            //COLISÃO COM POLICIA 8 - aqui é else if
            if (x_ladrao <= policia_8_x + 15 &&        //esquerda
                x_ladrao + 15 >= policia_8_x &&        //direita
                y_ladrao <= policia_8_y + 19 &&        //baixo
                y_ladrao + 18 >= policia_8_y) {           //cima
                
                pthread_mutex_unlock(&lock);
        
                printf("COLIDIU\n");
                break;
            }
        }

        else if(x_ladrao >= 344 && y_ladrao > 32){

            //COLISÃO COM POLICIA 9
            if (x_ladrao <= policia_9_x + 15 &&        //esquerda
                x_ladrao + 15 >= policia_9_x &&        //direita
                y_ladrao <= policia_9_y + 19 &&        //baixo
                y_ladrao + 18 >= policia_9_y) {           //cima
                
                pthread_mutex_unlock(&lock);
        
                printf("COLIDIU\n");
                break;
            }
        }

        else if(x_ladrao < 288 && y_ladrao > 128){

            //COLISÃO COM POLICIA 10
            if (x_ladrao <= policia_10_x + 15 &&        //esquerda
                x_ladrao + 15 >= policia_10_x &&        //direita
                y_ladrao <= policia_10_y + 19 &&        //baixo
                y_ladrao + 18 >= policia_10_y) {           //cima
                
                pthread_mutex_unlock(&lock);
        
                printf("COLIDIU\n");
                break;
            }
        }

        if(clicou){
            pthread_mutex_unlock(&lock);
            break;
        }

        pthread_mutex_unlock(&lock);
    }

    if(pthread_cancel(thread_id) != 0){
        perror("falhou cancel\n");
        return 1;
    }

    if(pthread_cancel(thread_id2) != 0){
        perror("falhou cancel\n");
        return 1;
    }

    if(pthread_cancel(thread_id3) != 0){
        perror("falhou cancel\n");
        return 1;
    }

    if(pthread_cancel(thread_id4) != 0){
        perror("falhou cancel\n");
        return 1;
    }

    if(pthread_cancel(thread_id5) != 0){
        perror("falhou cancel\n");
        return 1;
    }

    //AGUARDA A FINALIZAÇÃO DE DETERMINADA THREAD
    if (pthread_join(thread_id, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

        //AGUARDA A FINALIZAÇÃO DE DETERMINADA THREAD
    if (pthread_join(thread_id2, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

        //AGUARDA A FINALIZAÇÃO DE DETERMINADA THREAD
    if (pthread_join(thread_id3, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    //AGUARDA A FINALIZAÇÃO DE DETERMINADA THREAD
    if (pthread_join(thread_id4, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

        //AGUARDA A FINALIZAÇÃO DE DETERMINADA THREAD
    if (pthread_join(thread_id5, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    pthread_mutex_destroy(&lock);

    // Fechar os dispositivos
    close(fd_mouse);

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
