#include <stdio.h>
#include <string.h>
#include <locale.h>

#define S 20
#define N 50
#define L 50
int main(){
	setlocale(LC_ALL,"Portuguese");
//exemplo 1//
	char origem[S]={"Ola, mundo!"};
	char destino[S];

	printf("antes do strcpy:\n");
	puts(origem);
	puts(destino);

	strcpy(destino,origem);

	printf("Depois do strcpy:\n");
	puts(origem);
	puts(destino);
//exemplo 2//
	char s1[N]={"logica de"};
	char s2[N]={" programacao!"};

	printf("antes do strcat:\n");
	printf("str1: %s\n", s1);
	printf("str2: %s\n", s2);

	strcat(s1,s2);

	printf("depois de strcat:\n");
	puts(s1);
//exemplo 3//
	char s[L];
	int i;
	

	printf("Digite um texto:\n");
	fgets(s, sizeof(s), stdin);
	i=strlen(s);
	printf("\ntamanho do texto: %d\n\n", i);

	printf("Impressao de posicao a posicao:\n");
	for(i=0;i<strlen(s);i++){
		printf("%c", s[i]);
	} printf("\n");
//todo esse comando poderia ser substituido por puts(s)//
//exemplo 4//
	char a[]="oi";
	char b[50];

	printf("Digite um texto:\n");
	fgets(b, sizeof(b), stdin);
	b[strcspn(b, "\n")] = '\0';
	if(strcmp(a, b)==0){
		printf("Textos iguais\n");
	}
	else{
		printf("Textos diferentes\n");
	}
return 0;
}



