#include <stdio.h>
#include <stdlib.h>
#define M 2
#define N 2
#define K 2
void mul (int m, int n, int k, int a[][n], int b[][k], int c[][k])
{
    for (int i = 0; i < m; i++){
        for (int j = 0; j < k; j++){
            c[i][j] = 0;
            for (int l = 0; l < n; l++){
                c[i][j] += a[i][l] * b[l][j];
            }
        }
    }
}
void vvod (int m, int n, int a[][n])
{
	for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &a[i][j]);
        }
    }
} 
int main(int argc, char *argv[])
{
    int m, n,k;
    m = atoi(argv[1]);
    printf("m=%d\n",m);
    n = atoi(argv[2]);
    k = atoi(argv[3]);
    int a[m][n], b[n][k], c[m][k];
    printf("first\n");
    vvod (m, n, a);
    printf("second\n");
    vvod (n, k, b);
    printf("answer\n");
    mul( M, N, K, a, b, c);
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < k; ++j){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
