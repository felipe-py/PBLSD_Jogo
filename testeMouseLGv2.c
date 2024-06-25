#include "biblioteca_gpu.h"
#include <linux/input.h>
   
#define MOUSE_DEVICE "/dev/input/event0"

int main() {
    int fd_mouse;
    struct input_event ev;
    ssize_t n;
    int x_real = 0, y_real = 0;
    int x_mouse, y_mouse;

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

    //Sprite barra
    set_sprite_wbr(1, 320, 240, 0, 1);

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
        
        //Limitar as coordenadas acumuladas
        if (x_real < 0) x_real = 0;

        if (x_real > 619) x_real = 619;

        if (y_real < 0) y_real = 0;

        if (y_real > 459) y_real = 459;
        
        set_sprite_wbr(1, x_real, y_real, 0, 1);
    }

    // Fechar os dispositivos
    close(fd_mouse);

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}