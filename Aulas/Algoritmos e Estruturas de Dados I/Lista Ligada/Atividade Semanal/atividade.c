#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INVALIDO -1

typedef struct{
    int chave;
    // outros campos...
} REGISTRO;

typedef struct elemento_aux{
    REGISTRO reg;
    struct elemento_aux *prox, *ant; 
}ELEMENTO;

typedef struct{
    ELEMENTO *inicio;
}LISTA;

void inicializar_lista(LISTA *lista){
    lista -> inicio = NULL;
}

int tamanho_lista(LISTA *lista){
    int tamanho = 0;
    ELEMENTO *pos_atual = lista -> inicio;
    while(pos_atual != NULL){
        tamanho ++;
        pos_atual = pos_atual -> prox;
    }
    return tamanho;
}

ELEMENTO  *busca_auxiliar (LISTA *lista, int chave, ELEMENTO **anterior){
    *anterior = NULL;
    ELEMENTO *atual = lista -> inicio;

    while (atual != NULL && atual -> reg.chave < chave){
        *anterior = atual;
        atual = atual -> prox;
    }
    if (atual != NULL && atual -> reg.chave == chave) return atual;
    else return NULL;
}

ELEMENTO *busca_lista_ord(LISTA *lista, int chave, int *pos){
    ELEMENTO *atual = lista -> inicio;
    *pos = 0;
    while (atual != NULL && atual -> reg.chave < chave){
        atual = atual -> prox;
        (*pos)++;
    }

    if (atual != NULL && atual -> reg.chave == chave) return atual;
    else return NULL;
}

ELEMENTO *inserir_lista_ord(LISTA *lista, REGISTRO reg){
    ELEMENTO *anterior, *atual, *novo_elemento;

    atual = busca_auxiliar (lista, reg.chave, &anterior);

    if (atual != NULL) return NULL;

    novo_elemento = malloc(sizeof(ELEMENTO));

    if (novo_elemento == NULL) return NULL; 

    novo_elemento -> reg = reg;

    if (anterior == NULL){
        novo_elemento -> prox = lista -> inicio;
        novo_elemento -> ant = NULL;

        if (lista -> inicio != NULL) lista -> inicio -> ant = novo_elemento;

        lista -> inicio = novo_elemento;
    }

    else{
        novo_elemento -> prox = anterior -> prox;
        novo_elemento -> ant = anterior;
        
        if (anterior->prox != NULL) anterior->prox->ant = novo_elemento;
        
        anterior -> prox = novo_elemento;
    }

    return 0;
}

void exibir_lista(LISTA *lista){
    ELEMENTO *pos_atual = lista -> inicio;
    printf("Tamanho: %d, Elementos: ", tamanho_lista(lista));
    while(pos_atual != NULL){
        printf("%i ", pos_atual -> reg.chave);
        pos_atual = pos_atual -> prox;
    }
    printf("\n-----------------------------------------------------------------------------\n");
}

int excluir_elemento(LISTA *lista, int chave){
    ELEMENTO *anterior, *atual;

     atual = busca_auxiliar(lista, chave, &anterior);

    if (atual == NULL) return -1;

    if (anterior == NULL){
        lista -> inicio = atual -> prox;
    }
    else{
        anterior -> prox = atual -> prox;
    }
    free(atual);
    return 0;
}

void reinicializar_lista(LISTA *lista){
    ELEMENTO *atual = lista -> inicio;
    
    while (atual != NULL){
        ELEMENTO *apagar = atual;
        atual = atual -> prox;
        free(apagar);
    }
    lista -> inicio = NULL;
}

int main() {
    LISTA lista;
    inicializar_lista(&lista);

    for (int i = 0; i < 6; i++) {
		REGISTRO r = {.chave = random()%100 };
		printf("Inserindo elemento com chave = %d\n", r.chave);
		inserir_lista_ord(&lista, r);
		exibir_lista(&lista);
	}
	
    ELEMENTO *busca;
    int chave_buscada = 77;
    int pos;
    busca = busca_lista_ord(&lista, chave_buscada, &pos);
    if (busca != NULL){
       printf ("Chave %d encontrada na posicao %d\n", chave_buscada, pos);
    } else{
        printf("Chave %d nao encontrada!\n", chave_buscada);
    }

	excluir_elemento(&lista, 15);
	exibir_lista(&lista);

	excluir_elemento(&lista, 93);
	exibir_lista(&lista);

	excluir_elemento(&lista, 77);
	exibir_lista(&lista);

    reinicializar_lista(&lista);
    exibir_lista(&lista);
    return 0;
}