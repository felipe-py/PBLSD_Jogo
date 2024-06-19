#include "biblioteca_gpu.h"

int main() {

    //Abre arquivo de comunicação com o driver
    if (open_driver( ) == -1){
        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------------//      
    
    //Azul claro (ceu)
    set_cor_background_wbr(7, 7, 7); 

//-----------------------------------------------------------------------------------------------------------------------//   

    int y,x;

    // Desenhar quadrado maior (verde)
    for (x = 0; x < 20; x++) {
        for (y = 0; y < 20; y++) {
            edit_sprite_wsm(10000 + y * 20 + x, 0, 7, 0);
        }
    }

    // Desenhar quadrado menor (azul)
    for (x = 5; x < 15; x++) {
        for (y = 5; y < 15; y++) {
            edit_sprite_wsm(10000 + y * 20 + x, 7, 0, 7);  // Azul
        }
    }

//-----------------------------------------------------------------------------------------------------------------------//

    // Inicializa o sprite com pixels transparentes
    for (y = 0; y < 20; y++) {
        for (x = 0; x < 20; x++) {
            edit_sprite_wsm(10400 + y * 20 + x, 7, 7, 6);
        }
    }

    // Desenhar triângulo maior (verde)
    for (y = 0; y < 20; y++) {
        for (x = 0; x < 20; x++) {
            if (y <= 19 - x && y <= x){
                edit_sprite_wsm(10400 + y * 20 + x, 0, 7, 0);  // Verde
            }
        }
    }

    // Desenhar triângulo menor (vermelho)
    for (y = 5; y <= 14; y++) {
        for (x = 5; x <= 14; x++) {
            if (y <= 14 - x + 5 && y <= x - 5){
                edit_sprite_wsm(10400 + y * 20 + x, 0, 0, 7);  // vermelho
            }
        }
    }

//-----------------------------------------------------------------------------------------------------------------------//

    //Sprite quadrado
    set_sprite_wbr(1, 320, 240, 25, 1);

    //Sprite triangulo
    set_sprite_wbr(1, 360, 240, 26, 2);

//-----------------------------------------------------------------------------------------------------------------------//

    //Remove estruturas da tela
    //limpar_tela();

//-----------------------------------------------------------------------------------------------------------------------//

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
