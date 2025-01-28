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
typedef struct elemento_aux{
    REGISTRO reg;
    struct elemento_aux *prox; // notacao para indicar um ponteiro 'prox' do tipo ELEMENTO (usado pois a compilador ainda nao sabe da struct ELEMENTO)
}ELEMENTO;

// cria uma lista com esses elementos e um ponteiro de inicio
typedef struct{
    ELEMENTO *inicio;
}LISTA;

// inicializa a lista com o ponteiro inicio apontando para o vazio, ja que a lista esta vazia
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

// retorna o endereco do elemento que possui a chave ou que vem depois dele, no caso de inserir, e o endereco de seu anterior
ELEMENTO  *busca_auxiliar (LISTA *lista, int chave, ELEMENTO **anterior){
    *anterior = NULL;
    ELEMENTO *atual = lista -> inicio;

    // procura o endereco
    while (atual != NULL && atual -> reg.chave < chave){
        *anterior = atual;
        atual = atual -> prox;
    }
    // se achar a chave, devolve o endereco
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

// insere um registro ordenadamente
ELEMENTO *inserir_lista_ord(LISTA *lista, REGISTRO reg){
    ELEMENTO *anterior;
    ELEMENTO *novo_elemento;

    // acha a posicao em que o novo elemento deve ser inserido
    novo_elemento = busca_auxiliar (lista, reg.chave, &anterior);

    // quer dizer que foi encontrado um elemento com a chave que se deseja inserir, nao queremos chaves duplicadas
    if (novo_elemento != NULL) return NULL;

    // aloca memoria dinamicamente para o novo elemento
    novo_elemento = malloc(sizeof(ELEMENTO));

    // testa se foi alocado memoria com sucesso
    if (novo_elemento == NULL) return NULL; 

    // atribui o registro passado ao novo elemento
    novo_elemento -> reg = reg;

    // caso o elemento seja o primeiro da lista, seu proximo aponta para o que era o inicio (NULL) e o inicio aponta para ele
    if (anterior == NULL){
        novo_elemento -> prox = lista -> inicio;
        lista -> inicio = novo_elemento;
    }

    // o proximo elemento apontado pelo anterior agora eh o novo elemento e o proximo elemento apontado pelo novo elemento eh o apontado pelo anterior
    else{
        novo_elemento -> prox = anterior -> prox;
        anterior -> prox = novo_elemento;
    }

    return 0;
}

// mostra o conteudo da lista
void exibir_lista(LISTA *lista){
    ELEMENTO *pos_atual = lista -> inicio;
    printf("Tamanho: %d, Elementos: ", tamanho_lista(lista));
    while(pos_atual != NULL){
        printf("%i ", pos_atual -> reg.chave);
        pos_atual = pos_atual -> prox;
    }
    printf("\n-----------------------------------------------------------------------------\n");
}

// exclui um elemento
int excluir_elemento(LISTA *lista, int chave){
    ELEMENTO *anterior, *atual;

     atual = busca_auxiliar(lista, chave, &anterior);

    if (atual == NULL) return -1;

    // se o elemento eh o primeiro da lista, o inicio aponta para o seu proximo (NULL)
    if (anterior == NULL){
        lista -> inicio = atual -> prox;
    }
    // se o elemento tem anterior, seu anterior agora aponta para o proximo do atual (pula o elemento excluido)
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
