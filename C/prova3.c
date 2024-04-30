#include <stdio.h>
#define TRUE 1
#define FALSE 0
int main() {
int chuva=TRUE;
int temperatura=30;
printf("%s\n", (chuva || (temperatura<28))?"calcas":"bermudas");
return 0;
}
