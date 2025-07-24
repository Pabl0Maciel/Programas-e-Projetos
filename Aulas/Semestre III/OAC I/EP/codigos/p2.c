#include <stdio.h>

void main () {
  int a, b, r;
  a=12;
  b=11;
  r=0;
  if (b & 0x01) r+=a;
  a=a<<1;
  if (b & 0x02) r+=a;
  a=a<<1;
  if (b & 0x04) r+=a;
  a=a<<1;
  if (b & 0x08) r+=a;
  printf ("%d\n", r);
}
