#include "biblioteca_gpu.h"
#include <stdlib.h>
#include <math.h>

int main() {

    //Abre arquivo de comunicação com o driver
    if (open_driver( ) == -1){
        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------------//      
    
    //Azul claro (ceu)
    set_cor_background_wbr(7, 7, 7); 

//-----------------------------------------------------------------------------------------------------------------------//   
//CIRCULO

int x, y;

for (y = 0; y < 20; y++) {
    for (x = 0; x < 20; x++) {
        int endereco = 10000 + y * 20 + x;
        int azul = 7, verde = 7, vermelho = 6; // Cor padrão (transparente)

        // Condições para a borda verde
        if ((x == 2 && (y >= 6 && y <= 13)) ||
            (x == 3 && (y >= 4 && y <= 15)) ||
            (x == 4 && (y >= 3 && y <= 16)) ||
            (x == 5 && (y >= 2 && y <= 17)) ||
            (x == 6 && (y >= 1 && y <= 18)) ||
            (x == 7 && (y >= 1 && y <= 18)) ||
            (x == 8 && (y >= 1 && y <= 18)) ||
            (x == 9 && (y >= 1 && y <= 18)) ||
            (x == 10 && (y >= 1 && y <= 18)) ||
            (x == 11 && (y >= 1 && y <= 18)) ||
            (x == 12 && (y >= 1 && y <= 18)) ||
            (x == 13 && (y >= 1 && y <= 18)) ||
            (x == 14 && (y >= 2 && y <= 17)) ||
            (x == 15 && (y >= 3 && y <= 16)) ||
            (x == 16 && (y >= 4 && y <= 15)) ||
            (x == 17 && (y >= 6 && y <= 13))) {
            vermelho = 0;
            verde = 7;
            azul = 0;
        }

        // Condições para o preenchimento azul do círculo
        if ((x >= 3 && x <= 16) &&
            ((y >= 5 && y <= 14) ||
            (x >= 4 && x <= 15 && (y >= 4 && y <= 15)) ||
            (x >= 5 && x <= 14 && (y >= 3 && y <= 16)) ||
            (x >= 6 && x <= 13 && (y >= 2 && y <= 17)) ||
            (x >= 7 && x <= 12 && (y >= 2 && y <= 17)) ||
            (x >= 8 && x <= 11 && (y >= 1 && y <= 18)))) {
            vermelho = 0;
            verde = 0;
            azul = 7;
        }

        edit_sprite_wsm(endereco, azul, verde, vermelho);
    }
}

//-----------------------------------------------------------------------------------------------------------------------//
//LOSANGO

    // Iterar por cada pixel do sprite de 20x20
    for (x = 0; x < 20; x++) {
        for (y = 0; y < 20; y++) {
            int endereco = 10400 + y * 20 + x;

            // Desenhar o fundo como cor nula (0, 0, 0)
            int azul = 7;
            int verde = 7;
            int vermelho = 6;

            // Desenhar o contorno verde
            if ((abs(x - 9) + abs(y - 9) >= 7 && abs(x - 9) + abs(y - 9) <= 8) ||
                (abs(x - 10) + abs(y - 10) >= 7 && abs(x - 10) + abs(y - 10) <= 8)) {
                azul = 0;
                verde = 7;
                vermelho = 0;
            }

            // Desenhar o losango vermelho
            if ((abs(x - 9) + abs(y - 9) >= 5 && abs(x - 9) + abs(y - 9) <= 6) ||
                (abs(x - 10) + abs(y - 10) >= 5 && abs(x - 10) + abs(y - 10) <= 6)) {
                azul = 0;
                verde = 0;
                vermelho = 7;
            }

            // Desenhar a cruz azul
            if (x == 9 || x == 10 || y == 9 || y == 10) {
                azul = 7;
                verde = 0;
                vermelho = 0;
            }

            if (y == 0) {
                azul = 7; 
                verde = 7; 
                vermelho = 6;
            }

            edit_sprite_wsm(endereco, azul, verde, vermelho);
        }
    }

//-----------------------------------------------------------------------------------------------------------------------//
//PAUSE

    //Loop através de cada pixel
    for (int y = 0; y < 20; y++) {
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

            // Atualiza o pixel
            edit_sprite_wsm(endereco, azul, verde, vermelho);
        }
    }

//-----------------------------------------------------------------------------------------------------------------------//
//LOUD

// Loop para percorrer os pixels da imagem 20x20
for (y = 0; y < 20; y++) {
    for (x = 0; x < 20; x++) {
        int endereco = 11200 + y * 20 + x;
        int azul = 7, verde = 7, vermelho = 6;

        // Desenhando o triângulo conforme a imagem fornecida
        if (x <= 10 && y >= x && y <= 19 - x) {
            verde = 7;  // Definindo o pixel como verde
            vermelho = 0;
            azul = 0;
        }

        if (y == 0) {
            azul = 7; 
            verde = 7; 
            vermelho = 6;
        }

        edit_sprite_wsm(endereco, azul, verde, vermelho);
    }
}

//-----------------------------------------------------------------------------------------------------------------------//
//X

// Loop para percorrer os pixels da imagem 20x20
for (y = 0; y < 20; y++) {
    for (x = 0; x < 20; x++) {
        int endereco = 11600 + y * 20 + x;
        int azul = 7, verde = 7, vermelho = 6; // Cor padrão (transparente)

        // Desenhando o "X" vermelho com borda verde
        if (abs(x - y) <= 1 || abs(x - (19 - y)) <= 1) {
            vermelho = 7;  // Definindo o pixel como vermelho
            verde = 0;
            azul = 0;
        }

        // Adicionando a borda verde ao redor do "X"
        if ((abs(x - y) == 2 || abs(x - (19 - y)) == 2) || 
            (abs(x - y) == 1 && abs(x - (19 - y)) == 1)) {
            vermelho = 0;
            verde = 7;
            azul = 0;
        }

        if (y == 0) {
            azul = 7; 
            verde = 7; 
            vermelho = 6;
        }

        edit_sprite_wsm(endereco, azul, verde, vermelho);
    }
}

//-----------------------------------------------------------------------------------------------------------------------//
//COROA

    // Loop para percorrer os pixels da imagem 20x20
    for (y = 0; y < 20; y++) {
        for (x = 0; x < 20; x++) {
            int endereco = 12000+y * 20 + x;
            int azul = 7, verde = 7, vermelho = 6;

            // Desenhando a coroa conforme a imagem fornecida
            if (
                // Parte amarela
                (y == 10 && (x >= 0 && x <= 4 || x >= 6 && x <= 8 || x >= 12 && x <= 14 || x >= 16 && x <= 19)) ||
                (y == 11 && (x >= 0 && x <= 19)) ||
                (y == 12 && (x >= 0 && x <= 19)) ||
                (y == 13 && (x >= 0 && x <= 19)) ||
                (y == 14 && (x >= 0 && x <= 19)) ||
                (y == 15 && (x >= 0 && x <= 19)) ||
                (y == 16 && (x >= 0 && x <= 19)) ||
                (y == 17 && (x >= 0 && x <= 19)) ||
                (y == 18 && (x >= 0 && x <= 19)) ||
                (y == 19 && (x >= 0 && x <= 19)) ||
                
                // Parte vermelha
                (y == 9 && (x >= 5 && x <= 15)) ||
                (y == 8 && (x >= 6 && x <= 14)) ||
                (y == 7 && (x >= 7 && x <= 13)) ||
                (y == 6 && (x >= 8 && x <= 12)) ||
                (y == 5 && (x >= 9 && x <= 11)) ||
                (y == 4 && x == 10)
            ) {
                if (y >= 10) {
                    verde = 6;  // Definindo a parte inferior como amarela
                    vermelho = 6;
                    azul = 0;
                } else {
                    vermelho = 6;  // Definindo a parte superior como vermelha
                    azul=0;
                    verde=0;
                }
            }

            edit_sprite_wsm(endereco, azul, verde, vermelho);
        }
    }

//-----------------------------------------------------------------------------------------------------------------------//

    //Sprite quadrado
    set_sprite_wbr(1, 320, 240, 25, 1);

    //Sprite triangulo
    set_sprite_wbr(1, 360, 240, 26, 2);

    //Sprite pause 
    set_sprite_wbr(1, 400, 240, 27, 3);

    //Sprite loud
    set_sprite_wbr(1, 280, 240, 28, 4);

    //Sprite X
    set_sprite_wbr(1, 280, 200, 29, 5);

    //Sprite COROA
    set_sprite_wbr(1, 320, 200, 30, 6);

//-----------------------------------------------------------------------------------------------------------------------//

    //Remove estruturas da tela
    //limpar_tela();

//-----------------------------------------------------------------------------------------------------------------------//

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
