#include <stdio.h>

int a[]={3, 5, 7, 11, 13};

void main () {
  int i=0;
  do {
    printf ("%d, %d", i, a[i]);
  } while (++i<5);
}
