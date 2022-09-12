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
	//сортировка пузырьком
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			if (a[j] > a[j+1])
			{
				buf = a[j];
				a[j] = a[j+1];
				a[j+1] = buf;
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
