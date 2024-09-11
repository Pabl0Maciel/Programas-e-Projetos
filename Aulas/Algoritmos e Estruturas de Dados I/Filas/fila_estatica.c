#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct{
    int chave;
}REGISTRO;

typedef struct{
    REGISTRO elementos[MAX];
    int inicio;
    int tamanho;
}FILA;

void inicializar_fila(FILA *fila){
    fila -> inicio = 0;
    fila -> tamanho = 0;
}

int tamanho_fila(FILA *fila){
    return fila -> tamanho;
}

void exibir_fila(FILA *fila){
    int inicio = fila -> inicio;

    printf("Fila (%d): ", fila -> tamanho);

    for (int i = 0; i < fila -> tamanho; i++){
        printf("%d ", fila -> elementos[inicio].chave);
        inicio = (inicio + 1) % MAX;
    }
    printf("\n");
    printf("--------------------------------------\n");
}

int enqueue_fila(FILA *fila, REGISTRO reg){
    if ((fila -> tamanho) >= MAX) return -1;

    int pos_inserir = ((fila -> inicio) + (fila -> tamanho)) % MAX;
    fila -> elementos[pos_inserir] = reg;
    fila -> tamanho++;

    return 0;   
}

int dequeue(FILA *fila, REGISTRO *reg){
    if (fila -> tamanho == 0) return -1;

    *reg = fila -> elementos[fila -> inicio];
    fila -> inicio = ((fila -> inicio) + 1) % MAX;
    fila -> tamanho --; 

    return 0;
}

void reinicializar_fila(FILA *fila){
    inicializar_fila(fila);
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
        int deucerto = dequeue(&fila, &reg);

        if (deucerto == 0){
            printf("Elemento desenfileirado: %d\n", fila.elementos[i].chave);
            exibir_fila(&fila);
        }

        else printf("Fila vazia\n");
    }

    return 0;
}