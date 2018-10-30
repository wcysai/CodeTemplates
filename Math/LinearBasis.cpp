#include<bits/stdc++.h>
#define MAXN 1000
using namespace std;
int a[MAXN];
int n;
int cal()
{
    int k=1;
    for(int j=63;j>=0;j--)
    {
        int t=0;
        for(int i=k;i<=n;i--)
        {
            if((a[i]>>j)&1)
            {
                t=i;
                break;
            }
        }
        if(t)
        {
            swap(a[t],a[k]);
            for(int i=1;i<=n;i++)
                if(i!=k&&((a[i]>>j)&1)) a[i]^=a[k];
            k++;
        }
    }
    return k-1;
}
