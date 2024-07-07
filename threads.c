#include "threads.h"
#include "biblioteca_gpu.h"
#include "mapeamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/input.h>

int cria_threads_jogo(){
    //CRIA AS THREADS DO JOGO

    if (pthread_create(&thread_mouse, NULL, movimenta_mouse, NULL) != 0) {
        return 1;
    }

    if (pthread_create(&thread_policais_1, NULL, movimenta_policiais_1, NULL) != 0) {
        return 1;
    }

    if (pthread_create(&thread_policiais_2_3_6_8, NULL, movimenta_policiais_2_3_6_8, NULL) != 0) {
        return 1;
    }

    if (pthread_create(&thread_policiais_4_5_7, NULL, movimenta_policiais_4_5_7, NULL) != 0) {
        return 1;
    }

    if (pthread_create(&thread_policias_9_10, NULL, movimenta_policiais_9_10, NULL) != 0) {
        return 1;
    }

    return 0;
}

int cancela_threads_jogo(){
    //CANCELA AS THREADS DO JOGO

    if(pthread_cancel(thread_mouse) != 0){
        return 1;
    }

    if(pthread_cancel(thread_policais_1) != 0){
        return 1;
    }

    if(pthread_cancel(thread_policiais_2_3_6_8) != 0){
        return 1;
    }

    if(pthread_cancel(thread_policiais_4_5_7) != 0){
        return 1;
    }

    if(pthread_cancel(thread_policias_9_10) != 0){
        return 1;
    }

    return 0;
}

int espera_cancelamento_threads_jogo(){
    //AGUARDA A FINALIZAÇÃO DAS THREADS DO JOGO

    if (pthread_join(thread_mouse, NULL) != 0) {
        return 1;
    }

    if (pthread_join(thread_policais_1, NULL) != 0) {
        return 1;
    }

    if (pthread_join(thread_policiais_2_3_6_8, NULL) != 0) {
        return 1;
    }

    if (pthread_join(thread_policiais_4_5_7, NULL) != 0) {
        return 1;
    }

    if (pthread_join(thread_policias_9_10, NULL) != 0) {
        return 1;
    }

    return 0;
}

void* movimenta_mouse(void* arg) {
    ssize_t n;

    int verificar, offset_ladrao = 25;

    while(1){
        pthread_mutex_lock(&lock);
        if (pause == 0){
            pthread_mutex_unlock(&lock);
        
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
            //SE ESTIVER NO MODO FURTIVO, NÃO PRECISA LER MOVIMENTOS
            if(furtivo == 0) {
                pthread_mutex_unlock(&lock);
                
                if (ev.type == EV_REL) {
                    pthread_mutex_lock(&lock);
                    if (ev.code == REL_X) {
                        verificar = x_ladrao + ev.value;
                            
                        if (verifica_colisao_parede(x_ladrao, y_ladrao, verificar, 'x')){}

                        else
                            x_ladrao += ev.value;
                    } 
                    
                    else if (ev.code == REL_Y) {

                        verificar = y_ladrao + ev.value;

                        if (verifica_colisao_parede(x_ladrao, y_ladrao, verificar, 'y')){}

                        else
                            y_ladrao += ev.value;
                    }
                }

                //Limitar as coordenadas acumuladas
                if (x_ladrao < 0) x_ladrao = 0;
                if (x_ladrao > 619) x_ladrao = 619;
                if (y_ladrao < 0) y_ladrao = 0;
                if (y_ladrao > 459) y_ladrao = 459;
            }
            
            //LADRAO
            set_sprite_wbr(1, x_ladrao, y_ladrao, offset_ladrao, 15);
            pthread_mutex_unlock(&lock);

            //SE NÃO TIVER MAIS HABILIDADES, NÃO PRECISA VERIFICAR AÇÃO DE FURTIVIDADE
            pthread_mutex_lock(&lock);
            if (habilidades > 0) {
                pthread_mutex_unlock(&lock);
                
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
                        pthread_mutex_lock(&lock);
                        if (furtivo) {
                            habilidades -= 1;

                            furtivo = 0;
                            pthread_mutex_unlock(&lock);

                            offset_ladrao = 25;
                        }

                        else
                            pthread_mutex_unlock(&lock);
                    }
                }
            }
            pthread_mutex_unlock(&lock);
        }

        pthread_mutex_unlock(&lock);
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
        pthread_mutex_lock(&lock);
        if (pause == 0){
            pthread_mutex_unlock(&lock);

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
        pthread_mutex_lock(&lock);
        if (pause == 0) {
            pthread_mutex_unlock(&lock);

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

        pthread_mutex_unlock(&lock);
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* movimenta_policiais_9_10(void* arg) {
    int sentido_policial_9 = SENTIDO_PARA_DIREITA;
    int sentido_policial_10 = SENTIDO_PARA_ESQUERDA;

    while(1){
        pthread_mutex_lock(&lock);
        if (pause == 0){
            pthread_mutex_unlock(&lock);

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

        pthread_mutex_unlock(&lock);
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* movimenta_policiais_1(void* arg) {
    int sentido_policial_1 = SENTIDO_PARA_DIREITA;

    while(1){
        pthread_mutex_lock(&lock);
        if (pause == 0){
            pthread_mutex_unlock(&lock);

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

        pthread_mutex_unlock(&lock);
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

void* botao(void* arg) {
    int botao_clicou;
    
    while(1){
        botao_clicou = verifica_botao();

        if(botao_clicou == 7){
            pthread_mutex_lock(&lock);
            pause = 1;
            pthread_mutex_unlock(&lock);
        }

        else if(botao_clicou == 11){
            pthread_mutex_lock(&lock);
            pause = 0;
            pthread_mutex_unlock(&lock);
        }

        else if(botao_clicou == 13){
            pthread_mutex_lock(&lock);
            start = 1;
            pthread_mutex_unlock(&lock);
        }

        else if(botao_clicou == 14){
            pthread_mutex_lock(&lock);
            sair = 1;
            pthread_mutex_unlock(&lock);
        } 
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}
