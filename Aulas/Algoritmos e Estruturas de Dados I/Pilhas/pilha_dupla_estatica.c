#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct{
    int chave;
}REGISTRO;

typedef struct{
    REGISTRO elementos[MAX];
    int topo1;
    int topo2;
}PILHA_DUPLA;

void inicializar_pilha(PILHA_DUPLA *pilha){
    pilha -> topo1 = -1;
    pilha -> topo2 = MAX;
}

int tamanho_pilha(PILHA_DUPLA *pilha){
    return ((pilha -> topo1+1) + (MAX - (pilha -> topo2)));
}

int push(PILHA_DUPLA *pilha, int n_pilha, REGISTRO reg){
    if ((pilha -> topo1 + 1) == (pilha -> topo2)) return -1;

    if (n_pilha != 1 && n_pilha != 2) return -1;

    if (n_pilha == 1){
        pilha -> topo1++;
        pilha -> elementos[pilha -> topo1] = reg;
    }

    if (n_pilha == 2){
        pilha -> topo2--;
        pilha -> elementos[pilha -> topo2] = reg;
    }

    return 0;
}

int pop(PILHA_DUPLA *pilha, int n_pilha, REGISTRO *reg){
    if (n_pilha != 1 && n_pilha != 2) return -1;

    if (n_pilha == 1){
        if (pilha -> topo1 == -1) return -1;
        *reg = pilha -> elementos[pilha -> topo1];
        pilha -> topo1--;
    }

    if (n_pilha == 2){
        if (pilha -> topo2 == -1) return -1;
        *reg = pilha -> elementos[pilha -> topo2];
        pilha -> topo2++;
    }

    return 0;
}

void reinicializar_pilha(PILHA_DUPLA *pilha){
    pilha -> topo1 = -1;
    pilha -> topo2 = MAX;
}

void exibir_pilha(PILHA_DUPLA *pilha){
    
    printf("Pilha (%d), topo1: ", tamanho_pilha(pilha));
    for (int i = pilha -> topo1; i >= 0; i--){
        printf("%d ", pilha -> elementos[i].chave);
    }
    printf("base 1\n");

    printf("Pilha (%d), topo2: ", tamanho_pilha(pilha));
    for (int i = pilha -> topo2; i < MAX; i++){
        printf("%d ", pilha -> elementos[i].chave);
    }
    printf("base 2\n");
    printf("-------------------------------------------------------\n");
}

int main(){

    PILHA_DUPLA pilha;
    REGISTRO reg, reg2;

    inicializar_pilha(&pilha);

    reg.chave = 10;
    push(&pilha, 1, reg);
    exibir_pilha(&pilha);

    reg.chave = 50;
    push(&pilha, 1, reg);
    exibir_pilha(&pilha);

    reg.chave = 30;
    push(&pilha, 1, reg);
    exibir_pilha(&pilha);

    pop(&pilha, 1, &reg);
    printf("Chave removida da pilha 1: %d\n", reg.chave);
    exibir_pilha(&pilha);

    pop(&pilha, 1, &reg);
    printf("Chave removida da pilha 1: %d\n", reg.chave);
    exibir_pilha(&pilha);

    reg2.chave = 100;
    push(&pilha, 2, reg2);
    exibir_pilha(&pilha);

    reg2.chave = 500;
    push(&pilha, 2, reg2);
    exibir_pilha(&pilha);

    reg2.chave = 300;
    push(&pilha, 2, reg2);
    exibir_pilha(&pilha);

    pop(&pilha, 2, &reg2);
    printf("Chave removida da pilha 2: %d\n", reg.chave);
    exibir_pilha(&pilha);

    pop(&pilha, 2, &reg2);
    printf("Chave removida da pilha 2: %d\n", reg.chave);
    exibir_pilha(&pilha);


    return 0;
}