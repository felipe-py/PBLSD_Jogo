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

    for(int i=0; i<=79; i++){
        for(int j=0; j<=59; j++){
            desabilita_bloco_background_wbm(i,j);
        }
    }

        for(int j=1; j<=31; j++){
            set_sprite_wbr(0,0,0,0,j);
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
        encerra_display();

    //Espera escolha do jogador entre jogar ou sair
    while (1) {        
        if(sair || start ){  
            break;
        } 
    }

    //Se pressionou jogar
    if (start) {
        
        pthread_mutex_lock(&lock);
        start = 0;
        pthread_mutex_unlock(&lock);

        limpar_tela(0);

        tela_padrao();
        

        //JOGAR NOVAMENTE
        while (1) {
            x_ladrao = INICIO_LADRAO_X;
            y_ladrao = INICIO_LADRAO_Y;
            set_sprite_wbr(1, x_ladrao, y_ladrao, 25, 15);

            policia_2_x = INICIO_POLICIAL_2_X;
            policia_3_x = INICIO_POLICIAL_3_X;
            policia_6_x = INICIO_POLICIAL_6_X;
            policia_8_x = INICIO_POLICIAL_8_X;

            policia_2_y = INICIO_FIM_POLICIAL_2_Y;
            policia_3_y = INICIO_POLICIAL_3_Y;
            policia_6_y = INICIO_FIM_POLICIAL_6_Y;
            policia_8_y = INICIO_FIM_POLICIAL_8_Y;
            //POLICIA 2
            set_sprite_wbr(1, policia_2_x, policia_2_y, 30, 6);
            //POLICIA 3
            set_sprite_wbr(1, policia_3_x, policia_3_y, 30, 7);
            //POLICIA 6
            set_sprite_wbr(1, policia_6_x, policia_6_y, 30, 10);
            //POLICIA 8
            set_sprite_wbr(1, policia_8_x, policia_8_y, 30, 12);

            policia_4_x = INICIO_POLICIAL_4_X;
            policia_5_x = INICIO_POLICIAL_5_X;
            policia_7_x = INICIO_POLICIAL_7_X;

            policia_4_y = INICIO_FIM_POLICIAL_4_Y;
            policia_5_y = INICIO_FIM_POLICIAL_5_Y;
            policia_7_y = INICIO_POLICIAL_7_Y;
            
            //POLICIA 4
            set_sprite_wbr(1, policia_4_x, policia_4_y, 30, 8);
            //POLICIA 5
            set_sprite_wbr(1, policia_5_x, policia_5_y, 30, 9);
            //POLICIA 7
            set_sprite_wbr(1, policia_7_x, policia_7_y, 30, 11);

            policia_9_x = INICIO_POLICIAL_9_X;
            policia_10_x = INICIO_POLICIAL_10_X;

            policia_9_y = INICIO_POLICIAL_9_Y;
            policia_10_y = INICIO_POLICIAL_10_Y;

            //POLICIA 9
            set_sprite_wbr(1, policia_9_x, policia_9_y, 30, 13);
            //POLICIA 10
            set_sprite_wbr(1, policia_10_x, policia_10_y, 30, 14);

            policia_1_x = INICIO_POLICIAL_1_X;
            policia_1_y = INICIO_POLICIAL_1_Y;

            //POLICIA 1
            set_sprite_wbr(1, policia_1_x, policia_1_y, 30, 5);

            if(cria_threads_jogo()) {
                perror("pthread_create");
                return 1;
            }

            printf("Criei threads jogo na main\n");

            int vidas = 3,
            trofeu_dir = 0, trofeu_esq = 0, 
            win = 0, lost = 0,
            colidiu = 0;


            pthread_mutex_lock(&lock);
            habilidades = 3;
            pausar = 0;
            pthread_mutex_unlock(&lock);
            
            inicia_display();

            //LOOP DO JOGO
            while (1) {
                //SE JOGO NÃO ESTÁ PAUSADO
                if (pausar == 0) {
                    //Sprite Pause
                    set_sprite_wbr(0, PAUSE_X, PAUSE_Y, 27, 4);

                    //SE NÃO ESTIVER NO MODO FURTIVO, VERIFICA COLISÕES
                    if(furtivo == 0) {
                        
                        pthread_mutex_lock(&lock);
                        //VERIFICA SE LADRAO TEM 2 TROFEUS E SAIU PELA PORTA
                        if ((trofeu_dir == 1 && trofeu_esq == 1) && x_ladrao == PORTA_X && y_ladrao == PORTA_Y) {              
                                pthread_mutex_unlock(&lock);
                                //GANHOU
                                win = 1;
                                break;
                        }

                        //VERIFICA SE LADRAO PEGOU TROFÉU ESQUERDA
                        else if (trofeu_esq == 0 && x_ladrao < 72 && y_ladrao < 64) {
                            //Colisão com troféu esquerdo
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, TROFEU_ESQ_X, TROFEU_ESQ_Y)) {
                                //DESABILITA TROFÉU ESQUERDO
                                set_sprite_wbr(0, TROFEU_ESQ_X, TROFEU_ESQ_Y, 24, 2);
                                
                                trofeu_esq = 1;
                            }
                        }
                        
                        //VERIFICA SE LADRAO PEGOU TROFÉU DIREITA
                        else if (trofeu_dir == 0 && (x_ladrao > 72 && x_ladrao < 160) && y_ladrao < 152) {
                            //Colisão com troféu direito
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, TROFEU_DIR_X, TROFEU_DIR_Y)) {
                                //DESABILITA TROFÉU DIREITO
                                set_sprite_wbr(0, TROFEU_DIR_X, TROFEU_DIR_Y, 24, 3);
                                

                                trofeu_dir = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 1
                        else if ((x_ladrao >= 96 && x_ladrao < 440) && y_ladrao < 144) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_1_x, policia_1_y)) {

                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 2
                        else if (x_ladrao > 440 && y_ladrao < 120) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_2_x, policia_2_y)) {
                                
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 3 E 6
                        else if (x_ladrao > 440 && (y_ladrao > 96 && y_ladrao < 336)) {
                            if (
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_3_x, policia_3_y) || 
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_6_x, policia_6_y)
                                ) {
                                    
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 4 E 5
                        else if ((x_ladrao >= 80 && x_ladrao < 440) && (y_ladrao > 120 && y_ladrao < 256)) {
                            if (
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_4_x, policia_4_y) || 
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_5_x, policia_5_y)
                                ) {
                                
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 7 E 8
                        else if ((x_ladrao >= 80 && x_ladrao < 440) && (y_ladrao > 248 && y_ladrao < 424)) {
                            if (
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_7_x, policia_7_y) || 
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_8_x, policia_8_y)
                                ) {
                                    
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 9
                        else if (x_ladrao >= 344 && y_ladrao > 32) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_9_x, policia_9_y)) {
                                
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 10
                        else if (x_ladrao < 288 && y_ladrao > 128) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_10_x, policia_10_y)) {
                                
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

                            if(trofeu_dir || trofeu_esq){
                                trofeu_dir = 0;
                                trofeu_esq = 0;

                                set_sprite_wbr(1, TROFEU_ESQ_X, TROFEU_ESQ_Y, 24, 2);
                                set_sprite_wbr(1, TROFEU_DIR_X, TROFEU_DIR_Y, 24, 3);
                            }

                            pthread_mutex_lock(&lock);
                            //SE AINDA TIVER VIDAS, VOLTA PARA O INÍCIO
                            x_ladrao = INICIO_LADRAO_X;
                            y_ladrao = INICIO_LADRAO_Y;
                                        //LADRAO
                            set_sprite_wbr(1, x_ladrao, y_ladrao, 25, 15);    
                            pthread_mutex_unlock(&lock);
                        }

                        //Atualiza display a cada iteração
                        att_display(vidas, habilidades);
                    }
                }

                //SE JOGO ESTÁ PAUSADO
                else
                    //Sprite Pause
                    set_sprite_wbr(1, PAUSE_X, PAUSE_Y, 27, 4);

                //VERIFICA SE JOGADOR QUER REINICIAR OU SAIR DO JOGO (SEMPRE)
                if (start || sair){
                    break;
                }
            } //LOOP DO JOGO

            pthread_mutex_lock(&lock);
            cancela_threads_policiais = 0;
            pthread_mutex_unlock(&lock);

            if(espera_cancelamento_threads_policias()){
                perror("pthread_join");
                return 1;
            }

            if(cancela_thread_mouse()){
                perror("pthread_cancel");
                return 1;
            }

            if (win || lost) {
                att_display(vidas, habilidades);
                limpar_tela(0);

                if (win) tela_win();

                else if (lost) tela_lose();

                //ESPERA JOGADOR ESCOLHER ENTRE JOGAR DE NOVO OU SAIR
                while (1) { 
                    if(start || sair){  
                        break;
                    }
                }

                if(start) { 
                    limpar_tela(0);
                    tela_padrao();
                }
            }
            
            //CLICOU EM SAIR
            if (sair){ 
                break;
            }

            pthread_mutex_lock(&lock);
            start = 0;
            cancela_threads_policiais = 1;
            pthread_mutex_unlock(&lock);     
        } //LOOP JOGAR NOVAMENTE

        //fecha comunicação com o mouse
        close(fd_mouse);
    }

    encerra_display();

    pthread_mutex_lock(&lock);
    cancela_thread_botoes = 1;
    pthread_mutex_unlock(&lock);
    
    //Aguarda cancelamento da thread do botão
    if (pthread_join(thread_botao, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    //Destróit mutex padrão
    pthread_mutex_destroy(&lock);

    if(encerra_map() == -1){
        return -1;
    }

    limpar_tela(0);

    tela_bye();

    sleep(5);

    limpar_tela(1);

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}




