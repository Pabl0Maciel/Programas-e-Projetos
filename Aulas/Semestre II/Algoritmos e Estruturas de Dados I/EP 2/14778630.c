/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I		            **/
/**   EACH-USP - Segundo Semestre de 2024			                **/
/**								                                    **/
/**   Segundo Exercicio-Programa				                    **/
/**								                                    **/
/**   Pablo Caballero Maciel		 14778630               2024202 **/
/**								                                    **/
/*********************************************************************/

/*
Este codigo eh responsavel pela criacao e administracao de uma Trie (arvore de prefixos). Faz uso de funcoes como Insercao, Busca e Exclusao, bem como outras funcoes auxiliares. Existe uma breve descricao de cada funcao logo acima dela e tambem comentarios explicando trechos de codigos.
*/


#include <stdlib.h>
#include <stdio.h>

#define false 0
#define true 1

#define LETRAS 26

#define VALOR_a 97

typedef int bool;


/*
A estrutura NO foi projetada para armazenar os nos de nossa trie. Ela e composta por dois campos:
  - contador: valor numerico que indica quantas copias da respectiva palavra estao armazenadas;
  - filhos: campo do tipo ponteiro para ponteiros de NOs que tem por objetivo armazenar o endereco do arranjo de filhos do respectivo no ou NULL se o no nao possuir filhos.
*/
typedef struct aux {
	int contador;
	struct aux** filhos;
} NO, * PONT;


/*
Funcao usada em testes da correcao automatica
   NAO APAGAR OU MODIFICAR 
*/
void print123(){

}


/*
Funcao que recebe como parametro o endereco da raiz de uma trie e realiza a inicializacao da estrutura. Isto e, atribui o valor 0 (zero) para o campo contador e o valor NULL para o campo filhos. */
void inicializar(PONT raiz){
	raiz->contador = 0;
	raiz->filhos = NULL;
}

/*
Funcao que aloca memoria para um novo no, inicializa seus campos (valor zero para contador e NULL para filhos) e retorna o endereco do novo no.
*/
PONT criarNo(){
	PONT novo = (PONT)malloc(sizeof(NO));
	novo->contador = 0;
	novo->filhos = NULL;
	return novo;
}


/*
Funcao recursiva que recebe o endereco de um no e retorna o numero de nos da trie a partir do no atual. Se a funcao for chamada a partir da raiz, retornara o numero total de nos na trie.
*/
int contarNos(PONT atual){
	if (!atual) return 0;
	int res = 1;
	int i;
	if (atual->filhos) 
		for (i=0;i<LETRAS;i++)
			if (atual->filhos[i])
				res += contarNos(atual->filhos[i]);
	return res;
}


/*
Funcao recursiva que recebe o endereco de um no e retorna o numero de arranjos de ponteiros para filhos da trie a partir do no atual, ou seja, retorna a quantidade de nos internos (nos que nao sao folha) da trie. Se a funcao for chamada a partir da raiz, retornara o numero total de arranjos na trie.
*/
int contarArranjos(PONT atual){
	if (!atual) return 0;
	int res = 0;
	int i;
	if (atual->filhos){
		//printf("No em endereco: %p\n", (int*)atual);
		res++; 
		for (i=0;i<LETRAS;i++)
			if (atual->filhos[i])
				res += contarArranjos(atual->filhos[i]);
	}
	return res;
}


/*
Funcao recursiva que recebe o endereco de um no e retorna o numero de palavras diferentes da trie a partir do no atual. Palavras diferentes significa que cada palavra sera contada uma unica vez. Se a funcao for chamada a partir da raiz, retornara o numero total de palavras diferentes na trie.
*/
int contarPalavrasDiferentes(PONT atual){
	if (!atual) return 0;
	int res = 0;
	if (atual->contador>0) res = 1;
	int i;
	if (atual->filhos) 
		for (i=0;i<LETRAS;i++)
			if (atual->filhos[i])
				res += contarPalavrasDiferentes(atual->filhos[i]);
	return res;
}



/*
Funcao recursiva que recebe o endereco de um no e retorna o numero de palavras da trie a partir do no atual. Uma palavra sera contada mais de uma vez, caso o campo contador seja maior do que 1. Se a funcao for chamada a partir da raiz, retornara o numero total de palavras na trie.
*/
int contarPalavras(PONT atual){
	if (!atual) return 0;
	int res = atual->contador;
	int i;
	if (atual->filhos) 
		for (i=0;i<LETRAS;i++)
			if (atual->filhos[i])
				res += contarPalavras(atual->filhos[i]);
	return res;
}



/*
Funcao recursiva que recebe o endereco de um no, o endereco de um arranjo de caracteres e a posicao da letra atual da palavra. Caso o no atual corresponda a letra final de uma palavra (contador maior que zero) imprime a palavra atual. Se o no atual possuir filhos, realiza uma chamada recursiva para cada um de seus filhos adicionando a letra correspondente ao seu filho no arranjo palavra.
*/
void exibirAux(PONT atual, char* palavra, int pos){
	if (!atual) return;
	if (atual->contador>0){
		palavra[pos] = '\0';
		printf("%3i %s [%i]\n", atual->contador,palavra, pos);
	}
	int i;
	if (atual->filhos) 
		for (i=0;i<LETRAS;i++)
			if (atual->filhos[i]){
				palavra[pos] = (char)(VALOR_a+i);
				exibirAux(atual->filhos[i], palavra, pos+1);
			}
}



