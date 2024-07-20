#ifndef CARREGA_TELAS_SPRITES_H
#define CARREGA_TELAS_SPRITES_H

/**Função para modificar a memória de sprites da GPU e inserir sprites criados para o jogo 
 * LADRÃO PADRÃO, SAIR, PAUSE, PLAY, LADRÃO FURTIVO, POLICIAL, PORTA - Respectivamente na ordem
 */
int
carrega_sprites();

/* Função para exibir tela inicial do jogo */
int 
tela_inicial();

/* Função para exibir tela de vitória do jogo */
int 
tela_win();

/* Função para exibir tela de derrota do jogo */
int 
tela_lose();

/* Função para exibir tela de saída do jogo */
int 
tela_bye();

/* Função para exibir tela padrão do jogo */
int 
tela_padrao();

#endif
