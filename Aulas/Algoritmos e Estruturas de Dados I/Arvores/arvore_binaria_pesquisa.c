#include <stdio.h>
#include <stdlib.h>

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

    return 0;
}
