#include <stdio.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    int n = 6;
    int a[2][6] = {{2, 8, 9, 3, 4, 1}, {6, 11, 2, 2, 7, 3}};
    int e1 = 4, e2 = 2;
    int t[2][5] = {{3, 1, 2, 1, 3}, {3, 4, 1, 1, 3}};
    int x1 = 3, x2 = 7;

    int f1[n], f2[n];
    int l1[n], l2[n];
    l1[0] = 1;
    l2[0] = 2;
    f1[0] = e1 + a[0][0];
    f2[0] = e2 + a[1][0];

    for (int i = 1; i < n; i++)
    {
        if (f1[i - 1] + a[0][i] <= f2[i - 1] + t[1][i - 1] + a[0][i])
        {
            f1[i] = f1[i - 1] + a[0][i];
            l1[i] = 1;
        }
        else
        {
            f1[i] = f2[i - 1] + t[1][i-1] + a[0][i];
            l1[i] = 2;
        }

        if (f2[i - 1] + a[1][i] <= f1[i - 1] + t[0][i - 1] + a[1][i])
        {
            f2[i] = f2[i - 1] + a[1][i];
            l2[i] = 2;
        }
        else
        {
            f2[i] = f1[i - 1] + t[0][i-1] + a[1][i];
            l2[i] = 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", f1[i], f2[i]);
        printf("    %d %d\n", l1[i], l2[i]);
    }

    int f = min(f1[n - 1] + x1, f2[n - 1] + x2);

    printf("Total time = %d", f);
    return 0;
}