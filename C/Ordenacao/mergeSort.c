#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void merge(int *V, int inicio, int meio, int fim){
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim-inicio+1;
    p1 = inicio;
    p2 = meio+1;
    temp = (int *) malloc(tamanho*sizeof(int));
    if(temp != NULL){
        for(i=0; i<tamanho; i++){
            if(!fim1 && !fim2){
                if(V[p1] < V[p2])
                    temp[i]=V[p1++];
                else
                    temp[i]=V[p2++];

                if(p1>meio) fim1=1;
                if(p2>fim) fim2=1;
            }else{
                if(!fim1)
                    temp[i]=V[p1++];
                else
                    temp[i]=V[p2++];
            }
        }
        for(j=0, k=inicio; j<tamanho; j++, k++)
            V[k]=temp[j];
    }
    free(temp);
}

void mergeSort(int *V, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = floor((inicio+fim)/2);
        mergeSort(V,inicio,meio);
        mergeSort(V,meio+1,fim);
        merge(V,inicio,meio,fim);
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

    mergeSort(vet,0,N-1);
    printf("Depois de ordenar:\n");
    for(i=0; i<N; i++){
        printf("%d\n",vet[i]);
    }
}