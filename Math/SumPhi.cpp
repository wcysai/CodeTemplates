#include<bits/stdc++.h>
#define MAXN 5000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
bool is_prime[MAXN];
ll cnt,phi[MAXN],prime[MAXN];
ll n,f[MAXN];
map<ll,ll> mp;
ll mul_mod(ll a,ll i)
{
	ll s=0;a%=MOD;
	while(i)
	{
		if(i&1) s=(s+a)%MOD;
		a=(a+a)%MOD;
		i>>=1;
	}
	return s;
}
 
ll pow_mod(ll a,ll i)
{
	ll s=1;
	while(i)
	{
		if(i&1) s=mul_mod(s,a);
		a=mul_mod(a,a);
		i>>=1;
	}
	return s;
}
void genphi(ll n)
{
    ll p=0;
    memset(phi,0,sizeof(phi));
    phi[1]=1;
     for(ll i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    for(ll i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; phi[i]=i-1;}
        for(ll j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            phi[i*prime[j]]=phi[i]*(i%prime[j]?prime[j]-1:prime[j]);
            if(i%prime[j]==0) break;
        }
    }
    for(ll i=1;i<=n;i++) f[i]=(f[i-1]+phi[i])%MOD;
}
ll calc(ll x)
{
	if(x<=5000000) return f[x];
	if(mp.find(x)!=mp.end()) return mp[x];
	ll ans=mul_mod(mul_mod(x,x+1),pow_mod(2,MOD-2));
	for(ll i=2,r;i<=x;i=r+1)
	{
		r=x/(x/i);
		ans=(ans-calc(x/i)*((r-i+1)%MOD)%MOD+MOD)%MOD;
	}
	return mp[x]=ans;
}
int main()
{
	genphi(5000000);
	scanf("%lld",&n);
	printf("%lld\n",calc(n));
	return 0;
}