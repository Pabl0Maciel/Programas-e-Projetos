#include <stdio.h>
void main(){
int idade=0;
double peso=0.0;
char nome[50];
printf("digite uma idade:\n");
scanf("%d" , &idade);
printf("digite um peso:\n");
scanf("%lf", &peso);
printf("digite o nome completo:\n");
scanf(" %[^\n]s", nome);
printf("dados informados:\n");
printf("idade: %d.\n", idade);
printf("peso: %2lf.\n", peso);
printf("nome: %s.\n", nome);
}
