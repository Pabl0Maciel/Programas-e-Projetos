/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I		            **/
/**   EACH-USP - Segundo Semestre de 2024			                **/
/**								                                    **/
/**   Segundo Exercicio-Programa				                    **/
/**								                                    **/
/**   Pablo Caballero Maciel		 14778630               2024202 **/
/**								                                    **/
/*********************************************************************/


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



/*
Funcao que recebe o endereco do no raiz de uma trie (raiz), o endereco de um arranjo de caracteres (palavra) e o tamanho da palavra presente no arranjo de caracteres (n) e retorna o numero de copias dessa palavra na trie. Provavelmente voce desejara realizar a busca chamando uma funcao auxiliar recursiva (desenvolvida por voce) que tenha, ao menos, um parametro adicional para indicar qual a letra atual da busca. Caso a palavra nao exista na trie, sua funcao devera retornar 0 (zero), caso contrario, devera retornar o valor do campo contador do no correspondente a ultima letra da palavra.
*/

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

// Funcao que busca a palavra em si. Usa a funcao de buscaCaractere e retorna o valor do contador daquele no caso tenha encontrado a palavra.
int buscarPalavra(PONT raiz, char* palavra, int n){
  int resposta = 0; // assume que a resposta eh 0, ou seja, que nao encontrou a palavra
  
  PONT achou = buscarPalavra_Aux(raiz, palavra, n, 0); // chama a funcao de buscarPalavra_Aux e atribui o resultado a variavel 'achou'

  if (achou != NULL) { // se 'achou' nao for nulo, atribui o valor de seu contador a variavel 'resposta'
	resposta = achou -> contador;
  }

  return resposta; // retorna a resposta
}


/*
Funcao que recebe o endereco do no raiz de uma trie (raiz), o endereco de um arranjo de caracteres (palavra) e o tamanho da palavra presente no arranjo de caracteres (n) e insere essa palavra na trie. Provavelmente voce desejara realizar a insercao chamando uma funcao auxiliar recursiva (desenvolvida por voce) que tenha, ao menos, um parametro adicional para indicar qual a letra atual da chamada recursiva (assumindo que a cada chamada recursiva uma letra sera inserida/processada). Voce pode assumir que todos os parametros desta funcao terao valores validos e a palavra a ser inserida (presente no arranjo de caracteres) possuira apenas letras minusculas (sem acentos ou caracteres especiais). A insercao funciona da seguinte forma (potencialmente recursiva):
  (i) se ainda falta inserir caractere(s) e o no atual nao possui arranjo de filhos, e necessario:
     (a) criar esse arranjo, preencher suas posicoes com valores NULL e atribuir o endereco dele no campo filhos do no atual;
     (b) criar o no correspondente ao proximo caractere, acertar seus campos (se voce usar a funcao criarNo ela ja acerta esses valores) e colocar o endereco dele na posicao correspondente do arranjo filhos; e
     (c) continuar recursivamente com o processo sendo que, se voce acabou de criar o ultimo caractere da palavra, o campo contador deve receber o valor 1 e a insercao foi concluida.
  (ii) se ainda falta inserir caractere(s) e o no atual possui o arranjo de filhos: caso o no correspondente ao proximo caractere ja exista no arranjo de filhos, basta prosseguir a insercao (recursivamente) a partir dele, caso contrario e necessario prosseguir de acordo com o processo (i.b).
  (iii) se voce chegou ao ultimo caractere da palavra e ele ja existe na trie, e necessario incrementar seu campo contador em uma unidade.
*/

