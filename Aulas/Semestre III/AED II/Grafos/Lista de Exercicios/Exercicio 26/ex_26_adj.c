#include <stdio.h>
#include <stdlib.h>

#define V 5

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct no {
    int adj;
    int contador; // número de mensagens
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
} VERTICE;

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

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
    }
}

// Insere aresta dirigida i -> j com contador (mensagens)
void inserirAresta(VERTICE *g, int i, int j, int mensagens) {
    NO *novo = malloc(sizeof(NO));
    novo->adj = j;
    novo->contador = mensagens;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
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
/*     FUNÇÃO PRINCIPAL DO PROBLEMA   */
/**************************************/

RESULTADO *usuariosRelacionados(VERTICE *g, int i, int k) {
    RESULTADO *lista = NULL;

    // Parte 1: mensagens enviadas por i
    NO *p = g[i].inicio;
    while (p) {
        if (p->contador >= k) {
            lista = inserirResultado(lista, p->adj);
        }
        p = p->prox;
    }

    // Parte 2: mensagens recebidas por i
    for (int j = 1; j <= V; j++) {
        if (j == i) continue;

        NO *q = g[j].inicio;
        while (q) {
            if (q->adj == i && q->contador >= k) {
                lista = inserirResultado(lista, j);
                break; // evita duplicatas
            }
            q = q->prox;
        }
    }

    return lista;
}

/**************************************/
/*               MAIN                 */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // Arestas com número de mensagens trocadas
    inserirAresta(grafo, 1, 2, 5);  // 1 → 2 (5 msgs)
    inserirAresta(grafo, 2, 1, 3);  // 2 → 1 (3 msgs)
    inserirAresta(grafo, 1, 3, 2);  // 1 → 3 (2 msgs)
    inserirAresta(grafo, 4, 1, 6);  // 4 → 1 (6 msgs)
    inserirAresta(grafo, 1, 5, 1);  // 1 → 5 (1 msg)

    int usuario = 1;
    int k = 3;

    exibirGrafo(grafo);

    printf("🔎 Verificando usuários com pelo menos %d mensagens trocadas com %d...\n", k, usuario);
    RESULTADO *res = usuariosRelacionados(grafo, usuario, k);
    exibirResultado(res);

    // Libera a lista
    while (res) {
        RESULTADO *tmp = res;
        res = res->prox;
        free(tmp);
    }

    return 0;
}


