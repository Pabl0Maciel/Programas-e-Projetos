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
        printf("alocado com sucesso!");
    }

    srand(time(NULL));

    for(int i = 0; i < tam; i++){
        array[i] = rand();
    }

    return array;
}

int main() {
    
    int tam;
    int* vetor;    
    char *resposta[10];
    
    do{
        
        printf("Insira o tamanho do array: ");
        scanf("%d", &tam);

        vetor = criar_array(tam);

        printf("Array gerado:\n");
        for (int i=0; i < tam; i++){
            printf("%d ", vetor[i]);
        }
        puts("");
        free(vetor);

        printf("Deseja gerar outro array? Responda 'sim' ou 'nao': ");
        scanf(" %[^\n]s", resposta);

        if (strcmp(resposta,"nao") == 0){
            break;
        }
        
        else if (strcmp(resposta, "sim") != 0){
            while (strcmp(resposta, "sim") != 0){
                printf("Resposta invalida! Digite novamente: ");
                scanf (" %[^\n]s", resposta);
                if (strcmp(resposta,"nao") == 0){
                    break;
                }
            }
        }
        
    }while (strcmp(resposta, "sim") == 0);

    return 0;
}


