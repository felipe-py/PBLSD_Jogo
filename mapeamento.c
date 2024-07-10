#include "mapeamento.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

//0, 1, 2, 3, -
int numeros[11] = {64, 121, 36, 48, 63};

//Ponteiro de endereço virtual para os digitos do display de 7seg
volatile int *HEX5_ptr;
volatile int *HEX4_ptr;
volatile int *HEX3_ptr;
volatile int *HEX2_ptr;
volatile int *HEX1_ptr;
volatile int *HEX0_ptr;

//Ponteiro de endereço virtual para os botões
volatile int *KEYS_BASE_ptr;

//Usado para abrir /dev/mem
int fd = -1;

//Endereços físicos para a ponte (light-weight bridge)
void *LW_virtual;

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
    *HEX0_ptr = numeros[3];
    *HEX1_ptr = numeros[0];

    *HEX2_ptr = numeros[4];
    *HEX3_ptr = numeros[4];

    *HEX4_ptr = numeros[3];
    *HEX5_ptr = numeros[0];
}

void att_display(int vidas, int habilidades){
    *HEX0_ptr = numeros[vidas % 10];

    *HEX1_ptr = numeros[vidas / 10];

    *HEX4_ptr = numeros[habilidades % 10];

    *HEX5_ptr = numeros[habilidades / 10];
}

void encerra_display(){
    *HEX0_ptr = numeros[4];
    *HEX1_ptr = numeros[4];

    *HEX2_ptr = numeros[4];
    *HEX3_ptr = numeros[4];

    *HEX4_ptr = numeros[4];
    *HEX5_ptr = numeros[4];
}

int verifica_botao(){
    //Ordem botões: 3, 2, 1, 0

    //Nenhum botão = 15
    //Botão 0 = 14
    //Botão 1 = 13
    //Botão 2 = 11
    //Botão 3 = 7
    //Mais de um botão = resto
    
    return *KEYS_BASE_ptr;
}
