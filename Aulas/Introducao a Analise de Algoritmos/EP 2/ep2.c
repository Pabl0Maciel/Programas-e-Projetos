#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    int chave;
    int campoDaEstrutura[1];
} Registro1;

typedef struct {
    int chave;
    int campoDaEstrutura[1000];
} Registro1000;

//typedef Registro1 Registro;
typedef Registro1000 Registro;

void insertionSort(Registro *V, int N, int *num_comp, int *num_mov){
    int i, j, aux;

    for(j = 1; j < N; j++){
        aux = V[j].chave;
        i = j-1;

        while (i >= 0 && V[i].chave > aux){
            (*num_comp)++;
            V[i+1].chave = V[i].chave;
            (*num_mov)++;
            i--;
        }
        (*num_comp)++;
        V[i+1].chave = aux;
        (*num_mov)++;
    }
}

void SelectionSort(Registro *V, int N, int *num_comp, int *num_mov){
    int i, j, min, x;

    for (i = 0; i < N-1; i++){
        min = i;

        for (j = i+1; j < N; j++){
            
            (*num_comp)++;
            if (V[j].chave < V[min].chave){
                min = j;
            }
        }

        if (min != i){
            x = V[i].chave;
            V[i].chave = V[min].chave;
            V[min].chave = x;
            (*num_mov) += 3;
        }
        
    }
}

void BubbleSort(Registro *V, int N, int *num_comp, int *num_mov){
    int i, trocou, aux, fim = N;
    do{
        trocou = 0;
        for(i = 0; i < fim-1; i++){
            
            (*num_comp)++;
            if (V[i].chave > V[i+1].chave){
                aux = V[i].chave;
                V[i].chave = V[i+1].chave;
                V[i+1].chave = aux;
                trocou = i;
                (*num_mov) +=3;
            }
        }
        fim--;
    }while(trocou != 0);
}

void ShellSort(Registro *V, int N, int *num_comp, int *num_mov) {
    int i, j, h, chave;

    for (h = 1; h < N; h = 3*h+1);

    h = (h-1)/3;
    while (h > 0) {

        for(j = h; j < N; j++) {
            chave = V[j].chave;
            i = j;

            (*num_comp)++;
            while (i >= h && V[i - h].chave > chave) {
                V[i].chave = V[i - h].chave;
                i -= h;
                (*num_mov)++;
                (*num_comp)++;
            }

            V[i].chave = chave;
            (*num_mov)++;
        }
        h = (h-1)/3;
    }
}

void Merge(Registro *V, int esq, int meio, int dir, int *num_comp, int *num_mov){
    int n1 = (meio - esq) + 1;
    int n2 = dir - meio;

    Registro *L = (Registro *)malloc(n1 * sizeof(Registro));
    Registro *R = (Registro *)malloc(n2 * sizeof(Registro));

    for (int i = 0; i < n1; i++) {
        L[i].chave = V[esq + i].chave;
        (*num_mov)++; 
    }

    for (int j = 0; j < n2; j++) {
        R[j].chave = V[meio + 1 + j].chave;
        (*num_mov)++; 
    }

    int k1 = 0;
    int k2 = 0;

    for (int k = esq; k <= dir; k++){
        
        (*num_comp)++;
        if (k1 < n1 && (k2 >= n2 || L[k1].chave <= R[k2].chave)){
            V[k].chave = L[k1].chave;
            k1++;
            (*num_mov)++;
        }
        else{
            V[k].chave = R[k2].chave;
            k2++;
            (*num_mov)++;
        }
    }

    free(L);
    free(R);
}

void MergeSort(Registro *V, int inicio, int fim, int *num_comp, int *num_mov){
    int meio;
    
    if (inicio < fim){
        meio = (inicio + fim) / 2;
        MergeSort(V, inicio, meio, num_comp, num_mov);
        MergeSort(V, meio+1, fim, num_comp, num_mov);
        Merge(V, inicio, meio, fim, num_comp, num_mov);
    }
}

void ConstroiHeap(Registro *V, int N, int i, int *num_comp, int *num_mov){
    int maior = i;
    int filho_esq = (2 * i) + 1;
    int filho_dir = (2 * i) + 2;

    if (filho_esq < N){
        
        (*num_comp)++;
        if (V[filho_esq].chave > V[maior].chave){
            maior = filho_esq;
        }
    }

    if (filho_dir < N){
        
        (*num_comp)++;
        if (V[filho_dir].chave > V[maior].chave){
            maior = filho_dir;
        }
    }

    if (maior != i){
        Registro aux = V[i];
        V[i] = V[maior];
        V[maior] = aux;

        (*num_mov) += 3; 

        ConstroiHeap(V, N, maior, num_comp, num_mov);
    }
}

