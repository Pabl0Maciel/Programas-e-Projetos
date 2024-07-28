#include <stdio.h>
#include <stdlib.h>

void selectionSort(int *V, int N){
    int i, j, menor, troca;
    for(i = 0; i < N-1; i++){
        menor = i;
        for(j = i+1; j < N; j++){
            if(V[j] < V[menor])
                menor = j;
        }
        if(i != menor){
            troca = V[i];
            V[i] = V[menor];
            V[menor] = troca;
        }
    }
}

int main(){
    int i;
    int vet[10] = {23,4,67,-8,54,90,21,14,-5,1};
    int N = 10;

    printf("Sem ordenar:\n");
    for(i=0; i<N; i++){
        printf("%d\n",vet[i]);
    }

    selectionSort(vet,N);
    printf("Depois de ordenar:\n");
    for(i=0; i<N; i++){
        printf("%d\n",vet[i]);
    }
}