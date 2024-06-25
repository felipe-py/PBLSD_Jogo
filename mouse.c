#include "mouse.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int fd_mouse;
struct input_event ev;

int abrir_mouse(){
    // Abrir o dispositivo do mouse
    fd_mouse = open(MOUSE_DEVICE, O_RDONLY);
    if (fd_mouse == -1) {
        fprintf(stderr, "Erro ao abrir o mouse\n");
        return 1;
    }

    return 0;
}

void fechar_mouse(){
    close(fd_mouse);
}

int ler_mouse(){
    ssize_t n = read(fd_mouse, &ev, sizeof(ev));
        
    if (n == (ssize_t)-1) {
        fprintf(stderr, "Erro de leitura\n");
        return -1;
    } 
    
    else if (n != sizeof(ev)) {
        fprintf(stderr, "Erro ao ler %ld bytes, o esperado era %ld\n", n, sizeof(ev));
        return -1;
    }

    return 0;
}

int movimenta_mouse(int *x_real, int *y_real){
    if (ler_mouse() == -1){
        return -1;
    }

    if (ev.type == EV_REL && ev.code == REL_X) {
        int x_mouse = ev.value;
        *x_real += x_mouse;
    }

    if (ev.type == EV_REL && ev.code == REL_Y) {
        int y_mouse = ev.value;
        *y_real += y_mouse;
    }

    //Limitar as coordenadas acumuladas
    if (*x_real < 0) *x_real = 0;

    if (*x_real > 619) *x_real = 619;

    if (*y_real < 0) *y_real = 0;

    if (*y_real > 459) *y_real = 459;

    return 0;
}

int clique_esquerdo_mouse(){
    if (ler_mouse() == -1){
        return -1;
    }

    if (ev.type == EV_KEY && ev.code == BTN_LEFT) {
        if (ev.value == 1) {
            printf("Botão esquerdo pressionado\n");
            return 1;
        } 
        
        else if (ev.value == 0) {
            printf("Botão esquerdo liberado\n");
        }
    }

    return 0;
}