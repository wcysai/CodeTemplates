#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<deque>
#include<stack>
#include<map>
#define MAXN 1005000
using namespace std;
typedef long long ll;
vector<ll> a;
ll pow_mod(ll a,ll i,ll mod)
{
    if(i==0) return 1;
     ll s=1;
    while(i>0)
     {
         if(i&1) s=(s*a)%mod;
         a=(a*a)%mod;
         i>>=1;
     }
     return s;
}
bool g_test(ll g,ll p)
{
    for(ll i=0;i<a.size();i++)
        if(pow_mod(g,(p-1)/a[i],p)==1)
            return 0;
    return 1;
}
ll primitive_root(ll p)
{
    ll tmp=p-1;
    for(ll i=2;i<=tmp/i;i++)
        if(tmp%i==0)
        {
            a.push_back(i);
            while(tmp%i==0)
                tmp/=i;
        }
    if(tmp!=1)
    {
        a.push_back(tmp);
    }
    ll g=1;
    while(true)
    {
        if(g_test(g,p))
            return g;
        ++g;
    }
}
int main()
{
    ll n;
    while(scanf("%lld",&n)==1)
        printf("%lld\n",primitive_root(n));
    return 0;
}
