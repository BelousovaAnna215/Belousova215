
#include <stdio.h>
int main(void)
{
 int n, a = 1, b = 1;
 int res;
 scanf("%d",&n);
 if (n == 1)
  printf ("1 ");
 else
 {
  printf ("1 1 ");
  for (int i = 2; i < n; i++)
  {
   res = a + b;
   a = b;
   b = res;
   printf ("%d ", b);
  }
 }
return 0;
}
