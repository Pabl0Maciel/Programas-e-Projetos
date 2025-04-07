#include <stdio.h>
#include <stdlib.h>

#define V 5

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];  // matriz[i][j] = mensagens enviadas de i para j
} GRAFO;

/**************************************/
/*     LISTA LIGADA DE RESULTADO      */
/**************************************/

typedef struct resultado {
    int usuario;
    struct resultado *prox;
} RESULTADO;

RESULTADO *inserirResultado(RESULTADO *lista, int usuario) {
    RESULTADO *novo = malloc(sizeof(RESULTADO));
    novo->usuario = usuario;
    novo->prox = lista;
    return novo;
}

void exibirResultado(RESULTADO *lista) {
    if (!lista) {
        printf("❌ Nenhum usuário encontrado com esse critério.\n");
        return;
    }
    printf("📬 Usuários relacionados com pelo menos K mensagens:\n");
    while (lista) {
        printf("- Usuário %d\n", lista->usuario);
        lista = lista->prox;
    }
}

/**************************************/
/*        FUNÇÕES DO GRAFO            */
/**************************************/

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            g->matriz[i][j] = 0;
}

void inserirAresta(GRAFO *g, int i, int j, int mensagens) {
    g->matriz[i][j] = mensagens;
}

void exibirMatriz(GRAFO *g) {
    printf("\nMatriz de adjacência:\n    ");
    for (int j = 1; j <= V; j++) printf("%2d ", j);
    printf("\n");
    for (int i = 1; i <= V; i++) {
        printf("%2d: ", i);
        for (int j = 1; j <= V; j++) {
            printf("%2d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

/**************************************/
/*     FUNÇÃO PRINCIPAL DO PROBLEMA   */
/**************************************/

RESULTADO *usuariosRelacionados(GRAFO *g, int i, int k) {
    RESULTADO *lista = NULL;

    // Parte 1: mensagens enviadas por i
    for (int j = 1; j <= V; j++) {
        if (g->matriz[i][j] >= k)
            lista = inserirResultado(lista, j);
    }

    // Parte 2: mensagens recebidas por i
    for (int j = 1; j <= V; j++) {
        if (j != i && g->matriz[j][i] >= k)
            lista = inserirResultado(lista, j);
    }

    return lista;
}

/**************************************/
/*               MAIN                 */
/**************************************/

int main() {
    GRAFO g;
    inicializarGrafo(&g);

    // Entradas: g.matriz[i][j] = mensagens de i → j
    inserirAresta(&g, 1, 2, 5);  // 1 → 2
    inserirAresta(&g, 2, 1, 3);  // 2 → 1
    inserirAresta(&g, 1, 3, 2);  // 1 → 3
    inserirAresta(&g, 4, 1, 6);  // 4 → 1
    inserirAresta(&g, 1, 5, 1);  // 1 → 5

    int usuario = 1;
    int k = 3;

    exibirMatriz(&g);

    printf("🔎 Verificando usuários com pelo menos %d mensagens trocadas com %d...\n", k, usuario);
    RESULTADO *res = usuariosRelacionados(&g, usuario, k);
    exibirResultado(res);

    // Libera a lista
    while (res) {
        RESULTADO *tmp = res;
        res = res->prox;
        free(tmp);
    }

    return 0;
}
