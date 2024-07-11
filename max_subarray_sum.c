#include<stdio.h>

int subArrSum(int* arr, int beg, int end, int* first,int* last)
{
    if(beg == end)
    {
        return arr[beg];
    }
    
    int mid = (beg+end)/2;
    
    int ls = subArrSum(arr, beg, mid, first, last);
    int rs = subArrSum(arr, mid+1, end, first, last);
    
    int lss = arr[mid];
    int rss = arr[mid+1];
    
    int l = mid, r = mid+1;
    for(int i = beg; i<= mid -1; i++)
    {
        int tlss = 0;
        for(int j = i; j<=mid; j++)
        {
            tlss+=arr[j];
        }
        // lss = tlss>lss?tlss:lss;
        if(tlss>lss)
        {
            lss = tlss;
            l = i;
        }
    }
    
    for(int i = mid+2; i<=end; i++)
    {
        int trss = 0;
        for(int j = mid+1; j<=i; j++)
        {
            trss+=arr[j];
        }
        if(trss>rss)
        {
            rss = trss;
            r = i;
        }
    }
    
    int cs = lss+rss;
    int max = 0;
    
    if(cs>ls && cs>rs)
    {
        max = cs;
        *first = l;
        *last = r;
    }
    
    return max;
}

int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    
    for(int i=0; i<n;i++)
    {
        scanf("%d", &a[i]);
    }
    
    int first = a[n/2], last = a[n/2 + 1];
    
    int ans = subArrSum(a, 0, n-1, &first, &last);
    
    printf("The maximum sub array is [%d", a[first]);
    for(int x = first+1; x<=last; x++)
    {
        printf(" %d", a[x]);
    }
    printf("]\nThe maximum sub array sum is :");
    printf("%d", ans);
    
    return 0;
}