#include "biblioteca_gpu.h"
#include "mouse.h"

int main() {
    //Abre arquivo de comunicação com o driver
    if (open_driver( ) == -1){
        return -1;
    }

    if(abrir_mouse() == -1){
        return -1;
    }

    //Sprite barra
    set_sprite_wbr(1, 320, 240, 0, 1);

    int x_real = 0, y_real = 0;

    // Loop infinito para receber as coordenadas do mouse
    while (1) {
        if(movimenta_mouse(&x_real, &y_real) == -1){
            break;
        }

        int confirma = clique_esquerdo_mouse();

        if(confirma!=0){
            break;
        }
        
        set_sprite_wbr(1, x_real, y_real, 0, 1);
    }

    //Fecha arquivo de comunicação com o driver
    close_driver();
    fechar_mouse();

    return 0;
}