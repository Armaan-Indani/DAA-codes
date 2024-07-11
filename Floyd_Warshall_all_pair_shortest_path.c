#include <stdio.h>
#include <limits.h>

int min(int a, int b)
{
    return a > b ? b : a;
}

int main()
{
    int x = 100;
    int n = 4;
    int a[4][4] = {
        {0, 3, x, 5},
        {2, 0, x, 4},
        {x, 1, 0, x},
        {x, x, 2, 0},
    };

    printf("A0 =\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (int k = 0; k < n; k++)
    {
        printf("A%d=\n", k + 1);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (a[i][k] != INT_MAX && a[k][j] != INT_MAX)
                {
                    a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}