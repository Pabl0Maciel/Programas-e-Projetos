#include <stdio.h>
void main(){

	int i=1, j=1, k;

	while(i<=10){
		printf("%d ", i);
		i++;
		if(i==5){
			break;
		}
	}

	printf("\n");

	do{
		printf("%d ", j);
		j++;
	}while(j<=10);

	printf("\n");

	for(k=1; k<=10; k++){
		printf("%d ", k);
	}
	printf("\n");
}
