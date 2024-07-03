#include "biblioteca_gpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/input.h>

#define MOUSE_DEVICE "/dev/input/event0"

volatile int x_real = 0;
volatile int y_real = 0;
volatile int clicou = 0;
volatile int parar = 0;

int fd_mouse;
struct input_event ev;

pthread_mutex_t lock; 

void* movimenta_mouse(void* arg) {
    ssize_t n;
    int parou2;
    
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
                x_real += ev.value;
            } 
            
            else if (ev.code == REL_Y) {
                y_real += ev.value;
            }
        }
        
        //Limitar as coordenadas acumuladas
        if (x_real < 0) x_real = 0;
        if (x_real > 619) x_real = 619;
        if (y_real < 0) y_real = 0;
        if (y_real > 459) y_real = 459;

        set_sprite_wbr(1, x_real, y_real, 0, 1);

        pthread_mutex_unlock(&lock);

        if (ev.type == EV_KEY && ev.code == BTN_LEFT) {
            if (ev.value == 1) {
                clicou = 1;
                break;
            } 
        }

        pthread_mutex_lock(&lock);
        parou2 = parar;
        pthread_mutex_unlock(&lock);

        if(parou2) break;
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

int main() {
    pthread_t thread_id;
    int x_sprite = 0;

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

    set_cor_background_wbr(7,7,7);

    //Mouse
    set_sprite_wbr(1, x_real, y_real, 0, 1);

    //Bixo correndo
    set_sprite_wbr(1, x_sprite, 240, 0, 2);

    // Inicializa o mutex de sprite
    pthread_mutex_init(&lock, NULL);
    
    if (pthread_create(&thread_id, NULL, movimenta_mouse, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    int sentido = 1;
    int temp_x_real, temp_y_real, clicou2;
    
    while(1){
        //7 segundos / 619 (7 000 000 dividido pelo total de pixels) -> Tempo para um pixel ir de 0 a 619
        usleep(10000);

        //Desloca da esquerda para direita
        if(sentido == 1){
            x_sprite += 1;     
            if(x_sprite == 619){
                sentido = 0;
            }
        }

        //Desloca da direita para esquerda
        else {
            x_sprite -= 1;       
            if(x_sprite == 0){
                sentido = 1;
            }
        }
        
        set_sprite_wbr(1, x_sprite, 224, 1, 2);

        pthread_mutex_lock(&lock);
        temp_x_real = x_real;
        temp_y_real = y_real;
        pthread_mutex_unlock(&lock);

        //COLISÃO
        if (temp_x_real <= x_sprite + 21 &&      //esquerda 
            temp_x_real + 21 >= x_sprite &&      //direita
            temp_y_real <= 224 + 22 &&           //baixo
            temp_y_real + 22 >= 224) {           //cima
            
            pthread_mutex_lock(&lock);
            parar=1;
            pthread_mutex_unlock(&lock);

            printf("COLIDIU\n");
            break;
        }

        pthread_mutex_lock(&lock);
        clicou2 = clicou;
        pthread_mutex_unlock(&lock);

        if(clicou2) break;
    }

    //AGUARDA A FINALIZAÇÃO DE DETERMINADA THREAD
    if (pthread_join(thread_id, NULL) != 0) {
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
