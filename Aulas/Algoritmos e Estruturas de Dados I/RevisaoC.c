#include <stdio.h>
#include <stdlib.h>

// funcoes
    void somar_um(int *num){

        *num += 1;
        printf("resultado: %d\n", *num);

    }

int main(){

// ponteiros e alocacao dinamica
    int MeuInteiro = 11;
    int *int_ptr = &MeuInteiro;

    printf("Localizacao do ponteiro: %p\n", int_ptr);
    printf("Conteudo do ponteiro: %d\n", *int_ptr);

    int_ptr = malloc(sizeof(int)); // alocacao de um inteiro na memoria
    *int_ptr = 2024; // alteracao do valor onde o ponteiro aponta

    printf("Localizacao do ponteiro: %p\n", int_ptr);
    printf("Conteudo do ponteiro: %d\n", *int_ptr);

// funcoes
    printf("MeuInteiro fora da funcao: %d\n", MeuInteiro);
    somar_um(&MeuInteiro);
    printf("MeuInteiro alterado: %d\n", MeuInteiro);

    return 0;
}