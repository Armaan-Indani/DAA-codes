#include<stdio.h>

int min(int a, int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d", &n);
    
    int d[n+1];
    int x;
    
    scanf("%d", &d[0]);
    for(int i=1; i<n; i++)
    {
        scanf("%d %d", &x, &d[i]);
        if(x!=d[i])
        {
            printf("*%d %d Error. Invalid input.*", x, d[i]);
            return 1;
        }
    }
    scanf("%d",&d[n]);
    
    int mat[n][n];
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=i;j++)
        {
            mat[i][j] = 0;
        }
    }
    for(int t = 1; t<n; t++)
    {
        for(int i=0; i<n-t; i++)
        {
            int j = i+t;
            mat[i][j] = mat[i][i]+mat[i+1][j]+d[i]*d[i+1]*d[j+1];
            for(int k=i+1; k<j; k++)
            {
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k+1][j] + d[i]*d[k+1]*d[j+1]);
            }
        }
    }
    printf("The minimum number of multiplication needed is %d", mat[0][n-1]);
    return 0;
}