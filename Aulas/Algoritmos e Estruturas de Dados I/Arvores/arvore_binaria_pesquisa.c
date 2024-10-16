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
