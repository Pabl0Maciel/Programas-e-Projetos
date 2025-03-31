/************************************************************************************************/
/* Enunciado: Considere um grafo dirigido representando uma rede de e-mails.                   */
/* Cada vértice é um usuário, e cada aresta representa um e-mail enviado com campo `id`.        */
/* Uma mensagem `x` é considerada spam. Um usuário é suspeito se:                               */
/* - Ele enviou a mensagem `x`,                                                                 */
/* - Mas nunca a recebeu de ninguém.                                                            */
/************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define V 5  // número máximo de vértices

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct no {
    int adj;            // destino da aresta
    int id;             // id da mensagem
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
} VERTICE;

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
    }
}

void inserirAresta(VERTICE *g, int i, int j, int id) {
    NO *novo = malloc(sizeof(NO));
    novo->adj = j;
    novo->id = id;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
}

void exibirGrafo(VERTICE *g) {
    printf("Grafo (rede de emails):\n");
    for (int i = 1; i <= V; i++) {
        printf("%d: ", i);
        NO *p = g[i].inicio;
        while (p) {
            printf("%d(id=%d) -> ", p->adj, p->id);
            p = p->prox;
        }
        printf("NULL\n");
    }
}

/**************************************/
/*    FUNÇÃO PRINCIPAL DO PROBLEMA    */
/**************************************/

void usuariosSuspeitos(VERTICE *g, int x) {
    int recebeu[V + 1] = {0};  // marca quem recebeu a mensagem x

    // Etapa 1: marcar quem recebeu a mensagem x
    for (int i = 1; i <= V; i++) {
        NO *p = g[i].inicio;
        while (p) {
            if (p->id == x) {
                recebeu[p->adj] = 1;
            }
            p = p->prox;
        }
    }

    // Etapa 2: verificar quem enviou x mas não recebeu
    printf("Usuários suspeitos (mensagem x = %d):\n", x);
    for (int i = 1; i <= V; i++) {
        NO *p = g[i].inicio;
        int enviou = 0;

        while (p) {
            if (p->id == x) {
                enviou = 1;
                break;
            }
            p = p->prox;
        }

        if (enviou && recebeu[i] == 0) {
            printf("- Usuário %d\n", i);
        }
    }
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];

    // Exemplo 1: simples propagação
    printf("=== EXEMPLO 1 ===\n");
    inicializarGrafo(grafo);

    inserirAresta(grafo, 1, 2, 10);  // 1 envia x=10 para 2
    inserirAresta(grafo, 2, 3, 10);  // 2 envia x=10 para 3
    inserirAresta(grafo, 3, 4, 20);  // 3 envia outra mensagem

    exibirGrafo(grafo);
    usuariosSuspeitos(grafo, 10);  // x = 10
    printf("\n");

    // Exemplo 2: múltiplos envios, um suspeito
    printf("=== EXEMPLO 2 ===\n");
    inicializarGrafo(grafo);

    inserirAresta(grafo, 1, 2, 99);  // 1 envia spam
    inserirAresta(grafo, 3, 2, 99);  // 3 envia spam
    inserirAresta(grafo, 4, 5, 42);  // 4 envia outra mensagem

    exibirGrafo(grafo);
    usuariosSuspeitos(grafo, 99);  // x = 99

    return 0;
}
