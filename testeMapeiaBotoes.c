#include "mapeamento.h"
#include <pthread.h>

volatile int botao_clicou = 0;

pthread_mutex_t lock; 

void* botao(void* arg) {
    while(1){
        pthread_mutex_lock(&lock);

        botao_clicou = verifica_botao();
        
        if(botao_clicou == 7){
            pthread_mutex_unlock(&lock);
            break;
        }

        pthread_mutex_unlock(&lock);
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
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
        
        if(botao_clicou == 7){
            pthread_mutex_unlock(&lock);
            break;
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
