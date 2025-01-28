#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef struct{
    int comeco;
    int fim;
    int vazia;
    NO *nos[MAX];
}FILA;

typedef struct{
    int topo;
    NO *nos[1000];
}PILHA;

typedef struct aux {
    int chave;
    struct aux *esq, *dir;
} NO;

NO *criar_no(int chave){
    NO *novo_no = malloc(sizeof(NO));
    
    novo_no -> esq = NULL;
    novo_no -> dir = NULL;
    novo_no -> chave = chave;

    return(novo_no);
}

NO *inicializar(){
    return NULL;
}

NO *inserir(NO *raiz, int nova_chave){
    if (raiz == NULL){
        return criar_no(nova_chave);
    }

    if (nova_chave < raiz -> chave){
        raiz -> esq = inserir(raiz -> esq, nova_chave);
    }
    else if (nova_chave > raiz -> chave){
        raiz -> dir = inserir(raiz -> dir, nova_chave);
    }

    return (raiz);
}

NO *busca(NO *arvore, int chave_buscada){
    if (arvore == NULL) return NULL;

    if (arvore -> chave == chave_buscada){
        return arvore;
    }

    if (chave_buscada > arvore -> chave){
        return busca(arvore -> dir, chave_buscada);
    }

    else{
        return busca(arvore -> esq, chave_buscada);
    }

}

int tamanho(NO *arvore){
    if (arvore == NULL) return 0;

    return 1 + tamanho(arvore -> esq) + tamanho(arvore -> dir);
}

void exibir_PreOrdem(NO *arvore){
    if (arvore == NULL) return;

    printf("%d (", arvore -> chave);
    exibir_PreOrdem(arvore -> esq);
    exibir_PreOrdem(arvore -> dir);
    printf(")");
}

void exibir_EmOrdem(NO *arvore){
    if (arvore == NULL) return;

    printf("%d (", arvore -> chave);
    exibir_EmOrdem(arvore -> esq);
    exibir_EmOrdem(arvore -> dir);
    printf(")");
}

void push(PILHA *pilha, NO * no){
    pilha -> nos[pilha -> topo++] = no;
}

void pop (PILHA *pilha, NO **no){
    pilha -> topo--;

    *no = pilha -> nos[pilha -> topo];
}

int pilha_vazia (PILHA *pilha){
    return pilha -> topo == 0;
}

void exibir_PreOrdemIterativo(NO *arvore){
    if (arvore == NULL) return;
    
    PILHA pilha;

    push(&pilha, arvore);

    while (pilha_vazia(&pilha) != 0){
        NO *aux;
        pop(&pilha, &aux);

        printf("%d ", aux -> chave);

        if (aux -> dir != NULL) push (&pilha, aux -> dir);

        if (aux -> esq != NULL) push (&pilha, aux -> esq);
    }
}

void inicializar_fila(FILA *fila){
    fila -> comeco = 0;
    fila -> fim = 0;
    fila -> vazia = 0;
}

void enqueue(FILA *fila, NO *no){
    fila -> nos[fila -> fim++] = no;
    fila -> fim = fila -> fim % MAX;
    fila -> vazia = -1;
}

NO *dequeue (FILA *fila){
    NO * aux = fila -> nos[fila -> comeco];
    fila -> comeco = (fila -> comeco + 1) % MAX;

    if (fila -> comeco == fila -> fim) fila -> vazia = 0;

    return aux;
}

void exibir_emNivel(NO *arvore){
    if (arvore == NULL) return;

    FILA fila;

    enqueue (&fila, &arvore);

    while (fila.vazia != 0){
        
        NO *aux;

        aux = dequeue(&fila);

        printf("%d ", aux -> chave);

        if (aux -> esq != NULL )enqueue(&fila, aux -> esq);
        if (aux -> dir != NULL )enqueue(&fila, aux -> dir);
    }
}

NO *buscar_iterativo(NO* arv, int valor_buscado, NO **pai) {

    *pai = NULL;

	while (arv != NULL) {
		if (arv->chave == valor_buscado) {
			return arv;
		}

        *pai = arv;
		if (valor_buscado > arv->chave) {
			arv = arv->dir;
		}
		
		if (valor_buscado < arv->chave) {
			arv = arv->esq;
		}
	}
	
	return NULL;
}

