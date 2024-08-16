#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura linear na qual cada elemento possui no máximo um predecessor e um sucessor.
// Cada elemento precisa indicar quem é o seu sucessor.
#define INVALIDO -1
#define MAX 50

// cria um registro com as chaves
typedef struct{
    int chave;
    // outros campos...
} REGISTRO;

// faz com que cada elemento possua uma variavel de registro e uma que aponte para um proximo
typedef struct{
    REGISTRO reg;
    int prox;
}ELEMENTO;

// cria uma lista com esses elementos, o inicio e as posicoes disponiveis
typedef struct{
    ELEMENTO elementos[MAX];
    int inicio;
    int disp;
}LISTA;

// inicializa a lista como vazia
inicializa_lista(LISTA *lista){
    lista -> inicio = INVALIDO;
    lista -> disp = 0;

    // faz com que os todos elementos apontem para o proximo disponivel, com a lista vazia.
    for (int i = 0; i < MAX; i++){
        lista -> elementos[i].prox = i+1;
    }
    lista -> elementos[MAX].prox = INVALIDO; // ultimo elemento nao aponta para ninguem
}

int tamanho_lista(LISTA *lista){
    int tamanho = 0;
    int pos_atual = lista -> inicio;

    while(pos_atual != INVALIDO){
        tamanho++;
        pos_atual += lista -> elementos[pos_atual].prox;
    }
}

void exibir_lista(LISTA *lista){
    printf("Conteudo da Lista (%d): ", tamanho_lista(lista));
    for (int pos =  lista -> inicio; pos != INVALIDO; pos = lista -> elementos[pos].prox){
        printf("%d ", lista -> elementos[pos].reg.chave);
    }
    printf("\n");
}

int inserir_lista_ord(LISTA *lista, REGISTRO reg){
    int anterior = INVALIDO;
    int pos = lista -> inicio;

    if (lista -> disp == INVALIDO) return -1;

    while (pos != INVALIDO && (lista -> elementos[pos].reg.chave < reg.chave)){
        anterior = pos;
        pos = lista -> elementos[pos].prox;
    }

    // pegando disponivel
    int prox_disp = lista -> disp;
    lista -> disp = lista -> elementos[prox_disp].prox;

    if (anterior == INVALIDO){
        int antigo_prox = lista -> inicio;
        lista -> elementos[prox_disp].reg = reg;
        lista -> elementos[prox_disp].prox = antigo_prox;
        lista -> inicio = prox_disp;
    }

    else{
    int antigo_prox = lista -> elementos[anterior].prox;
    lista -> elementos[anterior].prox = prox_disp;
    lista -> elementos[prox_disp].reg = reg;
    lista -> elementos[prox_disp].prox = antigo_prox;
    }
}


int main(){



    return 0;
}