#include "biblioteca_gpu.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
   
#define MOUSE_DEVICE "/dev/input/event0"

int bateu_parede(int ladrao_x, int ladrao_y, int bloco_x, int bloco_y){
    bloco_x *= 8;
    bloco_y *= 8;

    if (ladrao_x <= bloco_x + 2 &&   //esquerda
        ladrao_x + 15 >= bloco_x &&      //direita
        ladrao_y <= bloco_y + 6 &&       //baixo
        ladrao_y + 18 >= bloco_y) {      //cima
        
        return 1; // Colisão detectada
    }

    return 0; // Sem colisão
}

int bateu_policia(int ladrao_x, int ladrao_y, int policia_x, int policia_y){

    if (ladrao_x <= policia_x + 15 &&   //esquerda
        ladrao_x + 15 >= policia_x &&      //direita
        ladrao_y <= policia_y + 19 &&       //baixo
        ladrao_y + 18 >= policia_y) {      //cima
        
        return 1; // Colisão detectada
    }

    return 0; // Sem colisão
}

int main() {
    int fd_mouse;
    struct input_event ev;
    ssize_t n;

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

    int x_real = 456, y_real = 32;
    int teste;

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
                teste = x_real + ev.value;
                if(x_real >= 448 && teste < 448 && (y_real >= 0 && y_real < 56)

                ){}

                else
                    x_real += ev.value;
            } 
            
            else if (ev.code == REL_Y) {
                teste = y_real + ev.value;
                if(y_real <= 35 && teste > 35 && x_real >= 448

                ){}

                else
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

        set_sprite_wbr(1, x_real, y_real, 25, 1);
    }

    // Fechar os dispositivos
    close(fd_mouse);

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
