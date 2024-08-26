#include <stdio.h>

void merge(int *arr, int esq, int meio, int dir){
    int n1 = (meio - esq) + 1;
    int n2 = (dir - meio);

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++){
        L[i] = arr[esq + i];
    }
    for (int i = 0; i < n2; i++){
        R[i] = arr[(meio + 1) + i];
    }

    int i = 0, j = 0, k = esq;

    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int *arr, int esq, int dir){
    if (esq < dir){
        int meio = (esq + dir) / 2;

        MergeSort(arr, esq, meio);
        MergeSort(arr, meio+1, dir);
        merge(arr, esq, meio, dir);
    }
}

int main(){
    int v[] = {15, 42, 78, 3, 91, 56, 27, 64, 10, 34};
    int tam = 10;

    MergeSort(v, 0, tam-1);
    printf("Array Ordenado: ");
    for (int i = 0; i < 10; i++){
        printf("%d, ", v[i]);
    }
}

