#include <stdio.h>
void main(){
#define A 43
#define B 91
printf("A=%d\n", A);
printf("B=%d\n", B);
printf("&&, %d\n", (A<50)&&(B>50));
printf("||, %d\n", (A<50)||(B>50));
printf("!, %d\n", !(A<50));
printf("composto, %d\n", !(A<50)&&(B>50));
printf("outro composto, %d\n", !(A<50)||(B>50));
printf("()?:, %d\n", ((A<50)&&!(B>50))?20:-50);
int EstaChovendo=0;
printf("%s o guarda-chuva\n", (EstaChovendo?"leve":"?"));
}
