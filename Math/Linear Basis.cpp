#include<bits/stdc++.h>
#define MAXN 1000
using namespace std;
int p[63],a[MAXN];
int n;
int cal()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=62;j>=0;j--)
        {
            if(!p[j]) {p[j]=a[i]; break;}
            else a[i]^=p[j];
        }
    }
    for(int j=0;j<=62;j++) if(p[j]) r++;
    return r;
}
