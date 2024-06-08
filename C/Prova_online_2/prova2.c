#include <stdio.h>
#define N 3
int main(){
    for (int cand = 0; cand < (1<<N); cand++){

      printf("Subconjunto %d: ", cand+1);


      for (int i = 0; i < N; i++){

         if (cand & (1<<i)){

            printf("1");

         }

         else{

         printf("0");

         }
      }
    printf("\n");
    }

    return 0;
}