void HeapSort(Registro *V, int N, int *num_comp, int *num_mov){
    for (int i = (N / 2) - 1; i >= 0; i--){
        ConstroiHeap(V, N, i, num_comp, num_mov);
    }

    for (int i = N-1; i >= 0 ; i--){
        Registro aux = V[0];
        V[0] = V[i];
        V[i] = aux;

        (*num_mov) += 3;

        ConstroiHeap(V, i, 0, num_comp, num_mov);
    }
}


int main(int argc, char *argv[]){

    /*-----------------------------------------------------Leitura do arquivo e inicializacoes---------------------------------------------------------------*/

    char *algoritmos[] = {"InsertionSort", "SelectionSort", "BubbleSort", "ShellSort", "MergeSort", "HeapSort", "QuickSort"};

    // verifica se foi passada a quantidade de argumentos certa
    if (argc < 2){
        printf("Passe o Arquivo de Entrada!\n");
        exit(-1);
    }

    // cria a variavel do arquivo, tamanho do vetor e os vetores
    FILE *entrada, *saida;
    int N;
    Registro *V1, *V2, *V3, *V4, *V5, *V6, *V7;

    // abre o arquivo
    entrada = fopen(argv[1], "r");
    if (entrada == NULL){
        printf("Erro ao abrir!\n");
        exit(-1);
    }

    // le a primeira linha (tamanho) e atribui a N
    fscanf(entrada, "%d", &N);

    // cria memoria dinamicamente para os vetores
    V1 = (Registro *)malloc(N * sizeof(Registro));
    V2 = (Registro *)malloc(N * sizeof(Registro));
    V3 = (Registro *)malloc(N * sizeof(Registro));
    V4 = (Registro *)malloc(N * sizeof(Registro));
    V5 = (Registro *)malloc(N * sizeof(Registro));
    V6 = (Registro *)malloc(N * sizeof(Registro));
    V7 = (Registro *)malloc(N * sizeof(Registro));

    // atribui os valores do arquivo para os vetores
    for (int i = 0; i < N; i++){
        fscanf(entrada, "%d", &V1[i].chave);
    }

    for (int i = 0; i < N; i++) {
        V2[i] = V1[i];
    }

    for (int i = 0; i < N; i++) {
        V3[i] = V1[i];
    }

    for (int i = 0; i < N; i++) {
        V4[i] = V1[i];
    }

    for (int i = 0; i < N; i++) {
        V5[i] = V1[i];
    }

    for (int i = 0; i < N; i++) {
        V6[i] = V1[i];
    }

    for (int i = 0; i < N; i++) {
        V7[i] = V1[i];
    }

    // fecha o arquivo
    fclose(entrada);

    saida = fopen("10000_Decrescente.txt", "w");
    if (saida == NULL){
        printf("Erro ao abrir!\n");
        exit(-1);
    }

    // cria as variaveis para medir o tempo
    clock_t inicio, fim;
    double tempo_execucao;

    printf("Arquivo: %s\n\n", argv[1]);

/*----------------------------------------------------------------------Testes-------------------------------------------------------------------------------*/

    // InsertionSort
    printf("InsertionSort\n");

    int num_comp_InsertionSort = 0;
    int num_mov_InsertionSort = 0;

    inicio = clock();
    insertionSort(V1, N, &num_comp_InsertionSort, &num_mov_InsertionSort);
    fim = clock();

    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;


    printf("Numero de Comparacoes: %d\n", num_comp_InsertionSort);
    printf("Numero de Movimentacoes: %d\n", num_mov_InsertionSort);
    printf("Tempo de execucao: %f segundos\n", tempo_execucao);

    fprintf(saida, "%s;%f;%d;%d\n", algoritmos[0], tempo_execucao, num_comp_InsertionSort, num_mov_InsertionSort);

    /*
    printf("Lista ordenada:\n");
    for (int i = 0; i < N; i++){
        printf("%d ", V1[i].chave);
    }
    printf("\n");
    */

    printf("-----------------------------------------------------\n");

    // SelectionSort
    printf("SelectionSort\n");

    int num_comp_SelectionSort = 0;
    int num_mov_SelectionSort = 0;

    inicio = clock();
    SelectionSort(V2, N, &num_comp_SelectionSort, &num_mov_SelectionSort);
    fim = clock();

    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;


    printf("Numero de Comparacoes: %d\n", num_comp_SelectionSort);
    printf("Numero de Movimentacoes: %d\n", num_mov_SelectionSort);
    printf("Tempo de execucao: %f segundos\n", tempo_execucao);

    fprintf(saida, "%s;%f;%d;%d\n", algoritmos[1], tempo_execucao, num_comp_SelectionSort, num_mov_SelectionSort);

    /*
    printf("Lista ordenada:\n");
    for (int i = 0; i < N; i++){
        printf("%d ", V2[i].chave);
    }
    printf("\n");
    */

    printf("-----------------------------------------------------\n");

    // BubbleSort
    printf("BubbleSort\n");

    int num_comp_BubbleSort = 0;
    int num_mov_BubbleSort = 0;

    inicio = clock();
    BubbleSort(V3, N, &num_comp_BubbleSort, &num_mov_BubbleSort);
    fim = clock();

    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Numero de Comparacoes: %d\n", num_comp_BubbleSort);
    printf("Numero de Movimentacoes: %d\n", num_mov_BubbleSort);
    printf("Tempo de execucao: %f segundos\n", tempo_execucao);

    fprintf(saida, "%s;%f;%d;%d\n", algoritmos[2], tempo_execucao, num_comp_BubbleSort, num_mov_BubbleSort);

    /*
    printf("Lista ordenada:\n");
    for (int i = 0; i < N; i++){
        printf("%d ", V3[i].chave);
    }
    printf("\n");
    */

    printf("-----------------------------------------------------\n");

    // ShellSort
    printf("ShellSort\n");

    int num_comp_ShellSort = 0;
    int num_mov_ShellSort = 0;

    inicio = clock();
    ShellSort(V4, N, &num_comp_ShellSort, &num_mov_ShellSort);
    fim = clock();

    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Numero de Comparacoes: %d\n", num_comp_ShellSort);
    printf("Numero de Movimentacoes: %d\n", num_mov_ShellSort);
    printf("Tempo de execucao: %f segundos\n", tempo_execucao);

    fprintf(saida, "%s;%f;%d;%d\n", algoritmos[3], tempo_execucao, num_comp_ShellSort, num_mov_ShellSort);

    /*
    printf("Lista ordenada:\n");
    for (int i = 0; i < N; i++){
        printf("%d ", V4[i].chave);
    }
    printf("\n");
    */

    printf("-----------------------------------------------------\n");

    // MergeSort
    printf("MergeSort\n");

    int num_comp_MergeSort = 0;
    int num_mov_MergeSort = 0;

    inicio = clock();
    MergeSort(V5, 0, N-1, &num_comp_MergeSort, &num_mov_MergeSort);
    fim = clock();

    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Numero de Comparacoes: %d\n", num_comp_MergeSort);
    printf("Numero de Movimentacoes: %d\n", num_mov_MergeSort);
    printf("Tempo de execucao: %f segundos\n", tempo_execucao);

    fprintf(saida, "%s;%f;%d;%d\n", algoritmos[4], tempo_execucao, num_comp_MergeSort, num_mov_MergeSort);

    /*
    printf("Lista ordenada:\n");
    for (int i = 0; i < N; i++){
        printf("%d ", V5[i].chave);
    }
    printf("\n");
    */

    printf("-----------------------------------------------------\n");

    // HeapSort
    printf("HeapSort\n");

    int num_comp_HeapSort = 0;
    int num_mov_HeapSort = 0;

    inicio = clock();
    HeapSort(V6, N, &num_comp_HeapSort, &num_mov_HeapSort);
    fim = clock();

    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Numero de Comparacoes: %d\n", num_comp_HeapSort);
    printf("Numero de Movimentacoes: %d\n", num_mov_HeapSort);
    printf("Tempo de execucao: %f segundos\n", tempo_execucao);

    fprintf(saida, "%s;%f;%d;%d\n", algoritmos[5], tempo_execucao, num_comp_HeapSort, num_mov_HeapSort);

    /*
    printf("Lista ordenada:\n");
    for (int i = 0; i < N; i++){
        printf("%d ", V6[i].chave);
    }
    printf("\n");
    */

    printf("-----------------------------------------------------\n");


    free(V1);
    free(V2);
    free(V3);
    free(V4);
    free(V5);
    free(V6);
    free(V7);
    return 0;
}

