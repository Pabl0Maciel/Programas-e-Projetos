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

    srand(time(NULL));

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

int main() {
    
    int tam;
    int* vetor;    
    char resposta[10];
    clock_t start, end;
    double cpu_time_used;
    
    do{
        
        printf("Insira o tamanho do array de inteiros: ");
        scanf("%d", &tam);

        vetor = criar_array(tam);
        
        start = clock();
        insertionSort(vetor, tam);
        end = clock();
        
        printf("Array gerado e organizado:\n");
        for (int i=0; i < tam; i++){
            printf("%d ", vetor[i]);
        }
        puts("");
        free(vetor);

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        int cpu_time_used_minutes = (int)cpu_time_used / 60;
        double cpu_time_used_seconds = cpu_time_used - (cpu_time_used_minutes * 60);
        printf("Tempo de execucao: %d minutos e %.2f segundos\n", cpu_time_used_minutes, cpu_time_used_seconds);


        printf("Deseja gerar outro array? Responda 'sim' ou 'nao': ");
        scanf(" %s", resposta);

        while (strcmp(resposta, "sim") != 0 && strcmp(resposta, "nao") != 0) {
            printf("Resposta invalida! Digite novamente: ");
            scanf("%s", resposta);
        }
        
    }while (strcmp(resposta, "sim") == 0);

    return 0;
}


