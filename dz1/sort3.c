#include <stdio.h>
#include <math.h>

int main(void){
	const int n = 10;
	int a[n];
	//ввод массива
	for (int i = 0; i < n; i++)
	{
		scanf ("%d", &a[i]);
	}
	int buf;
	//сортировка выбором
		for (int i = 0; i < n - 1; i++)
		{
			//поиск мин
			int min = a[9];
			int imin = 9;
			for (int j = i; j < n; j++)
			{
				if ( a[j] <  min )
				{
					min = a[j];
					imin = j;
				}
			}
			buf = a[imin];
			a[imin] = a[i];
			a[i] = buf;
			
		}
	//вывод массива
	for (int i = 0; i < n; i++)
	{
		printf ("%d ", a[i]);
	}
	printf ("\n");
	return 0;
}
