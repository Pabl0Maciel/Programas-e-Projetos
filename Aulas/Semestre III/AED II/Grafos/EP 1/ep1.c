//------------------------------------------------------------------------------------------------
// COLOQUE OS NOMES DOS RESPONSÁVEIS AQUI: Pablo Caballero Maciel E Pedro Henrique Teixeira Soares
//------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

// INFORME O NRO DO GRUPO CONFORME PLANILHA DIVULGADA
int grupo() {
    return 6;
}

int nroUSP1() {
    return 14778630;
}

int nroUSP2() {
    return 15484158;
}

// -----------------------------
// ESTRUTURAS DE FILA (DINÂMICA)
// -----------------------------

typedef struct No {
    int dado;
    struct No *prox;
} NO_FILA;

typedef struct {
    NO_FILA *inicio;
    NO_FILA *fim;
} FILA;

void inicializaFila(FILA *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int filaVazia(FILA *f) {
    return f->inicio == NULL;
}

void entrarFila(FILA *f, int valor) {
    NO_FILA *novo = (NO_FILA *) malloc(sizeof(NO_FILA));
    if (novo == NULL) return;
    novo->dado = valor;
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

int sairFila(FILA *f) {
    if (filaVazia(f)) return -1;

    NO_FILA *remover = f->inicio;
    int valor = remover->dado;
    f->inicio = remover->prox;
    if (f->inicio == NULL) f->fim = NULL;
    free(remover);
    return valor;
}

// -------------------
// ESTRUTURAS DE GRAFO 
// -------------------

typedef struct estr {
    int adj;
    struct estr *prox;
} NO;

typedef struct {
    NO *inicio;
    int flag;
    int via;
} VERTICE;

void inicializarGrafo(VERTICE *g, int V){
    for (int i = 1; i <= V; i++){
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].via = -1;
    }
}

void zerarFlags(VERTICE *g, int V) {
    for (int i = 1; i <= V; i++) {
        g[i].flag = 0;
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

bool arestaExiste(VERTICE *g, int i, int j) {
    NO *p = g[i].inicio;
    while (p) {
        if (p->adj == j) return true;
        p = p->prox;
    }
    return false;
}

void caminhosMaisCurtos(VERTICE *g, int origem, int *dist, int V) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g, V);

    for (int i = 1; i <= V; i++)
        dist[i] = -1;

    entrarFila(f, origem);
    g[origem].flag = 1;
    dist[origem] = 0;

    while (!filaVazia(f)) {
        int atual = sairFila(f);
        NO *p = g[atual].inicio;

        while (p) {
            int v = p->adj;
            if (g[v].flag == 0) {
                g[v].flag = 1;
                dist[v] = dist[atual] + 1;
                entrarFila(f, v);
            }
            p = p->prox;
        }
    }

    free(f);
}

void liberarLista(NO* l) {
    while (l) {
        NO* temp = l;
        l = l->prox;
        free(temp);
    }
}
// --------------------------
// FUNÇÃO PRINCIPAL
// --------------------------

NO *equidistantes(int V, int A, int ij[], int v1, int v2){
    if (V <= 0 || A < 0 || ij == NULL || v1 < 1 || v1 > V || v2 < 1 || v2 > V)
    return NULL;
    
    NO* resp = NULL;
    VERTICE *g = malloc((V+1) * sizeof(VERTICE));
    inicializarGrafo(g, V);

    for (int i = 0; i < 2*A; i += 2){
        if (arestaExiste(g, ij[i], ij[i+1])) continue;
        inserirAresta(g, ij[i], ij[i+1]);
    }

    int *dist1 = malloc((V+1) * sizeof(int));
    int *dist2 = malloc((V+1) * sizeof(int));

    caminhosMaisCurtos(g, v1, dist1, V);
    caminhosMaisCurtos(g, v2, dist2, V);

    for (int i = 1; i <= V; i++) {
        if (i != v1 && i != v2 && dist1[i] != -1 && dist1[i] == dist2[i]) {
            NO *novo = malloc(sizeof(NO));
            novo->adj = i;
            novo->prox = resp;
            resp = novo;
        }
    }

    free(dist1);
    free(dist2);
    free(g);

    return resp;
}

// --------------------------
// MAIN DE TESTES
// --------------------------

int main() {
    printf("\n===== TESTE 1: Tres vértices equidistantes =====\n");
    int ij1[] = {1, 2, 2, 3, 2, 4, 4, 5};
    NO* r1 = equidistantes(5, 4, ij1, 1, 3);
    for (NO* p = r1; p != NULL; p = p->prox)
        printf("Equidistante: %d\n", p->adj);
    liberarLista(r1);
    printf("------------------------------------------\n");

    printf("\n===== TESTE 2: Dois vértices equidistantes =====\n");
    int ij2[] = {1, 2, 2, 3, 2, 4, 4, 5, 3, 6, 6, 5};
    NO* r2 = equidistantes(6, 6, ij2, 1, 3);
    for (NO* p = r2; p != NULL; p = p->prox)
        printf("Equidistante: %d\n", p->adj);
    liberarLista(r2);
    printf("------------------------------------------\n");

    printf("\n===== TESTE 3: Um vértice equidistante =====\n");
    int ij3[] = {1, 2, 2, 3};
    NO* r3 = equidistantes(3, 2, ij3, 1, 3);
    if (!r3) printf("Lista vazia (NULL)\n");
    else for (NO* p = r3; p != NULL; p = p->prox)
        printf("Equidistante: %d\n", p->adj);
    liberarLista(r3);
    printf("------------------------------------------\n");

    printf("\n===== TESTE 4: Grafo desconexo =====\n");
    int ij4[] = {1, 2, 3, 4};
    NO* r4 = equidistantes(4, 2, ij4, 1, 3);
    if (!r4) printf("Lista vazia (NULL)\n");
    else for (NO* p = r4; p != NULL; p = p->prox)
        printf("Equidistante: %d\n", p->adj);
    liberarLista(r4);
    printf("------------------------------------------\n");

    printf("\n===== TESTE 5: Grafo mínimo =====\n");
    int ij5[] = {1, 2};
    NO* r5 = equidistantes(2, 1, ij5, 1, 2);
    if (!r5) printf("Lista vazia (NULL)\n");
    else for (NO* p = r5; p != NULL; p = p->prox)
        printf("Equidistante: %d\n", p->adj);
    liberarLista(r5);
    printf("------------------------------------------\n");

    printf("\n===== TESTE 6: Grafo com ciclo =====\n");
    int ij6[] = {1, 2, 2, 3, 3, 4, 4, 1};
    NO* r6 = equidistantes(4, 4, ij6, 1, 3);
    for (NO* p = r6; p != NULL; p = p->prox)
        printf("Equidistante: %d\n", p->adj);
    liberarLista(r6);
    printf("------------------------------------------\n");

    printf("\n===== TESTE 7: Grafo grande com múltiplos caminhos =====\n");
    int ij7[] = {1,2, 1,3, 2,4, 3,4, 4,5, 5,6, 6,7, 5,7, 3,6};
    NO* r7 = equidistantes(7, 9, ij7, 1, 7);
    for (NO* p = r7; p != NULL; p = p->prox)
        printf("Equidistante: %d\n", p->adj);
    liberarLista(r7);
    printf("------------------------------------------\n");

    printf("\n===== TESTE 8: Grafo nulo =====\n");
    int* ij8 = NULL;
    NO* r8 = equidistantes(0, 0, ij8, 1, 1);
    if (!r8) printf("Lista vazia (NULL)\n");
    liberarLista(r8);
    printf("------------------------------------------\n");

    printf("\n===== TESTE 9: Grafo com vértices isolados (sem arestas) =====\n");
    int ij9[] = {}; // vetor vazio
    NO* r9 = equidistantes(5, 0, ij9, 1, 2);
    if (!r9) printf("Lista vazia (NULL)\n");
    liberarLista(r9);
    printf("------------------------------------------\n");

    printf("\n===== TESTE 10: Vértice fora do intervalo =====\n");
    int ij10[] = {1, 2, 2, 3};
    NO* r10 = equidistantes(3, 2, ij10, 1, 10); // v2 está fora do grafo
    if (!r10) printf("Lista vazia (NULL)\n");
    liberarLista(r10);
    printf("------------------------------------------\n");


    return 0;
}
