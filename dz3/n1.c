#include<stdio.h>
void scopy (char *a, char *b )
{
 while ( *a != '\0')
 {
  *b = *a;
  b++;
  a++;
 }
 *b = '\0';
}
int main (void)
{
 char a[] = "abcde";
 char b[] = "123489";
 scopy (a, b);
 printf ("%s\n", b);
return 0;
}
