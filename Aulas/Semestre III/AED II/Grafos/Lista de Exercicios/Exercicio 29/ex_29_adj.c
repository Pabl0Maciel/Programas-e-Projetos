#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define TAM 100

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct no {
    int adj;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
    int flag;
    int pontoInteresse;
} VERTICE;

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

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].pontoInteresse = 0;
    }
}

void zerarFlags(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].flag = 0;
    }
}

void inserirAresta(VERTICE *g, int i, int j) {
    NO *novo1 = malloc(sizeof(NO));
    novo1->adj = j;
    novo1->prox = g[i].inicio;
    g[i].inicio = novo1;

    NO *novo2 = malloc(sizeof(NO));
    novo2->adj = i;
    novo2->prox = g[j].inicio;
    g[j].inicio = novo2;
}

void exibirGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) { 
        printf("%d: ", i);
        NO *p = g[i].inicio;
        while (p) {
            printf("%d -> ", p->adj);
            p = p->prox;
        }
        printf("NULL\n");
    }
}

/**************************************/
/*     FUNÇÃO PRINCIPAL DO PROBLEMA   */
/**************************************/

void caminhoPontoInteresse(VERTICE *g, int origem, int x, int n) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g);

    entrarFila(f, origem);
    g[origem].flag = 1;

    while (!filaVazia(f)) {
        int atual = sairFila(f);
        NO *p = g[atual].inicio;

        while (p) {
            int v = p->adj;

            if (g[v].flag == 0 && v != n) {
                g[v].flag = 1;

                if (g[v].pontoInteresse == x) {
                    printf("📍 Vértice mais próximo com ponto de interesse %d (evitando %d): %d\n", x, n, v);
                    free(f);
                    return;
                }

                entrarFila(f, v);
            }

            p = p->prox;
        }
    }

    printf("❌ Nenhum vértice com ponto de interesse %d encontrado (evitando %d).\n", x, n);
    free(f);
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // Criando arestas
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 3, 5);
    inserirAresta(grafo, 5, 6);

    // Definindo pontos de interesse
    grafo[2].pontoInteresse = 2; // restaurante
    grafo[4].pontoInteresse = 1; // hotel
    grafo[6].pontoInteresse = 3; // hospital

    exibirGrafo(grafo);

    // Exemplo: buscar hospital (3) a partir de 1, evitando a área 5
    caminhoPontoInteresse(grafo, 1, 3, 5);

    return 0;
}
