#include "biblioteca_gpu.h"
#include "mapeamento.h"
#include "utils.h"
#include "threads.h"
#include "carrega_telas_sprites.h"

int main() {
    /* Abre arquivo de comunicação com o driver */
    if (open_driver() == -1) {
        return -1;
    }

    /* Inicia comunicação com os periféricos da placa */
    if (inicia_map() == -1) {
        return -1;
    }

    /* Carrega sprites do jogo na GPU */
    if (carrega_sprites() == -1) {
        return -1;
    }

    /* Inicializa o mutex */
    pthread_mutex_init(&lock, NULL);

    /* Cria thread do botão */
    pthread_t thread_botao;
    if (pthread_create(&thread_botao, NULL, botao, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    /* Exibe tela inicial */
    pthread_mutex_lock(&lock);
    tela_inicial();
    pthread_mutex_unlock(&lock);
    
    /* Inicializa display de 7 segmentos com caracteres padronizados */
    inicia_display();

    /* Espera escolha do jogador entre jogar ou sair */
    while (1) {        
        if (sair || start) {  
            break;
        } 
    }

    /* Se pressionou jogar */
    if (start) {
        pthread_mutex_lock(&lock);
        start = 0;
        
        limpar_tela(0);

        tela_padrao();
        pthread_mutex_unlock(&lock);

        int vidas;
        int trofeu_dir, trofeu_esq;
        int win, lose;
        int colidiu;

        /* JOGAR NOVAMENTE */
        while (1) {
            /* Seta posição inicial do jogador (ladrão) */
            pthread_mutex_lock(&lock);
            inicia_ladrao();
            pthread_mutex_unlock(&lock);
            
            /* Inicializa threads dos policiais e mouse */
            if (cria_threads_jogo()) {
                perror("pthread_create");
                return 1;
            }

            /* Inicializa informações do jogo */
            trofeu_dir = 0, trofeu_esq = 0;
            win = 0, lose = 0;
            colidiu = 0;
            vidas = 3;

            pthread_mutex_lock(&lock);
            habilidades = 3;
            
            /* Sinaliza funcionamento dos botões de pause e despause */
            jogando = 1;
            att_display(vidas, habilidades);
            pthread_mutex_unlock(&lock);

            /* LOOP DO JOGO */
            while (1) {

                /* SE JOGO NÃO ESTÁ PAUSADO, COLISÕES SÃO VERIFICADAS */
                if (pausar == 0) {
                    
                    /* SE NÃO ESTIVER NO MODO FURTIVO, COLISÕES SÃO VERIFICADAS */
                    if (furtivo == 0) {
                        pthread_mutex_lock(&lock);
                        /* VERIFICA SE LADRAO TEM 2 TROFÉUS E SAIU PELA PORTA - Condição de vitória */
                        if ((trofeu_dir == 1 && trofeu_esq == 1) && x_ladrao == PORTA_X && y_ladrao == PORTA_Y) {              
                                pthread_mutex_unlock(&lock);
                                
                                /* GANHOU */
                                win = 1;
                                break;
                        }

                        /* VERIFICA SE LADRAO PEGOU TROFÉU ESQUERDA */
                        if (trofeu_esq == 0 && x_ladrao < 72 && y_ladrao < 64) {  
                            /* Colisão com troféu esquerdo */
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, TROFEU_ESQ_X, TROFEU_ESQ_Y)) {
                                /* DESABILITA TROFÉU ESQUERDO E CONTABILIZA */
                                set_sprite_wbr(0, TROFEU_ESQ_X, TROFEU_ESQ_Y, 24, 2);
                                
                                trofeu_esq = 1;
                            }
                        }
                        
                        /* VERIFICA SE LADRAO PEGOU TROFÉU DIREITA */
                        else if (trofeu_dir == 0 && (x_ladrao > 72 && x_ladrao < 160) && y_ladrao < 152) {
                            /* Colisão com troféu direito */
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, TROFEU_DIR_X, TROFEU_DIR_Y)) {
                                /* DESABILITA TROFÉU DIREITO E CONTABILIZA */
                                set_sprite_wbr(0, TROFEU_DIR_X, TROFEU_DIR_Y, 24, 3);
                                
                                trofeu_dir = 1;
                            }
                        }

                        /* VERIFICA COLISAO COM POLICIAL 1 */
                        else if ((x_ladrao >= 136 && x_ladrao < 440) && y_ladrao < 128) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_1_x, policia_1_y)) {

                                colidiu = 1;
                            }
                        }

                        /* VERIFICA COLISAO COM POLICIAL 2 */
                        else if (x_ladrao > 440 && (y_ladrao > 40 && y_ladrao < 104)) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_2_x, policia_2_y)) {

                                colidiu = 1;
                            }
                        }

                        /* VERIFICA COLISAO COM POLICIAL 3 */
                        else if (x_ladrao > 440 && (y_ladrao > 104 && y_ladrao < 192)) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_3_x, policia_3_y)) {
                                    
                                colidiu = 1;
                            }
                        }

                        /* VERIFICA COLISAO COM POLICIAL 6 */
                        else if (x_ladrao > 440 && (y_ladrao > 264 && y_ladrao < 328)) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_6_x, policia_6_y)) {
                                    
                                colidiu = 1;
                            }
                        }

                        /* VERIFICA COLISAO COM POLICIAL 4 E 5 */
                        else if ((x_ladrao >= 80 && x_ladrao < 440) && (y_ladrao > 128 && y_ladrao < 248)) {
                            if (
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_4_x, policia_4_y) || 
                                verifica_colisao_policia(x_ladrao, y_ladrao, policia_5_x, policia_5_y)
                                ) {
                                
                                colidiu = 1;
                            }
                        }

                        /* VERIFICA COLISAO COM POLICIAL 7 */
                        else if ((x_ladrao >= 80 && x_ladrao < 440) && (y_ladrao > 256 && y_ladrao < 368)) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_7_x, policia_7_y)) {
                                    
                                colidiu = 1;
                            }
                        }

                        /* VERIFICA COLISAO COM POLICIAL 8 */
                        else if ((x_ladrao >= 80 && x_ladrao < 248) && (y_ladrao > 352 && y_ladrao < 416)) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_8_x, policia_8_y)) {
                                    
                                colidiu = 1;
                            }
                        }

                        /* VERIFICA COLISAO COM POLICIAL 9 */
                        else if (x_ladrao >= 368 && y_ladrao > 336) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_9_x, policia_9_y)) {  

                                colidiu = 1;
                            }
                        }

                        /* VERIFICA COLISAO COM POLICIAL 10 */
                        else if (x_ladrao < 248 && y_ladrao > 168) {
                            if (verifica_colisao_policia(x_ladrao, y_ladrao, policia_10_x, policia_10_y)) {  

                                colidiu = 1;
                            }
                        }

                        pthread_mutex_unlock(&lock);
                        
                        /* SE COLIDIU COM ALGUM POLICIAL, PERDE VIDA */
                        if (colidiu) {
                            colidiu = 0;
                            --vidas;

                            /* SE ACABOU AS VIDAS, GAME OVER */
                            if (vidas == 0) {
                                pthread_mutex_lock(&lock);
                                set_sprite_wbr(0, 0, 0, 25, 15);
                                pthread_mutex_unlock(&lock);
                                
                                /* PERDEU */
                                lose = 1;

                                break;
                            }

                            /* SE AINDA TEM VIDAS, RESETA POSIÇÃO INICIAL DO JOGADOR */
                            pthread_mutex_lock(&lock);
                            inicia_ladrao();
                            pthread_mutex_unlock(&lock);

                            /* SE JOGADOR TIVER PEGO ALGUM TROFÉU, O TROFÉU É DEVOLVIDO */
                            if (trofeu_dir || trofeu_esq) {
                                trofeu_dir = 0;
                                trofeu_esq = 0;

                                pthread_mutex_lock(&lock);
                                set_sprite_wbr(1, TROFEU_ESQ_X, TROFEU_ESQ_Y, 24, 2);
                                set_sprite_wbr(1, TROFEU_DIR_X, TROFEU_DIR_Y, 24, 3);
                                pthread_mutex_unlock(&lock);
                            }
                        }

                        /* Atualiza display com as vidas e habilidades restantes */
                        att_display(vidas, habilidades);
                    }
                }

                /* VERIFICA SE JOGADOR QUER REINICIAR OU SAIR DO JOGO (SEMPRE) */
                if (start || sair) {
                    break;
                }

            } //LOOP DO JOGO

            /* SE SAIU DO LOOP DO JOGO, AS THREADS DOS POLICIAIS E MOUSE SÃO CANCELADAS */
            pthread_mutex_lock(&lock);
            cancela_threads_policiais = 1;

            /* Sinaliza o não funcionamento dos botões de pause e despause */
            jogando = 0;

            /* SE JOGO ESTAVA PAUSADO, É DESPAUSADO AUTOMATICAMENTE */
            pausar = 0;
            set_sprite_wbr(0, PAUSE_X, PAUSE_Y, 27, 4);

            /* Atualiza display de 7 segmentos com as informações finais das vidas e habilidades */
            att_display(vidas, habilidades);
            pthread_mutex_unlock(&lock);

            if (espera_cancelamento_threads_policias()) {
                perror("pthread_join");
                return 1;
            }

            if (cancela_thread_mouse()) {
                perror("pthread_cancel");
                return 1;
            }

            /* SE SAIU DO LOOP DO JOGO PORQUE GANHOU OU PERDEU, LIMPA TELA, EXIBE TELA INDICATIVA E AGUARDA CONFIRMAÇÃO */
            if (win || lose) {
                pthread_mutex_lock(&lock);
                limpar_tela(0);

                if (win) {
                    tela_win();
                }

                else if (lose) {
                    tela_lose();
                } 

                pthread_mutex_unlock(&lock);

                /* ESPERA JOGADOR ESCOLHER ENTRE JOGAR DE NOVO OU SAIR */
                while (1) { 
                    if (start || sair) {  
                        break;
                    }
                }
                
                /* SE ESCOLHEU JOGAR NOVAMENTE, LIMPA TELA E VOLTA A TELA PADRÃO */
                if (start) {
                    pthread_mutex_lock(&lock);
                    limpar_tela(0);
                    tela_padrao();
                    pthread_mutex_unlock(&lock);
                }
            }
            
            /* SE CLICOU EM SAIR, TANTO NO MEIO DO JOGO OU APÓS GANHAR OU PERDER */
            if (sair) { 
                break;
            }

            /* SE CLICOU EM REINICIAR/JOGAR NOVAMENTE, TANTO NO MEIO DO JOGO OU APÓS GANHAR OU PERDER */
            pthread_mutex_lock(&lock);
            start = 0;
            cancela_threads_policiais = 0;

            /* CASO CLICOU EM REINICIAR NO MEIO DO JOGO E ALGUM TROFÉU JA TENHA SIDO PEGO, TROFÉUS SÃO SETADOS NOVAMENTE EM TELA */
            set_sprite_wbr(1, TROFEU_ESQ_X, TROFEU_ESQ_Y, 24, 2);
            set_sprite_wbr(1, TROFEU_DIR_X, TROFEU_DIR_Y, 24, 3);
            pthread_mutex_unlock(&lock);  
            
        } //LOOP JOGAR NOVAMENTE

        //fecha comunicação com o mouse
        close(fd_mouse);
    }

    /* Finaliza display de 7 segmentos com caracteres padronizados */
    inicia_display();

    /* Sinaliza cancelamento da thread dos botões */
    pthread_mutex_lock(&lock);
    cancela_thread_botoes = 1;
    pthread_mutex_unlock(&lock);
    
    /* Aguarda cancelamento da thread dos botões */
    if (pthread_join(thread_botao, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    /* Encerra comunicação com os botões da FPGA */
    if (encerra_map() == -1) {
        return -1;
    }

    /* Limpa tela, exibe tela de despedida por 3 segundos e limpa tela novamente*/
    pthread_mutex_lock(&lock);
    limpar_tela(0);

    tela_bye();

    sleep(3);

    limpar_tela(1);
    pthread_mutex_unlock(&lock);

    /* Destróit mutex */
    pthread_mutex_destroy(&lock);

    /* Fecha arquivo de comunicação com o driver */
    close_driver();

    return 0;
}
