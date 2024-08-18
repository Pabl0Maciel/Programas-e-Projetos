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
void inicializa_lista(LISTA *lista){
    lista -> inicio = INVALIDO;
    lista -> disp = 0;

    // faz com que os todos elementos apontem para o proximo disponivel, com a lista vazia.
    for (int i = 0; i < MAX-1; i++){
        lista -> elementos[i].prox = i+1;
    }
    lista -> elementos[MAX-1].prox = INVALIDO; // ultimo elemento nao aponta para ninguem
}

int tamanho_lista(LISTA *lista){
    int tamanho = 0;
    int pos_atual = lista -> inicio;

    while(pos_atual != INVALIDO){
        tamanho++;
        pos_atual += lista -> elementos[pos_atual].prox;
    }
    return tamanho;
}

void exibir_lista(LISTA *lista){
    printf("Conteudo da Lista (%d): ", tamanho_lista(lista));
    for (int pos =  lista -> inicio; pos != INVALIDO; pos = lista -> elementos[pos].prox){
        printf("%d ", lista -> elementos[pos].reg.chave);
    }
    printf("\n");
}

// insere chaves ordenadamente
int inserir_lista_ord(LISTA *lista, int chave){

    // verifica se a lista esta cheia
    if (lista -> disp == INVALIDO) return -1;

    // atribui ao novo elemento a primeira posicao disponivel e e faz ela apontar para a proxima posicao disponivel
    int novo = lista -> disp;
    lista -> disp = lista -> elementos[novo].prox;

    // atribui a chave desejada para o novo elemento
    lista -> elementos[novo].reg.chave = chave;

    // Se a lista está vazia ou o novo elemento é menor que o primeiro elemento
    if (lista -> inicio == INVALIDO || chave < lista -> elementos[lista -> inicio].reg.chave){
        lista -> elementos[novo].prox = lista -> inicio;
        lista -> inicio = novo;
    }

    // percorre a lista desde de o inicio, procurando a posicao correta para inserir o novo elemento
    int atual = lista -> inicio;
    int anterior = INVALIDO;

    while (atual != INVALIDO && lista -> elementos[atual].reg.chave < lista -> elementos[novo].reg.chave){
        anterior = atual;
        atual = lista -> elementos[atual].prox;
    }

    // insere o elemento (como o elemento deve ser inserido atras da posicao atual, seu proximo recebe o atual e seu anterior aponta para o novo elemento)
    lista -> elementos[novo].prox = atual;
    lista -> elementos[anterior].prox = novo;

    return 0;
}

// exclui um elemento pela chave passada
int excluir_elemento(LISTA *lista, int chave){
    // verifica se a lista esta vazia
    if (lista -> inicio == INVALIDO) return -1;

    int anterior = INVALIDO;
    int atual = lista -> inicio;

    // procura a posicao do elemento
    while (atual != INVALIDO && lista -> elementos[atual].reg.chave != chave){
        anterior = atual;
        atual = lista -> elementos[atual].prox;
    }

    // se o elemento nao esta na lista
    if (atual == INVALIDO) return -1;

    // se o elemento e o primeiro da lista
    if (anterior == INVALIDO){
        lista -> inicio == lista -> elementos[atual].prox;
    }

    // pula o elemento excluido (faz com que seu anterior aponte diretamente para o proximo do elemento excluido)
    else{
        lista -> elementos[anterior].prox = lista -> elementos[atual].prox;
    }

    // faz com que o elemento exlcuido aponte para a posicao disponivel
    lista -> elementos[atual].prox = lista -> disp;
    lista -> disp = atual;

    return 0;
}

int main(){



    return 0;
}