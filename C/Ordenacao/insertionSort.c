#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void insertionSort(int *V, int N){
    int i, j, aux;
    for(i = 1; i < N; i++){
        aux = V[i];
        for(j = i; (j > 0) && (aux < V[j - 1]); j--)
            V[j] = V[j - 1];
        V[j] = aux;
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

    insertionSort(vet,N);
    printf("Depois de ordenar:\n");
    for(i=0; i<N; i++){
        printf("%d\n",vet[i]);
    }
}