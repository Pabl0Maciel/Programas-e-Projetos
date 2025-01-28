#include<stdlib.h>
#include<stdio.h>


typedef struct {
	int* elementos;
	int n;
} MATRIZ_CIRCULANTE;

void inicializar_matriz(MATRIZ_CIRCULANTE *matriz, int ordem) {
	matriz->n = ordem;
	matriz->elementos = malloc (ordem * sizeof(int));
}

int calc_pos(int l, int c, int n) {
  int pos = (l-1) * n + (c-1);
  return pos;
}

int acessar_matriz(MATRIZ_CIRCULANTE *matriz, int l, int c, int *v) {
	if (l <= 0 || l > matriz->n || c <= 0 || c > matriz->n) {
		return -1;
	}

	*v = matriz->elementos[calc_pos(l,c,matriz->n)];
	
	return 0;
}

int atribuir_matriz(MATRIZ_CIRCULANTE *matriz, int l, int c, int v) {
	if (l != 1 || c <= 0 || c > matriz->n) {
		return -1;
	}
	
	matriz->elementos[c-1] = v;
	
	return 0;
}

int gera_matriz_ciclica(MATRIZ_CIRCULANTE *matriz, int **matriz_circulante){
    int n = matriz -> n;
    
    for (int c = 0; c < n; c++){
        matriz_circulante[0][c] = matriz -> elementos[c];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz_circulante[i][j] = matriz -> elementos[(j - i + n) % n];
        }
    }
    return 0;
}

int gera_matriz_ciclica_negativa(MATRIZ_CIRCULANTE *matriz, int **matriz_circulante_negativa){
    int n = matriz -> n;
    
    for (int c = 0; c < n; c++){
        matriz_circulante_negativa[0][c] = matriz -> elementos[c];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int pos_rotacionada = (j - i + n) % n;
            int valor = matriz->elementos[pos_rotacionada];

            // Invertemos os elementos que vêm antes da rotação
            if (j < i) {
                valor *= -1;
            }

            matriz_circulante_negativa[i][j] = valor;
        }
    }
    return 0;
}

void exibir_MatrizCirculante(int **matriz, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%4d ", matriz[i][j]);	
		}
		printf("\n");
	}
}

int main () {

	MATRIZ_CIRCULANTE matriz;
	inicializar_matriz(&matriz, 4);

	int **matriz_circulante = malloc(matriz.n * sizeof(int *));
    for (int i = 0; i < matriz.n; i++) {
        matriz_circulante[i] = malloc(matriz.n * sizeof(int));
    }

    int **matriz_circulante_negativa = malloc(matriz.n * sizeof(int *));
    for (int i = 0; i < matriz.n; i++) {
        matriz_circulante_negativa[i] = malloc(matriz.n * sizeof(int));
    }

	int i = 1;
        for (int j = 1; j <= matriz.n; j++) {
                int valor = random()%100;
                printf("Atribuindo valor %d na posição (%d, %d)\n", valor, i, j);
                int deucerto = atribuir_matriz(&matriz, i, j, valor);
                if (deucerto == -1)
                        printf("Nao foi possivel atribuir em (%d, %d)\n", i ,j);
        }
	printf("\n");

    gera_matriz_ciclica(&matriz, matriz_circulante);
	exibir_MatrizCirculante(matriz_circulante, matriz.n);
	printf("\n");

	gera_matriz_ciclica_negativa(&matriz, matriz_circulante_negativa);
    exibir_MatrizCirculante(matriz_circulante_negativa, matriz.n);
	
	return 0;

}