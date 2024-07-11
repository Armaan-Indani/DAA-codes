#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    char str1[40];
    char pat1[20];
    char str[20];
    char pat[10];

    fgets(str1, 40, stdin);
    fgets(pat1, 20, stdin);

    for (int i = 0; i < strlen(str1) / 2; i++)
    {
        str[i] = str1[2 * i];
    }
    for (int i = 0; i < strlen(pat1) / 2; i++)
    {
        pat[i] = pat1[2 * i];
    }
    pat[strlen(pat) - 1] = '\0';

    // printf("%ld %ld\n", strlen(pat),strlen(str));

    int pi_table[strlen(pat)];
    // puts(str);
    // printf("********\n");
    // puts(pat);

    for (int i = 0; i < strlen(pat); i++)
    {
        pi_table[i] = 0;
    }

    for (int i = 1; i < strlen(pat); i++)
    {
        if (pat[0] == pat[i])
        {
            for (int j = 0; j < strlen(pat) - i; j++)
            {
                if (pat[j] == pat[i + j])
                {
                    pi_table[i + j] = max(pi_table[i + j], j + 1);
                }
                else
                {
                    break;
                }
            }
        }
    }

    // for(int i=0; i<strlen(pat); i++)
    // {
    //     printf("%d ", pi_table[i]);
    // }

    int i = 0, j = 0;
    while (i < strlen(str))
    {
        // printf("[%d %d] ",i,j);
        if (j == strlen(pat))
        {
            printf("Pattern is found in the string\n");
            printf("Number of Shifts needed is %ld", i - strlen(pat));
            return 0;
        }
        if (str[i] == pat[j])
        {
            i++;
            j++;
        }
        else if (j == 0)
        {
            i++;
        }
        else
        {
            j = pi_table[j - 1];
        }
    }
    printf("Pattern is not found in the string");
    return 0;
}