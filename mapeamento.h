#ifndef MAPEAMENTO_H
#define MAPEAMENTO_H

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#define LW_BRIDGE_BASE 0xFF200000
#define LW_BRIDGE_SPAN 0x80

#define KEYS_BASE 0x0

#define HEX5_BASE 0x10
#define HEX4_BASE 0x20
#define HEX3_BASE 0x30
#define HEX2_BASE 0x40
#define HEX1_BASE 0x50
#define HEX0_BASE 0x60

//0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -
int numeros[11] = {64, 121, 36, 48, 25, 18, 2, 120, 0, 16, 63};

//Ponteiro de endereço virtual para os digitos do display de 7seg e botões
volatile int *HEX5_ptr;
volatile int *HEX4_ptr;
volatile int *HEX3_ptr;
volatile int *HEX2_ptr;
volatile int *HEX1_ptr;
volatile int *HEX0_ptr;

volatile int *KEYS_BASE_ptr;

int fd = -1; //Usado para abrir /dev/mem
void *LW_virtual; //Endereços físicos para a ponte (light-weight bridge)

int inicia_map(){
    // Abrir /dev/mem para dar acesso a endereços físicos
    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return (-1);
    }

    // Obter um mapeamento de endereços físicos para endereços virtuais
    LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    if (LW_virtual == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(fd);
        return (-1);
    }

    HEX5_ptr = (int *)(LW_virtual + HEX5_BASE);
    HEX4_ptr = (int *)(LW_virtual + HEX4_BASE);
    HEX3_ptr = (int *)(LW_virtual + HEX3_BASE);
    HEX2_ptr = (int *)(LW_virtual + HEX2_BASE);
    HEX1_ptr = (int *)(LW_virtual + HEX1_BASE);
    HEX0_ptr = (int *)(LW_virtual + HEX0_BASE);

    KEYS_BASE_ptr = (int *)(LW_virtual + KEYS_BASE);

    return 0;
}

int encerra_map() {
    // Fechar o mapeamento de endereço virtual previamente aberto
    if (munmap(LW_virtual, LW_BRIDGE_SPAN) != 0) {
        printf("ERROR: munmap() failed...\n");
        return (-1);
    }

    // Fechar /dev/mem para dar acesso a endereços físicos
    close(fd); 

    return 0;
}

void inicia_display(){
    *HEX0_ptr = numeros[0];
    *HEX1_ptr = numeros[0];

    *HEX2_ptr = numeros[10];
    *HEX3_ptr = numeros[10];

    *HEX4_ptr = numeros[0];
    *HEX5_ptr = numeros[0];
}

void att_placar(int pont_quadrado, int pont_triangulo){
    if(pont_quadrado > 0 && pont_quadrado < 100){
        *HEX0_ptr = numeros[pont_quadrado % 10];

        if(pont_quadrado >= 10){
            *HEX1_ptr = numeros[pont_quadrado / 10];
        }
    }

    if(pont_triangulo > 0 && pont_triangulo < 100){
        *HEX4_ptr = numeros[pont_triangulo % 10];

        if(pont_triangulo >= 10){
            *HEX5_ptr = numeros[pont_triangulo / 10];
        }
    }
}

int verifica_botao(){
    //Ordem botões: 3, 2, 1, 0

    //nenhum botão
    if(*KEYS_BASE_ptr == 15){
        return 0;
    }

    //botão 0 -> Encerra jogo
    else if(*KEYS_BASE_ptr == 14){
        return 1;
    }

    //botão 1 -> Reinicia Jogo
    else if(*KEYS_BASE_ptr == 13){
        return 2;
    }

    //botão 2 -> Despausa Jogo
    else if(*KEYS_BASE_ptr == 11){
        return 3;
    }

    //botão 3 -> Pause Jogo
    else if(*KEYS_BASE_ptr == 7){
        return 4;
    }

    //mais de um botão pressionado
    else{
        return -1;
    }
}

#endif
