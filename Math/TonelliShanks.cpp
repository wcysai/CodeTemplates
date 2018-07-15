#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
ll pow_mod(ll a,ll i,ll m)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=s*a%m;
        a=a*a%m;
        i>>=1;
    }
    return s;
}
ll Tonelli_Shanks(ll n,ll p)
{
    if(p==2) return (n&1)?1:-1;
    if(pow_mod(n,p>>1,p)!=1) return -1;
    if(p&2) return pow_mod(n,(p+1)>>2,p);
    int s=__builtin_ctzll(p^1);
    ll q=p>>s,z=2;
    for(;pow_mod(z,p>>1,p)==1;++z);
    ll c=pow_mod(z,q,p),r=pow_mod(n,(q+1)>>1,p),t=pow_mod(n,q,p),tmp;
    for(int m=s,i;t!=1;)
    {
        for(i=0,tmp=t;tmp!=1;++i) tmp=tmp*tmp%p;
        for(;i<--m;) c=c*c%p;
        r=r*c%p;c=c*c%p;t=t*c%p;
    }
    return r;
}
int main()
{
    ll n,p;
    while(scanf("%lld%lld",&n,&p)==2) printf("%lld\n",Tonelli_Shanks(n,p));
    return 0;
}

