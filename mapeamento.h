#ifndef MAPEAMENTO_H
#define MAPEAMENTO_H

#define LW_BRIDGE_BASE 0xFF200000
#define LW_BRIDGE_SPAN 0x80

#define KEYS_BASE 0x0

#define HEX5_BASE 0x10
#define HEX4_BASE 0x20
#define HEX3_BASE 0x30
#define HEX2_BASE 0x40
#define HEX1_BASE 0x50
#define HEX0_BASE 0x60

int inicia_map();

int encerra_map();

void inicia_display();

void att_placar(int pont_quadrado, int pont_triangulo);

int verifica_botao();

#endif
