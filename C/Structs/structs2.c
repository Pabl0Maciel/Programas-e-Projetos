#include <stdio.h>
#include <string.h>

#define TAM 3

struct tipo_pessoa{
	int idade;
	float peso;
	char nome[50];
};

typedef struct tipo_pessoa tipo_pessoa;

int main(){

	tipo_pessoa lista[TAM];
	int i;

	for(i=0; i<TAM; i++){
		printf("Insira os dados da pessoa (%d):\n", i+1);
		puts("Nome: ");
		scanf("%50[^\n]s", lista[i].nome);
		getchar();

		puts("Idade: ");
		scanf(" %d", &lista[i].idade);
		getchar();

		puts("Peso: ");
		scanf(" %f", &lista[i].peso);
		getchar();
	}

	for(i=0; i<TAM; i++){
		printf("\n-----------------Dados da pessoa (%d):-------------------------\n", i+1);
		printf("Nome: %s\n", lista[i].nome);
		printf("Idade: %d\n", lista[i].idade);
		printf("Peso: %.2f\n", lista[i].peso);
		
	}

	return 0;
}
