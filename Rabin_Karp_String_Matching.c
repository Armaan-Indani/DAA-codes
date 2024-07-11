#include <stdio.h>
#include <string.h>

int hash_fn(char *start, int len)
{
    int hash_val = 0;
    for (int i = 0; i < len; i++)
    {
        hash_val = 10 * hash_val + ((int)start[i] - 96);
    }
    return hash_val;
}

int check_str(char *pat, char *str, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (pat[i] != str[i])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    char str1[25];
    char pat1[10];
    char str[15];
    char pat[5];

    fgets(str1, 25, stdin);
    fgets(pat1, 10, stdin);

    for (int i = 0; i < strlen(str1) / 2; i++)
    {
        str[i] = str1[2 * i];
    }
    for (int i = 0; i < strlen(pat1) / 2; i++)
    {
        pat[i] = pat1[2 * i];
    }

    int pat_len = strlen(pat);
    int hash_p = hash_fn(&pat[0], strlen(pat));

    for (int i = 0; i < strlen(str) - pat_len + 1; i++)
    {
        int hash_str = hash_fn(&str[i], strlen(pat));
        if (hash_str == hash_p)
        {
            if (check_str(&pat[0], &str[i], pat_len))
            {
                printf("The given pattern is present in the String");
                return 0;
            }
        }
    }
    return 0;
}