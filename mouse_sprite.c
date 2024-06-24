#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <biblioteca_gpu.h>

#define MOUSEFILE "/dev/input/event0" // supondo o mouse em event0
#define SENSIBILIDADE 5

extern void set_sprite_wbr(int ativa_sprite, int cord_x, int cord_y, int offset, int registrador);

int main(void) {
    int fd;
    struct input_event ie;                      // como é bom não ter restrições para as bibliotecas...
    int cursor_x = 0, cursor_y = 0;             // Posição inicial do cursor, só pra inicializar mesmo
    int prev_x = cursor_x, prev_y = cursor_y;   // iniciando a posiçao anterior do cursor, lembrando que a posição é relativa
    struct winsize w;                           // o w vai guardar o tamanho da janela do terminal, não sei bem se no nosso caso precisa, já que a gente tem uma única janela com o terminal, mas ta aí
    int soma_x = 0, soma_y = 0;                 // somando o numero de deslocamentos em cada direção, para a sensibilidade a velocidade do mouse
    int sprite_offset = 0x0089;                 // Supondo que o sprite está neste offset na memória
    int sprite_registrador = 1;                 // chutando um valor pro registrador

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);       // aqui só "joga" o tamanho da janela do terminal em w

    if ((fd = open(MOUSEFILE, O_RDONLY)) == -1) {   // abre o mouse
        perror("opening device");
        return EXIT_FAILURE;
    }

    set_sprite_wbr(1, cursor_x, cursor_y, sprite_offset, sprite_registrador);   // fazendo o primeiro desenho do sprite na posição inicial do mouse

    while (1) {                                                                 // loop infinito
        if (read(fd, &ie, sizeof(struct input_event)) != -1) {                  // fazendo a leitura do arquivo
            if (ie.type == EV_REL) {                                            // verifica se o evento que ocorreu foi um deslocamento relativo do mouse
                if (ie.code == REL_X) {                                         // se o código de movimento for no eixo x
                    soma_x += abs(ie.value);                                    // incrementa a soma_x, o "abs" serve pra somar só o módulo do número, pra garantir que não vai ter negativo
                    if (soma_x >= SENSIBILIDADE) {                              // se a soma dos deslocamentos for maior que a sensibilidade
                        cursor_x += (ie.value > 0 ? 1 : -1);                    // atualiza a posição de x
                        if (cursor_x < 1) cursor_x = 1;                         // se tiver no limite esquerdo da tela e mandar se mover mais para a esquerda a posição fica em 1
                        if (cursor_x > w.ws_col) cursor_x = w.ws_col;           // mesma coisa para o limite direito da tela
                        soma_x = 0;                                             // zerando o soma_x pra garantir que a sensibilidade funcione depois do primeiro movimento
                    }
                } else if (ie.code == REL_Y) {                                  // mesma coisa da movimentação em x, sõ que pra y agora
                    soma_y += abs(ie.value);
                    if (soma_y >= SENSIBILIDADE) {
                        cursor_y += (ie.value > 0 ? 1 : -1);
                        if (cursor_y < 1) cursor_y = 1;
                        if (cursor_y > w.ws_row) cursor_y = w.ws_row;
                        soma_y = 0;
                    }
                }

                set_sprite_wbr(1, cursor_x, cursor_y, sprite_offset, sprite_registrador);   // depois de ter lido tudo e saber a posição certa, é só printar
            } 
        } else {
            perror("reading device");                                           // caso por algum motivo saia do loop
            close(fd);
            return EXIT_FAILURE;
        }
    }

    close(fd);                                                                  // aqui só fecha mesmo
    return EXIT_SUCCESS;
}
