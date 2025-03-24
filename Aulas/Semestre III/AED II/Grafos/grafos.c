#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5 // Número máximo de vértices

// -----------------------------
// ESTRUTURAS DE FILA (DINÂMICA)
// -----------------------------

// Nó da fila
typedef struct No {
    int dado;
    struct No *prox;
} NO_FILA;

// Estrutura da fila com ponteiros para início e fim
typedef struct {
    NO_FILA *inicio;
    NO_FILA *fim;
} FILA;

// Inicializa a fila vazia
void inicializaFila(FILA *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Verifica se a fila está vazia
int filaVazia(FILA *f) {
    return f->inicio == NULL;
}

// Insere elemento no final da fila
void entrarFila(FILA *f, int valor) {
    NO_FILA *novo = (NO_FILA *) malloc(sizeof(NO_FILA));
    if (novo == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }
    novo->dado = valor;
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;

    printf("Elemento %d enfileirado.\n", valor);
}

// Remove elemento do início da fila e retorna seu valor
int sairFila(FILA *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Não é possível desenfileirar.\n");
        return -1;
    }

    NO_FILA *remover = f->inicio;
    int valor = remover->dado;
    f->inicio = remover->prox;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(remover);
    printf("Elemento %d desenfileirado.\n", valor);
    return valor;
}

// -----------------------------
// ESTRUTURAS DE GRAFO (LISTA)
// -----------------------------

// Nó da lista de adjacência
typedef struct s {
    struct s *prox;
    int adj;
} NO;

// Estrutura de vértice: lista de adjacência + flags
typedef struct {
    NO *inicio; // início da lista de adjacência
    int flag;   // usado para marcações de busca
    int via;    // usado para reconstruir o menor caminho
} VERTICE;

// Inicializa o grafo com todas as listas vazias
void inicializar(VERTICE *g){
    for (int i = 1; i <= V; i++){
        g[i].inicio = NULL;
    }
}

// Verifica se uma aresta i -> j existe e retorna ponteiro para o nó
NO *arestaExiste(VERTICE *g, int i, int j, NO **ant){
    *ant = NULL;
    NO *p = g[i].inicio;

    while(p){
        if (p->adj == j) return p;
        *ant = p;
        p = p->prox;
    }

    return NULL;
}

// Insere aresta direcionada i -> j (se ainda não existir)
bool inserirAresta(VERTICE *g, int i, int j){
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if (atual) return false; // já existe

    NO *novo = (NO*)malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;

    return true;
}

// Remove aresta i -> j (se existir)
bool excluirAresta(VERTICE *g, int i, int j){
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if (!atual) return false; // não existe

    if (ant) ant->prox = atual->prox;
    else g[i].inicio = atual->prox;

    free(atual);
    return true;
}

// Retorna o grau de saída (quantidade de arestas que saem do vértice i)
int grauSaida(VERTICE *g, int i){
    int resp = 0;
    NO *p = g[i].inicio;
    while(p){
        resp++;
        p = p->prox;
    }
    return resp;
}

// Retorna o grau de entrada (quantas arestas chegam ao vértice i)
int grauEntrada(VERTICE *g, int i){
    int resp = 0;
    for (int j = 1; j <= V; j++){
        NO *p = g[j].inicio;
        while(p){
            if (p->adj == i) resp++;
            p = p->prox;
        }
    }
    return resp;
}

// Cria uma cópia profunda do grafo original
VERTICE *copiarGrafo(VERTICE *g){
    VERTICE *h = (VERTICE*)malloc(sizeof(VERTICE) * (V+1));
    for (int i = 1; i <= V; i++){
        NO *p = g[i].inicio;
        h[i].inicio = NULL;
        while(p){
            NO *novo = (NO*)malloc(sizeof(NO));
            novo->adj = p->adj;
            novo->prox = h[i].inicio;
            h[i].inicio = novo;
            p = p->prox;
        }
    }
    return h;
}

// Reseta os flags dos vértices para 0
void zerarFlags(VERTICE *g){
    for (int i = 1; i <= V; i++){
        g[i].flag = 0;
    }
}

