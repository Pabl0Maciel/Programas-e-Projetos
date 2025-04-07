#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define TAM 100

/**************************************/
/*         ESTRUTURAS DO GRAFO        */
/**************************************/

typedef struct no {
    int adj;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
    int flag;
    int nivel;
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
        g[i].nivel = -1;
    }
}

void zerarFlags(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].flag = 0;
        g[i].nivel = -1;
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
/*   BFS PARA RELAÇÕES ATÉ GRAU D     */
/**************************************/

void buscaEmNivel(VERTICE *g, int i, int d) {
    zerarFlags(g);
    FILA *f = (FILA *)malloc(sizeof(FILA));
    inicializaFila(f);

    g[i].flag = 1;
    g[i].nivel = 0;
    entrarFila(f, i);

    printf("🔍 Usuários relacionados com %d até grau %d:\n", i, d);

    while (!filaVazia(f)) {
        int atual = sairFila(f);
        g[atual].flag = 2;

        NO *p = g[atual].inicio;
        while (p) {
            int vizinho = p->adj;

            if (g[vizinho].flag == 0) {
                g[vizinho].nivel = g[atual].nivel + 1;

                if (g[vizinho].nivel <= d) {
                    g[vizinho].flag = 1;
                    entrarFila(f, vizinho);
                    printf("- Usuário %d (grau %d)\n", vizinho, g[vizinho].nivel);
                }
            }

            p = p->prox;
        }
    }

    free(f);
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // Rede de amizades
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 3, 5);
    inserirAresta(grafo, 5, 6);

    exibirGrafo(grafo);

    // Exemplo: mostrar conexões do usuário 1 até grau 2
    buscaEmNivel(grafo, 1, 2);

    return 0;
}
