#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define MOUSEFILE "/dev/input/mice"

int main() {
    int fd;
    struct input_event ie;

    // Abrir o dispositivo de entrada do mouse
    if ((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
        perror("Erro ao abrir dispositivo de entrada");
        exit(EXIT_FAILURE);
    }

    // Ler eventos do dispositivo de entrada do mouse
    while (read(fd, &ie, sizeof(struct input_event))) {
        if (ie.type == EV_REL && (ie.code == REL_X || ie.code == REL_Y)) {
            // Exibir posição X e Y do mouse
            printf("X: %d, Y: %d\n", ie.value, 0); // Note que o REL_Y pode ser usado para capturar o movimento vertical.
        }
    }

    // Fechar o dispositivo de entrada do mouse
    close(fd);

    return 0;
}
