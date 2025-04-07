#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define TAM 100

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];  // valor = código da companhia ou 0 (sem voo)
    int flag[V + 1];           // marcação de visitado
    int via[V + 1];            // vértice anterior no caminho
} GRAFO;

/**************************************/
/*         LISTA LIGADA DE RESULTADO  */
/**************************************/

typedef struct lista {
    int cidade;
    struct lista *prox;
} LISTA;

/**************************************/
/*              FILA BFS              */
/**************************************/

typedef struct {
    int dados[TAM];
    int ini, fim;
} FILA;

void inicializaFila(FILA *f) {
    f->ini = f->fim = 0;
}

bool filaVazia(FILA *f) {
    return f->ini == f->fim;
}

bool entrarFila(FILA *f, int v) {
    if ((f->fim + 1) % TAM == f->ini) return false;
    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % TAM;
    return true;
}

int sairFila(FILA *f) {
    if (filaVazia(f)) return -1;
    int v = f->dados[f->ini];
    f->ini = (f->ini + 1) % TAM;
    return v;
}

/**************************************/
/*         FUNÇÕES DO GRAFO           */
/**************************************/

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
        g->via[i] = -1;
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

void zerarFlags(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
        g->via[i] = -1;
    }
}

void inserirVoo(GRAFO *g, int i, int j, int companhia) {
    g->matriz[i][j] = companhia;
    g->matriz[j][i] = companhia;  // não-dirigido
}

LISTA *inserirLista(LISTA *lista, int cidade) {
    LISTA *novo = malloc(sizeof(LISTA));
    novo->cidade = cidade;
    novo->prox = lista;
    return novo;
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

LISTA *menorTrajeto(GRAFO *g, int a, int b, int c) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g);

    g->flag[a] = 1;
    entrarFila(f, a);

    while (!filaVazia(f)) {
        int atual = sairFila(f);

        for (int j = 1; j <= V; j++) {
            if (g->matriz[atual][j] == c && g->flag[j] == 0) {
                g->flag[j] = 1;
                g->via[j] = atual;
                entrarFila(f, j);
                if (j == b) break;
            }
        }
    }

    free(f);

    // Se destino não foi alcançado
    if (g->flag[b] == 0) return NULL;

    // Reconstruir caminho
    LISTA *caminho = NULL;
    int atual = b;
    while (atual != -1) {
        caminho = inserirLista(caminho, atual);
        atual = g->via[atual];
    }

    return caminho;
}

void exibirCaminho(LISTA *caminho) {
    if (!caminho) {
        printf("❌ Nenhum trajeto possível com a companhia informada.\n");
        return;
    }

    printf("🛫 Caminho com menor número de conexões:\n");
    while (caminho) {
        printf("-> Cidade %d ", caminho->cidade);
        caminho = caminho->prox;
    }
    printf("\n");
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO g;
    inicializarGrafo(&g);

    // companhias: 1 = AZUL, 2 = GOL, 3 = LATAM
    inserirVoo(&g, 1, 2, 1);
    inserirVoo(&g, 2, 3, 1);
    inserirVoo(&g, 1, 4, 2);
    inserirVoo(&g, 4, 5, 2);
    inserirVoo(&g, 5, 3, 2);
    inserirVoo(&g, 2, 6, 3);

    int origem = 1;
    int destino = 3;
    int companhia = 1;

    exibirMatriz(&g);

    LISTA *trajeto = menorTrajeto(&g, origem, destino, companhia);
    exibirCaminho(trajeto);

    return 0;
}
