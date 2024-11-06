#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void rotacao_para_dir(NO **p){
    NO *u = (*p) -> esq;

    (*p) -> esq = u -> dir;
    u -> dir = (*p);
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

void tratar_desbalanceamento_dir(NO **arv){
    NO *p = *arv;
    NO *u = p -> dir;

    if (u -> bal == 1){
        // caso RR
        p -> bal = 0;
        u -> bal = 0;
    
        rotacao_para_esq(arv);
    }
    else if (u -> bal == -1){
        // caso RL
        NO *v = u -> esq;

        if (v -> bal == 0){

            u -> bal = 0;
            p -> bal = 0;
        }
        else if (v -> bal == -1){

            u -> bal = 1;
            p -> bal = 0;
        }
        else {
            u -> bal = 0;
            p -> bal = -1;
        }

        rotacao_para_dir(&(p -> dir));
        rotacao_para_esq(arv);
    }
}

void tratar_desbalanceamento_esq(NO **arv){
    NO *p = *arv;
    NO *u = p -> esq;

    if (u -> bal == -1){
        // caso LL
        p -> bal = 0;
        u -> bal = 0;
    
        rotacao_para_dir(arv);
    }
    else if (u->bal == 1) {
		// caso LR
		NO *v = u->dir;

		if (v->bal == 0) {

			p->bal = 0;
			u->bal = 0;
		} 
        else if (v->bal == 1) {

			p->bal = 0;
			u->bal = -1;
			v->bal = 0;
		} 
        else {

			p->bal = 1;
			u->bal = 0;
			v->bal = 0;
		}
		
		rotacao_para_esq(&(p -> esq));
		rotacao_para_dir(arv); 
	} 
    else {
		printf("Caso nao tratado %s\n", __func__);
	}
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
                    tratar_desbalanceamento_dir(arv);
                    break;

                default:
                    printf("caso nao esperado\n");
                    break;

            }
        }
    }
    else{
        int aumentou_altura = inserir_avl(&aux -> esq, novo_valor);

        if (aumentou_altura == 1){
            switch (aux -> bal){

                    case 1:
                        aux -> bal = 0;
                        return -1;

                    case 0:
                        aux -> bal = -1;
                        return 1;

                    case -1:
                        printf("houve desbalanceamento na esquerda\n");
                        tratar_desbalanceamento_esq(arv);
                        break;

                    default:
                        printf("caso nao esperado\n");
                        break;
            }
        }
    }
    return -1;
}


int profundidade(NO* arv) {
	if (!arv) return 0;
	int pesq = profundidade(arv -> esq);
	int pdir = profundidade(arv -> dir);
	
	if (pesq > pdir) return 1 + pesq;
	else	return 1+ pdir; 
}

void exibe_nivel(NO *arv, int nivel, int spaces, bool first) {
    #define NUMDIGI 2
    if (nivel < 0) {
        return;
    } else if (nivel == 1) {
            
        if (arv) {
            printf("%*d", NUMDIGI * ((first) ? spaces : spaces*2), arv->val);
        } else {
            printf("%*c", NUMDIGI * ((first) ? spaces : spaces*2), ' ');
        }
    } else {
        if (arv) {
            exibe_nivel(arv->esq, nivel-1, spaces, first & true);
            exibe_nivel(arv->dir, nivel-1, spaces, false);
        } else {
            exibe_nivel(NULL, nivel-1, spaces, first & true);
            exibe_nivel(NULL, nivel-1, spaces, false);
        }
    }
}

void exibe_nivel_bal(NO *arv, int nivel, int spaces, bool first) {
    if (nivel < 0) {
        return;
    } else if (nivel == 1) {
            
        if (arv) {
            printf("%*d", NUMDIGI * ((first) ? spaces : spaces*2), arv->bal);
        } else {
            printf("%*c", NUMDIGI * ((first) ? spaces : spaces*2), ' ');
        }
    } else {
        if (arv) {
            exibe_nivel_bal(arv->esq, nivel-1, spaces, first & true);
            exibe_nivel_bal(arv->dir, nivel-1, spaces, false);
        } else {
            exibe_nivel_bal(NULL, nivel-1, spaces, first & true);
            exibe_nivel_bal(NULL, nivel-1, spaces, false);
        }
    }
}

void exibir_em_nivel(NO* arv) {
    if (!arv) return;

    int prof = profundidade(arv);

    for (int i = 1; i <= prof; i++) {

        int spaces = 1 << (prof-i);
        exibe_nivel(arv, i, spaces, true);
        printf("%*c", spaces*2, '|');
        exibe_nivel_bal(arv, i, spaces, true);
        printf("\n");
    }
}

void testar_RR(){
    NO *arv = NULL;

    for (int i = 0; i < 15; i++){
        inserir_avl(&arv, i);
        exibir_em_nivel(arv); printf("\n");
    }
}

void testar_LL(){
    NO *arv = NULL;

    for (int i = 0; i < 15; i++){
        inserir_avl(&arv, 50 - i);
        exibir_em_nivel(arv); printf("\n");
    }
}

void testar_LR() {
	NO *arv = NULL;
	printf("%s\n", __func__);
	
	inserir_avl(&arv, 30);
	exibir_em_nivel(arv); printf("\n");

	inserir_avl(&arv, 10);
	exibir_em_nivel(arv); printf("\n");

	inserir_avl(&arv, 20);
	exibir_em_nivel(arv); printf("\n");
}

void testar_RL() {
	NO *arv = NULL;
	printf("%s\n", __func__);
	
	inserir_avl(&arv, 50);
	exibir_em_nivel(arv); printf("\n");

	inserir_avl(&arv, 30);
	exibir_em_nivel(arv); printf("\n");

	inserir_avl(&arv, 80);
	exibir_em_nivel(arv); printf("\n");

    inserir_avl(&arv, 60);
	exibir_em_nivel(arv); printf("\n");

    inserir_avl(&arv, 20);
	exibir_em_nivel(arv); printf("\n");

	inserir_avl(&arv, 40);
	exibir_em_nivel(arv); printf("\n");

	inserir_avl(&arv, 10);
	exibir_em_nivel(arv); printf("\n");

    inserir_avl(&arv, 35);
	exibir_em_nivel(arv); printf("\n");

    inserir_avl(&arv, 45);
	exibir_em_nivel(arv); printf("\n");

    inserir_avl(&arv, 46);
	exibir_em_nivel(arv); printf("\n");
}



int main(){

    testar_RL();
/*
    NO *arv = NULL;

	inserir_avl(&arv, 50);
	exibir_em_nivel(arv); printf("\n");

	inserir_avl(&arv, 60);
	exibir_em_nivel(arv); printf("\n");

	inserir_avl(&arv, 80);
	exibir_em_nivel(arv); printf("\n");

	rotacao_para_esq(&arv);
	exibir_em_nivel(arv); printf("\n");
*/
    return 0;
}