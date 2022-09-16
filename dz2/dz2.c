#include<stdio.h>

int main(void)
{
 int a, b, c;
 int s = 0;
 int i = 111;
 while (i <= 999)
 {
	a = i;
	c = a%10;
	a = a/10;
	b = a%10;
	a = a/10;
	 if (  a==b || c==b || a==c )
	 {
		 s++;;
	 } 
	 i = i + 1;
 }
 printf ("answer: %d\n", s);
 return 0;
}
