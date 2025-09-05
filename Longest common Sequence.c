#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    char s1[20], s2[20];

    strcpy(s1, "stone");
    strcpy(s2, "longest");

    int l1 = strlen(s1);
    int l2 = strlen(s2);

    int mat[l1 + 1][l2 + 1];

    for (int i = 0; i <= l1; i++)
    {
        for (int j = 0; j <= l2; j++)
        {
            if (i == 0 || j == 0)
                mat[i][j] = 0;
            else if (s1[i - 1] == s2[j - 1])
                mat[i][j] = mat[i - 1][j - 1] + 1;
            else
                mat[i][j] = max(mat[i - 1][j], mat[i][j - 1]);
        }
    }

    // Backtracking to find the LCS
    int i = l1, j = l2, p = 0;
    char common[20];

    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            common[p++] = s1[i - 1];
            i--;
            j--;
        }
        else if (mat[i - 1][j] > mat[i][j - 1])
            i--;
        else
            j--;
    }

    common[p] = '\0';

    // Print LCS in correct order
    printf("The longest common subsequence is: ");
    for (int k = p - 1; k >= 0; k--)
    {
        printf("%c", common[k]);
    }
    printf("\n");

    return 0;
}
