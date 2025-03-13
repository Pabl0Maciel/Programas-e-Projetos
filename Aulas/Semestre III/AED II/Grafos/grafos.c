#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

typedef struct s {
    
    struct s *prox;
    int adj;
}NO;

typedef struct {
    
    NO *inicio;
    int flag;
}VERTICE;

void inicializar(VERTICE *g){
    
    for (int i = 1; i <= V; i++){
        
        g[i].inicio = NULL;
    }
}

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

bool inserirAresta(VERTICE *g, int i, int j){

    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);

    if (atual) return false; // ja existe

    NO *novo = (NO*)malloc(sizeof(NO));

    novo->adj = j;
    novo->prox = g[i].inicio;

    g[i].inicio = novo;

    return true;
}

bool excluirAresta(VERTICE *g, int i, int j){

    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);

    if (!atual) return false; // nao existe

    if (ant) ant->prox = atual->prox;
    else g[i].inicio = atual->prox;

    free(atual);

    return true;
}

int grauSaida(VERTICE *g, int i){
    
    int resp = 0;
    NO *p = g[i].inicio;

    while(p){
        
        resp++;
        p = p->prox;
    }
    
    return resp;
}

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

void zerarFlags(VERTICE *g){
    
    for (int i = 1; i <= V; i++){
        
        g[i].flag = 0;
    }
}

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

int main() {
    VERTICE grafo[V + 1];
    inicializar(grafo);
    
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 3, 4);
    inserirAresta(grafo, 4, 5);
    inserirAresta(grafo, 5, 1);
    
    printf("Representacao do Grafo:\n");
    exibirGrafo(grafo);

    printf("\nTestando grau de saída e entrada:\n");
    for (int i = 1; i <= V; i++) {
        printf("Vértice %d - Grau de saída: %d, Grau de entrada: %d\n", i, grauSaida(grafo, i), grauEntrada(grafo, i));
    }
    
    printf("\nTestando remoção de aresta 1 -> 2:\n");
    excluirAresta(grafo, 1, 2);
    exibirGrafo(grafo);
    
    printf("\nTestando busca em profundidade a partir do vértice 1:\n");
    zerarFlags(grafo);
    profundidade(grafo, 1);
    for (int i = 1; i <= V; i++) {
        printf("Vértice %d - Flag: %d\n", i, grafo[i].flag);
    }
    
    return 0;
}