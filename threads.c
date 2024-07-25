#include "threads.h"
#include "biblioteca_gpu.h"
#include "mapeamento.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/input.h>

/* Usando para abrir /dev/input/event0 */
int fd_mouse;

/* Estrutura para coleta dos dados referentes aos eventos do mouse */
struct input_event ev;

/* Mutex para sincronização entre as threads */
pthread_mutex_t lock;

/* IDs das threads do jogo */
pthread_t thread_mouse, thread_policais_1_2_3, thread_policiais_4_5_6, thread_policiais_7_8_9_10;

/* Variáveis para as coordenadas X e Y do sprite ladrão */
volatile int x_ladrao;
volatile int y_ladrao;

/* Variáveis para as coordenadas X dos sprites policiais */
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

/* Variáveis para as coordenadas Y dos sprites policiais */
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

/* Variáveis de controle responsáveis por cancelar as threads do jogo */
volatile int cancela_threads_policiais = 0;
volatile int cancela_thread_botoes = 0;

/* Variáveis responsáveis pelo controle do jogo */
volatile int pausar = 0;
volatile int start = 0;
volatile int sair = 0;

/* Variável usada para habilitar botões de pause e despause apenas quando o jogador estiver jogando */
volatile int jogando = 0;

/* Variável que indica a quantidade de habilidades restantes do jogador */
volatile int habilidades = 0;

/* Variável que indica se o jogador está utilizando a habilidade ou não */
volatile int furtivo = 0;

/* Função para setar posição inicial do jogador (sprite ladrão) */
void 
inicia_ladrao() {
    x_ladrao = INICIO_LADRAO_X;
    y_ladrao = INICIO_LADRAO_Y;
    set_sprite_wbr(1, x_ladrao, y_ladrao, 25, 15);
}

/**Função para criar as threads do jogo (mouse e policiais)
 * retorno ->       0 caso seja bem sucedido ou 1 caso ocorra algum erro
 */