NO *excluir(NO *arvore, int chave_excluir){

    if (arvore == NULL) return NULL;

    NO *excluido, *pai_do_excluido, *substituto;
    excluido = buscar_iterativo(arvore, chave_excluir, &pai_do_excluido);

    if (excluido == NULL) return arvore;
    
    if (excluido -> dir == NULL){
        substituto = excluido -> esq;
    }

    else if (excluido -> esq == NULL){
        substituto = excluido -> dir;
    }

    else{
        NO *pai_do_substituto = excluido;
        substituto = excluido -> dir;
        
        while (substituto -> esq != NULL){
            pai_do_substituto = substituto;
            substituto = substituto -> esq;
        }

        if (pai_do_substituto != excluido){
            pai_do_substituto -> esq = substituto -> dir;
            substituto -> dir = excluido -> dir;
        }

        substituto -> esq = excluido -> esq;
    }

    if (pai_do_excluido == NULL){
        free (excluido);
        return substituto;
    }

    else{
        
        if (pai_do_excluido -> esq != NULL && pai_do_excluido -> esq -> chave == excluido -> chave){
            pai_do_excluido -> esq = substituto;
        }
        
        else{
            pai_do_excluido -> dir = substituto;
        }
        free (excluido);
        return arvore;
    }

}

int profundidade(NO* arv) {
	if (!arv) return 0;
	int pesq = profundidade(arv->esq);
	int pdir = profundidade(arv->dir);
	
	if (pesq > pdir) return 1 + pesq;
	else	return 1+ pdir; 
}




int main(){
    NO * minha_arvore = inicializar();

    minha_arvore = inserir(minha_arvore, 50);
    minha_arvore = inserir(minha_arvore, 25);
    minha_arvore = inserir(minha_arvore, 75);
    minha_arvore = inserir(minha_arvore, 25);

    printf("Tamanho: %d\n", tamanho(minha_arvore));

    exibir_PreOrdem(minha_arvore);
    printf("\n");
    exibir_EmOrdem(minha_arvore);
    printf("\n");

    minha_arvore = inserir(minha_arvore, 12);
    minha_arvore = inserir(minha_arvore, 36);
    minha_arvore = inserir(minha_arvore, 63);
    minha_arvore = inserir(minha_arvore, 87);

    printf("Tamanho: %d\n", tamanho(minha_arvore));

    exibir_PreOrdem(minha_arvore);
    printf("\n");
    exibir_EmOrdem(minha_arvore);
    printf("\n");

    NO *no_buscado = busca(minha_arvore, minha_arvore -> chave);
    if (no_buscado != NULL){
        printf("Achou: %d\n", no_buscado -> chave);
    }
    else{
        printf("Nao achou!");
    }

    no_buscado = busca(minha_arvore, minha_arvore -> esq -> chave);
    if (no_buscado != NULL){
        printf("Achou: %d\n", no_buscado -> chave);
    }
    else{
        printf("Nao achou!");
    }

    no_buscado = busca(minha_arvore, minha_arvore -> dir -> chave);
    if (no_buscado != NULL){
        printf("Achou: %d\n", no_buscado -> chave);
    }
    else{
        printf("Nao achou!");
    }

    minha_arvore = inserir(minha_arvore, 40);
	minha_arvore = inserir(minha_arvore, 90);

	printf("tamanho %d\n", tamanho(minha_arvore));
	exibir_PreOrdem(minha_arvore);
	printf("\n");
	exibir_EmOrdem(minha_arvore);
	printf("\n");

    printf("teste excluir -1\n");
	minha_arvore = excluir(minha_arvore, -1);
	exibir_PreOrdem(minha_arvore);
	printf("\n");
	printf("teste excluir 12\n");
	minha_arvore = excluir(minha_arvore, 12);
	exibir_PreOrdem(minha_arvore);
	printf("\n");
	printf("teste excluir 36\n");
	minha_arvore = excluir(minha_arvore, 36);
	exibir_PreOrdem(minha_arvore);
	printf("\n");
	printf("teste excluir 50\n");
	minha_arvore = excluir(minha_arvore, 50);
	exibir_PreOrdem(minha_arvore);
	printf("\n");

    return 0;
}
