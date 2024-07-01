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

    set_cor_background_wbr(7, 7, 7);

    int x_real = 320, y_real = 240;
    
    int x_sprite = 400, y_sprite = 300;
    int bloco_x = 200, bloco_y = 150;

    set_sprite_wbr(1, x_sprite, y_sprite, 30, 2);
    edit_bloco_background_wbm(bloco_x, bloco_y, 0, 0, 0);

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

        //COLISÃO POLICIA
        if (x_real + 5 <= x_sprite + 16 &&        //esquerda
            x_real + 15 >= x_sprite + 3 &&        //direita
            y_real + 1 <= y_sprite + 18 &&        //cima
            y_real + 18 >= y_sprite + 1) {        //baixo
                
            printf("COLISÃO\n");
        }

        /*
        //COLISÃO BLOCO
        if (x_real + 5 <= bloco_x + 8 &&        //esquerda
            x_real + 15 >= bloco_x &&           //direita
            y_real + 1 <= bloco_y + 8 &&        //cima
            y_real + 18 >= bloco_y) {           //baixo
                
            printf("COLISÃO\n");
        }*/
        
        else{
            set_sprite_wbr(1, x_real, y_real, 0, 1);
        }
    }

    // Fechar os dispositivos
    close(fd_mouse);

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