int 
cria_threads_jogo() {

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

/**Função para cancelar a thread do mouse
 * retorno ->       0 caso seja bem sucedido ou 1 caso ocorra algum erro
 */
int 
cancela_thread_mouse() {
    if (pthread_cancel(thread_mouse) != 0) {
        return 1;
    }

    return 0;
}

/**Função para esperar o encerramento das threads dos policiais
 * retorno ->       0 caso seja bem sucedido ou 1 caso ocorra algum erro
 */
int 
espera_cancelamento_threads_policias() {

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

/**Função referente a thread para captação dos eventos do mouse
 *                  verificar: variável usada para verificar se a posição atual X ou Y do jogador + movimento relativo X ou Y do mouse,
 *                  irá resultar em uma colisão (ou ultrapassagem) com uma estrutura do mapa do jogo
 *                  offset_ladrao: variável usada para determinar sprite (ladrão padrão ou ladrão furtivo) 
 *                  referente ao jogador estar usando habilidade de furtividade ou não
 * retorno ->       NULL caso seja bem sucedido ou -1 caso ocorra algum erro
 */
void* 
movimenta_mouse(void* arg) {
    ssize_t n;

    int verificar, offset_ladrao = 25;

    while (1) {
        n = read(fd_mouse, &ev, sizeof(ev));
            
        if (n == (ssize_t)-1) {
            fprintf(stderr, "Erro de leitura\n");
            return -1;
        } 
        
        if (n != sizeof(ev)) {
            fprintf(stderr, "Erro ao ler %ld bytes, o esperado era %ld\n", n, sizeof(ev));
            return -1;
        }

        /* Se o jogo não estiver pausado, thread funciona */
        if (pausar == 0) {
            pthread_mutex_lock(&lock);

            /* SE ESTIVER NO MODO FURTIVO, NÃO PRECISA LER MOVIMENTOS */
            if (furtivo == 0) {
                if (ev.type == EV_REL) {
                    if (ev.code == REL_X) {
                        verificar = x_ladrao + ev.value;

                        /* Verifica se a movimentação da coordenada X gera colisão ou ultrapassagem */    
                        if (verifica_colisao_parede(x_ladrao, y_ladrao, verificar, 'x')) {}

                        else x_ladrao += ev.value;
                    } 
                    
                    else if (ev.code == REL_Y) {
                        verificar = y_ladrao + ev.value;

                        /* Verifica se a movimentação da coordenada Y gera colisão ou ultrapassagem */   
                        if (verifica_colisao_parede(x_ladrao, y_ladrao, verificar, 'y')) {}

                        else y_ladrao += ev.value;
                    }
                }
     
                /* Limitar as coordenadas acumuladas */
                if (x_ladrao < 0) x_ladrao = 0;
                if (x_ladrao > 619) x_ladrao = 619;
                if (y_ladrao < 0) y_ladrao = 0;
                if (y_ladrao > 459) y_ladrao = 459;  
            }

            /* SE NÃO TIVER MAIS HABILIDADES, NÃO PRECISA VERIFICAR AÇÃO DE FURTIVIDADE */
            if (habilidades > 0) {
                if (ev.type == EV_KEY && ev.code == BTN_LEFT) {
                    /* SE BOTÃO ESQUERDO TA SENDO PRESSIONADO, MODO FURTIVO ON */
                    if (ev.value == 1) {
                        furtivo = 1;
                    
                        offset_ladrao = 29;
                    }

                    /* SE BOTÃO ESQUERDO TA SOLTO, PORÉM ESTAVA MODO FURTIVO ON, HABILIDADE É CONTADA E FURTIVIDADE DESATIVADA */
                    else if (ev.value == 0) {
                        if (furtivo) {
                            --habilidades;

                            furtivo = 0;

                            offset_ladrao = 25;
                        }
                    }
                }
            }

            set_sprite_wbr(1, x_ladrao, y_ladrao, offset_ladrao, 15);    

            pthread_mutex_unlock(&lock); 
        }
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

/**Função referente a thread para movimentação dos policiais 1, 2 e 3
 * retorno ->       NULL caso seja bem sucedido ou -1 caso ocorra algum erro
 */
void* 
movimenta_policiais_1_2_3(void* arg) {
    /* Seta posições inicias dos policais 1, 2 e 3 */
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

    /* Seta sentidos de movimentações iniciais dos policias 1, 2 e 3 */
    int sentido_policial_1 = SENTIDO_PARA_DIREITA;
    int sentido_policial_2 = SENTIDO_PARA_ESQUERDA;
    int sentido_policial_3 = SENTIDO_PARA_DIREITA;

    while (cancela_threads_policiais == 0) {
        /* Se o jogo não estiver pausado, thread funciona */
        if (pausar == 0) {

            usleep(VELOCIDADE_POLICIAIS);
            
            /* Atualiza posições */
            pthread_mutex_lock(&lock);

            //POLICIA 1
                if (sentido_policial_1 == SENTIDO_PARA_DIREITA) {
                    policia_1_x += DESLOCAMENTO_POLICIAL_1;

                    if (policia_1_x >= FIM_POLICIAL_1_X) {
                        policia_1_x = FIM_POLICIAL_1_X;
                        sentido_policial_1 = SENTIDO_PARA_BAIXO;
                    }
                }

                else if (sentido_policial_1 == SENTIDO_PARA_BAIXO) {
                    policia_1_y += DESLOCAMENTO_POLICIAL_1; 

                    if (policia_1_y >= FIM_POLICIAL_1_Y) {
                        policia_1_y = FIM_POLICIAL_1_Y;
                        sentido_policial_1 = SENTIDO_PARA_ESQUERDA;
                    }
                }

                else if (sentido_policial_1 == SENTIDO_PARA_ESQUERDA) {
                    policia_1_x -= DESLOCAMENTO_POLICIAL_1; 

                    if (policia_1_x <= INICIO_POLICIAL_1_X) {
                        policia_1_x = INICIO_POLICIAL_1_X;
                        sentido_policial_1 = SENTIDO_PARA_CIMA;
                    }
                }

                else if (sentido_policial_1 == SENTIDO_PARA_CIMA) {
                    policia_1_y -= DESLOCAMENTO_POLICIAL_1; 

                    if (policia_1_y <= INICIO_POLICIAL_1_Y) {
                        policia_1_y = INICIO_POLICIAL_1_Y;
                        sentido_policial_1 = SENTIDO_PARA_DIREITA;
                    }
                }
            
            //POLICIA 2
                if (sentido_policial_2 == SENTIDO_PARA_ESQUERDA) {
                    policia_2_x -= DESLOCAMENTO_POLICIAL_2;   

                    if (policia_2_x <= FIM_POLICIAL_2_X) {
                        policia_2_x = FIM_POLICIAL_2_X;
                        sentido_policial_2 = SENTIDO_PARA_DIREITA;
                    }

                }

                else if (sentido_policial_2 == SENTIDO_PARA_DIREITA) {
                    policia_2_x += DESLOCAMENTO_POLICIAL_2;    

                    if (policia_2_x >= INICIO_POLICIAL_2_X) {
                        policia_2_x = INICIO_POLICIAL_2_X;
                        sentido_policial_2 = SENTIDO_PARA_ESQUERDA;
                    }
                }

            //POLICIA 3
                if (sentido_policial_3 == SENTIDO_PARA_DIREITA) {
                    policia_3_x += DESLOCAMENTO_POLICIAL_3;   

                    if (policia_3_x >= FIM_POLICIAL_3_X) {
                        policia_3_x = FIM_POLICIAL_3_X;
                        sentido_policial_3 = SENTIDO_PARA_BAIXO;
                    }
                }

                else if (sentido_policial_3 == SENTIDO_PARA_BAIXO) {
                    policia_3_y += DESLOCAMENTO_POLICIAL_3;   

                    if (policia_3_y >= FIM_POLICIAL_3_Y) {
                        policia_3_y = FIM_POLICIAL_3_Y;
                        sentido_policial_3 = SENTIDO_PARA_CIMA;
                    }
                }

                else if (sentido_policial_3 == SENTIDO_PARA_CIMA) {
                    policia_3_y -= DESLOCAMENTO_POLICIAL_3;      

                    if (policia_3_y <= INICIO_POLICIAL_3_Y) {
                        policia_3_y = INICIO_POLICIAL_3_Y;
                        sentido_policial_3 = SENTIDO_PARA_ESQUERDA;
                    }
                }

                else if (sentido_policial_3 == SENTIDO_PARA_ESQUERDA) {
                    policia_3_x -= DESLOCAMENTO_POLICIAL_3;       

                    if (policia_3_x <= INICIO_POLICIAL_3_X) {
                        policia_3_x = INICIO_POLICIAL_3_X;
                        sentido_policial_3 = SENTIDO_PARA_DIREITA;
                    }
                }

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

/**Função referente a thread para movimentação dos policiais 4, 5 e 6
 * retorno ->       NULL caso seja bem sucedido ou -1 caso ocorra algum erro
 */
void* 
movimenta_policiais_4_5_6(void* arg) {
    /* Seta posições inicias dos policais 4, 5 e 6 */
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

    /* Seta sentidos de movimentações iniciais dos policias 4, 5 e 6 */
    int sentido_policial_4 = SENTIDO_PARA_ESQUERDA;
    int sentido_policial_5 = SENTIDO_PARA_DIREITA;
    int sentido_policial_6 = SENTIDO_PARA_ESQUERDA;

    while (cancela_threads_policiais == 0) {
        /* Se o jogo não estiver pausado, thread funciona */
        if (pausar == 0) {

            usleep(VELOCIDADE_POLICIAIS);
            
            /* Atualiza posições */
            pthread_mutex_lock(&lock);

            //POLICIA 4
                if (sentido_policial_4 == SENTIDO_PARA_ESQUERDA) {
                    policia_4_x -= DESLOCAMENTO_POLICIAL_4;  

                    if (policia_4_x <= FIM_POLICIAL_4_X) {
                        policia_4_x = FIM_POLICIAL_4_X;
                        sentido_policial_4 = SENTIDO_PARA_DIREITA;
                    }
                }

                else if (sentido_policial_4 == SENTIDO_PARA_DIREITA) {
                    policia_4_x += DESLOCAMENTO_POLICIAL_4; 

                    if (policia_4_x >= INICIO_POLICIAL_4_X) {
                        policia_4_x = INICIO_POLICIAL_4_X;
                        sentido_policial_4 = SENTIDO_PARA_ESQUERDA;
                    }
                }

            //POLICIA 5
                if (sentido_policial_5 == SENTIDO_PARA_DIREITA) {
                    policia_5_x += DESLOCAMENTO_POLICIAL_5;  

                    if (policia_5_x >= FIM_POLICIAL_5_X) {
                        policia_5_x = FIM_POLICIAL_5_X;
                        sentido_policial_5 = SENTIDO_PARA_ESQUERDA;
                    }
                }

                else if (sentido_policial_5 == SENTIDO_PARA_ESQUERDA) {
                    policia_5_x -= DESLOCAMENTO_POLICIAL_5;   

                    if (policia_5_x <= INICIO_POLICIAL_5_X) {
                        policia_5_x = INICIO_POLICIAL_5_X;
                        sentido_policial_5 = SENTIDO_PARA_DIREITA;
                    }
                }
        
            //POLICIA 6
                if (sentido_policial_6 == SENTIDO_PARA_ESQUERDA) {
                    policia_6_x -= DESLOCAMENTO_POLICIAL_6;    

                    if (policia_6_x <= FIM_POLICIAL_6_X) {
                        policia_6_x = FIM_POLICIAL_6_X;
                        sentido_policial_6 = SENTIDO_PARA_DIREITA;
                    }
                }

                else if (sentido_policial_6 == SENTIDO_PARA_DIREITA) {
                    policia_6_x += DESLOCAMENTO_POLICIAL_6;     

                    if (policia_6_x >= INICIO_POLICIAL_6_X) {
                        policia_6_x = INICIO_POLICIAL_6_X;
                        sentido_policial_6 = SENTIDO_PARA_ESQUERDA;
                    }
                }

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

/**Função referente a thread para movimentação dos policiais 7, 8, 9 e 10
 * retorno ->       NULL caso seja bem sucedido ou -1 caso ocorra algum erro
 */
void* 
movimenta_policiais_7_8_9_10(void* arg) {
    /* Seta posições inicias dos policais 7, 8, 9, 10 */
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

    /* Seta sentidos de movimentações iniciais dos policias 7, 8, 9 e 10 */
    int sentido_policial_7 = SENTIDO_PARA_CIMA;
    int sentido_policial_8 = SENTIDO_PARA_DIREITA;
    int sentido_policial_9 = SENTIDO_PARA_DIREITA;
    int sentido_policial_10 = SENTIDO_PARA_ESQUERDA;

    while (cancela_threads_policiais == 0) {
        /* Se o jogo não estiver pausado, thread funciona */
        if (pausar == 0) {

            usleep(VELOCIDADE_POLICIAIS);

            /* Atualiza posições */
            pthread_mutex_lock(&lock);

            //POLICIA 7
                if (sentido_policial_7 == SENTIDO_PARA_CIMA) {
                    policia_7_y -= DESLOCAMENTO_POLICIAL_7; 

                    if (policia_7_y <= FIM_POLICIAL_7_Y) {
                        policia_7_y = FIM_POLICIAL_7_Y;
                        sentido_policial_7 = SENTIDO_PARA_ESQUERDA;
                    }
                }

                else if (sentido_policial_7 == SENTIDO_PARA_ESQUERDA) {
                    policia_7_x -= DESLOCAMENTO_POLICIAL_7;  

                    if (policia_7_x <= FIM_POLICIAL_7_X) {
                        policia_7_x = FIM_POLICIAL_7_X;
                        sentido_policial_7 = SENTIDO_PARA_DIREITA;
                    }
                }

                else if (sentido_policial_7 == SENTIDO_PARA_DIREITA) {
                    policia_7_x += DESLOCAMENTO_POLICIAL_7;  

                    if (policia_7_x >= INICIO_POLICIAL_7_X) {
                        policia_7_x = INICIO_POLICIAL_7_X;
                        sentido_policial_7 = SENTIDO_PARA_BAIXO;
                    }
                }

                else if (sentido_policial_7 == SENTIDO_PARA_BAIXO) {
                    policia_7_y += DESLOCAMENTO_POLICIAL_7;  

                    if (policia_7_y >= INICIO_POLICIAL_7_Y) {
                        policia_7_y = INICIO_POLICIAL_7_Y;
                        sentido_policial_7 = SENTIDO_PARA_CIMA;
                    }
                }

            //POLICIA 8
                if (sentido_policial_8 == SENTIDO_PARA_DIREITA) {
                    policia_8_x += DESLOCAMENTO_POLICIAL_8;     

                    if (policia_8_x >= FIM_POLICIAL_8_X) {
                        policia_8_x = FIM_POLICIAL_8_X;
                        sentido_policial_8 = SENTIDO_PARA_ESQUERDA;
                    }
                }

                else if (sentido_policial_8 == SENTIDO_PARA_ESQUERDA) {
                    policia_8_x -= DESLOCAMENTO_POLICIAL_8;      

                    if (policia_8_x <= INICIO_POLICIAL_8_X) {
                        policia_8_x = INICIO_POLICIAL_8_X;
                        sentido_policial_8 = SENTIDO_PARA_DIREITA;
                    }
                }
            
             //POLICIA 9
                if (sentido_policial_9 == SENTIDO_PARA_DIREITA) {
                    policia_9_x += DESLOCAMENTO_POLICIAL_9; 

                    if (policia_9_x >= FIM_POLICIAL_9_X && policia_9_y == INICIO_POLICIAL_9_Y) {
                        policia_9_x = FIM_POLICIAL_9_X;
                        sentido_policial_9 = SENTIDO_PARA_BAIXO;
                    }

                    else if (policia_9_x >= FIM_POLICIAL_9_X && policia_9_y == FIM_POLICIAL_9_Y) {
                        policia_9_x = FIM_POLICIAL_9_X;
                        sentido_policial_9 = SENTIDO_PARA_CIMA;
                    }
                }

                else if (sentido_policial_9 == SENTIDO_PARA_BAIXO) {
                    policia_9_y += DESLOCAMENTO_POLICIAL_9;    

                    if (policia_9_y >= FIM_POLICIAL_9_Y) {
                        policia_9_y = FIM_POLICIAL_9_Y;
                        sentido_policial_9 = SENTIDO_PARA_ESQUERDA;
                    }
                }

                else if (sentido_policial_9 == SENTIDO_PARA_ESQUERDA) {
                    policia_9_x -= DESLOCAMENTO_POLICIAL_9;  

                    if (policia_9_x <= FIM_2_POLICIAL_9_X && policia_9_y == FIM_POLICIAL_9_Y) {
                        policia_9_x = FIM_2_POLICIAL_9_X;
                        sentido_policial_9 = SENTIDO_PARA_DIREITA;
                    }

                    else if (policia_9_x <= INICIO_POLICIAL_9_X && policia_9_y == INICIO_POLICIAL_9_Y) {
                        policia_9_x = INICIO_POLICIAL_9_X;
                        sentido_policial_9 = SENTIDO_PARA_DIREITA;
                    }
                }

                else if (sentido_policial_9 == SENTIDO_PARA_CIMA) {
                    policia_9_y -= DESLOCAMENTO_POLICIAL_9;  

                    if (policia_9_y <= INICIO_POLICIAL_9_Y) {
                        policia_9_y = INICIO_POLICIAL_9_Y;
                        sentido_policial_9 = SENTIDO_PARA_ESQUERDA;
                    }
                }

            //POLICIA 10
                if (sentido_policial_10 == SENTIDO_PARA_ESQUERDA) {
                    policia_10_x -= DESLOCAMENTO_POLICIAL_10;     

                    if (policia_10_x <= FIM_POLICIAL_10_X) {
                        policia_10_x = FIM_POLICIAL_10_X;
                        sentido_policial_10 = SENTIDO_PARA_CIMA;
                    }
                }

                else if (sentido_policial_10 == SENTIDO_PARA_CIMA) {
                    policia_10_y -= DESLOCAMENTO_POLICIAL_10;     

                    if (policia_10_y <= FIM_POLICIAL_10_Y) {
                        policia_10_y = FIM_POLICIAL_10_Y;
                        sentido_policial_10 = SENTIDO_PARA_BAIXO;
                    }
                }

                else if (sentido_policial_10 == SENTIDO_PARA_BAIXO) {
                    policia_10_y += DESLOCAMENTO_POLICIAL_10;       

                    if (policia_10_y >= INICIO_POLICIAL_10_Y) {
                        policia_10_y = INICIO_POLICIAL_10_Y;
                        sentido_policial_10 = SENTIDO_PARA_DIREITA;
                    }
                }

                else if (sentido_policial_10 == SENTIDO_PARA_DIREITA) {
                    policia_10_x += DESLOCAMENTO_POLICIAL_10;     

                    if (policia_10_x >= INICIO_POLICIAL_10_X) {
                        policia_10_x = INICIO_POLICIAL_10_X;
                        sentido_policial_10 = SENTIDO_PARA_ESQUERDA;
                    }
                }

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

/**Função referente a thread para captação dos eventos dos botões da FPGA
 *                  botao_clicou: variável usada para retorno da função que retorna estado dos botões
 *                  clicou_start: variável usada para registrar apenas uma transição do botão de iniciar/jogar novamente (B1)
*                   clicou_pause: variável usada para registrar apenas uma transição do botão de pausar (B3)
*                   clicou_despause: variável usada para registrar apenas uma transição do botão de despausar (B2)
*                   clicou_sair: variável usada para registrar apenas uma transição do botão de sair (B0)
 * retorno ->       NULL caso seja bem sucedido ou -1 caso ocorra algum erro
 */
void* 
botao(void* arg) {
    int botao_clicou;

    int clicou_start = 0;
    int clicou_pause = 0;
    int clicou_despause = 0;
    int clicou_sair = 0;
    
    while(1){
        botao_clicou = verifica_botao();

        /* Botão 3 - Pause
         * Só volta a ser 0, quando soltar botão pressionado
         */
        if (clicou_pause == 1 && botao_clicou != 7) {
            clicou_pause = 0;
        }

        /* Botão 2 - Despause 
         * Só volta a ser 0, quando soltar botão pressionado
         */
        if (clicou_despause == 1 && botao_clicou != 11) {
            clicou_despause = 0;
        }

        /* Botão 1 - Iniciar/Jogar novamente 
         * Só volta a ser 0, quando soltar botão pressionado
         */
        if (clicou_start == 1 && botao_clicou != 13) {
            clicou_start = 0;
        }

        /* Botão 0 - Sair 
         * Só volta a ser 0, quando soltar botão pressionado
         */
        if (clicou_sair == 1 && botao_clicou != 14) {
            clicou_sair = 0;
        }

        //BOTAO 3 - PAUSE
        if (botao_clicou == 7) {

            /* Registra apenas uma transição - Primeiro sinal captado */
            if (clicou_pause == 0) {
                clicou_pause = 1;
                
                /* Só pausa se o jogador estiver jogando (tela padrão) */
                pthread_mutex_lock(&lock);
                if (jogando) {
                    pausar = 1;
                    set_sprite_wbr(1, PAUSE_X, PAUSE_Y, 27, 4);
                }
                pthread_mutex_unlock(&lock);
            }
        }

        //BOTAO 2 - DESPAUSE
        else if (botao_clicou == 11) {

            /* Registra apenas uma transição - Primeiro sinal captado */
            if (clicou_despause == 0) {
                clicou_despause = 1;

                /* Só despausa se o jogador estiver jogando (tela padrão) */
                pthread_mutex_lock(&lock);
                if (jogando) {
                    pausar = 0;
                    set_sprite_wbr(0, PAUSE_X, PAUSE_Y, 27, 4);
                }
                pthread_mutex_unlock(&lock);
            }
        }

        //BOTAO 1 - INICIAR JOGO OU JOGAR NOVAMENTE
        else if (botao_clicou == 13) {

            /* Registra apenas uma transição - Primeiro sinal captado */
            if (clicou_start == 0) {
                clicou_start = 1;

                pthread_mutex_lock(&lock);
                start = 1;
                pthread_mutex_unlock(&lock);
            }
        }

        //BOTAO 0 - SAIR
        else if (botao_clicou == 14) {

            /* Registra apenas uma transição - Primeiro sinal captado */
            if (clicou_sair == 0) {
                clicou_sair = 1;

                pthread_mutex_lock(&lock);
                sair = 1;
                pthread_mutex_unlock(&lock);
            }
        }

        /* Verifica se deve cancelar a thread */
        if (cancela_thread_botoes) {
            break;
        }
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}
