#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int chave;
}REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux *prox;
}ELEMENTO;

typedef struct{
    ELEMENTO *topo;
}PILHA;

void inicializar_pilha(PILHA *pilha){
    pilha -> topo = NULL;
}

int tamanho_pilha(PILHA *pilha){
    int tamanho = 0;
    if (pilha -> topo == NULL) return tamanho;

    ELEMENTO *atual = pilha -> topo;
    while (atual != NULL){
        tamanho++;
        atual = atual -> prox;
    }
    return tamanho;
}

int peek(PILHA *pilha){
    if (pilha -> topo == NULL) return -1;

    printf("Chave no topo: %d\n", pilha -> topo -> reg.chave);
    
    return 0;
}

void exibir_pilha(PILHA *pilha){
    printf("Pilha (%d), topo: ", tamanho_pilha(pilha));
    ELEMENTO *atual = pilha -> topo;
    
    while (atual != NULL){
        printf("%d ", atual -> reg.chave);
        atual = atual -> prox;
    }
    printf("\n----------------------------------------------------------------------\n");
}

int push(PILHA *pilha, REGISTRO reg){
    ELEMENTO *novo = malloc(sizeof(ELEMENTO));
    if (novo == NULL) return -1;

    novo -> reg = reg;
    
    novo -> prox = pilha -> topo;
    pilha -> topo = novo;

    return 0;
}

int pop(PILHA *pilha, REGISTRO *reg){
    if (pilha -> topo == NULL) return -1;

    *reg = pilha -> topo -> reg;

    ELEMENTO *apagar = pilha -> topo;
    pilha -> topo = pilha -> topo -> prox;
    free(apagar);

    return 0;
}

void reinicializar_pilha(PILHA *pilha){
    ELEMENTO *atual = pilha -> topo;
    ELEMENTO *apagar;

    while(atual != NULL){
        apagar = atual;
        atual = atual -> prox;
        free(apagar);
    }
    pilha -> topo = NULL;
}

int main(){

    PILHA *pilha = malloc(sizeof(PILHA));
    if (pilha == NULL) return -1;

    inicializar_pilha(pilha);

    for (int i = 0; i < 10; i++){
        int novachave = random() % 100;
        REGISTRO reg = {.chave = novachave};
        printf("Push %d\n", reg.chave);
        push(pilha, reg);
        peek(pilha);
        exibir_pilha(pilha);
    }

    for (int i = 0; i < 3; i++){
        REGISTRO reg_do_topo;
        pop(pilha, &reg_do_topo);
        printf("Chave removida: %d\n", reg_do_topo.chave);
        exibir_pilha(pilha);
    }

    reinicializar_pilha(pilha);
    exibir_pilha(pilha);

    return 0;
}