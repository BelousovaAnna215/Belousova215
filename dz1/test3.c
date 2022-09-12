#include <stdio.h>
#include <math.h>

int main(void){
 float a,sum=0;
 int n = 0;
 scanf ("%f", &a);
 while (a > sum)
 {
	 n++;
	 sum = sum + 1.0/n;
 }
 printf ("answer: %d\n", n);
 return 0;
}
