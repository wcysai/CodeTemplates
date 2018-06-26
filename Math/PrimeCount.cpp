#include<bits/stdc++.h>
#define MAXN 1000005// MAXN=sqrt(upper_bound)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll f[MAXN],g[MAXN],n,k; //f[i]:pi(n/i),g[i]:pi(i)
ll PrimeCount(ll n)
{
    ll i,j,m=0;
    for(m=1;m*m<=n;m++) f[m]=n/m-1;
    for(i=2;i<=m;i++) g[i]=i-1;
    for(i=2;i<=m;i++)
    {
        if(g[i]==g[i-1]) continue;
        for(j=1;j<=min(m-1,n/i/i);++j)
        {
            if(i*j<m) f[j]-=f[i*j]-g[i-1];
            else f[j]-=g[n/i/j]-g[i-1];
        }
        for(j=m;j>=i*i;j--) g[j]-=g[j/i]-g[i-1];
    }
    return f[1];
}
int main()
{
    while(scanf("%lld",&n)==1)
    {
        printf("%lld\n",PrimeCount(n));
    }
    return 0;
}
