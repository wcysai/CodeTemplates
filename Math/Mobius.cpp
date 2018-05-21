#include<bits/stdc++.h>
#define MAXN 1<<20
using namespace std;
int mu[MAXN];
void getMu()
{
    for(int i=1;i<=n;i++)
    {
        int target=i==1?1:0;
        int delta=target-mu[i];
        mu[i]=delta;
        for(int j=i+i;j<=n;j+=i)
            mu[j]+=delta;
    }
    return;
}
int main()
{
    return 0;
}
