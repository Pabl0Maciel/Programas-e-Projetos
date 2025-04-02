#include <stdio.h>
#include <stdlib.h>

#define V 7

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
} VERTICE;

typedef struct lista {
    int vertice;
    struct lista *prox;
} LISTA;

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
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
    printf("Grafo:\n");
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
/*   DFS PARA COLETAR UM COMPONENTE   */
/**************************************/

int dfsColetaGrupo(VERTICE *g, int i, LISTA **grupo) {
    g[i].flag = 1;

    LISTA *novo = malloc(sizeof(LISTA));
    novo->vertice = i;
    novo->prox = *grupo;
    *grupo = novo;

    int tam = 1;

    NO *p = g[i].inicio;
    while (p) {
        if (g[p->adj].flag == 0) {
            tam += dfsColetaGrupo(g, p->adj, grupo);
        }
        p = p->prox;
    }

    return tam;
}

/**************************************/
/*       LIBERA UMA LISTA AUXILIAR    */
/**************************************/

void liberarLista(LISTA *l) {
    while (l) {
        LISTA *tmp = l;
        l = l->prox;
        free(tmp);
    }
}

/**************************************/
/*  RETORNA LISTA DO MAIOR COMPONENTE */
/**************************************/

LISTA *maiorGrupo(VERTICE *g) {
    zerarFlags(g);
    LISTA *maior = NULL;
    int maiorTam = 0;

    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) {
            LISTA *grupoAtual = NULL;
            int tam = dfsColetaGrupo(g, i, &grupoAtual);

            if (tam > maiorTam) {
                liberarLista(maior);
                maior = grupoAtual;
                maiorTam = tam;
            } else {
                liberarLista(grupoAtual);
            }
        }
    }

    return maior;
}

/**************************************/
/*         EXIBE UMA LISTA            */
/**************************************/

void exibirLista(LISTA *l) {
    printf("Maior grupo: ");
    while (l) {
        printf("%d ", l->vertice);
        l = l->prox;
    }
    printf("\n");
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // Componente 1: 1-2-3
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 3);

    // Componente 2: 4-5
    inserirAresta(grafo, 4, 5);

    // Componente 3: 6-7
    inserirAresta(grafo, 6, 7);

    exibirGrafo(grafo);

    LISTA *maior = maiorGrupo(grafo);
    exibirLista(maior);
    liberarLista(maior);

    return 0;
}
