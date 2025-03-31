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

bool profundidadeComCiclo(VERTICE *g, int i) {
    g[i].flag = 1; // marca como "em recursão"
    NO *p = g[i].inicio;

    while (p) {
        if (g[p->adj].flag == 0) {
            if (!profundidadeComCiclo(g, p->adj)) return false;
        } else if (g[p->adj].flag == 1) {
            // Encontrou um vértice em recursão ativa: ciclo detectado
            return false;
        }
        p = p->prox;
    }

    g[i].flag = 2; // marca como "visitado completamente"
    return true;
}