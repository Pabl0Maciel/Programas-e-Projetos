#include <stdio.h>
#include <stdlib.h>

// Na lista linear sequencial, a ordem dos elementos vista pelo usuario e a mesma na memoria.
// Ex: em uma lista {1,2,3,4,5}, o usuario percebe que o 1 esta antes do 2. Isso se reflete na memoria do computador, em que o 1 esta em uma posicao na
// memoria antes do 2.

#define MAX 50 // tamanho do array

// registro com informacoes que um elemento pode ter
typedef struct{
    int chave;
    // outros campos...
}ELEMENTO;

// registro que contem um array de registros 'ELEMENTO'
typedef struct{
    ELEMENTO elementos[MAX];
    int tamanho;
}LISTA;

// inicializacao da lista
void inicializar_lista(LISTA *lista){
    lista -> tamanho = 0;
}

// retornar numero de elementos
int tamanho_lista(LISTA *lista){
    return lista -> tamanho;
}

// exibir lista
void exibi_lista(LISTA *lista){
    printf("Conteudo da Lista (%d): ", lista -> tamanho);
    for (int i = 0; i < lista -> tamanho; i++){
        printf("%d ", lista -> elementos[i].chave);
    }
    printf("\n");
}

// busca a posicao de uma chave na lista
int buscar_lista(LISTA *lista, int chave){
    for (int i = 0; i < lista -> tamanho; i++){
        if (lista -> elementos[i].chave == chave){
            return i;
        }
    }
    return -1;
}

// inserir um elemento no final da lista
int inserir_lista_fim(LISTA *lista, ELEMENTO el){
    if (lista -> tamanho == MAX){
        return -1;
    }
    lista -> elementos[lista -> tamanho] = el;
    lista -> tamanho++;
    return 0;
}

// insere um elemento em uma posicao especifica
int inserir_lista_pos (LISTA *lista, ELEMENTO el, int pos){
    // verifica se da para inserir
    if (lista -> tamanho == MAX || pos > lista -> tamanho || pos < 0){
        return -1;
    }
    // desloca os elementos da lista para direita
    int i = lista -> tamanho;
    while (i > pos){
        lista -> elementos[i] = lista -> elementos[i-1];
        lista -> tamanho--;
    }
    // insere o elemento na posicao desejada
    lista -> elementos[pos] = el;
    lista -> tamanho++;
    return 0;
}

// exclui um elemento da lista a partir da chave passada
void excluir_el_lista(LISTA *lista, int chave){
    // busca a posicao da chave passada
    int pos = buscar_lista(lista, chave);

    // verifica se a posicao e valida
    if (pos < 0) return -1;

    // desloca os elementos para esquerda
    for (int i = pos; i < lista -> tamanho-1; i++){
        lista -> elementos[i] = lista -> elementos[i+1];
    }
    lista -> tamanho--;
    return 0;
}

// reinicializacao da lista
void reinicializar_lista(LISTA *lista){
    lista -> tamanho = 0;
}

int main(){


    
    return 0;
}


