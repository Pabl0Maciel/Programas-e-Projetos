#include <stdio.h>
#include <stdbool.h>

#define V 7

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];
    int flag[V + 1];
} GRAFO;


bool ehCompleto(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        if (g->matriz[i][i] != 0) return false;
    }
    
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {

            if (i == j) continue;

            if (g->matriz[i][j] != 1) return false;
        }
    }
    return true;
}