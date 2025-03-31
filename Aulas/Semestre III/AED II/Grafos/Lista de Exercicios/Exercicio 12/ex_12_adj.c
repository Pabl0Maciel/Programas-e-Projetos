#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURAS DE DADOS          */
/**************************************/

typedef struct no {
    int adj;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
    int flag; // 0 = não visitado, 1 = em recursão, 2 = finalizado
} VERTICE;

bool profundidadeComCiclo(VERTICE *g, int i, int ant) {
    g[i].flag = 1; // marca como "em recursão"
    NO *p = g[i].inicio;

    while (p) {
        if (g[p->adj].flag == 0) {
            if (profundidadeComCiclo(g, p->adj, i)) return true;
        } else if (p->adj != ant) {
            // Encontrou um vértice em recursão ativa: ciclo detectado
            return true;
        }
        p = p->prox;
    }

    return false;
}

bool temCiclo(VERTICE *g) {
    zerarFlags(g);  // zera g[i].flag = 0 para todos os vértices

    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) {
            if (profundidadeComCiclo(g, i, -1)) return true;
        }
    }
    return false;  // nenhum ciclo detectado
}