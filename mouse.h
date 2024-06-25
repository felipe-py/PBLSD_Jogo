#ifndef MOUSE_H
#define MOUSE_H

#define MOUSE_DEVICE "/dev/input/event0"

int abrir_mouse();

void fechar_mouse();

int ler_mouse();

int movimenta_mouse(int *x_real, int *y_real);

int clique_esquerdo_mouse();

#endif