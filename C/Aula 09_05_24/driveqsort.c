#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printuf (char uf[60][60]) {
  for (int i=0;i<60;i++) {
    // puts (uf[i]);
    printf ("%s, %ld\n", uf[i], strlen(uf[i]));
  }
}

void main () {
  char uf[60][60]={
    "Acre","AC","Alagoas","AL","Amapa","AP","Amazonas","AM",
    "Bahia","BA","Ceara","CE","Espirito Santo","ES",
    "Goias","GO","Maranhao","MA","Mato Grosso","MT",
    "Mato Grosso do Sul","MS","Minas Gerais","MG",
    "Para","PA","Paraiba","PB","Parana","PR",
    "Pernambuco","PE","Piaui","PI","Rio de Janeiro","RJ",
    "Rio Grande do Norte","RN","Rio Grande do Sul","RS",
    "Rondonia","RO","Roraima","RR","Santa Catarina","SC",
    "Sao Paulo","SP","Sergipe","SE","Tocantins","TO",
    "Distrito Federal","DF", "São Paulo", "SP"};

  // char uf2[60][60];
  // memcpy (uf2, uf, 60*60*sizeof(char));
  qsort (uf, 60, 60*sizeof(char),strcmp);
  printuf(uf);

  struct timespec start, end;
  double execution_time;
  clock_gettime(CLOCK_MONOTONIC, &start);
  clock_gettime(CLOCK_MONOTONIC, &end);

  execution_time=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1e9
  printf("Tempo de execucao: %.9f segundos\n", execution_time);
}
