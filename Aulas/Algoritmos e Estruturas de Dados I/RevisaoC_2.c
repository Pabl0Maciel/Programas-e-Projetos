#include <stdio.h>
#include <stdlib.h>

typedef int TIPO_ANO;

typedef struct animal{
    int idade;
    int numero_patas;
    struct animal *filhote;
} animal_t;

void envelhecer (animal_t *a){
    a -> idade++;
}

void envelhecer_filhote (animal_t a){
    a.filhote -> idade++;
}

void inicializa_gato (animal_t *a, TIPO_ANO idade){
    a -> numero_patas = 4;
    a -> idade = idade;
    a -> filhote = NULL;
}


int main(){

    struct animal gato;
    TIPO_ANO AnoAtual = 2024;

    gato.idade = 10;
    gato.numero_patas = 4;

    printf("Idade antes: %d\n", gato.idade);
    envelhecer(&gato);
    printf("Idade depois: %d\n", gato.idade);

    animal_t outro_gato;
    outro_gato.idade = 1;
    outro_gato.numero_patas = 4;

    printf("Idade: %d\n", outro_gato.idade);

    animal_t meu_filhote;
    inicializa_gato(&meu_filhote, 0);
    meu_filhote.idade = 0;
    gato.filhote = &meu_filhote;

    printf("Idade do filhote antes: %d\n", gato.filhote -> idade);
    envelhecer_filhote(gato);
    printf("Idade do filhote depois: %d\n", gato.filhote -> idade);


    return 0;
}