/*
Funcao que recebe o endereco da raiz de uma trie e o endereco de um arranjo de caracteres e imprime na tela, em ordem alfabetica, todas as palavras da trie (utilizando a funcao exibirAux). O arranjo de caracteres, chamado palavra, e usado para  compor cada palavra a partir da raiz e entao imprimir essas palavras.
*/
void exibir(PONT raiz, char* palavra){
	exibirAux(raiz, palavra, 0);
}


// Funcao recursiva que percorre a trie caractere por caractere procurando a palavra, recebe a raiz, o array de caracteres da palavra, o tamanho dela e o caractere atual (comeca em 0).
PONT buscarPalavra_Aux(PONT raiz, char *palavra, int n, int caractere_atual){
	int letra = palavra[caractere_atual] - VALOR_a; // calcula o valor da letra atual segundo a tabela ASCII

	if (raiz == NULL) return NULL; // Se o no for nulo, retorna nulo

	if (n == caractere_atual){ // Se o caractere atual da busca for igual ao tamanho da palavra, quer dizer que encontrou a palavra na trie. Retorna o no.
		return raiz;
	}

	return buscarPalavra_Aux(raiz -> filhos[letra], palavra, n, caractere_atual+1); // Chama a funcao recursivamente para percorrer todos os nos 
																					// existentes daquela palavra.
}

// Funcao que busca a palavra em si. Usa a funcao de buscaPalavra_Aux e retorna o valor do contador daquele no caso tenha encontrado a palavra.
int buscarPalavra(PONT raiz, char* palavra, int n){
  int resposta = 0; // assume que a resposta eh 0, ou seja, que nao encontrou a palavra
  
  PONT achou = buscarPalavra_Aux(raiz, palavra, n, 0); // chama a funcao de buscarPalavra_Aux e atribui o resultado a variavel 'achou'

  if (achou != NULL) { // se 'achou' nao for nulo, atribui o valor de seu contador a variavel 'resposta'
	resposta = achou -> contador;
  }

  return resposta; // retorna a resposta
}


// funcao que insere uma palavra na trie, letra por letra, verificando se ja existe aquela letra ou aquela palavra.
void inserir_Aux(PONT raiz, char *palavra, int n, int caractere_atual){
	int letra = palavra[caractere_atual] - VALOR_a; // calcula a letra atual
	
	if (raiz -> filhos == NULL) { // se o no atual nao tiver um array de filhos, cria ele e inicializa como NULL

        raiz -> filhos = malloc(LETRAS * sizeof(PONT)); // aloca memoria para o arranjo dos filhos

        for (int i = 0; i < LETRAS; i++) { // atribui NULL para cada letra no arranjo dos filhos

            raiz -> filhos[i] = NULL;
        }
    }

	if (raiz -> filhos[letra] == NULL) { // se o array de filhos do no atual nao tiver a letra a ser inserida, cria um no para aquela letra

        raiz -> filhos[letra] = criarNo();
    }

	if (n-1 == caractere_atual){ // se o caractere atual eh o ultimo a ser inserido, aumenta o contador da palavra

		raiz -> filhos[letra] -> contador++;
		return;
	}

	return inserir_Aux(raiz -> filhos[letra], palavra, n, caractere_atual+1);
}

// funcao que usa a funcao auxiliar acima para inserir uma palavra na trie
void inserir(PONT raiz, char* palavra, int n){
	
	inserir_Aux(raiz, palavra, n, 0);
}


// Funcao que exclui todas as copias de uma palavra existente na trie. Caso alguma letra dessa palavra nao faca parte de alguma outra palavra, exclui esse no. O funcionamento geral da funcao se baseia em chamadas recursivas que sempre retornarao 1 caso o no possa ser excluido, -1 caso nao possa e NULL se ele nao existe.
int excluirTodas_Aux(PONT raiz, char *palavra, int n, int caractere_atual) {
    if (raiz == NULL) return -1; // se a raiz for nula, retorna null

	//printf("Excluindo no em endereco: %p\n", (void*)raiz);

    int letra = palavra[caractere_atual] - VALOR_a; // calcula a letra atual

    if (caractere_atual == n) { // se chegou na palavra

        if (raiz -> contador > 0) { // se ela de fato existe

            raiz -> contador = 0; // zera suas copias
        }

        if (raiz -> filhos == NULL) { // se ela nao for parte de outra palavra, pode excluir

            return 1; 
        } 

		else { // senao, nao pode

            return -1;
        }
    }


    
    if (raiz -> filhos != NULL && raiz -> filhos[letra] != NULL) { // se o no atual tiver um arranjo de filhos e eles possuirem uma letra da palavra

        if (excluirTodas_Aux(raiz->filhos[letra], palavra, n, caractere_atual + 1) == 1) { // se pode excluir, exclui o no da letra

			//printf("No em endereco %p excluido.\n", (void*)raiz->filhos[letra]);
            free(raiz -> filhos[letra]);  
            raiz -> filhos[letra] = NULL; 
        }

    } 
	
	else{ // se o no nao tiver a letra da palavra, nao faz nada

		return -1;
	}

    // verifica se o array de filhos eh nulo
    for (int i = 0; i < LETRAS; i++) { 

        if (raiz -> filhos != NULL && raiz -> filhos[i] != NULL) {

            return -1;  
        }
    }

    if (raiz -> contador == 0){ // se a palavra nao tem mais copias, pode excluir

		return 1;
	}

	else{ // se nao, nao pode

		return -1;
	}
}

