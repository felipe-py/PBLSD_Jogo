#include "biblioteca_gpu.h"
#include "mapeamento.h"
#include "utils.h"
#include "threads.h"
#include "carrega_telas_sprites.h"

#include <stdio.h>
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

    //Inicializa o mutex padrão
    pthread_mutex_init(&lock, NULL);

    //Cria thread do botão
    pthread_t thread_botao;
    if (pthread_create(&thread_botao, NULL, botao, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    pthread_mutex_lock(&lock);
    //Exibe tela inicial
    tela_inicial();
    pthread_mutex_unlock(&lock);
        
    inicia_display();

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
        
        limpar_tela(0);

        tela_padrao();
        pthread_mutex_unlock(&lock);

        int vidas;
        int trofeu_dir, trofeu_esq;
        int win, lost;
        int colidiu;

        //JOGAR NOVAMENTE
        while (1) {
            pthread_mutex_lock(&lock);
            x_ladrao = INICIO_LADRAO_X;
            y_ladrao = INICIO_LADRAO_Y;
            set_sprite_wbr(1, x_ladrao, y_ladrao, 25, 15);
            pthread_mutex_unlock(&lock);
            
            if(cria_threads_jogo()) {
                perror("pthread_create");
                return 1;
            }

            trofeu_dir = 0, trofeu_esq = 0;
            win = 0, lost = 0;
            colidiu = 0;
            vidas = 3;

            pthread_mutex_lock(&lock);
            habilidades = 3;
            pausar = 0;
            jogando = 1;
            att_display(vidas, habilidades);
            pthread_mutex_unlock(&lock);

            //LOOP DO JOGO
            while (1) {
                //SE JOGO NÃO ESTÁ PAUSADO
                if (pausar == 0) {
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
                        if (trofeu_esq == 0 && x_ladrao < 72 && y_ladrao < 64) {
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
                        else if ((x_ladrao >= 136 && x_ladrao < 440) && y_ladrao < 128) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_1_x, policia_1_y)) {

                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 2
                        else if (x_ladrao > 440 && (y_ladrao > 40 && y_ladrao < 104)) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_2_x, policia_2_y)) {

                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 3
                        else if (x_ladrao > 440 && (y_ladrao > 104 && y_ladrao < 192)) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_3_x, policia_3_y)) {
                                    
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 6
                        else if (x_ladrao > 440 && (y_ladrao > 264 && y_ladrao < 328)) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_6_x, policia_6_y)) {
                                    
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 4 E 5
                        else if ((x_ladrao >= 80 && x_ladrao < 440) && (y_ladrao > 128 && y_ladrao < 248)) {
                            if (
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_4_x, policia_4_y) || 
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_5_x, policia_5_y)
                                ) {
                                
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 7
                        else if ((x_ladrao >= 80 && x_ladrao < 440) && (y_ladrao > 256 && y_ladrao < 368)) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_7_x, policia_7_y)) {
                                    
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 8
                        else if ((x_ladrao >= 80 && x_ladrao < 248) && (y_ladrao > 352 && y_ladrao < 416)) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_8_x, policia_8_y)) {
                                    
                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 9
                        else if (x_ladrao >= 368 && y_ladrao > 336) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_9_x, policia_9_y)) {  

                                colidiu = 1;
                            }
                        }

                        //VERIFICA COLISAO COM POLICIAL 10
                        else if (x_ladrao < 248 && y_ladrao > 168) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_10_x, policia_10_y)) {  

                                colidiu = 1;
                            }
                        }

                        pthread_mutex_unlock(&lock);
                        
                        //SE BATEU EM ALGUM POLICIAL
                        if (colidiu) {
                            colidiu = 0;
                            --vidas;

                            //GAME OVER
                            if (vidas == 0) {
                                pthread_mutex_lock(&lock);
                                set_sprite_wbr(0, 0, 0, 25, 15);
                                pthread_mutex_unlock(&lock);
                                
                                lost = 1;

                                break;
                            }

                            pthread_mutex_lock(&lock);
                            //SE AINDA TIVER VIDAS, VOLTA PARA O INÍCIO
                            x_ladrao = INICIO_LADRAO_X;
                            y_ladrao = INICIO_LADRAO_Y;
                            //LADRAO
                            set_sprite_wbr(1, x_ladrao, y_ladrao, 25, 15);    
                            pthread_mutex_unlock(&lock);

                            if(trofeu_dir || trofeu_esq){
                                trofeu_dir = 0;
                                trofeu_esq = 0;

                                pthread_mutex_lock(&lock);
                                set_sprite_wbr(1, TROFEU_ESQ_X, TROFEU_ESQ_Y, 24, 2);
                                set_sprite_wbr(1, TROFEU_DIR_X, TROFEU_DIR_Y, 24, 3);
                                pthread_mutex_unlock(&lock);
                            }
                        }

                        //Atualiza display a cada iteração
                        att_display(vidas, habilidades);
                    }
                }

                //VERIFICA SE JOGADOR QUER REINICIAR OU SAIR DO JOGO (SEMPRE)
                if (start || sair){
                    break;
                }

            } //LOOP DO JOGO

            pthread_mutex_lock(&lock);
            cancela_threads_policiais = 1;
            jogando = 0;
            att_display(vidas, habilidades);
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
                pthread_mutex_lock(&lock);
                limpar_tela(0);

                if (win) tela_win();

                else if (lost) tela_lose();
                pthread_mutex_unlock(&lock);

                //ESPERA JOGADOR ESCOLHER ENTRE JOGAR DE NOVO OU SAIR
                while (1) { 
                    if(start || sair){  
                        break;
                    }
                }

                if(start) {
                    pthread_mutex_lock(&lock);
                    limpar_tela(0);
                    tela_padrao();
                    pthread_mutex_unlock(&lock);
                }
            }
            
            //CLICOU EM SAIR
            if (sair){ 
                break;
            }

            pthread_mutex_lock(&lock);
            start = 0;
            cancela_threads_policiais = 0;
            pthread_mutex_unlock(&lock);  

        } //LOOP JOGAR NOVAMENTE

        //fecha comunicação com o mouse
        close(fd_mouse);
    }

    inicia_display();

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

    sleep(3);

    limpar_tela(1);

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
