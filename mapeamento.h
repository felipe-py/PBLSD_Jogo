#ifndef MAPEAMENTO_H
#define MAPEAMENTO_H

/* Endereço base do LW bridge */
#define LW_BRIDGE_BASE 0xFF200000   

/* Espaço mapeado do LW bridge */
#define LW_BRIDGE_SPAN 0x80        

/* Endereço dos botões da FPGA */
#define KEYS_BASE 0x0

/* Endereços dos dígitos do display de 7 segmentos da FPGA */
#define HEX5_BASE 0x10
#define HEX4_BASE 0x20
#define HEX3_BASE 0x30
#define HEX2_BASE 0x40
#define HEX1_BASE 0x50
#define HEX0_BASE 0x60

/* Função para inicializar comunicação com os periféricos da FPGA ( Mapeia botões e display de 7 segmentos ) */
int 
inicia_map();

/* Função para encerrar comunicação com os periféricos da FPGA ( fecha mapeamento com botões e display de 7 segmentos ) */
int 
encerra_map();

/* Função para atribuir o caractere "-" a todos os dígitos do display de 7 segmentos da FPGA */
void 
inicia_display();

/**Função para atualizar os dígitos do display de 7 segmentos da FPGA com as informações do jogo 
 * (quantidade de vidas e habilidades restantes do jogador)
 */
void 
att_display(int vidas, int habilidades);

/* Função que retorna o estado dos botões da FPGA (qual botão está sendo pressionado) */
int 
verifica_botao();

#endif
