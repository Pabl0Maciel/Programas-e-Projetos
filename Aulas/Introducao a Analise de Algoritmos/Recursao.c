#include <stdio.h>
#include <stdlib.h>

int fatorial(int n){
    if (n < 2) return 1;

    else return (n * fatorial(n-1));
}

int main(){
    char resposta;

    do{
        printf("Deseja calcular o fatorial de um numero natural? Digite 's' para sim e 'n' para nao: ");
        scanf("%c", &resposta);
        if (resposta != 's'){
            printf("Obrigado por usar o programa!\n");
            break;
        }

        printf("Digite um numero natural: ");
        int numero;
        scanf("%d", &numero);
        getchar();
        int resultado = fatorial(numero); 
        printf("Fatorial de %d: %d\n", numero, resultado); 
    }while (resposta == 's');

    return 0;
}