void excluirTodas(PONT raiz, char* palavra, int n) {

    excluirTodas_Aux(raiz, palavra, n, 0);
}



// Funcao que exclui apenas uma copia da palavra caso ela exista. Se a palavra tem mais de uma copia, exclui uma delas. Se a palavra tem exatamente uma copia, chama a funcao excluir todas.
void excluir(PONT raiz, char* palavra, int n){

	if (raiz == NULL) return; // se a raiz for nula, retorna null;

	PONT achou = buscarPalavra_Aux(raiz, palavra, n, 0); // procura a palavra

	if (achou != NULL) { // se achou ela

		if (achou -> contador == 1) { // se so tem uma copia

			excluirTodas(raiz, palavra, n); // exclui todas
		}

		else if(achou -> contador == 0){ // se nao tem copia, nao faz nada

			return;
		}

		else{ // se tem mais de uma copia, diminui em 1 o numero delas

			achou -> contador--;
		}
	}

}




/*
Funcao main que realiza ALGUNS testes nas funcoes implementadas.
Seu EP sera avaliado utilizando um conjunto distinto de testes.
*/
int main(){
	NO raiz1;
	char* temp = (char*)malloc(sizeof(char)*1025);

	printf("\n### Inicializacao.\n");
	inicializar(&raiz1);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Primeiras insercoes.\n");
	inserir(&raiz1, "teste", 5);
	inserir(&raiz1, "teste", 5);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Mais insercoes.\n");
	inserir(&raiz1, "testemunha", 10);
	inserir(&raiz1, "testemunhe", 10);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));	

	printf("\n### Mais insercoes.\n");
	inserir(&raiz1, "testa", 5);
	inserir(&raiz1, "testamento", 10);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Exclusoes.\n");
	excluir(&raiz1, "teste", 5);
	excluir(&raiz1, "teste", 5);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Mais exclusoes.\n");
	excluir(&raiz1, "teste", 5);
	excluir(&raiz1, "testemunha", 10);
	excluir(&raiz1, "testemunhe", 10);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Mais insercoes.\n");
	inserir(&raiz1, "abacate", 7);
	inserir(&raiz1, "abacaxi", 7);
	inserir(&raiz1, "abacaxi", 7);
	inserir(&raiz1, "abacaxi", 7);
	inserir(&raiz1, "abobora", 7);
	inserir(&raiz1, "banana", 6);
	inserir(&raiz1, "caju", 4);
	inserir(&raiz1, "melancia", 8);
	inserir(&raiz1, "melao", 5);
	inserir(&raiz1, "abacaxi", 7);
	inserir(&raiz1, "melao", 5);
	inserir(&raiz1, "melao", 5);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Exclusoes (excluir todas as copias).\n");
	excluirTodas(&raiz1, "teste", 5);
	excluirTodas(&raiz1, "abacaxi", 7);
	excluirTodas(&raiz1, "testa", 5);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Buscas.\n");
	printf("Foram encontradas %i copia(s) da palavra 'testa'.\n",buscarPalavra(&raiz1, "testa", 5));
	printf("Foram encontradas %i copia(s) da palavra 'mel'.\n",buscarPalavra(&raiz1, "mel", 3));
	printf("Foram encontradas %i copia(s) da palavra 'melao'.\n",buscarPalavra(&raiz1, "melao", 5));
	printf("Foram encontradas %i copia(s) da palavra 'melancia'.\n",buscarPalavra(&raiz1, "melancia", 8));
	
	printf("\n### Exclusoes adicionais (eliminando cada uma das palavras restantes).\n");
	excluirTodas(&raiz1, "abacate", 7);
	excluirTodas(&raiz1, "abobora", 7);
	excluirTodas(&raiz1, "banana", 6);
	excluirTodas(&raiz1, "caju", 4);
	excluirTodas(&raiz1, "melancia", 8);
	excluirTodas(&raiz1, "melao", 5);
	excluirTodas(&raiz1, "testamento", 10);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	
	printf("\n### Repetindo primeiras insercoes.\n");
	inserir(&raiz1, "teste", 5);
	inserir(&raiz1, "teste", 5);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	

	return 0;
}
