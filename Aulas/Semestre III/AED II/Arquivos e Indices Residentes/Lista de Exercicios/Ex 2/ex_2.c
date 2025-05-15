/*
QUESTÃO 2 – Parte I – Arquivos Simples (sem índices)

Enunciado:
Copie um arquivo texto (com registros no formato "NroUSP|curso|estado|idade") para um novo 
arquivo binário com estrutura REGISTRO. Todos os registros gerados devem ter o campo 
valido = true.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura de registro
typedef struct {
    int NroUSP;
    int curso;
    int estado;
    int idade;
    bool valido;
} REGISTRO;

/*
Função: converterTextoParaBinario
Objetivo: Ler registros de um arquivo texto e gravá-los em um arquivo binário,
preenchendo o campo 'valido' como true.
*/
void converterTextoParaBinario(const char *arqTxt, const char *arqBin) {
    FILE *txt = fopen(arqTxt, "r");   // Abre o arquivo texto para leitura
    FILE *bin = fopen(arqBin, "wb");  // Abre o arquivo binário para escrita

    if (!txt || !bin) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    REGISTRO r;

    // Lê os campos do texto e escreve no binário
    while (fscanf(txt, "%d|%d|%d|%d", &r.NroUSP, &r.curso, &r.estado, &r.idade) == 4) {
        r.valido = true;
        fwrite(&r, sizeof(REGISTRO), 1, bin);
    }

    fclose(txt);
    fclose(bin);
}

/*
Função principal: main
Objetivo: Criar um arquivo texto de teste e converter para binário.
*/
int main() {
    const char *arquivoTexto = "entrada.txt";
    const char *arquivoBinario = "saida.bin";

    // Criar arquivo texto manualmente para o exemplo
    FILE *txt = fopen(arquivoTexto, "w");
    if (txt) {
        fprintf(txt, "123|10|35|21\n");
        fprintf(txt, "456|11|25|22\n");
        fprintf(txt, "789|10|31|20\n");
        fclose(txt);
    }

    // Converter texto para binário
    converterTextoParaBinario(arquivoTexto, arquivoBinario);

    printf("Conversão concluída. Verifique o arquivo '%s'.\n", arquivoBinario);
    return 0;
}
