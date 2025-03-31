/**********************************************************************/
/* Enunciado: Escreva um algoritmo que, dado um grafo dirigido,      */
/*            verifique se ele é uma árvore enraizada.               */
/**********************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURA DO GRAFO           */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];  // matriz[i][j] == 1 se há aresta i → j
    int flag[V + 1];           // 0 = não visitado, 1 = em recursão, 2 = finalizado
} GRAFO;

/*********************************************/
/*       PROTÓTIPOS DAS FUNÇÕES AUXILIARES   */
/*********************************************/
void inicializar(GRAFO *g);
bool inserirAresta(GRAFO *g, int i, int j);
int grauEntrada(GRAFO *g, int v);
void zerarFlags(GRAFO *g);
bool dfs(GRAFO *g, int v);
void exibirMatriz(GRAFO *g);
void exibirResultado(bool resultado);

/*********************************************/
/*        FUNÇÕES DO PROBLEMA (TOPO)         */
/*********************************************/

/*
 * Realiza DFS com detecção de ciclos.
 * - flag[v] == 1 → ciclo detectado
 * - Retorna false se houver ciclo
 */
bool dfs(GRAFO *g, int v) {
    g->flag[v] = 1;

    for (int j = 1; j <= V; j++) {
        if (g->matriz[v][j]) {
            if (g->flag[j] == 0) {
                if (!dfs(g, j)) return false;
            } else if (g->flag[j] == 1) {
                return false;  // ciclo detectado
            }
        }
    }

    g->flag[v] = 2;
    return true;
}

/*
 * Verifica se um grafo é uma árvore enraizada:
 * - Exatamente um vértice com grau de entrada 0
 * - Todos os vértices acessíveis a partir da raiz
 * - Nenhum ciclo
 */
bool ehArvoreEnraizada(GRAFO *g) {
    int raiz = -1;
    int totalRaizes = 0;

    for (int i = 1; i <= V; i++) {
        if (grauEntrada(g, i) == 0) {
            raiz = i;
            totalRaizes++;
        }
    }

    if (totalRaizes != 1) return false;

    zerarFlags(g);
    if (!dfs(g, raiz)) return false;

    for (int i = 1; i <= V; i++) {
        if (g->flag[i] == 0) return false;
    }

    return true;
}

/*********************************************/
/*      FUNÇÕES AUXILIARES E DE SUPORTE      */
/*********************************************/

void inicializar(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

bool inserirAresta(GRAFO *g, int i, int j) {
    if (g->matriz[i][j] == 0) {
        g->matriz[i][j] = 1;
        return true;
    }
    return false;
}

int grauEntrada(GRAFO *g, int v) {
    int cont = 0;
    for (int i = 1; i <= V; i++) {
        if (g->matriz[i][v] == 1) cont++;
    }
    return cont;
}

void zerarFlags(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
    }
}

void exibirMatriz(GRAFO *g) {
    printf("   ");
    for (int j = 1; j <= V; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 1; i <= V; i++) {
        printf("%d: ", i);
        for (int j = 1; j <= V; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

void exibirResultado(bool resultado) {
    if (resultado)
        printf("É uma árvore enraizada.\n");
    else
        printf("NÃO é uma árvore enraizada.\n");
}

/*********************************************/
/*                  MAIN                     */
/*********************************************/

int main() {
    GRAFO grafo;

    // TESTE 1 — grafo válido
    inicializar(&grafo);
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 1, 3);
    inserirAresta(&grafo, 2, 4);
    inserirAresta(&grafo, 2, 5);
    printf("Teste 1 (grafo válido):\n");
    exibirMatriz(&grafo);
    exibirResultado(ehArvoreEnraizada(&grafo));

    // TESTE 2 — contém ciclo: 2 → 3 → 4 → 2
    inicializar(&grafo);
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 4, 2);  // ciclo
    printf("\nTeste 2 (com ciclo):\n");
    exibirMatriz(&grafo);
    exibirResultado(ehArvoreEnraizada(&grafo));

    // TESTE 3 — múltiplas raízes (2 e 3 sem entrada)
    inicializar(&grafo);
    inserirAresta(&grafo, 2, 1);
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 3, 5);
    printf("\nTeste 3 (múltiplas raízes):\n");
    exibirMatriz(&grafo);
    exibirResultado(ehArvoreEnraizada(&grafo));

    return 0;
}
