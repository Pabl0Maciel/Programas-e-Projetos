#include <stdio.h>

int main() {
    int nusp = 12345678;
    printf("Imprimindo inteiro: %i\n", nusp);
    printf("Imprimindo numero: %d\n", nusp);
    printf("Imprimindo float (com cast): %f\n", (float)nusp);
    printf("Imprimindo quociente: %i\n", nusp/2);
    printf("Imprimindo resto: %d\n", nusp%2);
    printf("Imprimindo quadrado: %d\n", nusp*nusp);
    return 0;
}