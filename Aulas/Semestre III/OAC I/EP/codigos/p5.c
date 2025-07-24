#include <stdio.h>

double f(double x, double y, double z) {
  return x*x+y*y+z*z;
}

void main () {
  int i=0;
  printf ("%lf", f(0.3, 5.0, 15.0));
}
