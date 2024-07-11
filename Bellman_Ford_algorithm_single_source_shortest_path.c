#include<stdio.h>
#include<limits.h>

int min(int a, int b)
{
    return a>b?b:a;
}

int main()
{
    int x=INT_MAX;
    int n=5;
    int c[5][5] = {
        {0,10,x,x,3},
        {x,0,2,x,4},
        {x,x,0,9,x},
        {x,x,7,0,x},
        {x,1,8,2,0},
    };
    
    int d[5] = {0,x,x,x,x};
    
    for(int k=0; k<n; k++)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(i!=j)
                {
                    if(c[i][j] != INT_MAX && d[i]!=INT_MAX)
                    {
                        d[j] = min(d[j], d[i] + c[i][j]);
                    }
                    
                    // printf("[(%d,%d) %d %d]\n",i,j,d[i], c[i][j]);
                }
            }
        }
    }
    
    printf("A-B : %d\n",d[1]);
    printf("A-E : %d\n",d[4]);
    printf("A-C : %d\n",d[2]);
    printf("A-D : %d\n",d[3]);
    
    return 0;
}