#include <stdio.h>
void main(){
#define A 43
#define B 0X1F642
printf("A=%d\n", A);
printf("B=%d\n", B);
printf("and (&), %d\n", A&B);
printf("or (|), %d\n", A|B);
printf("not (~), %d\n", ~A);
printf("xor (^), %d\n", A^B);
printf("shift left by 1 bit (<<1), %d\n", A<<1);
printf("shift right by 1 bit (>>1), %d\n", A>>1);
printf("shift left by 2 bits (<<2), %d\n", A<<2);
printf("shift right by 2 bits (>>2), %d\n", A>>2);
}

