#include "biblioteca_gpu.h"
#include "mapeamento.h"
#include "utils.h"
#include "threads.h"
#include "carrega_telas_sprites.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

int main() {
    //Abre arquivo de comunicação com o driver
    if (open_driver() == -1){
        return -1;
    }

    //Inicia comunicação com os periféricos da placa
    if(inicia_map() == -1){
        return -1;
    }

    //Carrega sprites do jogo na GPU
    if (carrega_sprites() == -1){
        return -1;
    }

    //Exibe tela inicial
    tela_inicial();

    //Inicializa o mutex padrão
    pthread_mutex_init(&lock, NULL);

    //Cria thread do botão
    pthread_t thread_botao;
    if (pthread_create(&thread_botao, NULL, botao, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    //Espera escolha do jogador entre jogar ou sair
    while (1) {
        pthread_mutex_lock(&lock);
        
        if(start || sair){
            pthread_mutex_unlock(&lock);
            
            break;
        }

        pthread_mutex_unlock(&lock);
    }

    pthread_mutex_lock(&lock);
    //Se pressionou jogar
    if (start) {
        start = 0;
        pthread_mutex_unlock(&lock);

        limpar_tela(0);

        tela_padrao();

        //JOGAR NOVAMENTE
        while (1) {
            //Abrir o dispositivo do mouse
            fd_mouse = open(MOUSE_DEVICE, O_RDONLY);
            if (fd_mouse == -1) {
                fprintf(stderr, "Erro ao abrir o mouse\n");
                return 1;
            }

            if(cria_threads_jogo()) {
                perror("pthread_create");
                return 1;
            }

            int vidas = 3,
            trofeu_dir = 0, trofeu_esq = 0, 
            win = 0, lost = 0,
            colidiu = 0;

            pthread_mutex_lock(&lock);
            habilidades = 3;
            pthread_mutex_unlock(&lock);

            att_display(vidas, habilidades);

            //LOOP DO JOGO
            while (1) {
                pthread_mutex_lock(&lock);

                //SE JOGO NÃO ESTÁ PAUSADO
                if (pause == 0) {
                    pthread_mutex_unlock(&lock);
                    
                    //Sprite Pause
                    set_sprite_wbr(0, PAUSE_X, PAUSE_Y, 27, 4);

                    pthread_mutex_lock(&lock);
                    //SE NÃO ESTIVER NO MODO FURTIVO, VERIFICA COLISÕES
                    if(furtivo == 0) {
                        pthread_mutex_unlock(&lock);

                        pthread_mutex_lock(&lock);
                        //VERIFICA SE LADRAO TEM 2 TROFEUS E SAIU PELA PORTA
                        if ((trofeu_dir == 1 && trofeu_esq == 1) && x_ladrao == PORTA_X && y_ladrao == PORTA_Y) {
                                pthread_mutex_unlock(&lock);

                                //GANHOU
                                win = 1;
                                break;
                        }

                        //VERIFICA SE LADRAO PEGOU TROFÉU ESQUERDA
                        if (trofeu_esq == 0 && x_ladrao < 72 && y_ladrao < 64) {
                            //Colisão com troféu esquerdo
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, TROFEU_ESQ_X, TROFEU_ESQ_Y)) {
                                pthread_mutex_unlock(&lock);

                                //DESABILITA TROFÉU ESQUERDO
                                set_sprite_wbr(1, TROFEU_ESQ_X, TROFEU_ESQ_Y, 24, 2);

                                trofeu_esq = 1;
                            }
                        }
                        
                        //VERIFICA SE LADRAO PEGOU TROFÉU DIREITA
                        else if (trofeu_dir == 0 && (x_ladrao > 72 && x_ladrao < 160) && y_ladrao < 152) {
                            //Colisão com troféu direito
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, TROFEU_DIR_X, TROFEU_DIR_Y)) {
                                pthread_mutex_unlock(&lock);

                                //DESABILITA TROFÉU DIREITO
                                set_sprite_wbr(0, TROFEU_DIR_X, TROFEU_DIR_Y, 24, 3);

                                trofeu_dir = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 1
                        else if ((x_ladrao >= 96 && x_ladrao < 440) && y_ladrao < 144) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_1_x, policia_1_y)) {
                                pthread_mutex_unlock(&lock);
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 2
                        else if (x_ladrao > 440 && y_ladrao < 120) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_2_x, policia_2_y)) {
                                pthread_mutex_unlock(&lock);
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 3 E 6
                        else if (x_ladrao > 440 && (y_ladrao > 96 && y_ladrao < 336)) {
                            if (
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_3_x, policia_3_y) || 
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_6_x, policia_6_y)
                                ) {
                                pthread_mutex_unlock(&lock);
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 4 E 5
                        else if ((x_ladrao >= 80 && x_ladrao < 440) && (y_ladrao > 120 && y_ladrao < 256)) {
                            if (
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_4_x, policia_4_y) || 
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_5_x, policia_5_y)
                                ) {
                                pthread_mutex_unlock(&lock);
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 7 E 8
                        else if ((x_ladrao >= 80 && x_ladrao < 440) && (y_ladrao > 248 && y_ladrao < 424)) {
                            if (
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_7_x, policia_7_y) || 
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_8_x, policia_8_y)
                                ) {
                                pthread_mutex_unlock(&lock);
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 9
                        else if (x_ladrao >= 344 && y_ladrao > 32) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_9_x, policia_9_y)) {
                                pthread_mutex_unlock(&lock);
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 10
                        else if (x_ladrao < 288 && y_ladrao > 128) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_10_x, policia_10_y)) {
                                pthread_mutex_unlock(&lock);
                                colidiu = 1;
                            }
                        }

                        pthread_mutex_unlock(&lock);

                        //SE BATEU EM ALGUM POLICIAL
                        if (colidiu) {
                            vidas -= 1;

                            //GAME OVER
                            if (vidas == 0) {
                                lost = 1;

                                break;
                            }

                            colidiu = 0;

                            //SE AINDA TIVER VIDAS, VOLTA PARA O INÍCIO
                            pthread_mutex_lock(&lock);
                            x_ladrao = INICIO_LADRAO_X;
                            y_ladrao = INICIO_LADRAO_Y;
                            pthread_mutex_unlock(&lock);
                        }

                        //Atualiza display a cada iteração
                        att_display(vidas, habilidades);
                    }

                    pthread_mutex_unlock(&lock);
                }

                pthread_mutex_unlock(&lock);

                //SE JOGO ESTÁ PAUSADO
                else
                    //Sprite Pause
                    set_sprite_wbr(1, PAUSE_X, PAUSE_Y, 27, 4);

                pthread_mutex_lock(&lock);     
                //VERIFICA SE JOGADOR QUER REINICIAR OU SAIR DO JOGO (SEMPRE)
                if (start || sair){
                    pthread_mutex_unlock(&lock);

                    break;
                }

                pthread_mutex_unlock(&lock);

            } //LOOP DO JOGO

            if(cancela_threads_jogo()){
                perror("falhou cancel\n");
                return 1;
            }

            if(espera_cancelamento_threads_jogo()){
                perror("pthread_join");
                return 1;
            }

            //fecha comunicação com o mouse
            close(fd_mouse);

            if (win || lost) {
                limpar_tela(0);

                if (win) tela_win();

                else if (lost) tela_lose();

                //ESPERA JOGADOR ESCOLHER ENTRE JOGAR DE NOVO OU SAIR
                while (1) {
                    pthread_mutex_lock(&lock);
                    
                    if(start || sair){
                        pthread_mutex_unlock(&lock);
                        
                        break;
                    }

                    pthread_mutex_unlock(&lock);
                }

                pthread_mutex_lock(&lock);
                if(start) {
                    pthread_mutex_unlock(&lock);

                    limpar_tela(0);
                    tela_padrao();
                }
                pthread_mutex_unlock(&lock);
            }

            //CLICOU EM SAIR
            pthread_mutex_lock(&lock);
            if (sair) break;
            pthread_mutex_unlock(&lock);

            pthread_mutex_lock(&lock);
            start = 0;
            pthread_mutex_unlock(&lock);

        } //LOOP JOGAR NOVAMENTE
    }

    pthread_mutex_unlock(&lock);

    limpar_tela(0);

    tela_bye();

    sleep(5);

    limpar_tela(1);

    //Cancela thread do botão
    if(pthread_cancel(thread_botao) != 0){
        perror("falhou cancel\n");
        return 1;
    }

    //Aguarda cancelamento da thread do botão
    if (pthread_join(thread_botao, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    //Destróit mutex padrão
    pthread_mutex_destroy(&lock);

    //Encerra comunicação com os periféricos da placa
    if(encerra_map() == -1){
        return -1;
    }

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}