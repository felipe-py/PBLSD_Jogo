#include "threads.h"
#include "biblioteca_gpu.h"
#include "mapeamento.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/input.h>

int fd_mouse;
struct input_event ev;

pthread_mutex_t lock;

pthread_t thread_mouse, thread_policais_1_2_3, thread_policiais_4_5_6, thread_policiais_7_8_9_10;

volatile int x_ladrao;
volatile int y_ladrao;

volatile int policia_1_x;
volatile int policia_2_x;
volatile int policia_3_x;
volatile int policia_4_x;
volatile int policia_5_x;
volatile int policia_6_x;
volatile int policia_7_x;
volatile int policia_8_x;
volatile int policia_9_x;
volatile int policia_10_x;

volatile int policia_1_y;
volatile int policia_2_y;
volatile int policia_3_y;
volatile int policia_4_y;
volatile int policia_5_y;
volatile int policia_6_y;
volatile int policia_7_y;
volatile int policia_8_y;
volatile int policia_9_y;   
volatile int policia_10_y;

volatile int cancela_threads_policiais = 0;
volatile int cancela_thread_botoes = 0;

volatile int pausar = 0;
volatile int start = 0;
volatile int sair = 0;

volatile int jogando = 0;

volatile int habilidades = 0;
volatile int furtivo = 0;

void inicia_ladrao(){
    x_ladrao = INICIO_LADRAO_X;
    y_ladrao = INICIO_LADRAO_Y;
    set_sprite_wbr(1, x_ladrao, y_ladrao, 25, 15);
}

int cria_threads_jogo(){
    //CRIA AS THREADS DO JOGO
    if (pthread_create(&thread_mouse, NULL, movimenta_mouse, NULL) != 0) {
        return 1;
    }

    if (pthread_create(&thread_policais_1_2_3, NULL, movimenta_policiais_1_2_3, NULL) != 0) {
        return 1;
    }

    if (pthread_create(&thread_policiais_4_5_6, NULL, movimenta_policiais_4_5_6, NULL) != 0) {
        return 1;
    }

    if (pthread_create(&thread_policiais_7_8_9_10, NULL, movimenta_policiais_7_8_9_10, NULL) != 0) {
        return 1;
    }

    return 0;
}

int cancela_thread_mouse(){
    if(pthread_cancel(thread_mouse) != 0){
        return 1;
    }

    return 0;
}

int espera_cancelamento_threads_policias(){
    //AGUARDA A FINALIZAÇÃO DAS THREADS DO JOGO

    if (pthread_join(thread_policais_1_2_3, NULL) != 0) {
        return 1;
    }

    if (pthread_join(thread_policiais_4_5_6, NULL) != 0) {
        return 1;
    }

    if (pthread_join(thread_policiais_7_8_9_10, NULL) != 0) {
        return 1;
    }

    return 0;
}

