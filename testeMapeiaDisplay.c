#include "mapeamento.h"
#include <unistd.h>

int main() {

    if(inicia_map() == -1){
        return -1;
    }

    inicia_display();
    usleep(1000000);

    for(int i=0; i<21; i++){
        att_placar(i,i);
        usleep(1000000);
    }

    usleep(1000000);

    printf("Tentando -1\n");
    att_placar(-1,-1);

    printf("Tentando 100\n");
    att_placar(100,100);


    if(encerra_map() == -1){
        return -1;
    }

    return 0;
}
