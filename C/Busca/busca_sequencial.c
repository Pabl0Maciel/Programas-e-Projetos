#include <stdio.h>

int buscaSequencial (int *v, int N, int num){
    for (int i = 0; i < N; i++){
        if (v[i] == num){
            return i;
        }
    }
    return -1;
}

int main(){
    
    int vet[] = {1,2,3,4,5,6,7,8,9};
    
    int index = buscaSequencial(vet, 9, 5);

    if (index != -1){
        printf("o numero foi encontrado no indice %d\n!", index);
    } 
    else{
        printf("o numero nao foi encontrado!\n");
    }

    return 0;
}