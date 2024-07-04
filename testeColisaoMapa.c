#include "biblioteca_gpu.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
   
#define MOUSE_DEVICE "/dev/input/event0"

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
    int verificar;

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

        if (ev.type == EV_REL) {
            if (ev.code == REL_X) {
                verificar = x_real + ev.value;
                    //AREA 1, 2, 3, 4 - COLUNA ESQUERDA
                if(
                    (x_real >= 448 && (y_real >= 0 && y_real < 432) && verificar < 448) ||
                    
                    //PASSAGEM 1
                    ((x_real >= 568 && x_real < 608) && (y_real > 35 && y_real < 64) && (verificar < 568 || verificar > 587)) ||

                    //PASSAGEM 2
                    ((x_real >= 520 && x_real < 560) && (y_real > 91 && y_real < 120) && (verificar < 520 || verificar > 539)) ||

                    
                    //AREA 3 MEIO DIREITA (LADO DIREITO DO QUADRADO SUPERIOR)
                    (x_real >= 592 && (y_real >= 163 && y_real < 196) && verificar < 592) ||

                    
                    //AREA 3 MEIO DIREITA (LADO ESQUERDO DO QUADRADO)
                   ((x_real >= 448 && x_real < 512) && (y_real > 163 && y_real < 264) && verificar > 492) ||

                    
                    
                    //AREA 3 MEIO DIREITA (LADO DIREITO DO QUADRADO INFERIOR)
                    (x_real >= 592 && (y_real >= 224 && y_real < 264) && verificar < 592) ||



                    //PASSAGEM 3
                    (x_real >= 592 && (y_real > 331 && y_real < 360) && verificar < 592) ||


                    //AREA 5 E 7 - COLUNA DIREITA
                    (x_real <= 420 && (y_real >= 0 && y_real < 432) && verificar > 420) ||

                    //AREA 5 E 7 E 8 - COLUNA ESQUERDA
                    (x_real >= 80 && (y_real >= 0 && y_real < 432) && verificar < 80) ||


                    //AREA 5 INFERIOR CENTRAL - DIREITA DO QUADRADO
                    (x_real >= 368 && y_real > 339 && verificar < 368) ||

                    //AREA 5 INFERIOR CENTRAL - ESQUERDA DO QUADRADO
                    (x_real <= 228 && y_real > 339 && verificar > 228) ||


                    //AREA 5 INFERIOR CENTRAL - PASSAGEM CIMA
                    ((x_real >= 80 && x_real < 120) && (y_real > 243 && y_real < 272) && (verificar < 80 || verificar > 100)) ||


                    //AREA 6 ESQUERDA TOTAL
                    (x_real <= 52 && (y_real >= 0 && y_real < 432) && verificar > 52) ||


                    //AREA 7 CENTRO SUPERIOR - MOLDURA
                    (x_real >= 144 && (y_real >= 27 && y_real < 144) && verificar < 144) ||


                    //AREA 8 TAÇA DIREITA
                   (x_real < 136 && (y_real > 27 && y_real < 136) && verificar > 116)
                    
                    ){}

                else
                    x_real += ev.value;
            } 
            
            else if (ev.code == REL_Y) {
                verificar = y_real + ev.value;

                    //AREA 1 CIMA DIREITA  - VERIFICA BAIXO
                if(
                    (y_real <= 35 && ((x_real >= 448 && x_real < 568) || (x_real > 587)) && verificar > 35) ||


                    //AREA 2 CIMA DIREITA - VERIFICA BAIXO
                    (y_real <= 91 && ((x_real >= 448 && x_real < 520) || (x_real > 539)) && verificar > 91) ||

                    //AREA 2 CIMA DIREITA - VERIFICA CIMA
                    (y_real >= 64 && ((x_real >= 448 && x_real < 568) || (x_real > 587)) && verificar < 64) ||


                    //AREA 3 MEIO DIREITA - VERIFICA CIMA
                    (y_real >= 120 && ((x_real >= 448 && x_real < 520) || x_real > 539) && verificar < 120) ||


                    //AREA 3 MEIO DIREITA (TOPO QUADRADO SUPERIOR) - VERIFICA BAIXO
                    (y_real <= 163 && (x_real > 491 && x_real < 592) && verificar > 163) ||

                    //AREA 3 MEIO DIREITA (DIREITA DO QUADRADO SUPERIOR) - VERIFICA BAIXO
                    (y_real <= 195 && x_real >= 592 && verificar > 195) ||

                    
                    //AREA 3 MEIO DIREITA - VERIFICA BAIXO
                    (y_real <= 331 && (x_real >= 448 && x_real < 592) && verificar > 331) ||


                    //AREA 3 MEIO DIREITA (QUADRADO INFERIOR) - VERIFICA CIMA
                    (y_real >= 264 && (x_real > 491 && x_real < 592) && verificar < 264) ||

                    //AREA 3 MEIO DIREITA (DIREITA DO QUADRADO INFERIOR) - VERIFICA CIMA
                    (y_real >= 224 && x_real >= 592 && verificar < 224) ||


                    //AREA 4 INFERIOR DIREITA - VERIFICA CIMA
                    (y_real >= 360 && (x_real >= 448 && x_real < 592) && verificar < 360) ||

                    //AREA 4 INFERIOR DIREITA - PASSAGEM - VERIFICA CIMA
                    (y_real >= 432 && (x_real > 419 && x_real < 448) && verificar < 432) ||


                    //AREA 5 INFERIOR CENTRO - VERIFICA CIMA
                    (y_real >= 272 && (x_real > 99 && x_real < 440) && verificar < 272) ||


                    //AREA 5 INFERIOR CENTRO - VERIFICA BAIXO (TOPO DO QUADRADO)
                    (y_real <= 339 && (x_real > 227 && x_real < 368) && verificar > 339) ||


                    //AREA 5 INFERIOR CENTRO - PASSAGEM ESQUERDA - VERIFICA CIMA
                    (y_real >= 432 && (x_real > 51 && x_real < 80) && verificar < 432) ||


                    //AREA 7 SUPERIOR CENTRO - VERIFICA CIMA MOLDURA
                    (y_real >= 144 && (x_real >= 80 && x_real < 144) && verificar < 144) ||

                    
                    //AREA 7 SUPERIOR CENTRO - VERIFICA BAIXO
                    (y_real <= 243 && (x_real > 99 && x_real < 440) && verificar > 243) ||


                    //AREA 8 TAÇA - VERIFICA BAIXO
                    (y_real <= 115 && (x_real >= 80 && x_real < 136) && verificar > 115) ||

                    //AREA 8 TAÇA - PASSAGEM
                    (y_real <= 27 && (x_real > 115 && x_real < 144) && verificar > 27)
                ){}

                else
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

        set_sprite_wbr(1, x_real, y_real, 25, 1);
    }

    // Fechar os dispositivos
    close(fd_mouse);

    //Fecha arquivo de comunicação com o driver
    close_driver();

    return 0;
}
