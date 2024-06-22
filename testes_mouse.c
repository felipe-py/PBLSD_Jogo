///////////////////////////////////////////////////////////////////////////////////////////

// CÓDIGO PARA EXIBIR A VELOCIDADE DO MOUSE EM UNIDADES POR SEGUNDO

///////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <time.h>

#define MOUSEFILE "/dev/input/event6" // Substitua pelo dispositivo correto

int main(void) {
    int fd;
    struct input_event ie;
    struct timespec ts, ts_prev;
    long delta_time;
    int delta_x, delta_y;

    // Abra o dispositivo do mouse
    if ((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
        perror("opening device");
        return EXIT_FAILURE;
    }

    // Inicializa as variáveis de tempo
    clock_gettime(CLOCK_MONOTONIC, &ts_prev);
    int somaX, somaY = 0;

    while (1) {
        // Lê os eventos do dispositivo
        if (read(fd, &ie, sizeof(struct input_event)) != -1) {
            // Verifica se o evento é do tipo EV_REL (movimento relativo)
            if (ie.type == EV_REL) {
                clock_gettime(CLOCK_MONOTONIC, &ts);
                delta_time = (ts.tv_sec - ts_prev.tv_sec) * 1000000000L + (ts.tv_nsec - ts_prev.tv_nsec);
                ts_prev = ts;

                if (ie.code == REL_X) {
                    delta_x = ie.value;
                    printf("Velocidade X: %.2f unidades/segundo\n", (float)delta_x / ((float)delta_time / 1000000000L));
                    
                    /*somaX++;
                    if(somaX==6){
                        printf("X: %d\n",delta_x);
                        somaX=0;
                    }*/
                    
                } else if (ie.code == REL_Y) {
                    delta_y = ie.value;
                    printf("Velocidade Y: %.2f unidades/segundo\n", (float)delta_y / ((float)delta_time / 1000000000L));
                    
                    /*somaY++;
                    if(somaY==6){
                        printf("Y: %d\n",delta_y);
                        somaY=0;
                    }*/
                   
                }
            }
        } else {
            perror("reading device");
            return EXIT_FAILURE;
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////

// CÓDIGO PARA PRINTAR UM CURSOR DO MOUSE NO TERMINAL EM TEMPO REAL

///////////////////////////////////////////////////////////////////////////////////////////

/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <termios.h>
#include <sys/ioctl.h>

#define MOUSEFILE "/dev/input/event6" // Substitua pelo dispositivo correto
#define CURSOR_CHAR 'O'
#define SENSIBILIDADE 5

void move_cursor(int x, int y) {
    printf("\033[%d;%dH%c", y, x, CURSOR_CHAR);
    fflush(stdout);
}

void erase_cursor(int x, int y) {
    printf("\033[%d;%dH ", y, x);
    fflush(stdout);
}

void hide_cursor() {
    printf("\033[?25l");
}

void show_cursor() {
    printf("\033[?25h");
}

int main(void) {
    int fd;
    struct input_event ie;
    int cursor_x = 40, cursor_y = 12; // Posição inicial do cursor
    int prev_x = cursor_x, prev_y = cursor_y; // Posição anterior do cursor
    struct winsize w;
    int soma_x = 0, soma_y = 0;

    // Obtém o tamanho do terminal
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // Abra o dispositivo do mouse
    if ((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
        perror("opening device");
        return EXIT_FAILURE;
    }

    // Esconde o cursor do terminal e move para a posição inicial
    hide_cursor();
    move_cursor(cursor_x, cursor_y);

    while (1) {
        // Lê os eventos do dispositivo
        if (read(fd, &ie, sizeof(struct input_event)) != -1) {
            // Verifica se o evento é do tipo EV_REL (movimento relativo)
            if (ie.type == EV_REL) {
                // Apaga o cursor na posição anterior
                erase_cursor(prev_x, prev_y);

                if (ie.code == REL_X) {
                    soma_x += abs(ie.value);
                    if (soma_x >= SENSIBILIDADE) {
                        cursor_x += (ie.value > 0 ? 1 : -1);
                        if (cursor_x < 1) cursor_x = 1;
                        if (cursor_x > w.ws_col) cursor_x = w.ws_col;
                        soma_x = 0;
                    }
                } else if (ie.code == REL_Y) {
                    soma_y += abs(ie.value);
                    if (soma_y >= SENSIBILIDADE) {
                        cursor_y += (ie.value > 0 ? 1 : -1);
                        if (cursor_y < 1) cursor_y = 1;
                        if (cursor_y > w.ws_row) cursor_y = w.ws_row;
                        soma_y = 0;
                    }
                }

                // Atualiza a posição do cursor
                move_cursor(cursor_x, cursor_y);

                // Armazena a nova posição como posição anterior
                prev_x = cursor_x;
                prev_y = cursor_y;
            } 
            // Verifica se o botão do mouse foi pressionado
            else if (ie.code == BTN_LEFT && ie.value == 1) {
                printf("JAIR");
                fflush(stdout);
            }
        } else {
            perror("reading device");
            close(fd);
            show_cursor();
            return EXIT_FAILURE;
        }
    }

    // Fecha o dispositivo e restaura o cursor do terminal
    close(fd);
    show_cursor();
    return EXIT_SUCCESS;
}*/
