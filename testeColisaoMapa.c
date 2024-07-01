#include "biblioteca_gpu.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
   
#define MOUSE_DEVICE "/dev/input/event0"

int bateu_parede(int ladrao_x, int ladrao_y, int bloco_x, int bloco_y){
    bloco_x *= 8;
    bloco_y *= 8;

    if (ladrao_x + 5 <= bloco_x + 8 &&   //esquerda
        ladrao_x + 15 >= bloco_x &&      //direita
        ladrao_y + 1 <= bloco_y + 8 &&       //cima
        ladrao_y + 18 >= bloco_y) {      //baixo
        
        return 1; // Colisão detectada
    }

    return 0; // Sem colisão
}

int bateu_policia(int ladrao_x, int ladrao_y, int policia_x, int policia_y){

    if (ladrao_x + 5 <= policia_x + 16 &&   //esquerda
        ladrao_x + 15 >= policia_x + 3 &&      //direita
        ladrao_y + 1 <= policia_y + 18 &&       //cima
        ladrao_y + 18 >= policia_y + 1) {      //baixo
        
        return 1; // Colisão detectada
    }

    return 0; // Sem colisão
}

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

    int x_real = 456, y_real = 32;

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

        //SE DER MERDA, SE EV.VALUE > 0 -> SOMA 1; SE EV.VALUE < 0 -> SUBTRAI 1
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

        int colisao = 0;
        int bloco_x, bloco_y;

        //Coluna da esquerda grande, direita grande e esquerda menor
        for(bloco_y=0; bloco_y<=53; bloco_y++){
            if(bateu_parede(x_real, y_real, 9, bloco_y) || bateu_parede(x_real, y_real, 55, bloco_y)){
                colisao = 1;
                break;
            }
            
            if(bloco_y >= 6 && bloco_y <= 17){
                if(bateu_parede(x_real, y_real, 17, bloco_y)){
                    colisao = 1;
                    break;
                }
            }
        }

        //SÓ VERIFICA COLISÃO SE O CURSOR ESTIVER NA PARTE CENTRAL DO MAPA
        if(colisao!=1 && x_real < 224 && y_real < 200){
            //Linha esquerda pequena
            for(bloco_x=10; bloco_x<=16; bloco_x++){
                if(bateu_parede(x_real, y_real, bloco_x, 17)){
                    colisao = 1;
                    break;
                }
            }
        }

        //SÓ VERIFICA COLISÃO SE O CURSOR ESTIVER NA PARTE CENTRAL DO MAPA
        if(colisao!=1 && (x_real > 64 && x_real < 464) && y_real > 190){
            //Linha central grande
            for(bloco_x=15; bloco_x<=54; bloco_x++){
                if(bateu_parede(x_real, y_real, bloco_x, 33)){
                    colisao = 1;
                    break;
                }
            }
        }
        
        //SÓ VERIFICA COLISÃO SE O CURSOR ESTIVER NA PARTE DIREITA DO MAPA
        if(colisao!=1 && x_real > 424){
            //Linha direita superior 1 e 2 (antes do buraco), e direita inferior
            for(bloco_x=56; bloco_x<=73; bloco_x++){
                if(bateu_parede(x_real, y_real, bloco_x, 44)){
                    colisao = 1;
                    break;
                }

                if(bloco_x <= 64){
                    if(bateu_parede(x_real, y_real, bloco_x, 14)){
                        colisao = 1;
                        break;
                    }
                }

                if(bloco_x <= 70){
                    if(bateu_parede(x_real, y_real, bloco_x, 7)){
                        colisao = 1;
                        break;
                    }
                }
            }

            if(colisao!=1){
                //Linha direita superior 1 e 2 (depois do buraco)
                for(bloco_x=70; bloco_x<=79; bloco_x++){
                    if(bateu_parede(x_real, y_real, bloco_x, 14)){
                        colisao = 1;
                        break;
                    }

                    if(bloco_x >= 76){
                        if(bateu_parede(x_real, y_real, bloco_x, 7)){
                            colisao = 1;
                            break;
                        }
                    }
                }
            }

            if(colisao!=1){
                //Estrutura quadrado da direita
                //Linha topo, meio, base
                for(bloco_x=65; bloco_x<=79; bloco_x++){
                    if(bloco_x <= 72){
                        if(bateu_parede(x_real, y_real, bloco_x, 23) || bateu_parede(x_real, y_real, bloco_x, 32)){
                            colisao = 1;
                            break;
                        }
                    }

                    else if(bloco_x >= 74){
                        if(bateu_parede(x_real, y_real, bloco_x, 27)){
                            colisao = 1;
                            break;
                        }
                    }
                }
            }

            if(colisao!=1){
                //Coluna esquerda e direita
                for(bloco_y=23; bloco_y<=32; bloco_y++){
                    if(bateu_parede(x_real, y_real, 64, bloco_y) || bateu_parede(x_real, y_real, 73, bloco_y)){
                        colisao = 1;
                        break;
                    }
                }
            }
        }

        //SÓ VERIFICA COLISÃO SE O CURSOR ESTIVER NA PARTE CENTRAL DO MAPA
        if(colisao!=1 && x_real > 160 && x_real < 450 ){
            //POLIGONO QUADRADO
            for(bloco_y=46; bloco_y<=59; bloco_y++){
                if(bateu_parede(x_real, y_real, 45, bloco_y) || bateu_parede(x_real, y_real, 31, bloco_y)){
                    colisao = 1;
                    break;
                }
            }

            if(colisao!=1){
                //POLIGONO QUADRADO
                for(bloco_x=31; bloco_x<=45; bloco_x++){
                    if(bateu_parede(x_real, y_real, bloco_x, 45)){
                        colisao = 1;
                        break;
                    }
                }
            }
        }

        //Se não houve colisão com nenhuma parede, cursor em tela é atualizado
        if(colisao == 0){
            set_sprite_wbr(1, x_real, y_real, 25, 1);
        } 
    }

    // Fechar os dispositivos
    close(fd_mouse);

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
