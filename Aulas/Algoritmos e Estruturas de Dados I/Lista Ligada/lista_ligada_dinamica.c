#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Versao com alocacao dinamica

// Estrutura linear na qual cada elemento possui no máximo um predecessor e um sucessor.
// Cada elemento precisa indicar quem é o seu sucessor.
#define INVALIDO -1

// cria um registro com as chaves
typedef struct{
    int chave;
    // outros campos...
} REGISTRO;

// faz com que cada elemento possua uma variavel de registro e um ponteiro que aponta para o proximo registro
typedef struct{
    REGISTRO reg;
    struct elemento_aux *prox;
}ELEMENTO;

// cria uma lista com esses elementos e um ponteiro de inicio
typedef struct{
    ELEMENTO *inicio;
}LISTA;

void inicializar_lista(LISTA *lista){
    lista -> inicio = NULL;
}

int tamanho_lista(LISTA *lista){
    int tamanho = 0;
    ELEMENTO *ptr = lista -> inicio;
    while(ptr != NULL){
        tamanho ++;
        ptr = ptr -> prox;
    }
    return tamanho;
}

void busca_auxiliar (LISTA *lista, int chave, ELEMENTO **anterior, int *achou){
    *anterior = NULL;
    *achou = -1;
    ELEMENTO *atual = lista -> inicio;

    while (atual != NULL && atual -> reg.chave < chave){
        *anterior = atual;
        atual = atual -> prox;
    }
    if (atual != NULL && atual -> reg.chave == chave) *achou = 0;
}

int inserir_lista_ord(LISTA *lista, REGISTRO reg){
    ELEMENTO *anterior;
    ELEMENTO *atual;
    int achou;

    ELEMENTO *novo_elemento = malloc(sizeof(ELEMENTO));
    if (novo_elemento == NULL) return -1;
    novo_elemento -> reg = reg;

    busca_auxiliar (lista, reg.chave, &anterior, &achou);

    while (atual != NULL && atual -> reg.chave < reg.chave){
        anterior = atual;
        atual = atual -> prox;
    }

    if (achou) return -1;

    if (anterior == NULL){
        novo_elemento -> prox = lista -> inicio;
        lista -> inicio = novo_elemento;
    }
    else{
        novo_elemento -> prox = anterior -> prox;
        anterior -> prox = novo_elemento;
    }

    return 0;
}

void exibir_lista(LISTA *lista){
    ELEMENTO *ptr = lista -> inicio;
    printf("Tamanho: %d, Elementos: ", tamanho_lista(lista));
    while(ptr != NULL){
        printf("%i ", ptr -> reg.chave);
        ptr = ptr -> prox;
    }
    return 0;
}

int excluir_elemento(LISTA *lista, int chave){
    ELEMENTO *anterior;
    int achou;
    busca_auxiliar(lista, chave, &anterior, &achou);

    if (!achou) return -1;

    if (anterior == NULL){
        ELEMENTO *a_dar_free = lista -> inicio;
        lista -> inicio = lista -> inicio -> prox;
        free (a_dar_free);
    }
    else{
        ELEMENTO *a_dar_free = anterior -> prox;
        anterior -> prox = anterior -> prox -> prox;
        free (a_dar_free);
    }
}
