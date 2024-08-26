#include <stdio.h>

typedef struct{
    int min;
    int max;
}Min_Max;


Min_Max min_max(int *arr, int esq, int dir){
    Min_Max resultado, esq_result, dir_result;

    // base: se tem apenas um elemento
    if (esq == dir){
        resultado.min = arr[esq];
        resultado.max = arr[esq];
        return resultado;
    }

    // base: se tem dois elementos
    if (dir == esq+1){
        if (arr[esq] < arr[dir]){
            resultado.min = arr[esq];
            resultado.max = arr[dir];
        }
        else{
            resultado.min = arr[dir];
            resultado.max = arr[esq];
        }
        return resultado;
    }
    


    // divisao do array
    int meio = (esq + dir) / 2;
    esq_result = min_max(arr, esq, meio);
    dir_result = min_max(arr, meio+1, dir);

    // comparacao entre as duas metades
    if (esq_result.min < dir_result.min){
        resultado.min = esq_result.min;
    }
    else resultado.min = dir_result.min;

    if (esq_result.max > dir_result.max){
        resultado.max = esq_result.max;
    }
    else resultado.max = dir_result.max;

    return resultado;
}

int main(){
    int v[] = {15, 42, 78, 3, 91, 56, 27, 64, 10, 34};
    int tam = 10;

    Min_Max resultado = min_max(v, 0, tam-1);
    printf("Minimo: %d\n", resultado.min);
    printf("Maximo: %d\n", resultado.max);

    return 0;
}