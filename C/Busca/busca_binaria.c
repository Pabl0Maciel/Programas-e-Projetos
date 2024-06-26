#include <stdio.h>

int buscaBinaria(int *v, int N, int num) {
    int esq = 0;
    int dir = N - 1;
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
 
        if (v[meio] == num) {
            return meio; 
        }

        if (v[meio] < num) {
            esq = meio + 1;
        }
        else {
            dir = meio - 1;
        }
    }

    return -1; 
}

int main() {
    int vet[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int N = 9;
    int num = 6;
    
    int resultado = buscaBinaria(vet, N, num);
    
    if (resultado != -1) {
        printf("Número encontrado no índice: %d\n", resultado);
    } else {
        printf("Número não encontrado\n");
    }

    return 0;
}
