#include <stdio.h>
#include <math.h>

int main(void){
	const int n = 10;
	int a[n];
	int buf;
	//ввод массива
	for (int i = 0; i < n; i++)
	{
		scanf ("%d", &a[i]);
	}
	//сортировка вставками
	for (int i = 1; i < n; i++)
	{
		while ( i > 0 && a[i-1]>a[i])
		{
			buf = a[i-1];
			a[i-1] = a[i];
			a[i] = buf;
			i--;
		}
	}
	//вывод массива
	for (int i = 0; i < n; i++)
	{
		printf ("%d ", a[i]);
	}
	printf ("\n");
	return 0;
}
