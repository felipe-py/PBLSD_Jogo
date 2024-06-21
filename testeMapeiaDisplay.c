#include "mapeamento.c"
#include <unistd.h>

int main() {

    if(inicia_map() == -1){
        return -1;
    }

    inicia_display();
    usleep(5000000);

    for(int i=0; i<21; i++){
        att_placar(i,i);
        usleep(1000000);
    }

    if(encerra_map() == -1){
        return -1;
    }

    return 0;
}