// funcao que insere uma palavra na trie, letra por letra, verificando se ja existe aquela letra ou aquela palavra.
void inserir_Aux(PONT raiz, char *palavra, int n, int caractere_atual){
	int letra = palavra[caractere_atual] - VALOR_a; // calcula a letra atual
	
	if (raiz -> filhos == NULL) { // se o no atual nao tiver um array de filhos, cria ele e inicializa como NULL

        raiz -> filhos = malloc(LETRAS * sizeof(PONT));

        for (int i = 0; i < LETRAS; i++) {
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



/*
Funcao que recebe o endereco do no raiz de uma trie (raiz), o endereco de um arranjo de caracteres (palavra) e o tamanho da palavra presente no arranjo de caracteres (n) e exclui todas as copias dessa palavra da trie. Provavelmente voce desejara realizar a exclusao chamando uma funcao auxiliar recursiva (desenvolvida por voce) que tenha, ao menos, um parametro adicional para indicar qual a letra atual da chamada recursiva (assumindo que cada chamada recursiva avancara uma letra na arvore). Adicionalmente, se a operacao de exclusao resultar na eliminacao de um no, pode ser necessario, recursivamente, apagar alguns dos nos anteriores, neste caso, voce pode precisar de mais um parametro adicional na sua funcao auxiliar recursiva ou ela pode ter um retorno (potencialmente booleano) para indicar que e necessario excluir nos na volta da chamada recursiva. Voce pode assumir que todos os parametros desta funcao terao valores validos e a palavra a ser excluida (presente no arranjo de caracteres) possuira apenas letras minusculas (sem acentos ou caracteres especiais). E possivel que a palavra nao exista na sua trie, entao a funcao de exclusao nao causara nenhuma mudanca na trie. A exclusao funciona da seguinte forma (potencialmente recursiva):
 Voce navegara na trie, caractere a caractere, ate passar por toda a palavra, isto e, chegar no caractere final da palavra. 
 (i) Se isto nao for possivel, isto e, se a sequencia de caracteres que forma a palavra nao esta presente na trie, sua funcao devera encerrar sem realizar nenhuma mudanca na estrutura; caso contrario, ha duas possibilidades principais:
 (ii) A palavra nao existe na trie (isto e, apesar de suas letras estarem la, o campo contador da ultima letra e igual a zero), neste caso, sua funcao deve encerrar sem modificar a estrutura;    
 (iii) A palavra existe na trie, neste caso ela dever ser excluida, considerando duas situacoes:
    (a) O no correspondente a ultima letra possui filhos, neste caso o contador dele devera ser zerado e nao ha mais nada a ser feito pela funcao; 
    (b) Caso o no correspondente a ultima letra nao possua filhos ele devera ser excluido, e o ponteiro para ele no arranjo de filhos de seu pai deve ser atualizado para NULL. Se apos essa exclusao, o pai desse no nao possuir mais filhos, seu arranjo de filhos deve ser excluido (memoria liberada) e seu campo filhos deve receber o valor NULL. Adicionalmente, se o campo contador do no pai valer zero este tambem deve ser apagado (e o processo iii.b deve ser repetido enquanto cada no [na volta da recursao] nao possuir mais filhos e nao for um no final de uma palavra).
Observacao: o no raiz nunca devera ser excluido, porem seu arranjo de filhos podera ser excluido caso este no nao possua filhos (trie sem nenhuma palavra) e, neste caso, seu campo filhos devera ser atualizado para NULL.
*/

int excluirTodas_Aux(PONT raiz, char *palavra, int n, int caractere_atual) {
    if (raiz == NULL) return -1;  

	//printf("Excluindo no em endereco: %p\n", (void*)raiz);

    int letra = palavra[caractere_atual] - VALOR_a;

    if (caractere_atual == n) {

        if (raiz->contador > 0) {
            raiz->contador = 0;  
        }

        if (raiz->filhos == NULL) {

            return 1; 
        } 

		else {
            return -1;
        }
    }


    
    if (raiz->filhos != NULL && raiz->filhos[letra] != NULL) {

        if (excluirTodas_Aux(raiz->filhos[letra], palavra, n, caractere_atual + 1) == 1) {
			//printf("No em endereco %p excluido.\n", (void*)raiz->filhos[letra]);
            free(raiz->filhos[letra]);  
            raiz->filhos[letra] = NULL; 
            //raiz->filhos = NULL;
        }

    } 
	
	else{
		return -1;
	}

    
    for (int i = 0; i < LETRAS; i++) {

        if (raiz->filhos != NULL && raiz->filhos[i] != NULL) {
            return -1;  
        }
    }

    if (raiz->contador == 0){

		return 1;
	}

	else{
		return -1;
	}
}

void excluirTodas(PONT raiz, char* palavra, int n) {
    excluirTodas_Aux(raiz, palavra, n, 0);
}



/*
Funcao que recebe o endereco do no raiz de uma trie (raiz), o endereco de um arranjo de caracteres (palavra) e o tamanho da palavra presente no arranjo de caracteres (n) e exclui uma copia dessa palavra da trie (isto e, caso a palavra exista na trie, diminui o contador correspondente a sua ultima letra em uma unidade). Observacoes: se a palavra nao existir na trie, nao ha nada a ser feito pela funcao; se a palavra existir e o contador valer 1 (um) antes da exclusao, entao a exclusao tera o mesmo comportamento da funcao excluirTodas.
*/
void excluir(PONT raiz, char* palavra, int n){

	if (raiz == NULL) return;

	PONT achou = buscarPalavra_Aux(raiz, palavra, n, 0);

	if (achou != NULL) {
		if (achou -> contador == 1) {
			excluirTodas(raiz, palavra, n);
		}

		else if(achou -> contador == 0){
			return;
		}
		else{
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