#include "utils.h"

/**Função para verificar colisão do sprite ladrão com estruturas do mapa do jogo e evitar atravessá-las 
 * parâmetros ->    x_ladrao: coordenada X do sprite ladrão
 *                  y_ladrao: coordenada Y do sprite ladrão
 *                  verificar: soma do coordenada X ou Y + o deslocamento relativo X ou Y do mouse
 *                  x_y: flag para determinar verificação de colisão para coordenada X ou Y
 * retorno ->       0 caso não ocorra colisão ou ultrapassagem de estruturas ou 1 caso ocorra
 */
int
verifica_colisao_parede(int x_ladrao, int y_ladrao, int verificar, char x_y) {
    if (x_y == 'x') {
        if (
            //AREA 1, 2, 3, 4 - COLUNA ESQUERDA
            (x_ladrao >= 448 - ESQ_SPRITE_LADRAO && (y_ladrao >= 0 && y_ladrao < 432) && verificar < 448 - ESQ_SPRITE_LADRAO) ||
            

            //PASSAGEM 1
            ((x_ladrao >= 568 - ESQ_SPRITE_LADRAO && x_ladrao < 608) && (y_ladrao > 35 && y_ladrao < 64) && (verificar < 568 - ESQ_SPRITE_LADRAO || verificar > 587 + DIR_SPRITE_LADRAO)) ||

            //PASSAGEM 2
            ((x_ladrao >= 520 - ESQ_SPRITE_LADRAO && x_ladrao < 560) && (y_ladrao > 91 && y_ladrao < 120) && (verificar < 520 - ESQ_SPRITE_LADRAO || verificar > 539 + DIR_SPRITE_LADRAO)) ||

            
            //AREA 3 MEIO DIREITA (LADO DIREITO DO QUADRADO SUPERIOR)
            (x_ladrao >= 592 - ESQ_SPRITE_LADRAO && (y_ladrao >= 163 && y_ladrao < 196) && verificar < 592 - ESQ_SPRITE_LADRAO) ||

            //AREA 3 MEIO DIREITA (LADO ESQUERDO DO QUADRADO)
            ((x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 512) && (y_ladrao > 163 && y_ladrao < 264) && verificar > 491 + DIR_SPRITE_LADRAO) ||
            
            //AREA 3 MEIO DIREITA (LADO DIREITO DO QUADRADO INFERIOR)
            (x_ladrao >= 592 - ESQ_SPRITE_LADRAO && (y_ladrao >= 224 && y_ladrao < 264) && verificar < 592 - ESQ_SPRITE_LADRAO) ||


            //PASSAGEM 3
            (x_ladrao >= 592 - ESQ_SPRITE_LADRAO && (y_ladrao > 331 && y_ladrao < 360) && verificar < 592 - ESQ_SPRITE_LADRAO) ||


            //AREA 5 E 7 - COLUNA DIREITA
            (x_ladrao <= 419 + DIR_SPRITE_LADRAO && (y_ladrao >= 0 && y_ladrao < 432) && verificar > 419 + DIR_SPRITE_LADRAO) ||

            //AREA 5 E 7 E 8 - COLUNA ESQUERDA
            (x_ladrao >= 80 - ESQ_SPRITE_LADRAO && (y_ladrao >= 0 && y_ladrao < 432) && verificar < 80 - ESQ_SPRITE_LADRAO) ||


            //AREA 5 INFERIOR CENTRAL - DIREITA DO QUADRADO
            (x_ladrao >= 368 - ESQ_SPRITE_LADRAO && y_ladrao > 339 && verificar < 368 - ESQ_SPRITE_LADRAO) ||

            //AREA 5 INFERIOR CENTRAL - ESQUERDA DO QUADRADO
            (x_ladrao <= 227 + DIR_SPRITE_LADRAO && y_ladrao > 339 && verificar > 227 + DIR_SPRITE_LADRAO) ||


            //AREA 5 INFERIOR CENTRAL - PASSAGEM CIMA
            ((x_ladrao >= 80 - ESQ_SPRITE_LADRAO && x_ladrao < 120) && (y_ladrao > 243 && y_ladrao < 272) && (verificar < 80 - ESQ_SPRITE_LADRAO || verificar > 99 + DIR_SPRITE_LADRAO)) ||


            //AREA 6 ESQUERDA TOTAL
            (x_ladrao <= 51 + DIR_SPRITE_LADRAO && (y_ladrao >= 0 && y_ladrao < 432) && verificar > 51 + DIR_SPRITE_LADRAO) ||


            //AREA 7 CENTRO SUPERIOR - MOLDURA
            (x_ladrao >= 144 - ESQ_SPRITE_LADRAO && (y_ladrao >= 27 && y_ladrao < 144) && verificar < 144 - ESQ_SPRITE_LADRAO) ||


            //AREA 8 TAÇA DIREITA
            (x_ladrao <= 115 + DIR_SPRITE_LADRAO && (y_ladrao > 27 && y_ladrao < 136) && verificar > 115 + DIR_SPRITE_LADRAO)
            
        ){
            return 1;
        }
    }

    else if (x_y == 'y') {
        if (
            //AREA 1 CIMA DIREITA  - VERIFICA BAIXO
            (y_ladrao <= 35 && ((x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 568 - ESQ_SPRITE_LADRAO) || (x_ladrao > 587 + DIR_SPRITE_LADRAO)) && verificar > 35) ||


            //AREA 2 CIMA DIREITA - VERIFICA BAIXO
            (y_ladrao <= 91 && ((x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 520 - ESQ_SPRITE_LADRAO) || (x_ladrao > 539 + DIR_SPRITE_LADRAO)) && verificar > 91) ||

            //AREA 2 CIMA DIREITA - VERIFICA CIMA
            (y_ladrao >= 64 && ((x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 568 - ESQ_SPRITE_LADRAO) || (x_ladrao > 587 + DIR_SPRITE_LADRAO)) && verificar < 64) ||


            //AREA 3 MEIO DIREITA - VERIFICA CIMA
            (y_ladrao >= 120 && ((x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 520 - ESQ_SPRITE_LADRAO) || x_ladrao > 539 + DIR_SPRITE_LADRAO) && verificar < 120) ||


            //AREA 3 MEIO DIREITA (TOPO QUADRADO SUPERIOR) - VERIFICA BAIXO
            (y_ladrao <= 163 && (x_ladrao > 491 + DIR_SPRITE_LADRAO && x_ladrao < 592 - ESQ_SPRITE_LADRAO) && verificar > 163) ||

            //AREA 3 MEIO DIREITA (DIREITA DO QUADRADO SUPERIOR) - VERIFICA BAIXO
            (y_ladrao <= 195 && x_ladrao >= 592 - ESQ_SPRITE_LADRAO && verificar > 195) ||

            
            //AREA 3 MEIO DIREITA - VERIFICA BAIXO
            (y_ladrao <= 331 && (x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 592 - ESQ_SPRITE_LADRAO) && verificar > 331) ||


            //AREA 3 MEIO DIREITA (QUADRADO INFERIOR) - VERIFICA CIMA
            (y_ladrao >= 264 && (x_ladrao > 491 + DIR_SPRITE_LADRAO && x_ladrao < 592 - ESQ_SPRITE_LADRAO) && verificar < 264) ||

            //AREA 3 MEIO DIREITA (DIREITA DO QUADRADO INFERIOR) - VERIFICA CIMA
            (y_ladrao >= 224 && x_ladrao >= 592 - ESQ_SPRITE_LADRAO && verificar < 224) ||


            //AREA 4 INFERIOR DIREITA - VERIFICA CIMA
            (y_ladrao >= 360 && (x_ladrao >= 448 - ESQ_SPRITE_LADRAO && x_ladrao < 592 - ESQ_SPRITE_LADRAO) && verificar < 360) ||

            //AREA 4 INFERIOR DIREITA - PASSAGEM - VERIFICA CIMA
            (y_ladrao >= 432 && (x_ladrao > 419 + DIR_SPRITE_LADRAO && x_ladrao < 448 - ESQ_SPRITE_LADRAO) && verificar < 432) ||


            //AREA 5 INFERIOR CENTRO - VERIFICA CIMA
            (y_ladrao >= 272 && (x_ladrao > 99 + DIR_SPRITE_LADRAO && x_ladrao < 440 - ESQ_SPRITE_LADRAO) && verificar < 272) ||


            //AREA 5 INFERIOR CENTRO - VERIFICA BAIXO (TOPO DO QUADRADO)
            (y_ladrao <= 339 && (x_ladrao > 227 + DIR_SPRITE_LADRAO && x_ladrao < 368 - ESQ_SPRITE_LADRAO) && verificar > 339) ||


            //AREA 5 INFERIOR CENTRO - PASSAGEM ESQUERDA - VERIFICA CIMA
            (y_ladrao >= 432 && (x_ladrao > 51 + DIR_SPRITE_LADRAO && x_ladrao < 80 - ESQ_SPRITE_LADRAO) && verificar < 432) ||


            //AREA 7 SUPERIOR CENTRO - VERIFICA CIMA MOLDURA
            (y_ladrao >= 144 && (x_ladrao >= 80 - ESQ_SPRITE_LADRAO && x_ladrao < 144 - ESQ_SPRITE_LADRAO) && verificar < 144) ||

            
            //AREA 7 SUPERIOR CENTRO - VERIFICA BAIXO
            (y_ladrao <= 243 && (x_ladrao > 99 + DIR_SPRITE_LADRAO && x_ladrao < 440) && verificar > 243) ||


            //AREA 8 TAÇA - VERIFICA BAIXO
            (y_ladrao <= 115 && (x_ladrao >= 80 - ESQ_SPRITE_LADRAO && x_ladrao < 136 - ESQ_SPRITE_LADRAO) && verificar > 115) ||

            //AREA 8 TAÇA - PASSAGEM
            (y_ladrao <= 27 && (x_ladrao > 115 + DIR_SPRITE_LADRAO && x_ladrao < 144 - ESQ_SPRITE_LADRAO) && verificar > 27)
        ){
            return 1;
        }
    }

    return 0;
}

/**Função para verificar colisão do sprite ladrão com sprites policiais e sprites troféus
 * parâmetros ->    x_ladrao: coordenada X do sprite ladrão
 *                  y_ladrao: coordenada Y do sprite ladrão
 *                  policia_x: coordenada X do sprite policial (ou troféu)
 *                  policia_y: coordenada Y do sprite policial (ou troféu)
 * retorno ->       0 caso não ocorra colisão ou 1 caso ocorra
 */
int 
verifica_colisao_policia(int x_ladrao, int y_ladrao, int policia_x, int policia_y) {
    
    if (x_ladrao <= policia_x + 15 &&        //esquerda
        x_ladrao + 15 >= policia_x &&        //direita
        y_ladrao <= policia_y + 19 &&        //cima
        y_ladrao + 18 >= policia_y) {        //baixo

        return 1;
    }

    return 0;
}
