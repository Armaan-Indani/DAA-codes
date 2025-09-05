#include <stdio.h>
#include <limits.h>

int min(int a, int b)
{
    return a > b ? b : a;
}

int main()
{
    int x = INT_MAX;
    int n = 6;
    int c[6][6] = {
        {x, x, x, x, x, x},
        {x, x, x, x, x, x},
        {x, x, x, x, x, x},
        {x, x, x, x, x, x},
        {x, x, x, x, x, x},
        {x, x, x, x, x, x},
    };

    int d[6] = {0, x, x, x, x, x};

    for (int i = 0; i < 9; i++)
    {
        char s, d, dash;
        int wt;
        scanf("%c%c%c", &s, &dash, &d);
        scanf("%d", &wt);
        getchar();

        int src = (int)s - 65;
        int dest = (int)d - 65;

        if (src > 5 || dest > 5)
        {
            printf("Error src = %d, dest = %d invalid", src, dest);
        }
        else
        {
            c[src][dest] = wt;
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    if (c[i][j] != INT_MAX && d[i] != INT_MAX)
                    {
                        d[j] = min(d[j], d[i] + c[i][j]);
                    }
                }
            }
        }
    }
    
    printf("A-%d\n", d[0]);
    printf("B-%d\n", d[1]);
    printf("C-%d\n", d[2]);
    printf("D-%d\n", d[3]);
    printf("E-%d\n", d[4]);
    printf("F-%d\n", d[5]);

    return 0;
}