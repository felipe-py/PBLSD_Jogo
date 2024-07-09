#include "mapeamento.h"
#include <pthread.h>

volatile int start = 0;

pthread_mutex_t lock; 

void* botao(void* arg) {
    int botao_clicou;
    //VARIÁVEL PARA PEGAR SOMENTE A PRIMEIRA OCORRENCIA DO CLICK DE INICAR PARTIDA/REINICIAR JOGO
    int clicou_start = 0;
    
    while(1){
        botao_clicou = verifica_botao();

        //SO CONSIDERA A SOLTURA DO BOTÃO SE JÁ TIVER SIDO CLICADO E RECEBER UM VALOR DIFERENTE DO REFERENTE AO CLICK DO BOTAO 1
        if(clicou_start == 1 && botao_clicou != 7){
            clicou_start = 0;
        }

        //BOTAO 3 - PAUSE
        if(botao_clicou == 7){
            //SO ALTERA VARIÁVEL PAUSE NO PRIMEIRO CLICK E SE ELA FOR 0 (JOGO NÃO ESTÁ PAUSADO
            if(clicou_start == 0){
                clicou_start = 1;
                pthread_mutex_lock(&lock);
                start = 1;
                pthread_mutex_unlock(&lock); 
            }
        }
    }
}

int main() {
    pthread_t thread_id;

    if(inicia_map() == -1){
        return -1;
    }

    // Inicializa o mutex de sprite
    pthread_mutex_init(&lock, NULL);
    
    if (pthread_create(&thread_id, NULL, botao, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    while(1){
        
        pthread_mutex_lock(&lock); 
        if(start){
            start = 0;
            printf("uma vez\n");
        }
        pthread_mutex_unlock(&lock); 

    }

    printf("Botão 3 clicado, gg\n");

    //AGUARDA A FINALIZAÇÃO DE DETERMINADA THREAD
    if (pthread_join(thread_id, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    pthread_mutex_destroy(&lock);

    if(encerra_map() == -1){
        return -1;
    }

    return 0;
}
