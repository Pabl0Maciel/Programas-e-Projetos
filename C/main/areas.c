#include <stdio.h>
#include "poligonos.h"

int main(){

	int n=10, m=10, o=10;
	printf("%.2f.\n", calcAreaRetangulo(m, n));
	printf("%.2f.\n", calcAreaTriangulo(n, m));
	printf("%.2f.\n", calcAreaCirculo(n));
	printf("%.2f.\n", calcPerimetroRetangulo(n, m));
	printf("%.2f.\n", calcPerimetroTriangulo(n, m, o));
	printf("%.2f.\n", calcPerimetroCirculo(n)); 
}
