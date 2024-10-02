#include <stdio.h>
#include <stdlib.h>

typedef struct NO_{
    int chave;
    struct NO *dir, *esq;
}NO;

typedef NO *ARVORE;

NO *criar_no(int chave){
    NO *novo = malloc(sizeof(NO));

    novo -> chave = chave;
    novo -> esq = NULL;
    novo -> dir = NULL;

    return novo;
}

void inicializar_arvore(ARVORE *arvore, int chave){
    *arvore = criar_no(chave);
}

NO *busca(ARVORE raiz, int chave_buscada){
    if (raiz == NULL) return NULL;

    if (raiz -> chave == chave_buscada) return raiz;

    NO *esq = busca(raiz -> esq, chave_buscada);
    if (esq != NULL) return esq;

    return busca(raiz -> dir, chave_buscada);
}

#define DIREITA 0
#define ESQUERDA 1

int inserir(ARVORE raiz, int chave_nova, int chave_pai, int lado){
    NO *pai = busca(raiz, chave_pai);
    if (pai == NULL) return -1;

    NO *novo = criar_no(chave_nova);

    if (lado == ESQUERDA){
        novo -> esq = pai -> esq;
        pai -> esq = novo;
    }

    else if (lado == DIREITA){
        novo -> dir = pai -> dir;
        pai -> dir = novo;
    }

    else{
        free(novo);
        printf("Lado %d invalido!\n", lado);
        return -1;
    }

    return 0;
}

void exibir_PreOrdem(ARVORE raiz){
    if (raiz == NULL) return;

    printf("%d", raiz -> chave);
    printf("(");
    exibir_PreOrdem(raiz -> esq);
    printf("|");
    exibir_PreOrdem(raiz -> dir);
    printf(")");
}

void free_SubArvore(ARVORE raiz){
    if (raiz == NULL) return;

    free_SubArvore(raiz -> esq);
    free_SubArvore(raiz -> dir);
    free_SubArvore(raiz);
}

int excluir(ARVORE *raiz, int chave_excluir){
    if ((*raiz) == NULL) return -1;

    if (*(raiz) -> chave == chave_excluir){
        free_SubArvore(*raiz);
        *raiz = NULL;
        return 0;
    }

    int deu_certo = excluir((*raiz) -> esq, chave_excluir);
    if (deu_certo == 0) return deu_certo;

    return excluir((*raiz) -> dir, chave_excluir);
}

int main(){
    ARVORE raiz;

    inicializar_arvore (&raiz, 1);
    exibir_PreOrdem(raiz);
    printf("\n");

    int deu_certo = inserir(raiz, 2, 1, ESQUERDA);
    if (deu_certo == -1){
        printf ("Erro ao inserir!\n");
    }
    exibir_PreOrdem(raiz);
    printf("\n");

    deu_certo = inserir(raiz, 3, 1, DIREITA);
    if (deu_certo == -1){
        printf ("Erro ao inserir!\n");
    }

    deu_certo = inserir(raiz, 20, 2, ESQUERDA);
    if (deu_certo == -1){
        printf ("Erro ao inserir!\n");
    }

    deu_certo = inserir(raiz, 40, 2, DIREITA);
    if (deu_certo == -1){
        printf ("Erro ao inserir!\n");
    }

    deu_certo = inserir(raiz, 30, 3, ESQUERDA);
    if (deu_certo == -1){
        printf ("Erro ao inserir!\n");
    }

    deu_certo = inserir(raiz, 60, 3, DIREITA);
    if (deu_certo == -1){
        printf ("Erro ao inserir!\n");
    }

    deu_certo = inserir(raiz, 100, 1, DIREITA);
    if (deu_certo == -1){
        printf ("Erro ao inserir!\n");
    }

    exibir_PreOrdem(raiz);
    printf("\n");

    deu_certo = inserir(raiz, 100, 99, DIREITA);
    if (deu_certo == -1){
        printf ("Erro ao inserir!\n");
    }

    deu_certo = excluir(&raiz, 3);
    if (deu_certo == -1){
        printf ("Erro ao excluir!\n");
    }
    
    exibir_PreOrdem(raiz);
    printf("\n");

    return 0;
}