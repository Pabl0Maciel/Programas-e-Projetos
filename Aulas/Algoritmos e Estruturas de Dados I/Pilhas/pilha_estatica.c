#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct{
    int chave;
}REGISTRO;

typedef struct{
    REGISTRO elementos[MAX];
    int topo;
}PILHA;

void inicializar_pilha(PILHA *pilha){
    pilha -> topo = -1;
}

int tamanho_pilha(PILHA *pilha){
    return (pilha -> topo + 1);
}

int push(PILHA *pilha, REGISTRO reg){
    if (pilha -> topo == MAX -1) return -1;

    pilha -> topo++;
    pilha -> elementos[pilha -> topo] = reg;

    return 0;
}

int pop(PILHA *pilha, REGISTRO *reg){
    if (pilha -> topo == -1) return -1;

    *reg = pilha -> elementos[pilha -> topo];
    pilha -> topo--;

    return 0;
}

void reinicializar_pilha(PILHA *pilha){
    pilha -> topo = -1;
}


void exibir_pilha(PILHA *pilha){
    printf("Pilha (%d), topo: ", tamanho_pilha(pilha));
    for (int i = pilha -> topo; i >= 0; i--){
        printf("%d ", pilha -> elementos[i].chave);
    }
    printf("base\n");
}
int main(){

    PILHA pilha;
    REGISTRO reg;

    inicializar_pilha(&pilha);

    reg.chave = 10;
    push(&pilha, reg);
    exibir_pilha(&pilha);

    reg.chave = 50;
    push(&pilha, reg);
    exibir_pilha(&pilha);

    reg.chave = 30;
    push(&pilha, reg);
    exibir_pilha(&pilha);

    pop(&pilha, &reg);
    printf("Chave removida: %d\n", reg.chave);
    exibir_pilha(&pilha);

    pop(&pilha, &reg);
    printf("Chave removida: %d\n", reg.chave);
    exibir_pilha(&pilha);


    return 0;
}