#include <stdio.h>
#include <stdlib.h>

int compara_decrescente(const void *a, const void *b){
    if (*(int*)a==*(int*)b){
        return 0;//iguais
    }
    else{
        if (*(int*)a > *(int*)b){
            return -1;//vem antes
        }
        else{
            return 1;//vem depois
        }
    }
}

int main(){
    int i, vet[10]={23,4,67,-8,54,90,21,14,-5,1};
    qsort(vet,10,sizeof(int),compara_decrescente);
    for(i=0;i<10;i++){
        printf("Number=%d\n",vet[i]);
    }

    
    return 0;
}