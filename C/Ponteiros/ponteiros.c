#include <stdio.h>
#include <stdlib.h>

// estrutura usada
struct time{
        char nome[20];
        float salario;
        unsigned gols;
    };
typedef struct time time; // renomeia  'struct jogador' para jogador

// funcao usada
void exibir(time *ptr5);

// main
int main(){
// conceitos basicos
    short total = 3126;
    printf("Valor: %d\nLocalizacao: %p\n", total, &total);

    short *ptr = &total; // armazena o endereco da variavel total (* e usado para declaracao de ponteiro)
    printf("Endereco armazenado no ponteiro: %p\nConteudo apontado: %d\n", ptr, *ptr); // *ptr acessa o conteudo apontado

    *ptr = *ptr + 1; // acessa o conteudo apontado pelo ponteiro, soma um e salva no mesmo local apontado
    printf("Agora 'total' vale: %d\n", total);

// ponteiros e structs
    time jogadores[5];
    snprintf(jogadores[0].nome, sizeof(jogadores[0].nome), "Pele"); // copia a string 'Pele' para jogadores[0].nome, garantindo que nao exceda o tamanho 
                                                                    // passado e que termine com \0
    jogadores[0].salario = 20000.0;
    jogadores[0].gols = 1200;

    // imprime o valor das variaveis da estrutura
    printf("Nome: %s\n", jogadores[0].nome);
    printf("Salario: %2f\n", jogadores[0].salario);
    printf("Gols: %u\n", jogadores[0].gols);

    time * estrela = &jogadores[0]; // armazena o endereco do time na estrutura

    // imprime  valor apontado pelo ponteiro na estrutura (se usa '->' para mostrar o valor na estrutura)
    printf("Nome: %s\n", estrela -> nome);
    printf("Salario: %2f\n", estrela -> salario);
    printf("Gols: %u\n", estrela -> gols);

// ponteiro e strings
    char frase[] = "tchau"; 
    char *ptr3 = frase; // ponteiro para o primeiro caractere (em um array, nao e necessario usar & para o primeiro elemento)
    char *ptr4 = &frase[1]; // ponteiro para o segundo caractere

    printf("Endereco do primeiro caractere: %p\n", ptr3);
    printf("Endereco do segundo caractere: %p\n", ptr4);

// ponteiros e funcoes
    time novato = {"Joaozinho", 100, 2};
    exibir(&novato); // deste modo, a funcao nao recebeu uma copia da informacoes do jogador e sim o endereco das variaveis dela.
                     // com isso tambem e possivel alterar o valor das variaveis na execucao da funcao.

    return 0;
}

// funcao usada
void exibir(time *ptr5){
        printf("Nome: %s\n", ptr5 -> nome);
        printf("Salario: %2.f\n", ptr5 -> salario);
        printf("Gols: %u\n", ptr5 -> gols);
    }