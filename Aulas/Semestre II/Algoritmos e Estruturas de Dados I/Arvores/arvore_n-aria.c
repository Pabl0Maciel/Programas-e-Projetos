#include <stdio.h>
#include <stdlib.h>

typedef struct NO_{
    int chave;
    struct NO_ *primeiro_filho;
    struct NO_ *prox_irmao;
}NO;

NO *criar_no(int chave){
    NO *novo = malloc(sizeof(NO));

    novo -> primeiro_filho = NULL;
    novo -> prox_irmao = NULL;
    novo -> chave = chave;

    return novo;
}

NO *inicializa(int chave){
    return(criar_no(chave));
}

NO *busca_chave(int chave_buscada, NO *raiz){
    if (raiz == NULL) return NULL;

    if (raiz -> chave == chave_buscada) return raiz;

    NO *atual = raiz -> primeiro_filho;

    while (atual != NULL){
        NO *resp = busca_chave(chave_buscada, atual);

        if (resp != NULL) return resp;

        atual = atual -> prox_irmao;
    }
    
    return (NULL);
}

NO *busca_pai(NO *raiz, int chave_filho){
    if (raiz == NULL) return NULL;

    NO *atual = raiz -> primeiro_filho;

    while(atual != NULL){
        if (atual -> chave == chave_filho){
            return raiz;
        }
        atual = atual -> prox_irmao;
    }

    NO *pai_encontrado = busca_pai(raiz -> primeiro_filho, chave_filho);
    if (pai_encontrado != NULL){
        return pai_encontrado;
    }
    
    return busca_pai(raiz -> prox_irmao, chave_filho);
}

int inserir(NO *raiz, int nova_chave, int chave_pai){
    NO *pai = busca_chave(chave_pai, raiz);
    if (pai == NULL) return -1;

    NO *filho = criar_no(nova_chave);

    NO *atual = pai -> primeiro_filho;

    if (atual == NULL){
        pai -> primeiro_filho = filho;
    }

    else{
        
        while (atual -> prox_irmao != NULL){
            atual = atual -> prox_irmao;
        }
        
        atual -> prox_irmao = filho;
    }
    
    return 0;
}

void exibir_arvore(NO *raiz){
    if (raiz == NULL) return;

    printf("%d(", raiz -> chave);

    NO *atual = raiz -> primeiro_filho;

    while (atual != NULL){
        exibir_arvore(atual);
        atual = atual -> prox_irmao;
    }
    printf(")");
}

int excluir (NO *raiz, int chave_exclusao){
    NO *pai = busca_pai(raiz, chave_exclusao);

    if (pai == NULL) return -1;

    NO *anterior = NULL;
    NO *atual = pai -> primeiro_filho;

    while(atual != NULL && atual -> chave != chave_exclusao){
        anterior = atual;
        atual = atual -> prox_irmao;
    }

    if (anterior == NULL){
        pai -> primeiro_filho = atual -> prox_irmao;
    }

    else{
        anterior -> prox_irmao = atual -> prox_irmao;
    }

    free (atual);
    
    return 0;
}

int main(){

    NO *arvore = inicializa(8);

    inserir(arvore, 15, 8);
    inserir(arvore, 23, 8);
    inserir(arvore, 2, 8);

    inserir(arvore, 20, 15);
    inserir(arvore, 10, 15);
    inserir(arvore, 28, 15);

    inserir(arvore, 36, 2);
    inserir(arvore, 7, 2);

    exibir_arvore(arvore);

    return 0;
}