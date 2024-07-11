#include<stdio.h>
#include<string.h>

int max(int a, int b)
{
    return a>b?a:b;
}

int main()
{
    char s1[20], s2[20];
    // fgets(s1, 20, stdin);
    // fgets(s2, 20, stdin);
    
    strcpy(s1, "stone\n");
    strcpy(s2, "longest\n");
    
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    
    l1--;
    l2--;
    
    int mat[l1+1][l2+1];
    
    for(int i = 0; i<l1+1; i++)
    {
        mat[i][0] = 0;
    }
    for(int i = 0; i<l2+1; i++)
    {
        mat[0][i] = 0;
    }
    
    for(int i = 1; i<l1+1; i++)
    {
        for(int j = 1; j<l2+1; j++)
        {
            if(s1[i-1] == s2[j-1])
            {
                mat[i][j] = mat[i-1][j-1] + 1;
            }
            else 
            {
                mat[i][j] = max(mat[i][j-1],mat[i-1][j]);
            }
        }
    }
    
    char common[20];
    int p = 0;
    int x = l2;
    for(int i = l1; i>0; i--)
    {
        if(mat[i][x] == mat[i-1][x])
        {
            continue;
        }
        common[p++] = s2[--x];
    }
    
    printf("The longest common sub sequence is : ");
    
    for(int i = p-1; i>=0; i--)
    {
        printf("%c", common[i]);
    }
    
    return 0;
}