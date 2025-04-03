#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define TAM 100

/**************************************/
/*      ESTRUTURA DO GRAFO + NÓ       */
/**************************************/

typedef struct no {
    int adj;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
    int flag;
    int distancia;
    bool estaOcupada;
} VERTICE;

/**************************************/
/*      ESTRUTURA DA FILA SIMPLES     */
/**************************************/

typedef struct {
    int dados[TAM];
    int ini, fim;
} FILA;

void inicializaFila(FILA *f) { f->ini = f->fim = 0; }

bool filaVazia(FILA *f) { return f->ini == f->fim; }

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
/*     LISTA LIGADA DE RESULTADOS     */
/**************************************/

typedef struct resultado {
    int sala;
    struct resultado *prox;
} RESULTADO;

RESULTADO* inserirResultado(RESULTADO *lista, int sala) {
    RESULTADO *novo = malloc(sizeof(RESULTADO));
    novo->sala = sala;
    novo->prox = lista;
    return novo;
}

void imprimirResultado(RESULTADO *lista) {
    if (!lista) {
        printf("❌ Nenhuma sala vazia encontrada.\n");
        return;
    }
    printf("\n🔍 Salas vazias mais próximas: ");
    while (lista) {
        printf("%d ", lista->sala);
        lista = lista->prox;
    }
    printf("\n");
}

/**************************************/
/*        FUNÇÕES DO GRAFO            */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].distancia = -1;
        g[i].estaOcupada = true;
    }
}

void zerarFlags(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].flag = 0;
        g[i].distancia = -1;
    }
}

void inserirAresta(VERTICE *g, int i, int j) {
    NO *novo1 = malloc(sizeof(NO));
    novo1->adj = j;
    novo1->prox = g[i].inicio;
    g[i].inicio = novo1;

    NO *novo2 = malloc(sizeof(NO));
    novo2->adj = i;
    novo2->prox = g[j].inicio;
    g[j].inicio = novo2;
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
/* BUSCA EM LARGURA COM EMPATE        */
/**************************************/

RESULTADO* salasVaziasMaisProximas(VERTICE *g, int origem) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g);

    RESULTADO *res = NULL;
    int menorDist = -1;

    entrarFila(f, origem);
    g[origem].flag = 1;
    g[origem].distancia = 0;

    while (!filaVazia(f)) {
        int atual = sairFila(f);
        NO *p = g[atual].inicio;

        while (p) {
            int v = p->adj;

            if (g[v].flag == 0) {
                g[v].flag = 1;
                g[v].distancia = g[atual].distancia + 1;

                // Se a sala está vazia
                if (!g[v].estaOcupada) {
                    if (menorDist == -1 || g[v].distancia == menorDist) {
                        menorDist = g[v].distancia;
                        res = inserirResultado(res, v);
                    }
                }

                // Só continua a BFS se ainda não encontrou salas vazias, ou está no mesmo nível
                if (menorDist == -1 || g[v].distancia <= menorDist) {
                    entrarFila(f, v);
                }
            }
            p = p->prox;
        }
    }

    free(f);
    return res;
}

/**************************************/
/*               MAIN                 */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // Conexões entre salas
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 3, 5);
    inserirAresta(grafo, 3, 6);

    // Marcar salas 5 e 6 como vazias
    grafo[5].estaOcupada = false;
    grafo[6].estaOcupada = false;

    exibirGrafo(grafo);

    printf("📍 Sala inicial: 1\n");
    RESULTADO *lista = salasVaziasMaisProximas(grafo, 1);
    imprimirResultado(lista);

    // Liberar a lista ligada
    while (lista) {
        RESULTADO *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }

    return 0;
}
