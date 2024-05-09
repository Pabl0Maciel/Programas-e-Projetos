#include <stdio.h>
#include <string.h>
#define TAM 50


struct tipo_pessoa{
	int idade;
	float peso;
	char nome[TAM];
};

typedef struct tipo_pessoa tipo_pessoa;

int main(){

	char a[]="pablo caballero maciel";

	tipo_pessoa pes={0, 0.0, "teste"};

	printf("Inicio:\n");
	printf("Idade da pessoa: %d\n", pes.idade);
	printf("Peso da pessoa: %.2f\n", pes.peso);
	printf("Nome da pessoa: %s\n", pes.nome);

//atribuindo valores
	pes.idade=10;
	pes.peso=99.99;
	strcpy(pes.nome, "texto");

	printf("depois das alteracoes:\n");
	printf("Idade da pessoa: %d\n", pes.idade);
        printf("Peso da pessoa: %.2f\n", pes.peso);
        printf("Nome da pessoa: %s\n", pes.nome);

//entrada pelo teclado
	printf("Digite sua idade:\n");
	scanf("%d", &pes.idade);
	printf("Digite seu peso:\n");
	scanf(" %f", &pes.peso);
	printf("Digite seu nome:\n");
	scanf(" %[^\n]", pes.nome);
	getchar();

	printf("dados digitados:\n");
	printf("Idade: %d\n", pes.idade);
	printf("Peso: %.2f\n", pes.peso);
	printf("Nome: %s\n", pes.nome);

	if(strcmp(a, pes.nome)==0){
		printf("iguais\n");
	}
	else{
		printf("nao iguais\n");
	}

	return 0;
}


