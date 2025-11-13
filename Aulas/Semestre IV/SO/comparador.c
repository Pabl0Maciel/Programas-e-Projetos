#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_DIFFS 50  // limite de diferenças mostradas

void compararArquivos(const char *orig, const char *teste) {
    FILE *f1 = fopen(orig, "rb");
    FILE *f2 = fopen(teste, "rb");

    if (!f1) {
        printf("❌ Não foi possível abrir %s\n", orig);
        return;
    }
    if (!f2) {
        printf("⚠️  Arquivo teste não encontrado: %s\n", teste);
        fclose(f1);
        return;
    }

    int c1, c2;
    long pos = 0;
    int diffs = 0;
    int iguais = 1;

    while (1) {
        c1 = fgetc(f1);
        c2 = fgetc(f2);

        if (c1 == EOF || c2 == EOF)
            break;

        if (c1 != c2) {
            iguais = 0;
            diffs++;
            if (diffs <= MAX_DIFFS)
                printf("Diferença no byte %ld: %02X ↔ %02X\n", pos, c1, c2);
        }
        pos++;
    }

    // Verifica tamanhos
    fseek(f1, 0, SEEK_END);
    fseek(f2, 0, SEEK_END);
    long tamanho1 = ftell(f1);
    long tamanho2 = ftell(f2);

    if (tamanho1 != tamanho2) {
        iguais = 0;
        printf("⚠️  Tamanhos diferentes: %ld bytes ↔ %ld bytes\n", tamanho1, tamanho2);
    }

    if (iguais)
        printf("✅ Arquivos idênticos.\n");
    else
        printf("❗ %d diferenças encontradas (mostradas até %d).\n", diffs, MAX_DIFFS);

    fclose(f1);
    fclose(f2);
}

int terminaCom(const char *str, const char *sufixo) {
    size_t lenstr = strlen(str);
    size_t lensuf = strlen(sufixo);
    if (lensuf > lenstr)
        return 0;
    return strcmp(str + lenstr - lensuf, sufixo) == 0;
}

void compararTipo(const char *extensao, const char *rotulo) {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("Erro ao abrir diretório");
        return;
    }

    struct dirent *ent;
    int encontrou = 0;

    printf("\n==============================\n");
    printf("🔍 Comparando arquivos %s\n", rotulo);
    printf("==============================\n");

    while ((ent = readdir(dir)) != NULL) {
        if (terminaCom(ent->d_name, extensao) &&
            strstr(ent->d_name, "_teste") == NULL) {

            encontrou = 1;

            char base[256];
            strcpy(base, ent->d_name);
            base[strlen(base) - strlen(extensao)] = '\0';

            char teste[300];
            sprintf(teste, "%s_teste%s", base, extensao);

            printf("\nComparando: %s ↔ %s\n", ent->d_name, teste);
            compararArquivos(ent->d_name, teste);
        }
    }

    if (!encontrou)
        printf("Nenhum arquivo %s encontrado.\n", extensao);

    closedir(dir);
}

int main() {
    compararTipo(".chrinked", "COMPACTADOS (.chrinked)");
    compararTipo(".txt", "DESCOMPACTADOS (.txt)");
    return 0;
}
