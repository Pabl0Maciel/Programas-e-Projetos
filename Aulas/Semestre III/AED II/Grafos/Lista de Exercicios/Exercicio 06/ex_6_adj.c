/**********************************************************************/
/* Enunciado: Escreva um algoritmo que, dado um grafo dirigido,      */
/*            verifique se ele é uma árvore enraizada.               */
/**********************************************************************/

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

/*********************************************/
/*         PROTÓTIPOS DAS FUNÇÕES            */
/*********************************************/

void zerarFlags(VERTICE *g);
int grauEntrada(VERTICE *g, int i);

/*********************************************/
/*        FUNÇÃO DO PROBLEMA (TOPO)          */
/*********************************************/

/*
 * Executa uma busca em profundidade a partir do vértice i,
 * usando flag para detectar ciclos:
 * - flag 0 = não visitado
 * - flag 1 = em processamento (recursão ativa)
 * - flag 2 = já processado (visitado por completo)
 * Retorna false se detectar ciclo.
 */
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

/*
 * Verifica se o grafo é uma árvore enraizada:
 * - Deve haver exatamente 1 vértice com grau de entrada 0 (a raiz)
 * - Não pode conter ciclos
 * - Todos os vértices devem ser acessíveis a partir da raiz
 */
bool ehArvoreEnraizada(VERTICE *g) {
    int raiz = -1;
    int contRaiz = 0;

    // Identifica a raiz como o vértice com grau de entrada 0
    for (int i = 1; i <= V; i++) {
        if (grauEntrada(g, i) == 0) {
            raiz = i;
            contRaiz++;
        }
    }

    if (contRaiz != 1) return false; // deve haver exatamente uma raiz

    zerarFlags(g); // prepara flags para DFS

    if (!profundidadeComCiclo(g, raiz)) return false; // detecta ciclos

    // Verifica se todos os vértices foram visitados (conexidade)
    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) return false;
    }

    return true;
}

/*********************************************/
/*         DEFINIÇÃO DAS FUNÇÕES AUXILIARES  */
/*********************************************/

/* Inicializa a estrutura de vértices */
void inicializar(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
    }
}

/* Insere uma aresta direcionada i → j */
bool inserirAresta(VERTICE *g, int i, int j) {
    NO *novo = malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
    return true;
}

/* Reinicia o vetor de flags para nova DFS */
void zerarFlags(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].flag = 0;
    }
}

/*
 * Calcula o grau de entrada de um vértice i,
 * percorrendo todas as listas de adjacência do grafo.
 */
int grauEntrada(VERTICE *g, int i) {
    int resp = 0;
    for (int j = 1; j <= V; j++) {
        NO *p = g[j].inicio;
        while (p) {
            if (p->adj == i) resp++;
            p = p->prox;
        }
    }
    return resp;
}

/* Exibe o resultado da verificação */
void exibirResultado(bool resultado) {
    if (resultado)
        printf("É uma árvore enraizada.\n");
    else
        printf("NÃO é uma árvore enraizada.\n");
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

/*********************************************/
/*                  MAIN                     */
/*********************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializar(grafo);

    // TESTE 1 — árvore válida
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 2, 5);
    printf("Teste 1 (grafo válido):\n");    
    exibirGrafo(grafo);
    exibirResultado(ehArvoreEnraizada(grafo));

    // TESTE 2 — contém ciclo: 2 → 3 → 4 → 2
    inicializar(grafo);
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 3);
    inserirAresta(grafo, 3, 4);
    inserirAresta(grafo, 4, 2);  // ciclo
    printf("\nTeste 2 (com ciclo):\n");  
    exibirGrafo(grafo);  
    exibirResultado(ehArvoreEnraizada(grafo));

    // TESTE 3 — mais de uma raiz (2 e 3 sem entrada)
    inicializar(grafo);
    inserirAresta(grafo, 2, 1);
    inserirAresta(grafo, 3, 4);
    inserirAresta(grafo, 3, 5);
    printf("\nTeste 3 (múltiplas raízes):\n");
    exibirGrafo(grafo);
    exibirResultado(ehArvoreEnraizada(grafo));

    return 0;
}

