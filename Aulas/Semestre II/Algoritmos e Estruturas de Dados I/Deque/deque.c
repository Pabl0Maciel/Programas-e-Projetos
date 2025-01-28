#include <stdio.h>
#include <stdlib.h> 


typedef struct{
    int chave;
}REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux *ant;
    struct aux *prox;
}ELEMENTO;

typedef struct{
    ELEMENTO *cabeca;
}DEQUE;

void inicializar_deque(DEQUE *deque){
    deque -> cabeca = malloc(sizeof(ELEMENTO));

    deque -> cabeca -> prox = deque -> cabeca;
    deque -> cabeca -> ant = deque -> cabeca;
}

int tamanho_deque(DEQUE *deque){
    int tam = 0;
    ELEMENTO *atual = deque -> cabeca -> prox;

    while (atual != deque -> cabeca){
        tam++;
        atual = atual -> prox;
    }

    return 0;
}

void exibir_deque(DEQUE *deque){
    ELEMENTO *atual = deque -> cabeca -> prox;

    printf("Fila (%d): ", tamanho_deque(deque));

    while (atual != deque -> cabeca){
        printf("%d ", atual -> reg.chave);
        atual = atual -> prox;
    }
    
    printf("\n");
    printf("--------------------------------------\n");
}

int inserir_deque_inicio(DEQUE *deque, REGISTRO reg){
    
    ELEMENTO *novo = malloc(sizeof(ELEMENTO));
    if (novo == NULL) return -1;

    novo -> reg = reg;
   
    novo -> ant = deque -> cabeca;
    novo -> prox = deque -> cabeca -> prox;

    deque -> cabeca -> prox -> ant = novo;
    deque -> cabeca -> prox = novo;

    return 0;
}

int inserir_deque_fim(DEQUE *deque, REGISTRO reg){
    
    ELEMENTO *novo = malloc(sizeof(ELEMENTO));
    if (novo == NULL) return -1;

    novo -> reg = reg;
   
    novo -> ant = deque -> cabeca -> ant;
    deque -> cabeca -> ant -> prox = novo;

    deque -> cabeca -> ant = novo;
    novo -> prox = deque -> cabeca;

    return 0;
}

int excluir_deque_inicio(DEQUE *deque, REGISTRO *reg){

    if (deque -> cabeca -> prox == deque -> cabeca) return -1;

    ELEMENTO *apagar = deque -> cabeca -> prox;

    *reg = apagar -> reg;

    deque -> cabeca -> prox = apagar -> prox;
    apagar-> prox -> ant = deque -> cabeca;

    free(apagar);

    return 0;
}

int excluir_deque_fim(DEQUE *deque, REGISTRO *reg){

    if (deque -> cabeca -> prox == deque -> cabeca) return -1;

    ELEMENTO *apagar = deque -> cabeca -> ant;

    *reg = apagar -> reg;

    deque -> cabeca -> ant = apagar -> ant;
    apagar-> ant -> prox = deque -> cabeca;

    free(apagar);

    return 0;
}

void reinicializar_deque(DEQUE *deque){
    ELEMENTO *atual = deque -> cabeca -> prox;

    while(atual != deque -> cabeca){
        ELEMENTO *apagar = atual;
        atual = atual -> prox;
        free(apagar);
    }
    deque -> cabeca -> prox = deque -> cabeca;
    deque -> cabeca -> ant = deque -> cabeca;
}

int main(){
    DEQUE deque;
    inicializar_deque(&deque);

    for (int i = 0; i < 7; i++){
        REGISTRO reg;
        reg.chave = (random() % 100);
        printf("Enfileirando reg com chave %d\n", reg.chave);
        //inserir_deque_inicio(&deque, reg);
        inserir_deque_fim(&deque, reg);
        exibir_deque(&deque);
    }

    printf("/////////////////////////////////////////////////////////\n");

    for (int i = 0; i < 8; i++){
        REGISTRO reg;
        //int deucerto = excluir_deque_inicio(&deque, &reg);
        int deucerto = excluir_deque_fim(&deque, &reg);

        if (deucerto == 0){
            printf("Elemento desenfileirado: %d\n", reg.chave);
            exibir_deque(&deque);
        }

        else printf("Fila vazia\n");
    }

    return 0;
}
