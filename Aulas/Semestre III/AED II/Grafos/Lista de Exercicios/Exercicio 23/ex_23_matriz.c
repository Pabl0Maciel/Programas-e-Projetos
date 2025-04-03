#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define TAM 100

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];  // 1 se houver aresta, 0 se não
    bool estaOcupada[V + 1];   // estado de cada sala
    int flag[V + 1];           // marcação para BFS
    int distancia[V + 1];      // distância até a origem
} GRAFO;

/**************************************/
/*         ESTRUTURA DA FILA          */
/**************************************/

typedef struct {
    int dados[TAM];
    int ini, fim;
} FILA;

void inicializaFila(FILA *f) { f->ini = f->fim = 0; }

bool filaVazia(FILA *f) { return f->ini == f->fim; }

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
/*     LISTA LIGADA DE RESULTADOS     */
/**************************************/

typedef struct resultado {
    int sala;
    struct resultado *prox;
} RESULTADO;

RESULTADO* inserirResultado(RESULTADO *lista, int sala) {
    RESULTADO *novo = malloc(sizeof(RESULTADO));
    novo->sala = sala;
    novo->prox = lista;
    return novo;
}

void imprimirResultado(RESULTADO *lista) {
    if (!lista) {
        printf("❌ Nenhuma sala vazia encontrada.\n");
        return;
    }
    printf("\n🔍 Salas vazias mais próximas: ");
    while (lista) {
        printf("%d ", lista->sala);
        lista = lista->prox;
    }
    printf("\n");
}

/**************************************/
/*         FUNÇÕES DO GRAFO           */
/**************************************/

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->estaOcupada[i] = true;
        g->flag[i] = 0;
        g->distancia[i] = -1;
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

void zerarFlags(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
        g->distancia[i] = -1;
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

    printf("\nOcupações das salas:\n");
    for (int i = 1; i <= V; i++) {
        printf("Sala %d: %s\n", i, g->estaOcupada[i] ? "ocupada" : "vazia");
    }
}

/**************************************/
/*     BFS: SALAS VAZIAS EMPATADAS    */
/**************************************/

RESULTADO* salasVaziasMaisProximas(GRAFO *g, int origem) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g);

    RESULTADO *res = NULL;
    int menorDist = -1;

    entrarFila(f, origem);
    g->flag[origem] = 1;
    g->distancia[origem] = 0;

    while (!filaVazia(f)) {
        int atual = sairFila(f);

        for (int j = 1; j <= V; j++) {
            if (g->matriz[atual][j] == 1 && g->flag[j] == 0) {
                g->flag[j] = 1;
                g->distancia[j] = g->distancia[atual] + 1;

                if (!g->estaOcupada[j]) {
                    if (menorDist == -1 || g->distancia[j] == menorDist) {
                        menorDist = g->distancia[j];
                        res = inserirResultado(res, j);
                    }
                }

                if (menorDist == -1 || g->distancia[j] <= menorDist) {
                    entrarFila(f, j);
                }
            }
        }
    }

    free(f);
    return res;
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO g;
    inicializarGrafo(&g);

    // Conexões entre salas
    inserirAresta(&g, 1, 2);
    inserirAresta(&g, 1, 3);
    inserirAresta(&g, 2, 4);
    inserirAresta(&g, 3, 5);
    inserirAresta(&g, 3, 6);

    // Salas 5 e 6 estão vazias
    g.estaOcupada[5] = false;
    g.estaOcupada[6] = false;

    exibirMatriz(&g);

    printf("📍 Sala inicial: 1\n");
    RESULTADO *lista = salasVaziasMaisProximas(&g, 1);
    imprimirResultado(lista);

    // Liberar a lista
    while (lista) {
        RESULTADO *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }

    return 0;
}
