#include "biblioteca_gpu.h"

int main() {

    //Abre arquivo de comunicação com o driver
    if (open_driver( ) == -1){
        return -1;
    }

    int x,y;

    //Branco
    set_cor_background_wbr(7, 7, 7);

/*
//-----------------------------------------------------------------------------------------------------------------------//
//TELA BYE

//ENVOLTO TITULO 
    for (x = 4; x <= 6; x++) {
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 16, 0, 0, 0);
        edit_bloco_background_wbm(x, 42, 0, 0, 0);
        edit_bloco_background_wbm(x, 44, 0, 0, 0);
    }

    for (x = 74; x <= 76; x++) {
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 16, 0, 0, 0);
        edit_bloco_background_wbm(x, 42, 0, 0, 0);
        edit_bloco_background_wbm(x, 44, 0, 0, 0);
    }

    for (x = 4; x < 77; x++) {
        edit_bloco_background_wbm(x, 15, 0, 0, 0);
        edit_bloco_background_wbm(x, 43, 0, 0, 0);
    }

    for (y = 17; y < 42; y++) {
        edit_bloco_background_wbm(5, y, 0, 0, 0);
        edit_bloco_background_wbm(75, y, 0, 0, 0);
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
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }
*/
//-----------------------------------------------------------------------------------------------------------------------//
//TELA INICIO
    
//ENVOLTO TITULO
    //superior e inferior esquerdo
    for (x = 2; x <= 5; x++) {
        edit_bloco_background_wbm(x, 6, 0, 0, 0);
        edit_bloco_background_wbm(x, 8, 0, 0, 0);
        edit_bloco_background_wbm(x, 9, 0, 0, 0);
        edit_bloco_background_wbm(x, 36, 0, 0, 0);
        edit_bloco_background_wbm(x, 37, 0, 0, 0);
        edit_bloco_background_wbm(x, 39, 0, 0, 0);
    }

    //superior e inferior direito
    for (x = 74; x <= 77; x++) {
        edit_bloco_background_wbm(x, 6, 0, 0, 0);
        edit_bloco_background_wbm(x, 8, 0, 0, 0);
        edit_bloco_background_wbm(x, 9, 0, 0, 0);
        edit_bloco_background_wbm(x, 36, 0, 0, 0);
        edit_bloco_background_wbm(x, 37, 0, 0, 0);
        edit_bloco_background_wbm(x, 39, 0, 0, 0);
    }

    //linha superior e inferior
    for (x = 2; x < 78; x++) {
        edit_bloco_background_wbm(x, 7, 0, 0, 0);
        edit_bloco_background_wbm(x, 38, 0, 0, 0);
    }

    //coluna superior e inferior
    for (y = 10; y < 36; y++) {
        edit_bloco_background_wbm(3, y, 0, 0, 0);
        edit_bloco_background_wbm(76, y, 0, 0, 0);
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
                edit_bloco_background_wbm(x, y, 0, 0, 0);
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
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//BOTOES - SPRITES 
    //Sprite loud - PLAY
    set_sprite_wbr(1, 128, 416, 28, 16);

    //Sprite losango - SAIR
    set_sprite_wbr(1, 488, 416, 26, 17);

//SHADOW
    for(y=12; y<=19; y++){
        for(x=21; x<=57; x++){
            if (
            (y == 12 && ((x >= 21 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 37) || (x >= 39 && x <= 42) || 
                (x >= 45 && x <= 49) || (x >= 51 && x <= 52) || (x >= 56 && x <= 57))) ||

            (y == 13 && ((x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) ||
                (x >= 36 && x <= 37) || (x >= 39 && x <= 40) || (x >= 42 && x <= 43) || (x >= 45 && x <= 46) || (x >= 48 && x <= 49) ||
                (x >= 51 && x <= 52) || (x >= 56 && x <= 57))) ||

            (y == 14 && ((x >= 21 && x <= 22) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) ||
                (x >= 39 && x <= 40) || (x >= 42 && x <= 43) || (x >= 45 && x <= 46) || (x >= 48 && x <= 49) || (x >= 51 && x <= 52) || (x >= 56 && x <= 57))) ||

            (y == 15 && ((x >= 22 && x <= 24) || (x >= 27 && x <= 30) || (x >= 33 && x <= 37) || (x >= 39 && x <= 40) || 
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
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//-----------------------------------------------------------------------------------------------------------------------//
//TELA VENCEDOR

//ENVOLTO TITULO
    //superior e inferior esquerdo
    for (x = 15; x <= 18; x++) {
        edit_bloco_background_wbm(x, 11, 0, 0, 0);
        edit_bloco_background_wbm(x, 13, 0, 0, 0);
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 27, 0, 0, 0);
        edit_bloco_background_wbm(x, 28, 0, 0, 0);
        edit_bloco_background_wbm(x, 30, 0, 0, 0);
    }

    //superior e inferior direito
    for (x = 63; x <= 66; x++) {
        edit_bloco_background_wbm(x, 11, 0, 0, 0);
        edit_bloco_background_wbm(x, 13, 0, 0, 0);
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 27, 0, 0, 0);
        edit_bloco_background_wbm(x, 28, 0, 0, 0);
        edit_bloco_background_wbm(x, 30, 0, 0, 0);
    }

    //linha superior e inferior
    for (x = 15; x < 67; x++) {
        edit_bloco_background_wbm(x, 12, 0, 0, 0);
        edit_bloco_background_wbm(x, 29, 0, 0, 0);
    }

    //coluna superior e inferior
    for (y = 15; y < 27; y++) {
        edit_bloco_background_wbm(16, y, 0, 0, 0);
        edit_bloco_background_wbm(65, y, 0, 0, 0);
    }

//YOU WON
    for(y=17; y<=24; y++){
        for(x=21; x<=60; x++){
            if (
            (y == 17 && ((x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || 
                (x >= 41 && x <= 42) || (x >= 46 && x <= 47) || (x >= 49 && x <= 53) || (x >= 55 && x <= 56) || (x >= 59 && x <= 60))) ||

            (y == 18 && ((x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || 
                (x >= 41 && x <= 42) || (x >= 46 && x <= 47) || (x >= 49 && x <= 50) || (x >= 52 && x <= 53) || (x >= 55 && x <= 57) || (x >= 59 && x <= 60))) ||

            (y == 19 && ((x >= 21 && x <= 22) || (x >= 24 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || 
                (x >= 41 && x <= 42) || (x >= 46 && x <= 47) || (x >= 49 && x <= 50) || (x >= 52 && x <= 53) || (x >= 55 && x <= 60))) ||

            (y == 20 && ((x >= 22 && x <= 25) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || 
                (x >= 41 && x <= 42) || (x >= 46 && x <= 47) || (x >= 49 && x <= 53) || (x >= 55 && x <= 56) || (x >= 58 && x <= 60))) ||

            ((y == 21 || y == 22) && ((x >= 23 && x <= 24) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || (x >= 41 && x <= 42) || 
                x == 44 || (x >= 46 && x <= 47) || (x >= 49 && x <= 50) || (x >= 52 && x <= 53) || (x >= 55 && x <= 56) || (x >= 59 && x <= 60))) ||

            (y == 23 && ((x >= 23 && x <= 24) || (x >= 27 && x <= 28) || (x >= 30 && x <= 31) || (x >= 33 && x <= 34) || (x >= 36 && x <= 37) || (x >= 42 && x <= 46) || 
                (x >= 49 && x <= 50) || (x >= 52 && x <= 53) || (x >= 55 && x <= 56) || (x >= 59 && x <= 60))) ||

            (y == 24 && ((x >= 23 && x <= 24) || (x >= 27 && x <= 31) || (x >= 33 && x <= 37) || x == 43 || x == 45 || (x >= 49 && x <= 53) || (x >= 55 && x <= 56 ) || 
                (x >= 59 && x <= 60)))
            ) {
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
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
                edit_bloco_background_wbm(x, y, 0, 0, 0);
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
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//Botoes - SPRITES 
    //Sprite loud - PLAY
    set_sprite_wbr(1, 128, 416, 28, 16);

    //Sprite losango - SAIR
    set_sprite_wbr(1, 488, 416, 26, 17);
/*
//-----------------------------------------------------------------------------------------------------------------------//
//TELA DERROTA

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
                edit_bloco_background_wbm(x, y, 0, 0, 0);
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
                edit_bloco_background_wbm(x, y, 0, 0, 0);
            }
        }
    }

//BOTOES - SPRITES 
    //Sprite loud - PLAY
    set_sprite_wbr(1, 128, 416, 28, 16);

    //Sprite losango - SAIR
    set_sprite_wbr(1, 488, 416, 26, 17);

//ENVOLTO TITULO
    //superior e inferior esquerdo
    for (x = 9; x <= 12; x++) {
        edit_bloco_background_wbm(x, 11, 0, 0, 0);
        edit_bloco_background_wbm(x, 13, 0, 0, 0);
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 27, 0, 0, 0);
        edit_bloco_background_wbm(x, 28, 0, 0, 0);
        edit_bloco_background_wbm(x, 30, 0, 0, 0);
    }

    //superior e inferior direito
    for (x = 68; x <= 71; x++) {
        edit_bloco_background_wbm(x, 11, 0, 0, 0);
        edit_bloco_background_wbm(x, 13, 0, 0, 0);
        edit_bloco_background_wbm(x, 14, 0, 0, 0);
        edit_bloco_background_wbm(x, 27, 0, 0, 0);
        edit_bloco_background_wbm(x, 28, 0, 0, 0);
        edit_bloco_background_wbm(x, 30, 0, 0, 0);
    }

    //linha superior e inferior
    for (x = 9; x < 72; x++) {
        edit_bloco_background_wbm(x, 12, 0, 0, 0);
        edit_bloco_background_wbm(x, 29, 0, 0, 0);
    }

    //coluna superior e inferior
    for (y = 15; y < 27; y++) {
        edit_bloco_background_wbm(10, y, 0, 0, 0);
        edit_bloco_background_wbm(70, y, 0, 0, 0);
    }

    //GAME OVER
    for(y=17; y<=24; y++){
        for(x=15; x<=65; x++){
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
                (x >= 55 && x <= 56) || (x >= 58 && x <= 59) || (x >= 61 && x <= 62) || (x >= 64 && x <= 65))) ||

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
*/
//-----------------------------------------------------------------------------------------------------------------------//
//TELA PADRAO

//ESTRUTURAS

    //Quadrado da esquerda
    set_quadrado_dp(0, 0, 0, 11, 304, 416, 0);

    //Coluna da esquerda grande, direita grande e esquerda menor
    for(y=0; y<=53; y++){
        edit_bloco_background_wbm(9, y, 0, 0, 0);
        edit_bloco_background_wbm(55, y, 0, 0, 0);
        
        if(y >= 6 && y <= 17){
            edit_bloco_background_wbm(17, y, 0, 0, 0);
        }
    }

    //Linha esquerda pequena
    for(x=10; x<=16; x++){
        edit_bloco_background_wbm(x, 17, 0, 0, 0);
    }

    //Linha central grande
    for(x=15; x<=54; x++){
        edit_bloco_background_wbm(x, 33, 0, 0, 0);
    }

    //Linha direita superior 1 e 2 (antes do buraco), e direita inferior
    for(x=56; x<=73; x++){
        edit_bloco_background_wbm(x, 44, 0, 0, 0);

        if(x <= 70){
            edit_bloco_background_wbm(x, 7, 0, 0, 0);
        }

        if(x <= 64){
            edit_bloco_background_wbm(x, 14, 0, 0, 0);
        }
    }

    //Linha direita superior 1 e 2 (depois do buraco)
    for(x=70; x<=79; x++){
        edit_bloco_background_wbm(x, 14, 0, 0, 0);

        if(x >= 76){
            edit_bloco_background_wbm(x, 7, 0, 0, 0);
        }
    }

    //Estrutura quadrado da direita
        //Linha topo, meio, base
        for(x=65; x<=79; x++){
            if(x <= 72){
                edit_bloco_background_wbm(x, 23, 0, 0, 0);
                edit_bloco_background_wbm(x, 32, 0, 0, 0);
            }

            else if(x >= 74){
                edit_bloco_background_wbm(x, 27, 0, 0, 0);
            }
        }

        //Coluna esquerda e direita
        for(y=23; y<=32; y++){
            edit_bloco_background_wbm(64, y, 0, 0, 0);
            edit_bloco_background_wbm(73, y, 0, 0, 0);
        }

//SPRITE

    //Sprite Ladrão
    set_sprite_wbr(1, 456, 32, 25, 1);

    //Sprite Porta
    set_sprite_wbr(1, 456, 0, 31, 1);

    //Sprite troféu esquerdo
    set_sprite_wbr(1, 24, 16, 24, 3);

    //Sprite troféu direito
    set_sprite_wbr(1, 96, 104, 24, 4);

    //Sprite Pause
    set_sprite_wbr(1, 608, 0, 27, 5);


    //Sprite policial 1
    set_sprite_wbr(1, 160, 8, 30, 6);

    //Sprite policial 2
    set_sprite_wbr(1, 600, 72, 30, 7);

    //Sprite policial 3
    set_sprite_wbr(1, 456, 128, 30, 8);

    //Sprite policial 4
    set_sprite_wbr(1, 400, 160, 30, 9);

    //Sprite policial 5
    set_sprite_wbr(1, 88, 216, 30, 10);

    //Sprite policial 6
    set_sprite_wbr(1, 608, 296, 30, 11);

    //Sprite policial 7
    set_sprite_wbr(1, 392, 336, 30, 12);

    //Sprite policial 8
    set_sprite_wbr(1, 96, 384, 30, 13);

    //Sprite policial 9
    set_sprite_wbr(1, 456, 368, 30, 14);

    //Sprite policial 10
    set_sprite_wbr(1, 208, 448, 30, 15);

//-----------------------------------------------------------------------------------------------------------------------//
    
    limpar_tela();

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