void* movimenta_mouse(void* arg) {
    ssize_t n;

    int verificar, offset_ladrao = 25;

    //Abrir o dispositivo do mouse
    fd_mouse = open(MOUSE_DEVICE, O_RDONLY);
    if (fd_mouse == -1) {
        fprintf(stderr, "Erro ao abrir o mouse\n");
        return 1;
    }

    while(1){
        if (pausar == 0){
            n = read(fd_mouse, &ev, sizeof(ev));
                
            if (n == (ssize_t)-1) {
                fprintf(stderr, "Erro de leitura\n");
                return -1;
            } 
            
            if (n != sizeof(ev)) {
                fprintf(stderr, "Erro ao ler %ld bytes, o esperado era %ld\n", n, sizeof(ev));
                return -1;
            }
            
            //SE ESTIVER NO MODO FURTIVO, NÃO PRECISA LER MOVIMENTOS
            if(furtivo == 0) {
                if (ev.type == EV_REL) {
                    if (ev.code == REL_X) {
                        verificar = x_ladrao + ev.value;
                            
                        if (verifica_colisao_parede(x_ladrao, y_ladrao, verificar, 'x')){}

                        else x_ladrao += ev.value;
                    } 
                    
                    else if (ev.code == REL_Y) {
                        verificar = y_ladrao + ev.value;

                        if (verifica_colisao_parede(x_ladrao, y_ladrao, verificar, 'y')){}

                        else y_ladrao += ev.value;
                    }
                }
     
                //Limitar as coordenadas acumuladas
                if (x_ladrao < 0) x_ladrao = 0;
                if (x_ladrao > 619) x_ladrao = 619;
                if (y_ladrao < 0) y_ladrao = 0;
                if (y_ladrao > 459) y_ladrao = 459;  
            }

            //SE NÃO TIVER MAIS HABILIDADES, NÃO PRECISA VERIFICAR AÇÃO DE FURTIVIDADE
            if (habilidades > 0) {
                if (ev.type == EV_KEY && ev.code == BTN_LEFT) {
                    //SE BOTÃO ESQUERDO TA SENDO PRESSIONADO, MODO FURTIVO ON
                    if(ev.value == 1) {
                        pthread_mutex_lock(&lock);
                        furtivo = 1;
                        pthread_mutex_unlock(&lock);
                    
                        offset_ladrao = 29;
                    }

                    //SE BOTÃO ESQUERDO TA SOLTO, PORÉM ESTAVA MODO FURTIVO ON, HABILIDADE É CONTADA E FURTIVIDADE DESATIVADA
                    else if (ev.value == 0) {
                        if (furtivo) {
                            pthread_mutex_lock(&lock);
                            --habilidades;

                            furtivo = 0;
                            pthread_mutex_unlock(&lock);

                            offset_ladrao = 25;
                        }
                    }
                }
            }

            pthread_mutex_lock(&lock);

            //LADRAO
            set_sprite_wbr(1, x_ladrao, y_ladrao, offset_ladrao, 15);    

            pthread_mutex_unlock(&lock); 
        }
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* movimenta_policiais_1_2_3(void* arg) {
    pthread_mutex_lock(&lock);
    policia_1_x = INICIO_POLICIAL_1_X;
    policia_2_x = INICIO_POLICIAL_2_X;
    policia_3_x = INICIO_POLICIAL_3_X;

    policia_1_y = INICIO_POLICIAL_1_Y;
    policia_2_y = INICIO_FIM_POLICIAL_2_Y;
    policia_3_y = INICIO_POLICIAL_3_Y;

    //POLICIA 1
    set_sprite_wbr(1, policia_1_x, policia_1_y, 30, 5);
    //POLICIA 2
    set_sprite_wbr(1, policia_2_x, policia_2_y, 30, 6);
    //POLICIA 3
    set_sprite_wbr(1, policia_3_x, policia_3_y, 30, 7);
    pthread_mutex_unlock(&lock);

    int sentido_policial_1 = SENTIDO_PARA_DIREITA;
    int sentido_policial_2 = SENTIDO_PARA_ESQUERDA;
    int sentido_policial_3 = SENTIDO_PARA_DIREITA;

    while(cancela_threads_policiais == 0){
        if (pausar == 0){

            usleep(VELOCIDADE_POLICIAIS);
            
            //atualizando posições

            //POLICIA 1
                if(sentido_policial_1 == SENTIDO_PARA_DIREITA){
                    policia_1_x += DESLOCAMENTO_POLICIAL_1;

                    if(policia_1_x >= FIM_POLICIAL_1_X){
                        policia_1_x = FIM_POLICIAL_1_X;
                        sentido_policial_1 = SENTIDO_PARA_BAIXO;
                    }
                }

                else if(sentido_policial_1 == SENTIDO_PARA_BAIXO){
                    policia_1_y += DESLOCAMENTO_POLICIAL_1; 

                    if(policia_1_y >= FIM_POLICIAL_1_Y){
                        policia_1_y = FIM_POLICIAL_1_Y;
                        sentido_policial_1 = SENTIDO_PARA_ESQUERDA;
                    }
                }

                else if(sentido_policial_1 == SENTIDO_PARA_ESQUERDA){
                    policia_1_x -= DESLOCAMENTO_POLICIAL_1; 

                    if(policia_1_x <= INICIO_POLICIAL_1_X){
                        policia_1_x = INICIO_POLICIAL_1_X;
                        sentido_policial_1 = SENTIDO_PARA_CIMA;
                    }
                }

                else if(sentido_policial_1 == SENTIDO_PARA_CIMA){
                    policia_1_y -= DESLOCAMENTO_POLICIAL_1; 

                    if(policia_1_y <= INICIO_POLICIAL_1_Y){
                        policia_1_y = INICIO_POLICIAL_1_Y;
                        sentido_policial_1 = SENTIDO_PARA_DIREITA;
                    }
                }
            
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
            
            pthread_mutex_lock(&lock);

            //POLICIA 1
            set_sprite_wbr(1, policia_1_x, policia_1_y, 30, 5);

            //POLICIA 2
            set_sprite_wbr(1, policia_2_x, policia_2_y, 30, 6);

            //POLICIA 3
            set_sprite_wbr(1, policia_3_x, policia_3_y, 30, 7);

            pthread_mutex_unlock(&lock);
        }
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* movimenta_policiais_4_5_6(void* arg) {
    pthread_mutex_lock(&lock);
    policia_4_x = INICIO_POLICIAL_4_X;
    policia_5_x = INICIO_POLICIAL_5_X;
    policia_6_x = INICIO_POLICIAL_6_X;

    policia_4_y = INICIO_FIM_POLICIAL_4_Y;
    policia_5_y = INICIO_FIM_POLICIAL_5_Y;
    policia_6_y = INICIO_FIM_POLICIAL_6_Y;

    //POLICIA 4
    set_sprite_wbr(1, policia_4_x, policia_4_y, 30, 8);
    //POLICIA 5
    set_sprite_wbr(1, policia_5_x, policia_5_y, 30, 9);
    //POLICIA 6
    set_sprite_wbr(1, policia_6_x, policia_6_y, 30, 10);
    pthread_mutex_unlock(&lock);

    int sentido_policial_4 = SENTIDO_PARA_ESQUERDA;
    int sentido_policial_5 = SENTIDO_PARA_DIREITA;
    int sentido_policial_6 = SENTIDO_PARA_ESQUERDA;

    while(cancela_threads_policiais == 0){
        if (pausar == 0){

            usleep(VELOCIDADE_POLICIAIS);
            
            //atualizando posições

            //POLICIA 4
                if(sentido_policial_4 == SENTIDO_PARA_ESQUERDA){
                    policia_4_x -= DESLOCAMENTO_POLICIAL_4;  

                    if(policia_4_x <= FIM_POLICIAL_4_X){
                        policia_4_x = FIM_POLICIAL_4_X;
                        sentido_policial_4 = SENTIDO_PARA_DIREITA;
                    }
                }

                else if(sentido_policial_4 == SENTIDO_PARA_DIREITA){
                    policia_4_x += DESLOCAMENTO_POLICIAL_4; 

                    if(policia_4_x >= INICIO_POLICIAL_4_X){
                        policia_4_x = INICIO_POLICIAL_4_X;
                        sentido_policial_4 = SENTIDO_PARA_ESQUERDA;
                    }
                }

            //POLICIA 5
                if(sentido_policial_5 == SENTIDO_PARA_DIREITA){
                    policia_5_x += DESLOCAMENTO_POLICIAL_5;  

                    if(policia_5_x >= FIM_POLICIAL_5_X){
                        policia_5_x = FIM_POLICIAL_5_X;
                        sentido_policial_5 = SENTIDO_PARA_ESQUERDA;
                    }
                }

                else if(sentido_policial_5 == SENTIDO_PARA_ESQUERDA){
                    policia_5_x -= DESLOCAMENTO_POLICIAL_5;   

                    if(policia_5_x <= INICIO_POLICIAL_5_X){
                        policia_5_x = INICIO_POLICIAL_5_X;
                        sentido_policial_5 = SENTIDO_PARA_DIREITA;
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

            pthread_mutex_lock(&lock);

            //POLICIA 4
            set_sprite_wbr(1, policia_4_x, policia_4_y, 30, 8);

            //POLICIA 5
            set_sprite_wbr(1, policia_5_x, policia_5_y, 30, 9);

            //POLICIA 6
            set_sprite_wbr(1, policia_6_x, policia_6_y, 30, 10);
            
            pthread_mutex_unlock(&lock);
        }
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* movimenta_policiais_7_8_9_10(void* arg) {
    pthread_mutex_lock(&lock);
    policia_7_x = INICIO_POLICIAL_7_X;
    policia_8_x = INICIO_POLICIAL_8_X;
    policia_9_x = INICIO_POLICIAL_9_X;
    policia_10_x = INICIO_POLICIAL_10_X;

    policia_7_y = INICIO_POLICIAL_7_Y;
    policia_8_y = INICIO_FIM_POLICIAL_8_Y;
    policia_9_y = INICIO_POLICIAL_9_Y;
    policia_10_y = INICIO_POLICIAL_10_Y;
    
    //POLICIA 7
    set_sprite_wbr(1, policia_7_x, policia_7_y, 30, 11);
    //POLICIA 8
    set_sprite_wbr(1, policia_8_x, policia_8_y, 30, 12);
    //POLICIA 9
    set_sprite_wbr(1, policia_9_x, policia_9_y, 30, 13);
    //POLICIA 10
    set_sprite_wbr(1, policia_10_x, policia_10_y, 30, 14);
    pthread_mutex_unlock(&lock);

    int sentido_policial_7 = SENTIDO_PARA_CIMA;
    int sentido_policial_8 = SENTIDO_PARA_DIREITA;
    int sentido_policial_9 = SENTIDO_PARA_DIREITA;
    int sentido_policial_10 = SENTIDO_PARA_ESQUERDA;

    while(cancela_threads_policiais == 0){
        if (pausar == 0) {

            usleep(VELOCIDADE_POLICIAIS);

            //atualizando posições

            //POLICIA 7
                if(sentido_policial_7 == SENTIDO_PARA_CIMA){
                    policia_7_y -= DESLOCAMENTO_POLICIAL_7; 

                    if(policia_7_y <= FIM_POLICIAL_7_Y){
                        policia_7_y = FIM_POLICIAL_7_Y;
                        sentido_policial_7 = SENTIDO_PARA_ESQUERDA;
                    }
                }

                else if(sentido_policial_7 == SENTIDO_PARA_ESQUERDA){
                    policia_7_x -= DESLOCAMENTO_POLICIAL_7;  

                    if(policia_7_x <= FIM_POLICIAL_7_X){
                        policia_7_x = FIM_POLICIAL_7_X;
                        sentido_policial_7 = SENTIDO_PARA_DIREITA;
                    }
                }

                else if(sentido_policial_7 == SENTIDO_PARA_DIREITA){
                    policia_7_x += DESLOCAMENTO_POLICIAL_7;  

                    if(policia_7_x >= INICIO_POLICIAL_7_X){
                        policia_7_x = INICIO_POLICIAL_7_X;
                        sentido_policial_7 = SENTIDO_PARA_BAIXO;
                    }
                }

                else if(sentido_policial_7 == SENTIDO_PARA_BAIXO){
                    policia_7_y += DESLOCAMENTO_POLICIAL_7;  

                    if(policia_7_y >= INICIO_POLICIAL_7_Y){
                        policia_7_y = INICIO_POLICIAL_7_Y;
                        sentido_policial_7 = SENTIDO_PARA_CIMA;
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
            
             //POLICIA 9
                if(sentido_policial_9 == SENTIDO_PARA_DIREITA){
                    policia_9_x += DESLOCAMENTO_POLICIAL_9; 

                    if(policia_9_x >= FIM_POLICIAL_9_X && policia_9_y == INICIO_POLICIAL_9_Y){
                        policia_9_x = FIM_POLICIAL_9_X;
                        sentido_policial_9 = SENTIDO_PARA_BAIXO;
                    }

                    else if(policia_9_x >= FIM_POLICIAL_9_X && policia_9_y == FIM_POLICIAL_9_Y){
                        policia_9_x = FIM_POLICIAL_9_X;
                        sentido_policial_9 = SENTIDO_PARA_CIMA;
                    }
                }

                else if(sentido_policial_9 == SENTIDO_PARA_BAIXO){
                    policia_9_y += DESLOCAMENTO_POLICIAL_9;    

                    if(policia_9_y >= FIM_POLICIAL_9_Y){
                        policia_9_y = FIM_POLICIAL_9_Y;
                        sentido_policial_9 = SENTIDO_PARA_ESQUERDA;
                    }
                }

                else if(sentido_policial_9 == SENTIDO_PARA_ESQUERDA){
                    policia_9_x -= DESLOCAMENTO_POLICIAL_9;  

                    if(policia_9_x <= FIM_2_POLICIAL_9_X && policia_9_y == FIM_POLICIAL_9_Y){
                        policia_9_x = FIM_2_POLICIAL_9_X;
                        sentido_policial_9 = SENTIDO_PARA_DIREITA;
                    }

                    else if (policia_9_x <= INICIO_POLICIAL_9_X && policia_9_y == INICIO_POLICIAL_9_Y){
                        policia_9_x = INICIO_POLICIAL_9_X;
                        sentido_policial_9 = SENTIDO_PARA_DIREITA;
                    }
                }

                else if(sentido_policial_9 == SENTIDO_PARA_CIMA){
                    policia_9_y -= DESLOCAMENTO_POLICIAL_9;  

                    if(policia_9_y <= INICIO_POLICIAL_9_Y){
                        policia_9_y = INICIO_POLICIAL_9_Y;
                        sentido_policial_9 = SENTIDO_PARA_ESQUERDA;
                    }
                }

            //POLICIA 10
                if(sentido_policial_10 == SENTIDO_PARA_ESQUERDA){
                    policia_10_x -= DESLOCAMENTO_POLICIAL_10;     

                    if(policia_10_x <= FIM_POLICIAL_10_X){
                        policia_10_x = FIM_POLICIAL_10_X;
                        sentido_policial_10 = SENTIDO_PARA_CIMA;
                    }
                }

                else if(sentido_policial_10 == SENTIDO_PARA_CIMA){
                    policia_10_y -= DESLOCAMENTO_POLICIAL_10;     

                    if(policia_10_y <= FIM_POLICIAL_10_Y){
                        policia_10_y = FIM_POLICIAL_10_Y;
                        sentido_policial_10 = SENTIDO_PARA_BAIXO;
                    }
                }

                else if(sentido_policial_10 == SENTIDO_PARA_BAIXO){
                    policia_10_y += DESLOCAMENTO_POLICIAL_10;       

                    if(policia_10_y >= INICIO_POLICIAL_10_Y){
                        policia_10_y = INICIO_POLICIAL_10_Y;
                        sentido_policial_10 = SENTIDO_PARA_DIREITA;
                    }
                }

                else if(sentido_policial_10 == SENTIDO_PARA_DIREITA){
                    policia_10_x += DESLOCAMENTO_POLICIAL_10;     

                    if(policia_10_x >= INICIO_POLICIAL_10_X){
                        policia_10_x = INICIO_POLICIAL_10_X;
                        sentido_policial_10 = SENTIDO_PARA_ESQUERDA;
                    }
                }
            
            pthread_mutex_lock(&lock);

            //POLICIA 7
            set_sprite_wbr(1, policia_7_x, policia_7_y, 30, 11);

            //POLICIA 8
            set_sprite_wbr(1, policia_8_x, policia_8_y, 30, 12);

            //POLICIA 9
            set_sprite_wbr(1, policia_9_x, policia_9_y, 30, 13);

            //POLICIA 10
            set_sprite_wbr(1, policia_10_x, policia_10_y, 30, 14);

            pthread_mutex_unlock(&lock);
        }
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* botao(void* arg) {
    int botao_clicou;

    int clicou_start = 0;
    int clicou_pause = 0;
    int clicou_despause = 0;
    int clicou_sair = 0;
    
    while(1){
        botao_clicou = verifica_botao();

        //botão 3 - pause
        if(clicou_pause == 1 && botao_clicou != 7){
            clicou_pause = 0;
        }

        //botão 2 - despause
        if(clicou_despause == 1 && botao_clicou != 11){
            clicou_despause = 0;
        }

        //botão 1 - jogar
        if(clicou_start == 1 && botao_clicou != 13){
            clicou_start = 0;
        }

        //botão 0 - sair
        if(clicou_sair == 1 && botao_clicou != 14){
            clicou_sair = 0;
        }

        //BOTAO 3 - PAUSE
        if(botao_clicou == 7){
            if(clicou_pause == 0){
                clicou_pause = 1;
                
                pthread_mutex_lock(&lock);
                if(jogando){
                    pausar = 1;
                    set_sprite_wbr(1, PAUSE_X, PAUSE_Y, 27, 4);
                }
                pthread_mutex_unlock(&lock);
            }
        }

        //BOTAO 2 - DESPAUSE
        else if(botao_clicou == 11){
            if(clicou_despause == 0){
                clicou_despause = 1;

                pthread_mutex_lock(&lock);
                if(jogando){
                    pausar = 0;
                    set_sprite_wbr(0, PAUSE_X, PAUSE_Y, 27, 4);
                }
                pthread_mutex_unlock(&lock);
            }
        }

        //BOTAO 1 - INICIAR JOGO OU JOGAR NOVAMENTE
        else if(botao_clicou == 13){
            if(clicou_start == 0){
                clicou_start = 1;

                pthread_mutex_lock(&lock);
                start = 1;
                pthread_mutex_unlock(&lock);
            }
        }

        //BOTAO 0 - SAIR
        else if(botao_clicou == 14){
            if(clicou_sair == 0){
                clicou_sair = 1;

                pthread_mutex_lock(&lock);
                sair = 1;
                pthread_mutex_unlock(&lock);
            }
        }

        if(cancela_thread_botoes){
            break;
        }
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}
