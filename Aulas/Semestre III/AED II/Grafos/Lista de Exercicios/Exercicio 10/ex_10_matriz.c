/************************************************************************************************/
/* Enunciado: Considere um grafo dirigido representando uma rede de e-mails.                   */
/* Cada vértice é um usuário, e cada aresta representa um e-mail enviado com campo `id`.        */
/* Uma mensagem `x` é considerada spam. Um usuário é suspeito se:                               */
/* - Ele enviou a mensagem `x`,                                                                 */
/* - Mas nunca a recebeu de ninguém.                                                            */
/************************************************************************************************/

#include <stdio.h>
#include <string.h>

#define V 5

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int id[V + 1][V + 1];  // id[i][j] = id da mensagem enviada de i para j
} GRAFO;

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            g->id[i][j] = 0;
}

void inserirAresta(GRAFO *g, int i, int j, int idMsg) {
    g->id[i][j] = idMsg;
}

void exibirMatriz(GRAFO *g) {
    printf("Matriz de mensagens (id):\n");
    printf("    ");
    for (int j = 1; j <= V; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 1; i <= V; i++) {
        printf("%2d: ", i);
        for (int j = 1; j <= V; j++) {
            printf("%2d ", g->id[i][j]);
        }
        printf("\n");
    }
}

/**************************************/
/*    FUNÇÃO PRINCIPAL DO PROBLEMA    */
/**************************************/

void usuariosSuspeitos(GRAFO *g, int x) {
    int recebeu[V + 1] = {0};  // marca quem recebeu a mensagem x

    // Etapa 1: marcar quem recebeu a mensagem x
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            if (g->id[i][j] == x) {
                recebeu[j] = 1;
            }
        }
    }

    // Etapa 2: verificar quem enviou a mensagem x mas não recebeu
    printf("Usuários suspeitos (mensagem x = %d):\n", x);
    for (int i = 1; i <= V; i++) {
        int enviou = 0;
        for (int j = 1; j <= V; j++) {
            if (g->id[i][j] == x) {
                enviou = 1;
                break;
            }
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
    GRAFO grafo;

    // EXEMPLO 1
    printf("=== EXEMPLO 1 ===\n");
    inicializarGrafo(&grafo);

    inserirAresta(&grafo, 1, 2, 10);  // 1 envia x=10 para 2
    inserirAresta(&grafo, 2, 3, 10);  // 2 envia x=10 para 3
    inserirAresta(&grafo, 3, 4, 20);  // 3 envia outra mensagem

    exibirMatriz(&grafo);
    usuariosSuspeitos(&grafo, 10);
    printf("\n");

    // EXEMPLO 2
    printf("=== EXEMPLO 2 ===\n");
    inicializarGrafo(&grafo);

    inserirAresta(&grafo, 1, 2, 99);  // 1 envia spam
    inserirAresta(&grafo, 3, 2, 99);  // 3 envia spam
    inserirAresta(&grafo, 4, 5, 42);  // outra mensagem

    exibirMatriz(&grafo);
    usuariosSuspeitos(&grafo, 99);

    return 0;
}
