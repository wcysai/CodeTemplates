#include<bits/stdc++.h>
#define MAXN 100000
using namespace std;
int phi[MAXN];
int phi1(int n)
{
    int res=n;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            res=res/i*(i-1);
            for(;n%i==0;n/=i);
        }
    }
    if(n!=1) res=res/n*(n-1);
    return res;
}
void phi2()
{
    for(int i=0;i<MAXN;i++) phi[i]=i;
    for(int i=2;i<MAXN;i++)
        if(phi[i]==i)
            for(int j=i;j<MAXN;j+=i) phi[j]=phi[j]/i*(i-1);
}
int main()
{
    return 0;
}
