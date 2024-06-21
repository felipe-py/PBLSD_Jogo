#include "mapeamento.h"

int main() {

    if(inicia_map() == -1){
        return -1;
    }

    while(1){
        int sla = verifica_botao();

        if(sla == 4)
            break;

        else if(sla == 1)
            printf("Botão 0 clicado\n");
        
        else if(sla == 2)
            printf("Botão 1 clicado\n");

        else if(sla == 3)
            printf("Botão 2 clicado\n");
    }

    printf("Botão 3 clicado, gg\n");

    if(encerra_map() == -1){
        return -1;
    }

    return 0;
}
