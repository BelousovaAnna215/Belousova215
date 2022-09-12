#include <stdio.h>
#include <math.h>

int main(void){
 float a,b,c;
 scanf ("%f", &a);
 scanf ("%f", &b);
 scanf ("%f", &c);
 float d, x, y;
 d = b * b - 4 * a * c;
 if ( d == 0 )
 {
	 x = -b/(2*a);
	 printf ("1 root: %f\n", x);
 }
 else {
	 if ( d > 0 )
	 {
		 x = (-b + sqrt(d))/(2*a);
		 y = (-b - sqrt(d))/(2*a);
		 printf ("2 roots: %.2f, %.2f\n", x, y);
	 }
	 else{
		 x = (-b)/(2*a);
		 d = d *(-1);
		 y = sqrt(d)/(2*a);
		 printf ("2 roots: %.2f+i*%.2f, %.2f-i*%.2f\n", x, y, x, y);
	 }
 }
 return 0;
}
