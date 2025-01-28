#include <stdio.h>
#include <stdlib.h>

/*Esta funcao encontra, a partir de uma sequencia de inteiros, uma subsequencia em que a soma de seus elementos consecutivos eh a maior possivel*/

int SCM(int *v, int tam, int *i, int *j){
    int global_max = 0; // scm 
    int sufixo_max = 0;
    int inicio = 0;

    // inicio e fim do subarray, respectivamente
    *i = 0;
    *j = 0;

    // percorre o array definindo a scm e as posicoes dela
    for (int k = 0; k < tam; k++){
        
        // se o sufixo eh maior que a scm, expande a scm, o sufixo e atualiza as posicoes
        if ((v[k] + sufixo_max) > global_max){
            sufixo_max = sufixo_max + v[k];
            global_max = sufixo_max;

            *j = k;
            *i = inicio;
            
        }

        else{
            
            // se o sufixo eh maior que zero, expande
            if ((v[k] + sufixo_max) > 0){
                sufixo_max = sufixo_max + v[k];
            }

            // se o sufixo eh negativo, atualiza seu valor para 0 e define o inicio para o proximo elemento
            else{
                sufixo_max = 0;
                inicio = k + 1;
            }
        }
    }

    return global_max;
}

int main(){

    int v[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = 9;
    int i;
    int j;

    int scm = SCM(v, n, &i, &j);

    printf("Subsequencia Continua Maxima: %d\n", scm);
    printf("Inicio: %d\n Final: %d\n", i, j);

    return 0;
}