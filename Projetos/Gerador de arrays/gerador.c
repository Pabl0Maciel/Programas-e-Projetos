#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int* criar_array(int tam){
    int* array = (int*)malloc(tam*sizeof(int));
    if (array==NULL){
        printf("erro ao alocar");
        exit(EXIT_FAILURE);
    }
    else{
        printf("alocado com sucesso!\n");
    }

    unsigned int seed = (unsigned int)time(NULL);
    printf("semente usada: %u\n", seed);
    srand(seed);

    for(int i = 0; i < tam; i++){
        array[i] = rand();
    }

    return array;
}

void insertionSort(int *V, int N){
    int i, j, aux;
    for(i = 1; i < N; i++){
        aux = V[i];
        for(j = i; (j > 0) && (aux < V[j - 1]); j--)
            V[j] = V[j - 1];
        V[j] = aux;
    }
}

int comparaCrescente(const void *a, const void *b){
    if (*(int*)a==*(int*)b){
        return 0;//iguais
    }
    else{
        if (*(int*)a<*(int*)b){
            return -1;//vem antes
        }
        else{
            return 1;//vem depois
        }
    }
}

int main() {
    
    int tam;
    int* vetor;    
    char resposta[10];
    struct timespec start, end;
    long long elapsed_nanoseconds;
    //long hours, minutes, seconds, nanoseconds;
    
    do{
        
        printf("Insira o tamanho do array de inteiros: ");
        scanf("%d", &tam);

        vetor = criar_array(tam);

        printf("Ultimo elemento nao ordenado: %d\n", vetor[tam-1]);
        
        clock_gettime(CLOCK_MONOTONIC, &start);
        insertionSort(vetor, tam);
        //qsort(vetor, tam, sizeof(int),comparaCrescente);
        clock_gettime(CLOCK_MONOTONIC, &end);
        
        //printf("Array gerado e organizado:\n");
        //for (int i=0; i < tam; i++){
        //    printf("%d ", vetor[i]);
        //}
        //puts("");
        free(vetor);

        elapsed_nanoseconds = (end.tv_sec - start.tv_sec) *1000000000LL + (end.tv_nsec - start.tv_nsec);
        //hours = elapsed_nanoseconds / (3600 * 1000000000LL);
        //=elapsed_nanoseconds %= (3600 * 1000000000LL);
        //minutes = elapsed_nanoseconds / (60 * 1000000000LL);
        //elapsed_nanoseconds %= (60 * 1000000000LL);
        //seconds = elapsed_nanoseconds / 1000000000LL;
        //nanoseconds = elapsed_nanoseconds % 1000000000LL;
        //printf("Tempo de execucao: %ld minutos, %ld segundos e %ld nanosegundos\n", minutes, seconds, nanoseconds);
        printf("Tempo de execucao: %lld nanosegundos\n", elapsed_nanoseconds);

        printf("Deseja gerar outro array? Responda 'sim' ou 'nao': ");
        scanf(" %s", resposta);

        while (strcmp(resposta, "sim") != 0 && strcmp(resposta, "nao") != 0) {
            printf("\nResposta invalida! Digite novamente: ");
            scanf("%s", resposta);
        }
        
    }while (strcmp(resposta, "sim") == 0);

    return 0;
}


