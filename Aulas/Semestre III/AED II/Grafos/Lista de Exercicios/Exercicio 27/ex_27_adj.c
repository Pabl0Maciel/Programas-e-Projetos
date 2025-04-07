#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define TAM 100

/**************************************/
/*        ESTRUTURAS E LISTAS         */
/**************************************/

typedef struct no {
    int adj;
    int companhia;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
    int flag;
    int via;
} VERTICE;

typedef struct lista {
    int cidade;
    struct lista *prox;
} LISTA;

typedef struct {
    int dados[TAM];
    int ini, fim;
} FILA;

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].via = -1;
    }
}

void zerarFlags(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].flag = 0;
        g[i].via = -1;
    }
}

void inserirAresta(VERTICE *g, int i, int j, int companhia) {
    NO *novo = malloc(sizeof(NO));
    novo->adj = j;
    novo->companhia = companhia;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;

    NO *novo2 = malloc(sizeof(NO));
    novo2->adj = i;
    novo2->companhia = companhia;
    novo2->prox = g[j].inicio;
    g[j].inicio = novo2;
}

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

LISTA *inserirLista(LISTA *lista, int cidade) {
    LISTA *novo = malloc(sizeof(LISTA));
    novo->cidade = cidade;
    novo->prox = lista;
    return novo;
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
/*   FUNÇÃO PRINCIPAL DO PROBLEMA     */
/**************************************/

LISTA *menorTrajeto(VERTICE *g, int a, int b, int c) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g);

    g[a].flag = 1;
    entrarFila(f, a);

    while (!filaVazia(f)) {
        int atual = sairFila(f);
        NO *p = g[atual].inicio;

        while (p) {
            if (p->companhia == c && g[p->adj].flag == 0) {
                g[p->adj].flag = 1;
                g[p->adj].via = atual;
                entrarFila(f, p->adj);

                if (p->adj == b) break;
            }
            p = p->prox;
        }
    }

    free(f);

    // Se não encontrou caminho
    if (g[b].flag == 0) return NULL;

    // Reconstruir caminho de b até a
    LISTA *caminho = NULL;
    int atual = b;
    while (atual != -1) {
        caminho = inserirLista(caminho, atual);
        atual = g[atual].via;
    }

    return caminho;
}

void exibirCaminho(LISTA *caminho) {
    if (!caminho) {
        printf("❌ Nenhum trajeto possível com a companhia informada.\n");
        return;
    }

    printf("🛫 Caminho com menor número de conexões:\n");
    while (caminho) {
        printf("-> Cidade %d ", caminho->cidade);
        caminho = caminho->prox;
    }
    printf("\n");
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // companhias: 1 = AZUL, 2 = GOL, 3 = LATAM
    inserirAresta(grafo, 1, 2, 1);
    inserirAresta(grafo, 2, 3, 1);
    inserirAresta(grafo, 1, 4, 2);
    inserirAresta(grafo, 4, 5, 2);
    inserirAresta(grafo, 5, 3, 2);
    inserirAresta(grafo, 2, 6, 3);

    int origem = 1;
    int destino = 3;
    int companhia = 1;

    exibirGrafo(grafo);

    LISTA *trajeto = menorTrajeto(grafo, origem, destino, companhia);
    exibirCaminho(trajeto);

    return 0;
}
