#include <stdio.h>
#include <stdlib.h>


#define MAX 50 // tamanho do array

typedef struct{
    int chave;
}ELEMENTO;

typedef struct{
    ELEMENTO elementos[MAX+1]; // alterei de MAX para MAX+1 por conta da busca com pivo
    int tamanho;
}LISTA;

void inicializar_lista(LISTA *lista){
    lista -> tamanho = 0;
}

int tamanho_lista(LISTA *lista){
    return lista -> tamanho;
}

void exibir_lista(LISTA *lista){
    printf("Conteudo da Lista (%d): ", lista -> tamanho);
    for (int i = 0; i < lista -> tamanho; i++){
        printf("%d ", lista -> elementos[i].chave);
    }
    printf("\n");
}


int buscar_lista_pivo(LISTA *lista, int chave_buscada){
    int i = 0;
    lista -> elementos[lista -> tamanho]. chave = chave_buscada;
    while(lista -> elementos[i].chave != chave_buscada){
        i++;
    }
    if (i == lista -> tamanho){
        return -1;
    }
    return i;   
}

int inserir_lista_fim(LISTA *lista, ELEMENTO el){
    if (lista -> tamanho == MAX){
        return -1;
    }
    lista -> elementos[lista -> tamanho] = el;
    lista -> tamanho++;
    return 0;
}

int inserir_lista_pos (LISTA *lista, ELEMENTO el, int pos){
    if (lista -> tamanho == MAX || pos > lista -> tamanho || pos < 0){
        return -1;
    }
    int i = lista -> tamanho;
    while (i > pos){
        lista -> elementos[i] = lista -> elementos[i-1];
        i--;
    }
    lista -> elementos[pos] = el;
    lista -> tamanho++;
    return 0;
}

int excluir_el_lista(LISTA *lista, int chave){
    int pos = buscar_lista_pivo(lista, chave);

    if (pos < 0) return -1;


    for (int i = pos; i < lista -> tamanho-1; i++){
        lista -> elementos[i] = lista -> elementos[i+1];
    }
    lista -> tamanho--;
    return 0;
}

void reinicializar_lista(LISTA *lista){
    lista -> tamanho = 0;
}

void ordenar_lista(LISTA *lista){

    int i, continua, aux, fim = lista -> tamanho;
    do{
        continua = 0;
        for(i = 0; i < fim-1; i++){
            if ((lista -> elementos[i].chave) > (lista -> elementos[i+1].chave)){
                aux = lista -> elementos[i].chave;
                lista -> elementos[i].chave = lista -> elementos[i+1].chave;
                lista -> elementos[i+1].chave = aux;
                continua = i;
            }
        }
        fim--;
    }while(continua != 0);
}

int main(){

    LISTA minha_lista;
	
	printf("tamanho antes %d\n", minha_lista.tamanho);
	inicializar_lista(&minha_lista);
	printf("tamanho depois %d\n", minha_lista.tamanho);
	
	ELEMENTO e1 = {.chave = 99};
	//e1.chave = 99;
	inserir_lista_fim(&minha_lista, e1);
	exibir_lista(&minha_lista);
	for (int i = 0; i < 5; i++) {
		ELEMENTO e = {.chave = i*i};
		inserir_lista_fim(&minha_lista, e);
	}
	exibir_lista(&minha_lista);

	ELEMENTO e2 = {.chave = 100};
	inserir_lista_pos(&minha_lista, e2, 0); 
	exibir_lista(&minha_lista);

	e2.chave = -1;
	inserir_lista_pos(&minha_lista, e2, minha_lista.tamanho);
	exibir_lista(&minha_lista);
	
	e2.chave = 1234;
	inserir_lista_pos(&minha_lista, e2, minha_lista.tamanho/2);
	exibir_lista(&minha_lista);
	
	e2.chave = -2;
	inserir_lista_pos(&minha_lista, e2, minha_lista.tamanho+1);
	exibir_lista(&minha_lista);
	
	int ret;
	int chave;
	chave = 100;
	ret = buscar_lista_pivo(&minha_lista, chave);
	if (ret >= 0)
		printf("chave %d encontrada na posicao %d\n", chave , ret);
	else
		printf("chave %d nao encontrada \n", chave);
		
	
	chave = -1;
	ret = buscar_lista_pivo(&minha_lista, chave);
	if (ret >= 0)
		printf("chave %d encontrada na posicao %d\n", chave , ret);
	else
		printf("chave %d nao encontrada \n", chave);
		
	
	chave = 1234;
	ret = buscar_lista_pivo(&minha_lista, chave);
	if (ret >= 0)
		printf("chave %d encontrada na posicao %d\n", chave , ret);
	else
		printf("chave %d nao encontrada \n", chave);
		
	
	chave = 333;
	ret = buscar_lista_pivo(&minha_lista, chave);
    if (ret >= 0)
		printf("chave %d encontrada na posicao %d\n", chave , ret);
	else{
		printf("chave %d nao encontrada \n", chave);
    }
    
    ordenar_lista(&minha_lista);
    exibir_lista(&minha_lista);
		
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

    ordenar_lista(&minha_lista);
    exibir_lista(&minha_lista);
    
    return 0;
}
