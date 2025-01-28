#include <stdio.h>
#include <stdlib.h> 

typedef struct{
    int chave;
}REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux *prox;
}ELEMENTO;

typedef struct{
    ELEMENTO *cabeca;
    ELEMENTO *fim;
}FILA;

void inicializar_fila(FILA *fila){
    fila -> cabeca = malloc(sizeof(ELEMENTO));
    fila -> cabeca -> prox = NULL;
    fila -> fim = NULL;
}

int tamanho_fila(FILA *fila){
    int tam = 0;
    ELEMENTO *atual = fila -> cabeca -> prox;

    while (atual != NULL){
        tam++;
        atual = atual -> prox;
    }
    return tam;
}

void exibir_fila(FILA *fila){
    ELEMENTO *atual = fila -> cabeca -> prox;

    printf("Fila (%d): ", tamanho_fila(fila));

    while (atual != NULL){
        printf("%d ", atual -> reg.chave);
        atual = atual -> prox;
    }
    
    printf("\n");
    printf("--------------------------------------\n");
}


int enqueue_fila(FILA *fila, REGISTRO reg){

    ELEMENTO *novo = malloc(sizeof(ELEMENTO));
    if(novo == NULL) return -1;

    novo -> reg = reg;
    novo -> prox = NULL;

    if(fila -> cabeca -> prox == NULL){
        fila -> cabeca -> prox = novo;
        fila -> fim = novo;
    }
    else{
        fila -> fim -> prox = novo;
        fila -> fim = novo;
    }
    
    return 0;
}

int dequeue_fila(FILA *fila, REGISTRO *reg){
    if (fila -> cabeca -> prox == NULL) return -1;

    *reg = fila -> cabeca -> prox -> reg;

    ELEMENTO *antigo_cabeca = fila -> cabeca -> prox;
    fila -> cabeca -> prox = fila -> cabeca -> prox -> prox;
    free(antigo_cabeca);

    if (fila -> cabeca -> prox == NULL) fila -> fim = NULL;

    return 0;
}

void reinicializar_lista(FILA *fila){
    ELEMENTO *atual = fila -> cabeca -> prox;

    while (atual != NULL){
        ELEMENTO *apagar = atual;
        atual = atual -> prox;
        free(apagar);
    }
    fila -> cabeca -> prox = NULL;
    fila -> fim = NULL;
}

int main(){
    FILA fila;
    inicializar_fila(&fila);

    for (int i = 0; i < 7; i++){
        REGISTRO reg;
        reg.chave = (random() % 100);
        printf("Enfileirando reg com chave %d\n", reg.chave);
        enqueue_fila(&fila, reg);
        exibir_fila(&fila);
    }

    printf("/////////////////////////////////////////////////////////\n");

    for (int i = 0; i < 8; i++){
        REGISTRO reg;
        int deucerto = dequeue_fila(&fila, &reg);

        if (deucerto == 0){
            printf("Elemento desenfileirado: %d\n", reg.chave);
            exibir_fila(&fila);
        }

        else printf("Fila vazia\n");
    }

    return 0;
}