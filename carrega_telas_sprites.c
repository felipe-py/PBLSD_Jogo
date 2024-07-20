#include "carrega_telas_sprites.h"
#include "biblioteca_gpu.h"
#include "utils.h"

/* Variáveis usadas para coordenadas X e Y dos blocos do background, e para iterações dos loops */
int x, y;

/**Função para modificar a memória de sprites da GPU e inserir sprites criados para o jogo
 * LADRÃO PADRÃO, SAIR, PAUSE, PLAY, LADRÃO FURTIVO, POLICIAL, PORTA - Respectivamente na ordem
 *                  endereco: variável usada para editar pixel a pixel de um sprite
 *                  azul: tom de azul (0 ao 7)
 *                  verde: tom de verde (0 ao 7)
 *                  vermelho: tom de vermelho (0 ao 7)
 * retorno ->       0 caso seja bem sucedido ou -1 caso ocorra algum erro
 */
int 
carrega_sprites() {
    int endereco, azul, verde, vermelho;

    //LADRÃO PADRÃO
    for (y = 0; y < 21; ++y) {
        for (x = 0; x < 20; ++x) {
            endereco = 10000 + y * 20 + x;
            
            //Cor padrão (transparente)
            azul = 7, verde = 7, vermelho = 6;

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

    //SAIR
    for (x = 0; x < 20; ++x) {
        for (y = 0; y < 21; ++y) {
            endereco = 10400 + y * 20 + x;

            //Cor padrão (transparente)
            azul = 7, verde = 7, vermelho = 6;

            //Desenhar o contorno verde
            if (
                (abs(x - 9) + abs(y - 9) >= 7 && abs(x - 9) + abs(y - 9) <= 8) ||
                (abs(x - 10) + abs(y - 10) >= 7 && abs(x - 10) + abs(y - 10) <= 8)
            ) {
                azul = 0;
                verde = 7;
                vermelho = 0;
            }

            //Desenhar o losango vermelho
            if (
                (abs(x - 9) + abs(y - 9) >= 5 && abs(x - 9) + abs(y - 9) <= 6) ||
                (abs(x - 10) + abs(y - 10) >= 5 && abs(x - 10) + abs(y - 10) <= 6)
            ) {
                azul = 0;
                verde = 0;
                vermelho = 7;
            }

            //Desenhar a cruz azul
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

    //PAUSE
    for (y = 0; y < 21; ++y) {
        for (x = 0; x < 20; ++x) {
            endereco = 10800 + y * 20 + x;

            //Cor padrão (transparente)
            vermelho = 6, verde = 7, azul = 7;

            //Desenha a borda do retângulo
            if (
                (x >= 3 && x <= 4 && y >= 3 && y <= 16) ||
                (x >= 15 && x <= 16 && y >= 3 && y <= 16) ||
                (y >= 3 && y <= 4 && x >= 3 && x <= 16) ||
                (y >= 15 && y <= 16 && x >= 3 && x <= 16) ||
                (x >= 8 && x <= 9 && y >= 8 && y <= 11) ||
                (x >= 11 && x <= 12 && y >= 8 && y <= 11))
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

            edit_sprite_wsm(endereco, azul, verde, vermelho);
        }
    }

    //PLAY
    for (y = 0; y < 21; ++y) {
        for (x = 0; x < 20; ++x) {
            endereco = 11200 + y * 20 + x;

            //Cor padrão (transparente)
            azul = 7, verde = 7, vermelho = 6;

            if (x <= 10 && y >= x && y <= 19 - x) {
                verde = 7;
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

    //LADRÃO FURTIVO
    for (y = 0; y < 21; ++y) {
        for (x = 0; x < 20; ++x) {
            endereco = 11600 + y * 20 + x;

            //Cor padrão (transparente)
            azul = 7, verde = 7, vermelho = 6;

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

    //POLICIA
    for (y = 0; y < 21; ++y) {
        for (x = 0; x < 20; ++x) {
            endereco = 12000 + y * 20 + x;

            //Cor padrão (transparente)
            azul = 7, verde = 7, vermelho = 6;
            
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
            else if (
                    (x == 3 && (y >= 10 && y <= 12)) ||

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
            else if (
                    ((x == 7 || x == 8 || x == 12 || x == 13) && (y == 11 || (y >= 17 && y <= 18))) ||

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

    //PORTA
    for (y = 0; y < 21; ++y) {
        for (x = 0; x < 20; ++x) {
            endereco = 12400 + y * 20 + x;

            //Cor padrão (transparente)
            azul = 7, verde = 7, vermelho = 6;

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
            else if (((x >= 8 && x <= 11) && (y >= 2 && y <= 17))) {
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

    return 0;
}

/**Função para exibir tela inicial do jogo
 * retorno ->       0 caso seja bem sucedido ou -1 caso ocorra algum erro
 */
int 
tela_inicial() {

    //Muda fundo para branco
    set_cor_background_wbr(7, 7, 7);

//ENVOLTO TITULO
    //superior e inferior esquerdo
    for (x = 2; x <= 5; ++x) {
        edit_bloco_background_wbm(x, 6, 0, 0, 0);
        edit_bloco_background_wbm(x, 8, 0, 0, 0);
        edit_bloco_background_wbm(x, 9, 0, 0, 0);
        edit_bloco_background_wbm(x, 36, 0, 0, 0);
        edit_bloco_background_wbm(x, 37, 0, 0, 0);
        edit_bloco_background_wbm(x, 39, 0, 0, 0);
    }

    //superior e inferior direito
    for (x = 74; x <= 77; ++x) {
        edit_bloco_background_wbm(x, 6, 0, 0, 0);
        edit_bloco_background_wbm(x, 8, 0, 0, 0);
        edit_bloco_background_wbm(x, 9, 0, 0, 0);
        edit_bloco_background_wbm(x, 36, 0, 0, 0);
        edit_bloco_background_wbm(x, 37, 0, 0, 0);
        edit_bloco_background_wbm(x, 39, 0, 0, 0);
    }

    //linha superior e inferior
    for (x = 2; x < 78; ++x) {
        edit_bloco_background_wbm(x, 7, 0, 0, 0);
        edit_bloco_background_wbm(x, 38, 0, 0, 0);
    }

    //coluna superior e inferior
    for (y = 10; y < 36; ++y) {
        edit_bloco_background_wbm(3, y, 0, 0, 0);
        edit_bloco_background_wbm(76, y, 0, 0, 0);
    }

//ENVOLTO BOTOES
    //Botao esquerdo
    for (y = 49; y <= 57; ++y) {
        for (x = 10; x <= 22; ++x) {
            if (
                ((y == 49 || y == 57) && (x >= 13 && x <= 19)) ||

                ((y == 50 || y == 56) && ((x >= 12 && x <= 13) || (x >= 19 && x <= 20))) ||

                ((y == 51 || y == 55) && (x == 11 || x == 21)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 10 || x == 22))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

    //Botao direito
    for (y= 49; y <= 57; ++y) {
        for (x = 56; x <= 68; ++x) {
            if (
                ((y == 49 || y == 57) && (x >= 59 && x <= 65)) ||

                ((y == 50 || y == 56) && ((x >= 58 && x <= 59) || (x >= 65 && x <= 66))) ||

                ((y == 51 || y == 55) && (x == 57 || x == 67)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 56 || x == 68))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//SHADOW
    for (y = 12; y <= 19; ++y) {
        for (x = 21; x <= 57; ++x) {
            if (
                (y == 12 && ((x >= 21 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 37) || (x >= 39 && x <= 42) || 
                    (x >= 45 && x <= 49) || (x >= 51 && x <= 52) || (x >= 56 && x <= 57))) ||

                (y == 13 && ((x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) ||
                    (x >= 36 && x <= 37) || (x >= 39 && x <= 40) || (x >= 42 && x <= 43) || (x >= 45 && x <= 46) || (x >= 48 && x <= 49) ||
                    (x >= 51 && x <= 52) || (x >= 56 && x <= 57))) ||

                (y == 14 && ((x >= 21 && x <= 22) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) ||
                    (x >= 39 && x <= 40) || (x >= 42 && x <= 43) || (x >= 45 && x <= 46) || (x >= 48 && x <= 49) || (x >= 51 && x <= 52) || (x >= 56 && x <= 57))) ||

                (y == 15 && ((x >= 22 && x <= 24) || (x >= 27 && x <= 31) || (x >= 33 && x <= 37) || (x >= 39 && x <= 40) || 
                    (x >= 42 && x <= 43) || (x >= 45 && x <= 46) || (x >= 48 && x <= 49) || (x >= 51 && x <= 52) || (x >= 56 && x <= 57))) ||

                ((y == 16 || y == 17) && ((x >= 24 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || (x >= 39 && x <= 40) || 
                    (x >= 42 && x <= 43) || (x >= 45 && x <= 46) || (x >= 48 && x <= 49) || (x >= 51 && x <= 52) || x == 54 || (x >= 56 && x <= 57))) ||

                (y == 18 && ((x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) ||
                    (x >= 36 && x <= 37) || (x >= 39 && x <= 40) || (x >= 42 && x <= 43) || (x >= 45 && x <= 46) || (x >= 48 && x <= 49) ||
                    (x >= 52 && x <= 56))) ||

                (y == 19 && ((x >= 21 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || 
                    (x >= 39 && x <= 42) || (x >= 45 && x <= 49) || x == 53 || x == 55))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//COLLISION
    for (y = 26; y <= 33; ++y) {
        for (x = 14; x <= 65; ++x) {
            if (
                (y == 26 && ((x >= 14 && x <= 18) || (x >= 20 && x <= 24) || (x >= 26 && x <= 27) || (x >= 32 && x <= 33) || (x >= 38 && x <= 41) || 
                    (x >= 43 && x <= 47) || (x >= 49 && x <= 52) || (x >= 54 && x <= 58) || (x >= 60 && x <= 61) || x == 64 || x == 65)) ||

                (y == 27 && ((x >= 14 && x <= 15) || (x >= 17 && x <= 18) || (x >= 20 && x <= 21) || (x >= 23 && x <= 24) || (x >= 26 && x <= 27) || (x >= 32 && x <= 33) || 
                    (x >= 39 && x <= 40) || (x >= 43 && x <= 44) || (x >= 46 && x <= 47) || (x >= 50 && x <= 51) || (x >= 54 && x <= 55) || (x >= 57 && x <= 58) || 
                    (x >= 60 && x <= 62) || x == 64 || x == 65)) ||

                (y == 28 && ((x >= 14 && x <= 15) || (x >= 20 && x <= 21) || (x >= 23 && x <= 24) || (x >= 26 && x <= 27) || (x >= 32 && x <= 33) || 
                    (x >= 39 && x <= 40) || (x >= 43 && x <= 44) || (x >= 50 && x <= 51) || (x >= 54 && x <= 55) || (x >= 57 && x <= 58) || 
                    (x >= 60 && x <= 65))) ||

                (y == 29 && ((x >= 14 && x <= 15) || (x >= 20 && x <= 21) || (x >= 23 && x <= 24) || (x >= 26 && x <= 27) || (x >= 32 && x <= 33) || 
                    (x >= 39 && x <= 40) || (x >= 44 && x <= 46) || (x >= 50 && x <= 51) || (x >= 54 && x <= 55) || (x >= 57 && x <= 58) || 
                    (x >= 60 && x <= 61) || (x >= 63 && x <= 65))) ||

                (y == 30 && ((x >= 14 && x <= 15) || (x >= 20 && x <= 21) || (x >= 23 && x <= 24) || (x >= 26 && x <= 27) || 
                    (x >= 32 && x <= 33) || (x >= 39 && x <= 40) || (x >= 46 && x <= 47) || (x >= 50 && x <= 51) || (x >= 54 && x <= 55) || 
                    (x >= 57 && x <= 58) || (x >= 60 && x <= 61) || x == 64 || x == 65)) ||
                    
                (y == 31 && ((x >= 14 && x <= 15) || (x >= 20 && x <= 21) || (x >= 23 && x <= 24) || (x >= 26 && x <= 27) || 
                    (x >= 32 && x <= 33) || (x >= 39 && x <= 40) || (x >= 46 && x <= 47) || (x >= 50 && x <= 51) || (x >= 54 && x <= 55) || 
                    (x >= 57 && x <= 58) || (x >= 60 && x <= 61) || x == 64 || x == 65)) ||

                (y == 32 && ((x >= 14 && x <= 15) || (x >= 17 && x <= 18) || (x >= 20 && x <= 21) || (x >= 23 && x <= 24) || (x >= 26 && x <= 27) || 
                    (x >= 32 && x <= 33) || (x >= 39 && x <= 40) || (x >= 43 && x <= 44) || (x >= 46 && x <= 47) || (x >= 50 && x <= 51) || (x >= 54 && x <= 55) || 
                    (x >= 57 && x <= 58) || (x >= 60 && x <= 61) || x == 64 || x == 65)) ||

                (y == 33 && ((x >= 14 && x <= 18) || (x >= 20 && x <= 24) || (x >= 26 && x <= 30) || (x >= 32 && x <= 36) || (x >= 38 && x <= 41) || 
                    (x >= 43 && x <= 47) || (x >= 49 && x <= 52) || (x >= 54 && x <= 58) || (x >= 60 && x <= 61) || x == 64 || x == 65))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//BOTOES - SPRITES 
    //Sprite loud - PLAY
    set_sprite_wbr(1, 128, 416, 28, 16);

    //Sprite losango - SAIR
    set_sprite_wbr(1, 488, 416, 26, 17);

    return 0;
}

/**Função para exibir tela de vitória do jogo
 * retorno ->       0 caso seja bem sucedido ou -1 caso ocorra algum erro
 */
int 
tela_win() {

//ENVOLTO TITULO
    //superior e inferior esquerdo
    for (x = 15; x <= 18; ++x) {
        edit_bloco_background_wbm(x, 11, 0, 0, 0);
        edit_bloco_background_wbm(x, 13, 0, 0, 0);
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 27, 0, 0, 0);
        edit_bloco_background_wbm(x, 28, 0, 0, 0);
        edit_bloco_background_wbm(x, 30, 0, 0, 0);
    }

    //superior e inferior direito
    for (x = 63; x <= 66; ++x) {
        edit_bloco_background_wbm(x, 11, 0, 0, 0);
        edit_bloco_background_wbm(x, 13, 0, 0, 0);
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 27, 0, 0, 0);
        edit_bloco_background_wbm(x, 28, 0, 0, 0);
        edit_bloco_background_wbm(x, 30, 0, 0, 0);
    }

    //linha superior e inferior
    for (x = 15; x < 67; ++x) {
        edit_bloco_background_wbm(x, 12, 0, 0, 0);
        edit_bloco_background_wbm(x, 29, 0, 0, 0);
    }

    //coluna superior e inferior
    for (y = 15; y < 27; ++y) {
        edit_bloco_background_wbm(16, y, 0, 0, 0);
        edit_bloco_background_wbm(65, y, 0, 0, 0);
    }

//YOU WIN
    for (y = 17; y <= 24; ++y) {
        for (x = 21; x <= 59; ++x) {
            if (
                (y == 17 && ((x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || 
                    (x >= 41 && x <= 42) || (x >= 46 && x <= 47) || (x >= 49 && x <= 52) || (x >= 54 && x <= 55) || (x >= 58 && x <= 59))) ||

                (y == 18 && ((x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || 
                    (x >= 41 && x <= 42) || (x >= 46 && x <= 47) || (x >= 50 && x <= 51) || (x >= 54 && x <= 56) || (x >= 58 && x <= 59))) ||

               (y == 19 && ((x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || 
                    (x >= 41 && x <= 42) || (x >= 46 && x <= 47) || (x >= 50 && x <= 51) || (x >= 54 && x <= 59))) ||

                (y == 20 && ((x >= 22 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || 
                    (x >= 41 && x <= 42) || (x >= 46 && x <= 47) || (x >= 50 && x <= 51) || (x >= 54 && x <= 55) || (x >= 57 && x <= 59))) ||

                ((y == 21 || y == 22) && ((x >= 23 && x <= 24) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || (x >= 41 && x <= 42) || 
                    x == 44 || (x >= 46 && x <= 47) || (x >= 50 && x <= 51) || (x >= 54 && x <= 55) || (x >= 58 && x <= 59))) ||

                (y == 23 && ((x >= 23 && x <= 24) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || (x >= 42 && x <= 46) || 
                    (x >= 50 && x <= 51) || (x >= 54 && x <= 55) || (x >= 58 && x <= 59))) ||

                (y == 24 && ((x >= 23 && x <= 24) || (x >= 27 && x <= 31) || (x >= 33 && x <= 37) || x == 43 || x == 45 || (x >= 49 && x <= 52) || (x >= 54 && x <= 55) || 
                    (x >= 58 && x <= 59)))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//ENVOLTO BOTOES
    //Botao esquerdo
    for (y = 49; y <=57 ; ++y) {
        for (x = 10; x <= 22; ++x) {
            if (
                ((y == 49 || y == 57) && (x >= 13 && x <= 19)) ||

                ((y == 50 || y == 56) && ((x >= 12 && x <= 13) || (x >= 19 && x <= 20))) ||

                ((y == 51 || y == 55) && (x == 11 || x == 21)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 10 || x == 22))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

    //Botao direito
    for (y = 49; y <= 57; ++y) {
        for (x = 56; x <= 68; ++x) {
            if (
                ((y == 49 || y == 57) && (x >= 59 && x <= 65)) ||

                ((y == 50 || y == 56) && ((x >= 58 && x <= 59) || (x >= 65 && x <= 66))) ||

                ((y == 51 || y == 55) && (x == 57 || x == 67)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 56 || x == 68))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//Botoes - SPRITES 
    //Sprite loud - PLAY
    set_sprite_wbr(1, 128, 416, 28, 16);

    //Sprite losango - SAIR
    set_sprite_wbr(1, 488, 416, 26, 17);

    return 0;
}

/**Função para exibir tela de derrota do jogo
 * retorno ->       0 caso seja bem sucedido ou -1 caso ocorra algum erro
 */
int 
tela_lose() {

//ENVOLTO BOTOES
    //Botao esquerdo
    for (y = 49; y <= 57; ++y){
        for (x = 10; x <= 22; ++x){
            if (
                ((y == 49 || y == 57) && (x >= 13 && x <= 19)) ||

                ((y == 50 || y == 56) && ((x >= 12 && x <= 13) || (x >= 19 && x <= 20))) ||

                ((y == 51 || y == 55) && (x == 11 || x == 21)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 10 || x == 22))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

    //Botao direito
    for (y = 49; y <= 57; ++y) {
        for (x = 56; x <= 68; ++x) {
            if (
                ((y == 49 || y == 57) && (x >= 59 && x <= 65)) ||

                ((y == 50 || y == 56) && ((x >= 58 && x <= 59) || (x >= 65 && x <= 66))) ||

                ((y == 51 || y == 55) && (x == 57 || x == 67)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 56 || x == 68))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//ENVOLTO TITULO
    //superior e inferior esquerdo
    for (x = 9; x <= 12; ++x) {
        edit_bloco_background_wbm(x, 11, 0, 0, 0);
        edit_bloco_background_wbm(x, 13, 0, 0, 0);
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 27, 0, 0, 0);
        edit_bloco_background_wbm(x, 28, 0, 0, 0);
        edit_bloco_background_wbm(x, 30, 0, 0, 0);
    }

    //superior e inferior direito
    for (x = 68; x <= 71; ++x) {
        edit_bloco_background_wbm(x, 11, 0, 0, 0);
        edit_bloco_background_wbm(x, 13, 0, 0, 0);
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 27, 0, 0, 0);
        edit_bloco_background_wbm(x, 28, 0, 0, 0);
        edit_bloco_background_wbm(x, 30, 0, 0, 0);
    }

    //linha superior e inferior
    for (x = 9; x < 72; ++x) {
        edit_bloco_background_wbm(x, 12, 0, 0, 0);
        edit_bloco_background_wbm(x, 29, 0, 0, 0);
    }

    //coluna superior e inferior
    for (y = 15; y < 27; ++y) {
        edit_bloco_background_wbm(10, y, 0, 0, 0);
        edit_bloco_background_wbm(70, y, 0, 0, 0);
    }

    //GAME OVER
    for (y = 17; y <= 24; ++y) {
        for (x = 15; x <= 65; ++x) {
            if (
                (y == 17 && ((x >= 15 && x <= 19) || (x >= 21 && x <= 25) || (x >= 27 && x <= 28) || (x >= 32 && x <= 33) || 
                    (x >= 35 && x <= 39) || (x >= 43 && x <= 47) || (x >= 49 && x <= 50) || (x >= 52 && x <= 53) || 
                    (x >= 55 && x <= 59) || (x >= 61 && x <= 65))) ||

                (y == 18 && ((x >= 15 && x <= 16) || (x >= 18 && x <= 19) || (x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 29) || (x >= 31 && x <= 33) || 
                    (x >= 35 && x <= 36) || (x >= 38 && x <= 39) || (x >= 43 && x <= 44) || (x >= 46 && x <= 47) || (x >= 49 && x <= 50) || (x >= 52 && x <= 53) || (x >= 55 && x <= 56) || 
                    (x >= 58 && x <= 59) || (x >= 61 && x <= 62) || (x >= 64 && x <= 65))) ||

                (y == 19 && ((x >= 15 && x <= 16) || (x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 33) || 
                    (x >= 35 && x <= 36) || (x >= 43 && x <= 44) || (x >= 46 && x <= 47) || (x >= 49 && x <= 50) || (x >= 52 && x <= 53) || 
                    (x >= 55 && x <= 56) || (x >= 61 && x <= 62) || (x >= 64 && x <= 65))) ||

                (y == 20 && ((x >= 15 && x <= 16) || (x >= 18 && x <= 19) || (x >= 21 && x <= 25) || (x >= 27 && x <= 28) || x == 30 || 
                    (x >= 32 && x <= 33) || (x >= 35 && x <= 38) || (x >= 43 && x <= 44) || (x >= 46 && x <= 47) || (x >= 49 && x <= 50) || (x >= 52 && x <= 53) || 
                    (x >= 55 && x <= 58) || (x >= 61 && x <= 64))) ||

                ((y == 21 || y == 22) && ((x >= 15 && x <= 16) || (x >= 18 && x <= 19) || (x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 28) || 
                    (x >= 32 && x <= 33) || (x >= 35 && x <= 36) || (x >= 43 && x <= 44) || (x >= 46 && x <= 47) || (x >= 49 && x <= 50) || (x >= 52 && x <= 53) || 
                    (x >= 55 && x <= 56) || (x >= 61 && x <= 62) || (x >= 64 && x <= 65))) ||

                (y == 23 && ((x >= 15 && x <= 16) || (x >= 18 && x <= 19) || (x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 28) || (x >= 32 && x <= 33) || 
                    (x >= 35 && x <= 36) || (x >= 38 && x <= 39) || (x >= 43 && x <= 44) || (x >= 46 && x <= 47) || (x >= 50 && x <= 53) || (x >= 55 && x <= 56) || 
                    (x >= 58 && x <= 59) || (x >= 61 && x <= 62) || (x >= 64 && x <= 65))) ||

                (y == 24 && ((x >= 15 && x <= 19) || (x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 28) || (x >= 32 && x <= 33) || (x >= 35 && x <= 39) || (x >= 43 && x <= 47) || 
                    (x >= 51 && x <= 53) || (x >= 55 && x <= 59) || (x >= 61 && x <= 62) || (x >= 64 && x <= 65)))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//BOTOES - SPRITES 
    //Sprite loud - PLAY
    set_sprite_wbr(1, 128, 416, 28, 16);

    //Sprite losango - SAIR
    set_sprite_wbr(1, 488, 416, 26, 17);

    return 0;
}

/**Função para exibir tela de saída do jogo
 * retorno ->       0 caso seja bem sucedido ou -1 caso ocorra algum erro
 */
int 
tela_bye() {

//ENVOLTO TITULO 
    for (x = 4; x <= 6; ++x) {
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 16, 0, 0, 0);
        edit_bloco_background_wbm(x, 42, 0, 0, 0);
        edit_bloco_background_wbm(x, 44, 0, 0, 0);
    }

    for (x = 74; x <= 76; ++x) {
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 16, 0, 0, 0);
        edit_bloco_background_wbm(x, 42, 0, 0, 0);
        edit_bloco_background_wbm(x, 44, 0, 0, 0);
    }

    for (x = 4; x < 77; ++x) {
        edit_bloco_background_wbm(x, 15, 0, 0, 0);
        edit_bloco_background_wbm(x, 43, 0, 0, 0);
    }

    for (y = 17; y < 42; ++y) {
        edit_bloco_background_wbm(5, y, 0, 0, 0);
        edit_bloco_background_wbm(75, y, 0, 0, 0);
    }

//LETRAS E ASTERISCOS
    for (y = 20; y <= 37; ++y) {
        for (x = 10; x <= 70; ++x) {
            if (
                (y == 20 && (x == 11 || (x >= 14 && x <= 17) || (x >= 25 && x <= 27) || (x >= 36 && x <= 38) || (x >= 43 && x <= 50))) ||
                
                (y == 21 && ((x >= 11 && x <= 18) || (x >= 25 && x <= 28) || x == 31 || x == 32 || (x >= 35 && x <= 38) || (x >= 43 && x <= 50))) ||
                
                (y == 22 && (x == 11 || x == 12 || (x >= 17 && x <= 19) || (x >= 26 && x <= 28) || x == 31 || x == 32 || (x >= 35 && x <= 37) || x == 43 || x == 44 || x == 49 || x == 50)) ||
                
                (y == 23 && (x == 11 || x == 12 || (x >= 18 && x <= 20) || (x >= 27 && x <= 29) || x == 31 || x == 32 || (x >= 34 && x <= 36) || (x >= 42 && x <= 46))) ||
                
                (y == 24 && (x == 11 || x == 12 || (x >= 19 && x <= 21) || (x >= 28 && x <= 29) || x == 31 || x == 32 || (x >= 34 && x <= 35) || (x >= 42 && x <= 46))) ||
                
                (y == 25 && ((x >= 10 && x <= 13) || (x >= 20 && x <= 21) || (x >= 28 && x <= 35) || (x >= 42 && x <= 46))) ||
                
                (y == 26 && ((x >= 10 && x <= 13) || (x >= 19 && x <= 21) || (x >= 28 && x <= 35) || (x >= 42 && x <= 46))) ||
                
                (y == 27 && ((x >= 10 && x <= 13) || (x >= 18 && x <= 21) || x == 26 || (x >= 31 && x <= 32) || x == 37 || (x >= 43 && x <= 44) || (x >= 49 && x <= 50))) ||
                
                (y == 28 && ((x >= 10 && x <= 20) || (x >= 26 && x <= 37) || (x >= 43 && x <= 50))) ||
                
                (y == 29 && ((x >= 10 && x <= 20) || x == 26 || (x >= 31 && x <= 32) || x == 37 || (x >= 43 && x <= 50))) ||
                
                (y == 30 && ((x >= 10 && x <= 13) || (x >= 18 && x <= 21) || x == 26 || (x >= 31 && x <= 32) || x == 37 || (x >= 43 && x <= 44) || (x >= 49 && x <= 50))) ||
                
                (y == 31 && ((x >= 10 && x <= 13) || (x >= 19 && x <= 21) || (x >= 29 && x <= 34) || (x >= 42 && x <= 46))) ||
                
                (y == 32 && ((x >= 10 && x <= 13) || (x >= 20 && x <= 21) || (x >= 29 && x <= 34) || (x >= 42 && x <= 46))) ||
                
                (y == 33 && (x == 11 || x == 12 || (x >= 19 && x <= 21) || (x >= 30 && x <= 33) || (x >= 42 && x <= 46) || x == 55 || x == 57 || x == 61 || x == 63 || x == 67 || x == 69)) ||
                
                (y == 34 && (x == 11 || x == 12 || (x >= 18 && x <= 20) || (x >= 30 && x <= 33) || (x >= 42 && x <= 46) || (x >= 54 && x <= 58) || (x >= 60 && x <= 64) || (x >= 66 && x <= 70))) ||
                
                (y == 35 && (x == 11 || x == 12 || (x >= 17 && x <= 19) || (x >= 29 && x <= 34) || x == 43 || x == 44 || x == 49 || x == 50 || x == 55 || x == 57 || x == 61 || x == 63 || x == 67 || x == 69)) ||
                
                (y == 36 && ((x >= 11 && x <= 18) || (x >= 29 && x <= 34) || (x >= 43 && x <= 50) || (x >= 54 & x <= 58) || (x >= 60 && x <= 64) || (x >= 66 & x <= 70))) ||
                
                (y == 37 && (x == 11 || (x >= 14 && x <= 17) || (x >= 29 && x <= 34) || (x >= 43 && x <= 50) || x == 55 || x == 57 || x == 61 || x == 63 || x == 67 || x == 69))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

    return 0;
}

/**Função para exibir tela padrão do jogo
 * retorno ->       0 caso seja bem sucedido ou -1 caso ocorra algum erro
 */
int 
tela_padrao() {

//ESTRUTURAS
    //Estrutura quadrado da esquerda
    for (x = 31; x <= 45; ++x) {
        for (y = 45; y <= 59; ++y) {
            edit_bloco_background_wbm(x, y, 0, 0, 0);
        }
    }

    //Coluna da esquerda grande, direita grande e esquerda menor
    for (y = 0; y <= 53; ++y) {
        edit_bloco_background_wbm(9, y, 0, 0, 0);
        edit_bloco_background_wbm(55, y, 0, 0, 0);
        
        if (y >= 6 && y <= 17) {
            edit_bloco_background_wbm(17, y, 0, 0, 0);
        }
    }

    //Linha esquerda pequena
    for (x = 10; x <= 16; ++x) {
        edit_bloco_background_wbm(x, 17, 0, 0, 0);
    }

    //Linha central grande
    for (x = 15; x <= 54; ++x) {
        edit_bloco_background_wbm(x, 33, 0, 0, 0);
    }

    //Linha direita superior 1 e 2 (antes do buraco), e direita inferior
    for (x = 56; x <= 73; ++x) {
        edit_bloco_background_wbm(x, 44, 0, 0, 0);

        if (x <= 70) {
            edit_bloco_background_wbm(x, 7, 0, 0, 0);
        }

        if (x <= 64) {
            edit_bloco_background_wbm(x, 14, 0, 0, 0);
        }
    }

    //Linha direita superior 1 e 2 (depois do buraco)
    for (x = 70; x <= 79; ++x) {
        edit_bloco_background_wbm(x, 14, 0, 0, 0);

        if (x >= 76) {
            edit_bloco_background_wbm(x, 7, 0, 0, 0);
        }
    }

    //Estrutura quadrado da direita
        //Linha topo, meio, base
        for (x = 65; x <= 79; ++x) {
            if (x <= 72) {
                edit_bloco_background_wbm(x, 23, 0, 0, 0);
                edit_bloco_background_wbm(x, 32, 0, 0, 0);
            }

            else if (x >= 74) {
                edit_bloco_background_wbm(x, 27, 0, 0, 0);
            }
        }

        //Coluna esquerda e direita
        for (y = 23; y <= 32; ++y) {
            edit_bloco_background_wbm(64, y, 0, 0, 0);
            edit_bloco_background_wbm(73, y, 0, 0, 0);
        }

//SPRITES
    //Sprite Porta
    set_sprite_wbr(1, PORTA_X, PORTA_Y, 31, 1);

    //Sprite troféu esquerdo
    set_sprite_wbr(1, TROFEU_ESQ_X, TROFEU_ESQ_Y, 24, 2);

    //Sprite troféu direito
    set_sprite_wbr(1, TROFEU_DIR_X, TROFEU_DIR_Y, 24, 3);

    return 0;
}
