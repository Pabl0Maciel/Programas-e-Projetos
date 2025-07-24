#include <stdio.h>


void p (int n, int *a) {
  int i=0;
  do {
    printf ("%d, %d", i, a[i]);
  } while (++i<n);
}

void main () {
  int a[]={3, 5, 7, 11, 13};
  int n=5;
  p(n,a);
}
