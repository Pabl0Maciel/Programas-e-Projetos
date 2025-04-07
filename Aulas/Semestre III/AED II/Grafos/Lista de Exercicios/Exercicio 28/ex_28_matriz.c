#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define TAM 100

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];  // 1 se há aresta
    int pontoInteresse[V + 1]; // código de interesse para cada vértice
    int flag[V + 1];
} GRAFO;

/**************************************/
/*         ESTRUTURA DA FILA          */
/**************************************/

typedef struct {
    int dados[TAM];
    int ini, fim;
} FILA;

void inicializaFila(FILA *f) {
    f->ini = f->fim = 0;
}

bool filaVazia(FILA *f) {
    return f->ini == f->fim;
}

bool entrarFila(FILA *f, int v) {
    if ((f->fim + 1) % TAM == f->ini) return false;
    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % TAM;
    return true;
}

int sairFila(FILA *f) {
    if (filaVazia(f)) return -1;
    int v = f->dados[f->ini];
    f->ini = (f->ini + 1) % TAM;
    return v;
}

/**************************************/
/*         FUNÇÕES DO GRAFO           */
/**************************************/

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->pontoInteresse[i] = 0;
        g->flag[i] = 0;
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

void zerarFlags(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
    }
}

void inserirAresta(GRAFO *g, int i, int j) {
    g->matriz[i][j] = 1;
    g->matriz[j][i] = 1;
}

void exibirMatriz(GRAFO *g) {
    printf("\nMatriz de adjacência:\n    ");
    for (int j = 1; j <= V; j++) printf("%2d ", j);
    printf("\n");
    for (int i = 1; i <= V; i++) {
        printf("%2d: ", i);
        for (int j = 1; j <= V; j++) {
            printf("%2d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

/**************************************/
/*     BUSCA PELO PONTO DE INTERESSE  */
/**************************************/

void caminhoPontoInteresse(GRAFO *g, int origem, int x) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g);

    entrarFila(f, origem);
    g->flag[origem] = 1;

    while (!filaVazia(f)) {
        int atual = sairFila(f);

        for (int j = 1; j <= V; j++) {
            if (g->matriz[atual][j] == 1 && g->flag[j] == 0) {
                g->flag[j] = 1;

                if (g->pontoInteresse[j] == x) {
                    printf("📍 Vértice mais próximo com ponto de interesse %d: %d\n", x, j);
                    free(f);
                    return;
                }

                entrarFila(f, j);
            }
        }
    }

    printf("❌ Nenhum vértice com ponto de interesse %d encontrado.\n", x);
    free(f);
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO g;
    inicializarGrafo(&g);

    // Arestas
    inserirAresta(&g, 1, 2);
    inserirAresta(&g, 1, 3);
    inserirAresta(&g, 2, 4);
    inserirAresta(&g, 3, 5);
    inserirAresta(&g, 5, 6);

    // Pontos de interesse
    g.pontoInteresse[2] = 2; // restaurante
    g.pontoInteresse[4] = 1; // hotel
    g.pontoInteresse[6] = 3; // hospital

    exibirMatriz(&g);

    // Busca pelo ponto mais próximo com código 3 (hospital)
    caminhoPontoInteresse(&g, 1, 3);

    return 0;
}
