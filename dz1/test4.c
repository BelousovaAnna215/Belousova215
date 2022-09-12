#include <stdio.h>
#include <math.h>

int main(void){
 int n;
 int i = 2;
 int fl;
 scanf ("%d", &n);
 printf ("answer: ");
 while (n > 0)
 {
	 fl = 0;
	//проверка простое ли число
	 for (int j=2; j<i; j++)
	 {
		 if (i%j==0)
		 {
			 fl = 1;
			 break;
		 }
	 }
	 if (fl == 0)
	 {
		 printf ("%d ", i);
		 n = n - 1;
	 }
	 i++;
 }
 printf ("\n");
 return 0;
}
