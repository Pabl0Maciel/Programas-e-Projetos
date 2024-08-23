#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INVALIDO -1

// cria um registro com as chaves
typedef struct{
    int chave;
    // outros campos...
} REGISTRO;

// faz com que cada elemento possua uma variavel de registro e um ponteiro que aponta para o proximo registro
typedef struct elemento_aux{
    REGISTRO reg;
    struct elemento_aux *prox; // notacao para indicar um ponteiro 'prox' do tipo ELEMENTO (usado pois a compilador ainda nao sabe da struct ELEMENTO)
}ELEMENTO;

// cria uma lista com esses elementos e um ponteiro de cabeca
typedef struct{
    ELEMENTO *cabeca;
}LISTA;

void inicializa_lista(LISTA *lista){
    lista -> cabeca = malloc(sizeof(ELEMENTO));
    lista -> cabeca -> prox = lista -> cabeca;
}

int tamanho_lista(LISTA *lista){
    int tamanho = 0;
    ELEMENTO *atual = lista -> cabeca -> prox;

    while (atual != lista -> cabeca){
        tamanho ++;
        atual = atual -> prox;
    }
    return tamanho;
}

void exibir_lista(LISTA *lista){
    ELEMENTO *atual = lista -> cabeca -> prox;
    printf("Tamanho: %d, Elementos: ", tamanho_lista(lista));
    while(atual != lista -> cabeca){
        printf("%i ", atual -> reg.chave);
        atual = atual -> prox;
    }
    printf("\n-----------------------------------------------------------------------------\n");
}

ELEMENTO  *busca_auxiliar (LISTA *lista, int chave, ELEMENTO **anterior){
    *anterior = lista -> cabeca;
    ELEMENTO *atual = lista -> cabeca -> prox;

    // procura o endereco
    while (atual != lista -> cabeca && atual -> reg.chave < chave){
        *anterior = atual;
        atual = atual -> prox;
    }
    // se achar a chave, devolve o endereco
    if (atual != lista -> cabeca && atual -> reg.chave == chave) return atual;
    else return NULL;
}

int *inserir_lista_ord(LISTA *lista, REGISTRO reg){
    ELEMENTO *anterior, *novo_elemento;
    
    novo_elemento = busca_auxiliar(lista, reg.chave, &anterior);
    if (novo_elemento != NULL) return NULL;

    novo_elemento = malloc(sizeof(ELEMENTO));
    if (novo_elemento == NULL) return NULL;

    novo_elemento -> reg = reg;

    novo_elemento -> prox = anterior -> prox;
    anterior -> prox = novo_elemento;
    return 0;
}

int excluir_elemento(LISTA *lista, int chave){
    ELEMENTO *anterior, *atual;
    
    atual = busca_auxiliar(lista, chave, &anterior);
    if (atual == NULL) return -1;

    anterior -> prox = atual -> prox;
    free(atual);
    return 0;
}

void reinicializar_lista(LISTA *lista){
    ELEMENTO *atual = lista -> cabeca -> prox;
    
    while (atual != lista -> cabeca){
        ELEMENTO *apagar = atual;
        atual = atual -> prox;
        free(apagar);
    }
    lista -> cabeca -> prox = lista -> cabeca;
}

ELEMENTO *busca_lista_ord(LISTA *lista, int chave, int *pos){
    ELEMENTO *atual = lista -> cabeca -> prox;
    *pos = 0;
    while (atual -> reg.chave < chave){
        atual = atual -> prox;
        (*pos)++;
    }

    if (atual != lista -> cabeca && atual -> reg.chave == chave) return atual;
    else return NULL;
}

int main() {
    LISTA lista;
    inicializa_lista(&lista);

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
        printf("Chave %d encontrada na posicao %d\n", chave_buscada, pos);
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