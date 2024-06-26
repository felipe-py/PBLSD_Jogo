#include "biblioteca_gpu.h"

int main() {

    //Abre arquivo de comunicação com o driver
    if (open_driver( ) == -1){
        return -1;
    }

    int x,y;

/*
//-----------------------------------------------------------------------------------------------------------------------//
//TELA BYE

//ENVOLTO TITULO 
    for (x = 4; x <= 6; x++) {
        edit_bloco_background_wbm(x, 14, 0, 3, 5);
        edit_bloco_background_wbm(x, 16, 0, 3, 5);
        edit_bloco_background_wbm(x, 42, 0, 3, 5);
        edit_bloco_background_wbm(x, 44, 0, 3, 5);
    }

    for (x = 74; x <= 76; x++) {
        edit_bloco_background_wbm(x, 14, 0, 3, 5);
        edit_bloco_background_wbm(x, 16, 0, 3, 5);
        edit_bloco_background_wbm(x, 42, 0, 3, 5);
        edit_bloco_background_wbm(x, 44, 0, 3, 5);
    }

    for (x = 4; x < 77; x++) {
        edit_bloco_background_wbm(x, 15, 0, 3, 5);
        edit_bloco_background_wbm(x, 43, 0, 3, 5);
    }

    for (y = 17; y < 42; y++) {
        edit_bloco_background_wbm(5, y, 0, 3, 5);
        edit_bloco_background_wbm(75, y, 0, 3, 5);
    }

//LETRAS E ASTERISCOS
    for(y=20; y<=37; y++){
        for(x=10; x<=70; x++){
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
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

//-----------------------------------------------------------------------------------------------------------------------//
//TELA INICIO
    
//ENVOLTO TITULO
    //superior e inferior esquerdo
    for (x = 2; x <= 5; x++) {
        edit_bloco_background_wbm(x, 6, 0, 3, 5);
        edit_bloco_background_wbm(x, 8, 0, 3, 5);
        edit_bloco_background_wbm(x, 9, 0, 3, 5);
        edit_bloco_background_wbm(x, 36, 0, 3, 5);
        edit_bloco_background_wbm(x, 37, 0, 3, 5);
        edit_bloco_background_wbm(x, 39, 0, 3, 5);
    }

    //superior e inferior direito
    for (x = 74; x <= 77; x++) {
        edit_bloco_background_wbm(x, 6, 0, 3, 5);
        edit_bloco_background_wbm(x, 8, 0, 3, 5);
        edit_bloco_background_wbm(x, 9, 0, 3, 5);
        edit_bloco_background_wbm(x, 36, 0, 3, 5);
        edit_bloco_background_wbm(x, 37, 0, 3, 5);
        edit_bloco_background_wbm(x, 39, 0, 3, 5);
    }

    //linha superior e inferior
    for (x = 2; x < 78; x++) {
        edit_bloco_background_wbm(x, 7, 0, 3, 5);
        edit_bloco_background_wbm(x, 38, 0, 3, 5);
    }

    //coluna superior e inferior
    for (y = 10; y < 36; y++) {
        edit_bloco_background_wbm(3, y, 0, 3, 5);
        edit_bloco_background_wbm(76, y, 0, 3, 5);
    }

//ENVOLTO BOTOES
    //Botao esquerdo
    for(y=49; y<=57; y++){
        for(x=10; x<=22; x++){
            if (
                ((y == 49 || y == 57) && (x >= 13 && x <= 19)) ||

                ((y == 50 || y == 56) && ((x >= 12 && x <= 13) || (x >= 19 && x <= 20))) ||

                ((y == 51 || y == 55) && (x == 11 || x == 21)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 10 || x == 22))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

    //Botao direito
    for(y=49; y<=57; y++){
        for(x=56; x<=68; x++){
            if (
                ((y == 49 || y == 57) && (x >= 59 && x <= 65)) ||

                ((y == 50 || y == 56) && ((x >= 58 && x <= 59) || (x >= 65 && x <= 66))) ||

                ((y == 51 || y == 55) && (x == 57 || x == 67)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 56 || x == 68))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

//BOTOES - SPRITES 
    //Sprite loud - PLAY
    set_sprite_wbr(1, 128, 416, 28, 4);

    //Sprite losango - SAIR
    set_sprite_wbr(1, 488, 416, 26, 5);

//TIC-TAC-TOE
    for(y=12; y<=19; y++){
        for(x=8; x<=70; x++){
            if (
            (y == 12 && ((x >= 8 && x <= 11) || (x >= 13 && x <= 16) || (x >= 18 && x <= 22) || (x >= 30 && x <= 34) || (x >= 36 && x <= 40) || 
                (x >= 42 && x <= 46) || (x >= 55 && x <= 58) || (x >= 60 && x <= 64) || (x >= 66 && x <= 70))) ||

            (y == 13 && ((x >= 9 && x <= 10) || (x >= 14 && x <= 15) || (x >= 18 && x <= 19) || (x >= 21 && x <= 22) || (x >= 32 && x <= 33) ||
                (x >= 36 && x <= 37) || (x >= 39 && x <= 40) || (x >= 42 && x <= 43) || (x >= 45 && x <= 46) || (x >= 56 && x <= 57) ||
                (x >= 60 && x <= 61) || (x >= 63 && x <= 64) || (x >= 66 && x <= 67) || (x >= 69 && x <= 70))) ||

            (y == 14 && ((x >= 9 && x <= 10) || (x >= 14 && x <= 15) || (x >= 18 && x <= 19) || (x >= 32 && x <= 33) || (x >= 36 && x <= 37) ||
                (x >= 39 && x <= 40) || (x >= 42 && x <= 43) || (x >= 56 && x <= 57) ||
                (x >= 60 && x <= 61) || (x >= 63 && x <= 64) || (x >= 66 && x <= 67))) ||

            (y == 15 && ((x >= 9 && x <= 10) || (x >= 14 && x <= 15) || (x >= 18 && x <= 19) || (x >= 24 && x <= 29) || (x >= 32 && x <= 33) || 
                (x >= 36 && x <= 40) || (x >= 42 && x <= 43) || (x >= 48 && x <= 53) || (x >= 56 && x <= 57) ||
                (x >= 60 && x <= 61) || (x >= 63 && x <= 64) || (x >= 66 && x <= 69))) ||

            (y == 16 && ((x >= 9 && x <= 10) || (x >= 14 && x <= 15) || (x >= 18 && x <= 19) || (x >= 24 && x <= 29) || (x >= 32 && x <= 33) || 
                (x >= 36 && x <= 37) || (x >= 39 && x <= 40) || (x >= 42 && x <= 43) || (x >= 48 && x <= 53) || (x >= 56 && x <= 57) ||
                (x >= 60 && x <= 61) || (x >= 63 && x <= 64) || (x >= 66 && x <= 69))) ||
                
            (y == 17 && ((x >= 9 && x <= 10) || (x >= 14 && x <= 15) || (x >= 18 && x <= 19) || (x >= 32 && x <= 33) || (x >= 36 && x <= 37) ||
                (x >= 39 && x <= 40) || (x >= 42 && x <= 43) || (x >= 56 && x <= 57) ||
                (x >= 60 && x <= 61) || (x >= 63 && x <= 64) || (x >= 66 && x <= 67))) ||

            (y == 18 && ((x >= 9 && x <= 10) || (x >= 14 && x <= 15) || (x >= 18 && x <= 19) || (x >= 21 && x <= 22) || (x >= 32 && x <= 33) ||
                (x >= 36 && x <= 37) || (x >= 39 && x <= 40) || (x >= 42 && x <= 43) || (x >= 45 && x <= 46) || (x >= 56 && x <= 57) ||
                (x >= 60 && x <= 61) || (x >= 63 && x <= 64) || (x >= 66 && x <= 67) || (x >= 69 && x <= 70))) ||

            (y == 19 && ((x >= 9 && x <= 10) || (x >= 13 && x <= 16) || (x >= 18 && x <= 22) || x == 32 || x == 33 || x == 36 || x == 37 || x == 39 || x == 40 ||
                (x >= 42 && x <= 46) || x == 56 || x == 57 || (x >= 60 && x <= 64) || (x >= 66 && x <= 70)))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

//COLLISION
    for(y=26; y<=33; y++){
        for(x=14; x<=65; x++){
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
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

//-----------------------------------------------------------------------------------------------------------------------//
//TELA VENCEDOR

//ENVOLTO BOTOES
    //Botao esquerdo
    for(y=49; y<=57; y++){
        for(x=10; x<=22; x++){
            if (
                ((y == 49 || y == 57) && (x >= 13 && x <= 19)) ||

                ((y == 50 || y == 56) && ((x >= 12 && x <= 13) || (x >= 19 && x <= 20))) ||

                ((y == 51 || y == 55) && (x == 11 || x == 21)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 10 || x == 22))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

    //Botao direito
    for(y=49; y<=57; y++){
        for(x=56; x<=68; x++){
            if (
                ((y == 49 || y == 57) && (x >= 59 && x <= 65)) ||

                ((y == 50 || y == 56) && ((x >= 58 && x <= 59) || (x >= 65 && x <= 66))) ||

                ((y == 51 || y == 55) && (x == 57 || x == 67)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 56 || x == 68))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

//Botoes - SPRITES 
    //Sprite loud - PLAY
    set_sprite_wbr(1, 128, 416, 28, 4);

    //Sprite losango - SAIR
    set_sprite_wbr(1, 488, 416, 26, 5);

//TABULEIRO
    //Linhas
    for(x=25; x<=53; x++){
        edit_bloco_background_wbm(x, 28, 0, 3, 5);
        edit_bloco_background_wbm(x, 38, 0, 3, 5);
    }

    //Colunas
    for(y=19; y<=47; y++){
        edit_bloco_background_wbm(34, y, 0, 3, 5);
        edit_bloco_background_wbm(44, y, 0, 3, 5);
    }

//JOGADAS TABUELEIRO
    //Sprite X
    set_sprite_wbr(1, 224, 176, 29, 7);       //Quadrante 0

    //Sprite X
    set_sprite_wbr(1, 304, 176, 29, 8);       //Quadrante 1

    //Sprite X
    set_sprite_wbr(1, 384, 176, 29, 9);      //Quadrante 2

    //Sprite O
    set_sprite_wbr(1, 224, 256, 25, 10);       //Quadrante 3

    //Sprite O
    set_sprite_wbr(1, 304, 256, 25, 11);       //Quadrante 4

//PINTANDO QUADRANTES VENCEDORES
    set_quadrado_dp(0, 7, 0, 2, 233, 186, 0);       //Quadrante 0 - MEIO

    set_quadrado_dp(0, 7, 0, 2, 313, 186, 1);       //Quadrante 1 - MEIO

    set_quadrado_dp(0, 7, 0, 2, 393, 186, 2);       //Quadrante 2 - MEIO

//TABELA INFORMAÇÃO
    //Moldura - SUPERIOR    
    for(y=1; y<=4; y++){
        for(x=31; x<=48; x++){
            if (
            (y == 1 && (x >= 39 && x <= 40)) ||
            (y == 2 && ((x >= 31 && x <= 34) || (x >= 39 && x <= 40) || (x >= 45 && x <= 48))) ||
            (y == 3 && (x == 31 || (x >= 34 && x <= 45) || x == 48)) ||
            (y == 4 && ((x >= 31 && x <= 33) || (x >= 46 && x <= 48)))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

    //Moldura - MEIO - coluna esquerda e direita
    for(y=5; y<=9; y++){
        edit_bloco_background_wbm(33, y, 0, 3, 5);
        edit_bloco_background_wbm(46, y, 0, 3, 5);
    }

    //Moldura - MEIO - bingula esquerda
    for(y = 7; y <= 8; y++) {
        for(x = 29; x <= 32; x++) {
            edit_bloco_background_wbm(x, y, 0, 3, 5);
        }
    }

    //Moldura - MEIO - bingula direita
    for(y = 7; y <= 8; y++) {
        for(x = 47; x <= 50; x++) {
            edit_bloco_background_wbm(x, y, 0, 3, 5);
        }
    }

    //Moldura - INFERIOR
    for(y=10; y<=13; y++){
        for(x=31; x<=48; x++){
            if (
            (y == 13 && (x >= 39 && x <= 40)) ||
            (y == 12 && ((x >= 31 && x <= 34) || (x >= 39 && x <= 40) || (x >= 45 && x <= 48))) ||
            (y == 11 && (x == 31 || (x >= 34 && x <= 45) || x == 48)) ||
            (y == 10 && ((x >= 31 && x <= 33) || (x >= 46 && x <= 48)))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

    //Sprite taça - VENCEDOR
    set_sprite_wbr(1, 288, 48, 24, 20);

    //Sprite X - JOGADOR 1
    set_sprite_wbr(1, 328, 48, 29, 16);

//-----------------------------------------------------------------------------------------------------------------------//
//TELA EMPATE

//ENVOLTO BOTOES
    //Botao esquerdo
    for(y=49; y<=57; y++){
        for(x=10; x<=22; x++){
            if (
                ((y == 49 || y == 57) && (x >= 13 && x <= 19)) ||

                ((y == 50 || y == 56) && ((x >= 12 && x <= 13) || (x >= 19 && x <= 20))) ||

                ((y == 51 || y == 55) && (x == 11 || x == 21)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 10 || x == 22))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

    //Botao direito
    for(y=49; y<=57; y++){
        for(x=56; x<=68; x++){
            if (
                ((y == 49 || y == 57) && (x >= 59 && x <= 65)) ||

                ((y == 50 || y == 56) && ((x >= 58 && x <= 59) || (x >= 65 && x <= 66))) ||

                ((y == 51 || y == 55) && (x == 57 || x == 67)) ||

                ((y == 52 || y == 53 || y == 54) && (x == 56 || x == 68))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

//BOTOES - SPRITES 
    //Sprite loud - PLAY
    set_sprite_wbr(1, 128, 416, 28, 4);

    //Sprite losango - SAIR
    set_sprite_wbr(1, 488, 416, 26, 5);

//TABULEIRO
    //Linhas
    for(x=25; x<=53; x++){
        edit_bloco_background_wbm(x, 28, 0, 3, 5);
        edit_bloco_background_wbm(x, 38, 0, 3, 5);
    }

    //Colunas
    for(y=19; y<=47; y++){
        edit_bloco_background_wbm(34, y, 0, 3, 5);
        edit_bloco_background_wbm(44, y, 0, 3, 5);
    }

//JOGADAS NO TABULEIRO
    //Sprite X
    set_sprite_wbr(1, 224, 176, 29, 7);       //Quadrante 0

    //Sprite X
    set_sprite_wbr(1, 304, 176, 29, 8);       //Quadrante 1

    //Sprite X
    set_sprite_wbr(1, 384, 176, 29, 9);      //Quadrante 2


    //Sprite X
    set_sprite_wbr(1, 224, 256, 29, 10);       //Quadrante 3

    //Sprite O
    set_sprite_wbr(1, 304, 256, 25, 11);       //Quadrante 4

    //Sprite O
    set_sprite_wbr(1, 384, 256, 25, 12);       //Quadrante 5


    //Sprite O
    set_sprite_wbr(1, 224, 336, 25, 13);       //Quadrante 6

    //Sprite O
    set_sprite_wbr(1, 304, 336, 25, 14);       //Quadrante 7

    //Sprite O
    set_sprite_wbr(1, 384, 336, 25, 15);       //Quadrante 8

//TABELA INFORMAÇÃO
    //Moldura - SUPERIOR
    for(y=1; y<=4; y++){
        for(x=29; x<=51; x++){
            if (
            (y == 1 && (x >= 39 && x <= 40)) ||
            (y == 2 && ((x >= 29 && x <= 32) || (x >= 39 && x <= 40) || (x >= 48 && x <= 51))) ||
            (y == 3 && (x == 29 || (x >= 32 && x <= 48) || x == 51)) ||
            (y == 4 && ((x >= 29 && x <= 31) || (x >= 49 && x <= 51)))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

    //Moldura - MEIO - coluna esquerda e direita
    for(y=5; y<=9; y++){
        edit_bloco_background_wbm(31, y, 0, 3, 5);
        edit_bloco_background_wbm(49, y, 0, 3, 5);
    }

    //Moldura - MEIO - bingula esquerda
    for(y = 7; y <= 8; y++) {
        for(x = 27; x <= 30; x++) {
            edit_bloco_background_wbm(x, y, 0, 3, 5);
        }
    }

    //Moldura - MEIO - bingula direita
    for(y = 7; y <= 8; y++) {
        for(x = 50; x <= 53; x++) {
            edit_bloco_background_wbm(x, y, 0, 3, 5);
        }
    }

    //Moldura - INFERIOR
    for(y=10; y<=13; y++){
        for(x=29; x<=51; x++){
            if (
            (y == 13 && (x >= 39 && x <= 40)) ||
            (y == 12 && ((x >= 29 && x <= 32) || (x >= 39 && x <= 40) || (x >= 48 && x <= 51))) ||
            (y == 11 && (x == 29 || (x >= 32 && x <= 48) || x == 51)) ||
            (y == 10 && ((x >= 29 && x <= 31) || (x >= 49 && x <= 51)))
            ) {
                edit_bloco_background_wbm(x, y, 0, 3, 5);
            }
        }
    }

    //Sprite BARRA DEITADA 1 - EMPATE
    set_sprite_wbr(1, 312, 40, 13, 18);

    //Sprite BARRA DEITADA 2 - EMPATE
    set_sprite_wbr(1, 312, 56, 13, 19);

    //Sprite X - JOGADOR 1
    set_sprite_wbr(1, 272, 48, 29, 16);

    //Sprite O - JOGADOR 2
    set_sprite_wbr(1, 352, 48, 25, 17);
*/
//-----------------------------------------------------------------------------------------------------------------------//
//TELA PADRAO

//TABULEIRO

    //Linhas
    for(x=25; x<=53; x++){
        edit_bloco_background_wbm(x, 24, 0, 3, 5);
        edit_bloco_background_wbm(x, 34, 0, 3, 5);
    }

    //Colunas
    for(y=15; y<=43; y++){
        edit_bloco_background_wbm(34, y, 0, 3, 5);
        edit_bloco_background_wbm(44, y, 0, 3, 5);
    }

    //Sprite Pause
    set_sprite_wbr(1, 520, 0, 27, 6);

//INIMIGOS
    //Sprite Inimigo azul - CIMA
    set_sprite_wbr(1, 304, 64, 0, 2);

    //Sprite Inimigo laranja - BAIXO
    set_sprite_wbr(1, 304, 384, 1, 3);


//JOGADAS TABUELEIRO
    //Sprite X
    set_sprite_wbr(1, 224, 144, 29, 7);       //Quadrante 0

    //Sprite X
    set_sprite_wbr(1, 304, 144, 29, 8);       //Quadrante 1

    //Sprite X
    set_sprite_wbr(1, 384, 144, 29, 9);      //Quadrante 2


    //Sprite X
    set_sprite_wbr(1, 224, 224, 29, 10);       //Quadrante 3

    //Sprite O
    set_sprite_wbr(1, 304, 224, 25, 11);       //Quadrante 4

    //Sprite O
    set_sprite_wbr(1, 384, 224, 25, 12);       //Quadrante 5


    //Sprite O
    set_sprite_wbr(1, 224, 304, 25, 13);       //Quadrante 6

    //Sprite O
    set_sprite_wbr(1, 304, 304, 25, 14);       //Quadrante 7

    //Sprite O
    set_sprite_wbr(1, 384, 304, 25, 15);       //Quadrante 8

//-----------------------------------------------------------------------------------------------------------------------//
    
    limpar_tela();

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
