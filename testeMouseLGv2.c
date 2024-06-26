#include "biblioteca_gpu.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
   
#define MOUSE_DEVICE "/dev/input/event0"

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

    int x_real = 320, y_real = 240;
    int x_mouse, y_mouse;
    int x_sprite = 400, y_sprite = 300;

    set_sprite_wbr(1, x_sprite, y_sprite, 1, 2);

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
                x_mouse = ev.value;
                x_real += x_mouse;
            } 
            
            else if (ev.code == REL_Y) {
                y_mouse = ev.value;
                y_real += y_mouse;
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
        if (x_real < x_sprite + 22 && 
            x_real + 22 > x_sprite && 
            y_real < y_sprite + 23 && 
            y_real + 23 > y_sprite) {
                
            printf("COLISÃO\n");
            break;
        }

        else{
            printf("NÃO TEVE COLISÃO\n");
        }
    }

    // Fechar os dispositivos
    close(fd_mouse);

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