// Busca em profundidade (DFS) recursiva
void profundidade(VERTICE *g, int i){
    g[i].flag = 1;
    NO *p = g[i].inicio;

    while(p){
        if (g[p->adj].flag == 0) { 
            profundidade(g, p->adj);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

// Busca em largura (BFS) a partir de vértice i
void largura(VERTICE *g, int i){
    zerarFlags(g);
    FILA *f = (FILA*)malloc(sizeof(FILA));
    inicializaFila(f);

    entrarFila(f, i);
    g[i].flag = 1;

    while(!filaVazia(f)){
        i = sairFila(f);
        g[i].flag = 2;

        NO *p = g[i].inicio;
        while(p){
            if (g[p->adj].flag == 0) {
                entrarFila(f, p->adj);
                g[p->adj].flag = 1;
            }
            p = p->prox;
        }
    }

    free(f);
}

// Busca o menor caminho (em arestas) de origem até destino via BFS
void buscaMenorCaminho(VERTICE *g, int origem, int destino) {
    zerarFlags(g);
    for (int j = 1; j <= V; j++) {
        g[j].via = -1;
    }

    g[origem].via = 0;
    g[origem].flag = 1;

    FILA *f = (FILA*)malloc(sizeof(FILA));
    inicializaFila(f);
    entrarFila(f, origem);

    while(!filaVazia(f)){
        int atual = sairFila(f);
        g[atual].flag = 2;

        NO *p = g[atual].inicio;
        while(p){
            if (g[p->adj].flag == 0) {
                g[p->adj].flag = 1;
                entrarFila(f, p->adj);
                g[p->adj].via = atual;
            }
            p = p->prox;
        }
    }

    // Impressão do caminho reconstruído
    printf("\nMenor caminho de %d até %d:\n", origem, destino);

    if (g[destino].via == -1 && origem != destino) {
        printf("Não existe caminho de %d até %d.\n", origem, destino);
    } else {
        int caminho[V + 1];
        int tam = 0;
        int atual = destino;

        while (atual != 0) {
            caminho[tam++] = atual;
            if (atual == origem) break;
            atual = g[atual].via;
        }

        if (caminho[tam - 1] != origem) {
            printf("Não existe caminho de %d até %d.\n", origem, destino);
        } else {
            for (int i = tam - 1; i >= 0; i--) {
                printf("%d", caminho[i]);
                if (i > 0) printf(" -> ");
            }
            printf("\n");
        }
    }

    free(f);
}

// Exibe o grafo em formato de listas de adjacência
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

// -----------------------------
// Função principal de testes
// -----------------------------
int main() {
    VERTICE g[V + 1];
    inicializar(g);

    // ----------------------------
    // Teste 1: Grau, remoção, DFS
    // ----------------------------
    /*
    // Criação de um grafo com ciclo: 1 → 2, 1 → 3, 2 → 4, 3 → 4, 4 → 5, 5 → 1
    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 4);
    inserirAresta(g, 4, 5);
    inserirAresta(g, 5, 1);

    printf("Representacao do Grafo:\n");
    exibirGrafo(g);

    printf("\nTestando grau de saída e entrada:\n");
    for (int i = 1; i <= V; i++) {
        printf("Vértice %d - Grau de saída: %d, Grau de entrada: %d\n", i, grauSaida(g, i), grauEntrada(g, i));
    }

    printf("\nTestando remoção de aresta 1 -> 2:\n");
    excluirAresta(g, 1, 2);
    exibirGrafo(g);

    printf("\nTestando busca em profundidade a partir do vértice 1:\n");
    zerarFlags(g);
    profundidade(g, 1);
    for (int i = 1; i <= V; i++) {
        printf("Vértice %d - Flag: %d\n", i, g[i].flag);
    }
    */

    // ----------------------------
    // Teste 2: BFS e menor caminho
    // ----------------------------

    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 4);
    inserirAresta(g, 4, 5);

    printf("Grafo:\n");
    exibirGrafo(g);

    printf("\nBusca em Largura a partir do vértice 1:\n");
    largura(g, 1);
    for (int i = 1; i <= V; i++) {
        printf("Vértice %d: flag = %d\n", i, g[i].flag);
    }

    printf("\nBusca do Menor Caminho (via BFS) de 1 até 5:\n");
    buscaMenorCaminho(g, 1, 5);
    for (int i = 1; i <= V; i++) {
        printf("Vértice %d veio de %d\n", i, g[i].via);
    }

    return 0;
}
