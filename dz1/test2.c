#include <stdio.h>
#include <math.h>

int main(void){
 int a, b, c;
 int s = 0;
 int i = 102;
 while (i <= 987)
 {
	a = i;
	c = a%10;
	a = a/10;
	b = a%10;
	a = a/10;
	 if (  a!=b && c!=b && a!=c )
	 {
		 s++;;
	 } 
	 i = i + 1;
 }
 printf ("answer: %d\n", s);
 return 0;
}
