#include <stdio.h>
#include <stdlib.h>

typedef struct NO_{

    struct NO_ *esq;
    struct NO_ *dir;
    int val;
    int bal;

}NO;

void rotacao_para_esq(NO **p){
    NO *u = (*p) -> dir;

    (*p) -> dir = u -> esq;
    u -> esq = (*p);
    *p = u;
}

NO *criar_no(int val){
    NO *novo = malloc(sizeof(NO));

    novo -> esq = NULL;
    novo -> dir = NULL;
    novo -> val = val;
    novo -> bal = 0;

    return novo;
}

// retorna se houve aumento de altura
int inserir_avl(NO **arv, int novo_valor){

    if ((*arv) == NULL){
        *arv = criar_no(novo_valor);
        return 1;
    }

    NO *aux = *arv;
    if (novo_valor == aux -> val ){

        return -1;
    } 
    else if (novo_valor > aux -> val){
        int aumentou_altura = inserir_avl(&aux -> dir, novo_valor);

        if (aumentou_altura == 1){

            switch (aux -> bal){

                case -1:
                    aux -> bal = 0;
                    return -1;

                case 0:
                    aux -> bal = 1;
                    return 1;

                case 1:
                    printf("houve desbalanceamento na direita\n");
                    break;

                default:
                    printf("caso nao esperado\n");
                    break;

            }
        }
    }
    else{
        int aumentou_altura = inserir_avl(&aux -> esq, novo_valor);

        switch (aux -> bal){

                case 1:
                    aux -> bal = 0;
                    return -1;

                case 0:
                    aux -> bal = -1;
                    return 1;

                case -1:
                    printf("houve desbalanceamento na esquerda\n");
                    break;

                default:
                    printf("caso nao esperado\n");
                    break;
        }
    }
    return -1;
}

int main(){

    NO *arv = NULL;
    int valor;
    inserir_avl(&arv, 50);

    return 0;
}