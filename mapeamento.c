#include "mapeamento.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

/**Vetor que contém números refetentes a codificação dos caracteres: 0, 1, 2, 3, -, respectivamente,
 * para envio aos dígitos do display de 7 segmentos da FPGA 
 */
int numeros[11] = {64, 121, 36, 48, 63};

/* Ponteiros de endereço virtual para os dígitos do display de 7 segmentos da FPGA */
volatile int *HEX5_ptr;
volatile int *HEX4_ptr;
volatile int *HEX3_ptr;
volatile int *HEX2_ptr;
volatile int *HEX1_ptr;
volatile int *HEX0_ptr;

/* Ponteiro de endereço virtual para os botões da FPGA */
volatile int *KEYS_BASE_ptr;

/* Usado para abrir /dev/mem */
int fd = -1;

/* Endereços físicos do LW bridge */
void *LW_virtual;

/**Função para inicializar comunicação com os periféricos da FPGA ( Mapeia botões e display de 7 segmentos )
 * retorno ->       0 caso comunicação seja iniciada ou -1 caso dê erro
 */
int 
inicia_map() {

    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return (-1);
    }

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

/**Função para encerrar comunicação com os periféricos da FPGA ( fecha mapeamento com botões e display de 7 segmentos )
 * retorno ->       0 caso comunicação seja encerrada ou -1 caso dê erro
 */
int 
encerra_map() {

    if (munmap(LW_virtual, LW_BRIDGE_SPAN) != 0) {
        printf("ERROR: munmap() failed...\n");
        return (-1);
    }

    close(fd); 

    return 0;
}

/* Função para atribuir o caractere "-" a todos os dígitos do display de 7 segmentos da FPGA */
void 
inicia_display() {
    *HEX0_ptr = numeros[4];
    *HEX1_ptr = numeros[4];

    *HEX2_ptr = numeros[4];
    *HEX3_ptr = numeros[4];

    *HEX4_ptr = numeros[4];
    *HEX5_ptr = numeros[4];
}

/**Função para atualizar os dígitos do display de 7 segmentos da FPGA com as informações do jogo 
 * (quantidade de vidas e habilidades restantes do jogador)
 * parâmetros ->    vidas: vidas restantes do jogador
 *                  habilidades: habilidades restantes do jogador
 */
void 
att_display(int vidas, int habilidades) {
    *HEX0_ptr = numeros[habilidades % 10];

    *HEX1_ptr = numeros[habilidades / 10];

    *HEX4_ptr = numeros[vidas % 10];

    *HEX5_ptr = numeros[vidas / 10];
}

/**Função que retorna o estado dos botões da FPGA (qual botão está sendo pressionado)
 * retorno ->       valor referente ao estado dos botões
 */
int 
verifica_botao() {
    //Ordem botões: 3, 2, 1, 0

    //Nenhum botão = 15
    //Botão 0 = 14
    //Botão 1 = 13
    //Botão 2 = 11
    //Botão 3 = 7
    //Mais de um botão = qualquer outro valor
    
    return *KEYS_BASE_ptr;
}
