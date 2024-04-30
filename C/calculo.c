#include <stdio.h>
void main (){
int A, B, soma, subtr, mult, divis;
printf("digite o primeiro valor:\n");
scanf("%d", &A);
printf("digite o segundo valor:\n");
scanf("%d", &B);

soma=A+B;
subtr=A-B;
mult=A*B;
divis=A/B;

printf("resultados:\n");
printf("soma:%d.\n", soma);
printf("subtracao:%d.\n", subtr);
printf("multiplicacao:%d.\n", mult);
printf("divisao:%d.\n", divis);

}
