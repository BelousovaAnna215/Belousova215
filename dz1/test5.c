#include <stdio.h>
#include <math.h>

int main(void){
 float e, a, b;
 int i = 3;
 scanf ("%f", &e);
 a = 2;
 b = 9.0/4.0;
 printf ("answer: ");
 while (fabsf(a-b)>=e)
 {
	a = b;
	b = pow(1 + 1.0/i, i);
	i++;
 }
 printf ("%f\n", b);
 return 0;
}
