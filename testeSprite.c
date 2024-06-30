#include "biblioteca_gpu.h"
#include <stdlib.h>
#include <math.h>

int main() {

    //Abre arquivo de comunicação com o driver
    if (open_driver( ) == -1){
        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------------//      
    
    //Branco
    set_cor_background_wbr(7, 7, 7); 

//-----------------------------------------------------------------------------------------------------------------------//   
//LADRÃO PADRÃO

int x, y;

for (y = 0; y < 21; y++) {
    for (x = 0; x < 20; x++) {
        int endereco = 10000 + y * 20 + x;
        int azul = 7, verde = 7, vermelho = 6; // Cor padrão (transparente)

        //Condições para preto
        if (
            ((x == 5 || x == 15) && (y >= 8 && y <= 11)) ||

            ((x == 6 || x == 14 ) && ((y >= 3 && y <= 5) || (y >= 7 && y <= 11))) ||

            (x == 7 && ((y >= 2 && y <= 9) || (y >= 12 && y <= 18))) ||

            (x == 8 && ((y >= 1 && y <= 2) || (y >= 5 && y <= 8) || (y >= 12 && y <= 18))) ||

            (x == 9 && ((y >= 1 && y <= 3) || (y >= 5 && y <= 7) || (y >= 12 && y <= 18))) ||

            (x == 10 && ((y >= 1 && y <= 2) || (y >= 5 && y <= 6) || (y >= 11 && y <= 13))) ||

            (x == 11 && ((y >= 1 && y <= 3) || (y >= 5 && y <= 6) || (y >= 10 && y <= 18))) ||

            (x == 12 && ((y >= 1 && y <= 2) || (y >= 5 && y <= 6) || (y >= 9 && y <= 18))) ||

            (x == 13 && ((y >= 2 && y <= 6) || (y >= 8 && y <= 18)))
        ) {
            vermelho = 0;
            verde = 0;
            azul = 0;
        }

        //Condições para marrom
        else if (
            (x == 7 && (y >= 10 && y <= 11)) ||

            (x == 8 && (y >= 9 && y <= 11)) ||

            (x == 9 && (y >= 8 && y <= 11)) ||

            (x == 10 && (y >= 7 && y <= 10)) ||

            (x == 11 && (y >= 7 && y <= 9)) ||

            (x == 12 && (y >= 7 && y <= 8)) ||

            (x == 13 && y == 7)
        ) {
            vermelho = 4;
            verde = 2;
            azul = 2;
        }

        //Condições para rosa cor de pele
        else if (
            ((x == 8 || x == 12 || x == 10) && (y >= 3 && y <= 4)) ||
            ((x == 9 || x == 11) && y == 4) ||
            ((x == 5 || x == 6 || x == 14 || x == 15)  && y == 12)
        ) {
            vermelho = 7;
            verde = 6;
            azul = 5;
        }

        if (y == 0 || y == 20) {
            azul = 7; 
            verde = 7; 
            vermelho = 6;
        }

        edit_sprite_wsm(endereco, azul, verde, vermelho);
    }
}

//-----------------------------------------------------------------------------------------------------------------------//
//LOSANGO -> Exit

    // Iterar por cada pixel do sprite de 20x20
    for (x = 0; x < 20; x++) {
        for (y = 0; y < 20; y++) {
            int endereco = 10400 + y * 20 + x;

            // Desenhar o fundo como cor nula (0, 0, 0)
            int azul = 7, verde = 7, vermelho = 6;

            // Desenhar o contorno verde
            if ((abs(x - 9) + abs(y - 9) >= 7 && abs(x - 9) + abs(y - 9) <= 8) ||
                (abs(x - 10) + abs(y - 10) >= 7 && abs(x - 10) + abs(y - 10) <= 8)
            ) {
                azul = 0;
                verde = 7;
                vermelho = 0;
            }

            // Desenhar o losango vermelho
            if ((abs(x - 9) + abs(y - 9) >= 5 && abs(x - 9) + abs(y - 9) <= 6) ||
                (abs(x - 10) + abs(y - 10) >= 5 && abs(x - 10) + abs(y - 10) <= 6)
            ) {
                azul = 0;
                verde = 0;
                vermelho = 7;
            }

            // Desenhar a cruz azul
            if (x == 9 || x == 10 || y == 9 || y == 10) {
                azul = 6;
                verde = 4;
                vermelho = 3;
            }

            if (y == 0 || y == 20) {
                azul = 7; 
                verde = 7; 
                vermelho = 6;
            }

            edit_sprite_wsm(endereco, azul, verde, vermelho);
        }
    }

//-----------------------------------------------------------------------------------------------------------------------//
//PAUSE -> Pause

    //Loop através de cada pixel
    for (int y = 0; y < 21; y++) {
        for (int x = 0; x < 20; x++) {
            int endereco = 10800 + y * 20 + x;
            int vermelho = 6, verde = 7, azul = 7;

            // Desenha a borda do retângulo
            if ((x >= 3 && x <= 4 && y >= 3 && y <= 16) || // Linha vertical esquerda engrossada
                (x >= 15 && x <= 16 && y >= 3 && y <= 16) || // Linha vertical direita engrossada
                (y >= 3 && y <= 4 && x >= 3 && x <= 16) || // Linha horizontal superior engrossada
                (y >= 15 && y <= 16 && x >= 3 && x <= 16) || // Linha horizontal inferior engrossada
                (x >= 8 && x <= 9 && y >= 8 && y <= 11) || // Linha vertical interna esquerda engrossada
                (x >= 11 && x <= 12 && y >= 8 && y <= 11)) // Linha vertical interna direita engrossada
            {
                vermelho = 7;
                verde = 0;
                azul = 0;
            }

            if (y == 0 || y == 20) {
                azul = 7; 
                verde = 7; 
                vermelho = 6;
            }

            // Atualiza o pixel
            edit_sprite_wsm(endereco, azul, verde, vermelho);
        }
    }

//-----------------------------------------------------------------------------------------------------------------------//
//LOUD -> Jogar Novamente

// Loop para percorrer os pixels da imagem 20x20
for (y = 0; y < 21; y++) {
    for (x = 0; x < 20; x++) {
        int endereco = 11200 + y * 20 + x;
        int azul = 7, verde = 7, vermelho = 6;

        // Desenhando o triângulo conforme a imagem fornecida
        if (x <= 10 && y >= x && y <= 19 - x) {
            verde = 7;  // Definindo o pixel como verde
            vermelho = 0;
            azul = 0;
        }

        if (y == 0 || y == 20) {
            azul = 7; 
            verde = 7; 
            vermelho = 6;
        }

        edit_sprite_wsm(endereco, azul, verde, vermelho);
    }
}

//-----------------------------------------------------------------------------------------------------------------------//
//LADRÃO FURTIVO

for (y = 0; y < 21; y++) {
    for (x = 0; x < 20; x++) {
        int endereco = 11600 + y * 20 + x;
        int azul = 7, verde = 7, vermelho = 6; // Cor padrão (transparente)

        //Condições para AMARELO
        if (
            ((x == 5 || x == 15) && (y >= 8 && y <= 11)) ||

            ((x == 6 || x == 14 ) && ((y >= 3 && y <= 5) || (y >= 7 && y <= 11))) ||

            (x == 7 && ((y >= 2 && y <= 9) || (y >= 12 && y <= 18))) ||

            (x == 8 && ((y >= 1 && y <= 2) || (y >= 5 && y <= 8) || (y >= 12 && y <= 18))) ||

            (x == 9 && ((y >= 1 && y <= 3) || (y >= 5 && y <= 7) || (y >= 12 && y <= 18))) ||

            (x == 10 && ((y >= 1 && y <= 2) || (y >= 5 && y <= 6) || (y >= 11 && y <= 13))) ||

            (x == 11 && ((y >= 1 && y <= 3) || (y >= 5 && y <= 6) || (y >= 10 && y <= 18))) ||

            (x == 12 && ((y >= 1 && y <= 2) || (y >= 5 && y <= 6) || (y >= 9 && y <= 18))) ||

            (x == 13 && ((y >= 2 && y <= 6) || (y >= 8 && y <= 18)))
        ) {
            vermelho = 6;
            verde = 6;
            azul = 0;
        }

        //Condições para marrom
        else if ((x == 7 && (y >= 10 && y <= 11)) ||

            (x == 8 && (y >= 9 && y <= 11)) ||

            (x == 9 && (y >= 8 && y <= 11)) ||

            (x == 10 && (y >= 7 && y <= 10)) ||

            (x == 11 && (y >= 7 && y <= 9)) ||

            (x == 12 && (y >= 7 && y <= 8)) ||

            (x == 13 && y == 7)
        ) {
            vermelho = 4;
            verde = 2;
            azul = 2;
        }

        //Condições para rosa cor de pele
        else if (
            ((x == 8 || x == 12 || x == 10) && (y >= 3 && y <= 4)) ||
            ((x == 9 || x == 11) && y == 4) ||
            ((x == 5 || x == 6 || x == 14 || x == 15)  && y == 12)
        ) {
            vermelho = 7;
            verde = 6;
            azul = 5;
        }

        if (y == 0 || y == 20) {
            azul = 7; 
            verde = 7; 
            vermelho = 6;
        }

        edit_sprite_wsm(endereco, azul, verde, vermelho);
    }
}

//-----------------------------------------------------------------------------------------------------------------------//
//POLICIA

for (y = 0; y < 21; y++) {
    for (x = 0; x < 20; x++) {
        int endereco = 12000 + y * 20 + x;
        int azul = 7, verde = 7, vermelho = 6; // Cor padrão (transparente)
        
        //Condições para Azul escuro
        if (
            ((x == 4 || x == 16) && (y >= 8 && y <= 10)) ||

            ((x == 5 || x == 15) && (y >= 7 && y <= 10)) ||

            ((x == 6 || x == 14) && (y >= 6 && y <= 9)) ||

            ((x == 7 || x == 13) && (y == 2 || (y >= 6 && y <= 10) || (y >= 12 && y <= 16))) ||

            (x == 8 && ((y >= 1 && y <= 2) || (y >= 5 && y <= 10) || (y >= 12 && y <= 16))) ||

            (x == 9 && (y == 2 || (y >= 5 && y <= 10) || (y >= 12 && y <= 16))) ||

            (x == 10 && (y == 2 || (y >= 5 && y <= 10) || (y >= 12 && y <= 13))) ||

            (x == 11 && (y == 2 || (y >= 5 && y <= 6) || (y >= 9 && y <= 10) || (y >= 12 && y <= 16))) ||

            (x == 12 && ((y >= 1 && y <= 2) || (y >= 5 && y <= 6) || (y >= 9 && y <= 10) || (y >= 12 && y <= 16)))
        ) {
            vermelho = 0;
            verde = 0;
            azul = 7;
        }

        //Condições para amarelo
        else if ((x == 3 && (y >= 10 && y <= 12)) ||

            ((x == 4 || x == 5) && y == 12) ||

            (x == 9 && y == 1) ||

            (x == 10 && (y == 1 || y == 11)) ||

            (x == 11 && (y == 1 || (y >= 7 && y <= 8))) ||

            (x == 12 && (y >= 7 && y <= 8))
        ) {
            vermelho = 6;
            verde = 6;
            azul = 0;
        }

        //Condições para rosa cor de pele
        else if (
            ((x == 8 || x == 12 || x == 10) && (y >= 3 && y <= 4)) ||
            ((x == 9 || x == 11) && y == 4) ||
            ((x == 4 || x == 5 || x == 15 || x == 16)  && y == 11)
        ) {
            vermelho = 7;
            verde = 6;
            azul = 5;
        }

        
        //Condições para preto
        else if (((x == 7 || x == 8 || x == 12 || x == 13) && (y == 11 || (y >= 17 && y <= 18))) ||

            ((x == 9 || x == 11) && (y == 3 || y == 11 || (y >= 17 && y <= 18)))
        ) {
            vermelho = 0;
            verde = 0;
            azul = 0;
        }

        if (y == 0 || y == 20) {
            azul = 7; 
            verde = 7; 
            vermelho = 6;
        }

        edit_sprite_wsm(endereco, azul, verde, vermelho);
    }
}

//-----------------------------------------------------------------------------------------------------------------------//
//PORTA

for (y = 0; y < 21; y++) {
    for (x = 0; x < 20; x++) {
        int endereco = 12400 + y * 20 + x;
        int azul = 7, verde = 7, vermelho = 6; // Cor padrão (transparente)

        //Condições para preto
        if (
            (x == 3 && (y >= 5 && y <= 17)) ||
            (x == 4 && ((y >= 4 && y <= 5) || y == 18)) ||
            (x == 5 && ((y >= 3 && y <= 4) || y == 18)) ||
            (x == 6 && ((y >= 2 && y <= 3) || y == 18)) ||
            (x == 7 && ((y >= 1 && y <= 2) || y == 18)) ||

            ((x >= 8 && x <= 11) && (y == 1 || y == 18)) ||

            (x == 12 && ((y >= 1 && y <= 2) || y == 18)) ||
            (x == 13 && ((y >= 2 && y <= 3) || y == 18)) ||
            (x == 14 && ((y >= 3 && y <= 4) || y == 18)) ||
            (x == 15 && ((y >= 4 && y <= 5) || y == 18)) ||
            (x == 16 && (y >= 5 && y <= 17))
        ) {
            vermelho = 0;
            verde = 0;
            azul = 0;
        }

        //Condições para maçaneta
        else if (((x == 12 || x == 13) && (y >= 11 && y <= 12))) {
            vermelho = 4;
            verde = 4;
            azul = 4;
        }

        //Condições para cor esquerda
        else if (
            ((x == 4 || x == 15) && (y >= 6 && y <= 17)) ||

            (x == 6 && (y >= 4 && y <= 17)) ||

            (x == 13 && ((y >= 4 && y <= 11) || (y >= 13 && y <= 17))) ||
            
            ((x == 8 || x == 11) && (y >= 3 && y <= 17))
        ) {
            vermelho = 4;
            verde = 3;
            azul = 2;
        }

        //Condições para cor direita
        else if (
            ((x == 5 || x == 14) && (y >= 5 && y <= 17)) ||

            (x == 7 && (y >= 3 && y <= 17)) ||

            (x == 12 && ((y >= 3 && y <= 10) || (y >= 13 && y <= 17)))
        ) {
            vermelho = 4;
            verde = 2;
            azul = 0;
        }

        //Condições para cor central
        else if (((x == 9 || x == 10) && (y >= 2 && y <= 17))) {
            vermelho = 4;
            verde = 3;
            azul = 3;
        }

        if (y == 0 || y == 20) {
            azul = 7; 
            verde = 7; 
            vermelho = 6;
        }

        edit_sprite_wsm(endereco, azul, verde, vermelho);
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

    //Sprite ladrão padrão
    set_sprite_wbr(1, 320, 240, 25, 1);

    //Sprite losango
    set_sprite_wbr(1, 360, 240, 26, 2);

    //Sprite pause 
    set_sprite_wbr(1, 400, 240, 27, 3);

    //Sprite loud
    set_sprite_wbr(1, 280, 240, 28, 4);

    //Sprite ladrão furtivo
    set_sprite_wbr(1, 240, 240, 29, 5);

    //Sprite policia
    set_sprite_wbr(1, 200, 240, 30, 6);

    //Sprite porta
    set_sprite_wbr(1, 160, 240, 31, 7);

//-----------------------------------------------------------------------------------------------------------------------//

    //Fecha arquivo de comunicação com o drivertesteSprite
    close_driver();

    return 0;
}
