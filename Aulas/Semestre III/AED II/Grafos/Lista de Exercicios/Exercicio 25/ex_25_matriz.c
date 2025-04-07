#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define TAM 100

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];  // 1 se houver ligação
    int flag[V + 1];           // marca se visitado
    int nivel[V + 1];          // nível na BFS
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
        g->flag[i] = 0;
        g->nivel[i] = -1;
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

void zerarFlags(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
        g->nivel[i] = -1;
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
/*   BFS PARA RELAÇÕES ATÉ GRAU D     */
/**************************************/

void buscaEmNivel(GRAFO *g, int origem, int d) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g);

    g->flag[origem] = 1;
    g->nivel[origem] = 0;
    entrarFila(f, origem);

    printf("🔍 Usuários relacionados com %d até grau %d:\n", origem, d);

    while (!filaVazia(f)) {
        int atual = sairFila(f);

        for (int j = 1; j <= V; j++) {
            if (g->matriz[atual][j] == 1 && g->flag[j] == 0) {
                g->nivel[j] = g->nivel[atual] + 1;

                if (g->nivel[j] <= d) {
                    g->flag[j] = 1;
                    entrarFila(f, j);
                    printf("- Usuário %d (grau %d)\n", j, g->nivel[j]);
                }
            }
        }
    }

    free(f);
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO g;
    inicializarGrafo(&g);

    // Conexões entre usuários
    inserirAresta(&g, 1, 2);
    inserirAresta(&g, 1, 3);
    inserirAresta(&g, 2, 4);
    inserirAresta(&g, 3, 5);
    inserirAresta(&g, 5, 6);

    exibirMatriz(&g);

    // Exemplo: listar usuários com até 2 graus de distância de 1
    buscaEmNivel(&g, 1, 2);

    return 0;
}
