#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 6
#define TAM 100

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];   // 1 se há aresta, 0 se não
    bool estaOcupada[V + 1];    // true se a sala i está ocupada
    int flag[V + 1];            // marcação para busca
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
        g->estaOcupada[i] = true;
        g->flag[i] = 0;
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

void inserirAresta(GRAFO *g, int i, int j) {
    g->matriz[i][j] = 1;
    g->matriz[j][i] = 1;
}

void zerarFlags(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
    }
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

    printf("\nOcupações das salas:\n");
    for (int i = 1; i <= V; i++) {
        printf("Sala %d: %s\n", i, g->estaOcupada[i] ? "ocupada" : "vazia");
    }
}

/**************************************/
/*      SALA VAZIA MAIS PRÓXIMA       */
/**************************************/

int salaVaziaMaisProxima(GRAFO *g, int origem) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g);

    entrarFila(f, origem);
    g->flag[origem] = 1;

    while (!filaVazia(f)) {
        int atual = sairFila(f);

        for (int j = 1; j <= V; j++) {
            if (g->matriz[atual][j] == 1 && g->flag[j] == 0) {
                if (!g->estaOcupada[j]) {
                    printf("\n🔍 Sala vazia mais próxima encontrada: %d\n", j);
                    free(f);
                    return j;
                }
                entrarFila(f, j);
                g->flag[j] = 1;
            }
        }
    }

    free(f);
    return -1;
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO g;
    inicializarGrafo(&g);

    // Conexões entre salas (grafo não-dirigido)
    inserirAresta(&g, 1, 2);
    inserirAresta(&g, 1, 3);
    inserirAresta(&g, 2, 4);
    inserirAresta(&g, 3, 5);
    inserirAresta(&g, 4, 6);

    // Marcar uma sala como vazia
    g.estaOcupada[5] = false;

    exibirMatriz(&g);

    int origem = 1;
    int sala = salaVaziaMaisProxima(&g, origem);
    if (sala == -1)
        printf("❌ Nenhuma sala vazia encontrada.\n");

    return 0;
}
