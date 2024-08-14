#include <stdio.h>
#include <stdlib.h>

// Versao 2: Uso de insercao ordenada e busca binaria

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
void exibir_lista(LISTA *lista){
    printf("Conteudo da Lista (%d): ", lista -> tamanho);
    for (int i = 0; i < lista -> tamanho; i++){
        printf("%d ", lista -> elementos[i].chave);
    }
    printf("\n");
}

// busca binaria
int busca_binaria(LISTA *lista, int chave_buscada){
	int esq, meio, dir;

	esq = 0;
	dir = lista -> tamanho-1;

	while(esq <= dir){
		meio = (esq + dir)/2;

		if (lista -> elementos[meio].chave == chave_buscada){
			return meio;
		}
		else if (lista -> elementos[meio].chave > chave_buscada){
			dir = meio-1;
		}
		else{
			esq = meio + 1;
		}
	}
	return -1;
}

// insere as chaves ordenadamente
int inserir_lista_ord(LISTA *lista, ELEMENTO el){
	if (lista -> tamanho == MAX){
		return -1;
	}
	int i = lista -> tamanho;
	while (i > 0 && (lista -> elementos[i-1].chave > el.chave)){
		lista -> elementos[i] = lista -> elementos[i-1];
		i--;
	}
	lista -> elementos[i] = el;
	lista -> tamanho++;
	return 0;

}

// exclui um elemento da lista a partir da chave passada
int excluir_el_lista(LISTA *lista, int chave){
    // busca a posicao da chave passada
    int pos = busca_binaria(lista, chave);

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

    LISTA minha_lista;
	
	printf("tamanho antes %d\n", minha_lista.tamanho);
	inicializar_lista(&minha_lista);
	printf("tamanho depois %d\n", minha_lista.tamanho);
	
	ELEMENTO e1 = {.chave = 99};
	//e1.chave = 99;
	inserir_lista_ord(&minha_lista, e1);
	exibir_lista(&minha_lista);
	for (int i = 0; i < 5; i++) {
		ELEMENTO e = {.chave = i*i};
		inserir_lista_ord(&minha_lista, e);
	}
	exibir_lista(&minha_lista);

	ELEMENTO e2 = {.chave = 100};
	inserir_lista_ord(&minha_lista, e2); 
	exibir_lista(&minha_lista);

	e2.chave = -1;
	inserir_lista_ord(&minha_lista, e2);
	exibir_lista(&minha_lista);
	
	e2.chave = 1234;
	inserir_lista_ord(&minha_lista, e2);
	exibir_lista(&minha_lista);
	
	e2.chave = -2;
	inserir_lista_ord(&minha_lista, e2);
	exibir_lista(&minha_lista);
	
	int ret;
	int chave;
	chave = 100;
	ret = busca_binaria(&minha_lista, chave);
	if (ret >= 0)
		printf("chave %d encontrada na posicao %d\n", chave , ret);
	else
		printf("chave %d nao encontrada \n", chave);
		
	
	chave = -1;
	ret = busca_binaria(&minha_lista, chave);
	if (ret >= 0)
		printf("chave %d encontrada na posicao %d\n", chave , ret);
	else
		printf("chave %d nao encontrada \n", chave);
		
	
	chave = 1234;
	ret = busca_binaria(&minha_lista, chave);
	if (ret >= 0)
		printf("chave %d encontrada na posicao %d\n", chave , ret);
	else
		printf("chave %d nao encontrada \n", chave);
		
	
	chave = 333;
	ret = busca_binaria(&minha_lista, chave);
    if (ret >= 0)
		printf("chave %d encontrada na posicao %d\n", chave , ret);
	else
		printf("chave %d nao encontrada \n", chave);
		
	excluir_el_lista(&minha_lista, -1);
	exibir_lista(&minha_lista);
	
	excluir_el_lista(&minha_lista, 100);
	exibir_lista(&minha_lista);
	
	excluir_el_lista(&minha_lista, 1234);
	exibir_lista(&minha_lista);
	
	
	excluir_el_lista(&minha_lista, 1333234);
	exibir_lista(&minha_lista);
	
	reinicializar_lista(&minha_lista);
	exibir_lista(&minha_lista);
    
    return 0;
}


