#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define NP 4

typedef struct{
    int chave;
}REGISTRO;

typedef struct{
    REGISTRO regs[MAX];
    int base[NP+1];
    int topo[NP+1];
}PILHA_MULTIPLA;

void inicializa_PilhaMultipla(PILHA_MULTIPLA *pilha){
    
    for (int i = 0; i < NP; i++){
        pilha -> base[i] = i * (MAX / NP);
        pilha -> topo[i] = pilha -> base[i] - 1;
    }
    pilha -> base[NP] = MAX;
}


int tamanho_pilha(PILHA_MULTIPLA *pilha, int k){
    if (k < 0 || k >= NP) return -1;

    return (pilha -> topo[k] - pilha -> base[k] + 1);
}

int pilha_cheia(PILHA_MULTIPLA *pilha, int k){
    if (k < 0 || k >= NP) return 0; // pilha invalida

    if (pilha -> topo[k] + 1 == pilha -> base[k+1]) return 0; // pilha cheia

    else return -1; // pilha nao cheia
}

int pilha_vazia(PILHA_MULTIPLA *pilha, int k){
    if (k < 0 || k >= NP) return -1; // pilha invalida

    if (pilha -> topo[k] + 1 == pilha -> base[k]) return 0; // pilha vazia

    else return -1; // pilha nao vazia
}

int deslocar_direita(PILHA_MULTIPLA *pilha, int k){
    if (k < 0 || k >= NP) return -1;

    if (pilha_cheia(pilha, k) == 0) return -1;

    for (int i = pilha -> topo[k]; i >= pilha -> base[k]; i--){
        pilha -> regs[i+1] = pilha -> regs[i];
    }

    pilha -> base[k]++;
    pilha -> topo[k]++;

    return 0;
}

int deslocar_esquerda(PILHA_MULTIPLA *pilha, int k){
    if (k < 1 || k >= NP) return -1;

    if (pilha_cheia(pilha, k-1) == 0) return -1;

    for (int i = pilha -> base[k]; i <= pilha -> topo[k]; i++){
        pilha -> regs[i-1] = pilha -> regs[i];
    }

    pilha -> base[k]--;
    pilha -> topo[k]--;

    return 0;
}

void exibir_PilhaMultipla(PILHA_MULTIPLA *pilha){
    for (int i = 0; i < NP; i++){
        printf("Pilha k = %d, tamanho = %d : (base) ", i, tamanho_pilha(pilha, i));

        for (int j = pilha -> base[i]; j <= pilha -> topo[i]; j++){
            printf("%d ", pilha -> regs[j].chave);
        }
        printf("(topo)\n");
        printf("------------------------------------------------\n");
    }
}

int pop(PILHA_MULTIPLA *pilha, int k, REGISTRO *reg){
    if (k < 0 || k >= NP) return -1;

    if (pilha_vazia(pilha, k) == 0) return -1;

    int topo = pilha -> topo[k];
    *reg = pilha -> regs[topo];
    pilha -> topo[k]--;

    return 0;
}

int push(PILHA_MULTIPLA *pilha, int k, REGISTRO reg){
    if (k < 0 || k >= NP) return -1;

    if (pilha_cheia(pilha, k) == 0){
        for (int i = k+1; i < NP; i++){
            deslocar_direita(pilha, i);
        }

        if (pilha_cheia(pilha, k) == 0){
            for (int i = 1; i <= k; i++){
                deslocar_esquerda(pilha, i);
            }

            if (pilha_cheia(pilha, k) == 0) return -1;
        }
    }
    
    pilha -> topo[k]++;
    int pos = pilha -> topo[k];
    pilha -> regs[pos] = reg;
    
    return 0;
}


int main(){

    PILHA_MULTIPLA pilha;
    inicializa_PilhaMultipla(&pilha);

    for (int i = 0; i < 7; i++){
        REGISTRO reg;
        reg.chave = random() % 100;
        printf("Inserindo chave %d...\n", reg.chave);
        push(&pilha, 2, reg);
        exibir_PilhaMultipla(&pilha);
    }

    for (int i = 0; i < 5; i++){
        REGISTRO reg2;
        printf("Removendo chave %d...\n", reg2.chave);
        pop(&pilha, 2, &reg2);
        exibir_PilhaMultipla(&pilha);
    }
}
