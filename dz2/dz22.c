#include<stdio.h>
int main(void)
{
 int n, s = 0, s1;
 scanf("%d", &n);
 s1 = n * n;
 while (n>0)
 {
  s = s + ( n % 10 );
  n = n / 10;
 }
 s = s * s * s;
 if (s == s1)
 printf("right\n");
 else printf("wrong\n");
 return 0;
}
