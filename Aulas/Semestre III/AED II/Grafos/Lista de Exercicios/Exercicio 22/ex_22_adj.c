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
    bool estaOcupada;
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
    if ((f->fim + 1) % TAM == f->ini) return false; // fila cheia
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
        g[i].estaOcupada = true; // por padrão, todas ocupadas
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
/*      SALA VAZIA MAIS PRÓXIMA       */
/**************************************/

int largura(VERTICE *g, int i) {
    zerarFlags(g);
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);

    entrarFila(f, i);
    g[i].flag = 1;

    while (!filaVazia(f)) {
        i = sairFila(f);
        g[i].flag = 2;

        NO *p = g[i].inicio;
        while (p) {
            int vizinho = p->adj;
            if (g[vizinho].flag == 0) {
                if (!g[vizinho].estaOcupada) {
                    printf("Sala %d vazia!\n", vizinho);
                    free(f);
                    return vizinho;
                }
                entrarFila(f, vizinho);
                g[vizinho].flag = 1;
            }
            p = p->prox;
        }
    }

    free(f);
    return -1; // nenhuma sala vazia encontrada
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // Conexões entre salas
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 3, 5);
    inserirAresta(grafo, 4, 6);

    // Ocupações: todas ocupadas exceto a 5
    grafo[5].estaOcupada = false;

    exibirGrafo(grafo);

    printf("🔍 Procurando sala vazia a partir da sala 1:\n");
    int sala = largura(grafo, 1);
    if (sala != -1) {
        printf("✅ Sala vazia mais próxima: %d\n", sala);
    } else {
        printf("❌ Nenhuma sala vazia encontrada.\n");
    }

    return 0;
}
