void bubbleSort2(int *V  , int N){//otimizado
    int i, continua, aux, fim = N;
    do{
        continua = 0;
        for(i = 0; i < fim-1; i++){
            if (V[i] > V[i+1]){
                aux = V[i];
                V[i] = V[i+1];
                V[i+1] = aux;
                continua = i;
            }
        }
        fim--;
    }while(continua != 0);
}

int main(){
    int i;
    int vet[10] = {23,4,67,-8,54,90,21,14,-5,1};
    int N = 10;

    printf("Sem ordenar:\n");
    for(i=0; i<N; i++){
        printf("%d\n",vet[i]);
    }

    bubbleSort2(vet,N);
    printf("Depois de ordenar:\n");
    for(i=0; i<N; i++){
        printf("%d\n",vet[i]);
    }
}