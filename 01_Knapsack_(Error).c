#include<stdio.h>

void knapsack(int n, char *s, int item, int p[n], int w[n],int m, int best)
{
    if(item>n)
    {
        return;
    }
    int wt = 0, pf = 0;
    for(int i=0; i<n; i++)
    {
        if(s[i] == '1')
        {
            wt+=w[i];
            pf+=p[i];
        }
    }
    
    if(wt>m)
    {
        return;
    }
    
    
    if(s[n-1] != '2')
    {
        if(pf>=best)
        {
            best = pf;
        }
        if(wt==m)
        {
            puts(s);
        }
        return;
    }
    
    s[item] = '0';
    for(int i = item+1; i<n;i++)
    {s[i] = '2';}
    knapsack(n,s,item+1,p,w,m,best);
    
    
    s[item] = '1';
    for(int i = item+1; i<n;i++)
    {s[i] = '2';}
    knapsack(n,s,item+1,p,w,m,best);
}


int main()
{
    int n,m;
    scanf("%d",&n);
    scanf("%d", &m);
    
    int p[n],w[n];
    char s[n];
    
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i]);
        s[i] = '2';
    }
    for(int i=0; i<n; i++)
    {
        scanf("%d", &w[i]);
    }
    
    knapsack(n,&s[0],0,p,w,m,0);
}