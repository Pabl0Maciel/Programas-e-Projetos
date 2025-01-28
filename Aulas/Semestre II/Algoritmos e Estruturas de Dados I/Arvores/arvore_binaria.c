#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int chave;
}REGISTRO;

typedef struct NO{
    REGISTRO reg;
    struct NO *dir, *esq;
}NO;

typedef NO ARVORE;

void minha_funcao(REGISTRO *reg){
    printf("%c ", reg -> chave);
}


void pre_ordem(ARVORE *arvore, void(*func)(REGISTRO*)){
    if (arvore == NULL) return;

    func(&arvore -> reg);
    pre_ordem(arvore -> esq, func);
    pre_ordem(arvore -> dir, func);
}

void em_ordem(ARVORE *arvore, void(*func)(REGISTRO*)){
    if (arvore == NULL) return;

    em_ordem(arvore -> esq, func);
    func(&arvore -> reg);
    em_ordem(arvore -> dir, func);
}

void pos_ordem(ARVORE *arvore, void(*func)(REGISTRO*)){
    if (arvore == NULL) return;

    pos_ordem(arvore -> esq, func);
    pos_ordem(arvore -> dir, func);
    func(&arvore -> reg);
}



int main(){
    ARVORE arvore;
    NO *no;

    arvore.reg.chave = 'A';

    no = malloc(sizeof(NO));

    no -> reg.chave = 'B';
    no -> esq = NULL;
    no -> dir = NULL;

    arvore.esq = no;


    no = malloc(sizeof(NO));

    no -> reg.chave = 'C';
    no -> esq = NULL;
    no -> dir = NULL;

    arvore.dir = no;

    pre_ordem(&arvore, &minha_funcao);
    printf("\n");
    em_ordem(&arvore, &minha_funcao);
    printf("\n");
    pos_ordem(&arvore, &minha_funcao);
    printf("\n");

}