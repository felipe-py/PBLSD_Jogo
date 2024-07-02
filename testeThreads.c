#include "biblioteca_gpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/input.h>

#define MOUSE_DEVICE "/dev/input/event0"

volatile int x_sprite = 120;
volatile int colisao = 0;

void* movimenta_sprite(void* arg) {
    int sentido = 1;
    
    while(colisao!=1){
        //Desloca da esquerda para direita
        if(sentido == 1){
            x_sprite += 16;     
            if(x_sprite == 520){
                sentido = 0;
            }
        }

        //Desloca da direita para esquerda
        else {
            //512 ao 1 (/2)
            x_sprite -= 16;       
            if(x_sprite == 120){
                sentido = 1;
            }
        }
        
        set_sprite_wbr(1, x_sprite, 224, 1, 2);
        
        if (colisao) break;
        
        usleep(500000);
    }
    
    //FINALIZA A EXECUÇÃO DA THREAD
    pthread_exit(NULL); // Finaliza a thread
}

int main() {
    int fd_mouse;
    struct input_event ev;
    ssize_t n;
    pthread_t thread_id;

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

    int x_real = 0, y_real = 0;

    //Mouse
    set_sprite_wbr(1, x_real, y_real, 0, 1);

    //Bixo correndo
    set_sprite_wbr(1, x_sprite, 224, 0, 2);
    
    if (pthread_create(&thread_id, NULL, movimenta_sprite, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Loop infinito para receber as coordenadas do mouse
    while (1) {
        // Ler o evento do mouse
        n = read(fd_mouse, &ev, sizeof(ev));
        
        if (n == (ssize_t)-1) {
            fprintf(stderr, "Erro de leitura\n");
            break;
        } 
        
        if (n != sizeof(ev)) {
            fprintf(stderr, "Erro ao ler %ld bytes, o esperado era %ld\n", n, sizeof(ev));
            break;
        }

        if (ev.type == EV_REL) {
            if (ev.code == REL_X) {
                x_real += ev.value;
            } 
            
            else if (ev.code == REL_Y) {
                y_real += ev.value;
            }
        }

        if (ev.type == EV_KEY && ev.code == BTN_LEFT) {
            if (ev.value == 1) {
                printf("Botão esquerdo pressionado\n");
                break;
            } 
        }
        
        //Limitar as coordenadas acumuladas
        if (x_real < 0) x_real = 0;
        if (x_real > 619) x_real = 619;
        if (y_real < 0) y_real = 0;
        if (y_real > 459) y_real = 459;

        set_sprite_wbr(1, x_real, y_real, 0, 1);

        //COLISÃO
        if (x_real <= x_sprite + 21 && 
            x_real + 21 >= x_sprite && 
            y_real <= 224 + 22 && 
            y_real + 22 >= 224) {
            
            printf("COLISÃO\n");
            colisao = 1;

            break;
        }
    }
    
    if(colisao==0) colisao = 1;

    //AGUARDA A FINALIZAÇÃO DE DETERMINADA THREAD
    if (pthread_join(thread_id, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    // Fechar os dispositivos
    close(fd_mouse);

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}