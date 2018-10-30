#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll inv2,inv6,a,b,c,l,r;//need initialize
struct E
{
    ll f,g,h;
    E(){}
    E(ll _f,ll _g,ll _h){f=_f,g=_g,h=_h;}
};
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=s*a%MOD;
        a=a*a%MOD;
        i>>=1;
    }
    return s;
}
// f:\sum_{i=0}^{n}\lfloor\frac{ai+b}{c}\rfloor
// g:\sum_{i=0}^{n}i\times\lfloor\frac{ai+b}{c}\rfloor
// g:\sum_{i=0}^{n}\lfloor\frac{ai+b}{c}\rfloor^{2}
E cal(ll a,ll b,ll c,ll n)
{
    if(!a) return E(0,0,0);
    E x,y;
    if(a>=c||b>=c)
    {
        x=cal(a%c,b%c,c,n);
        y.f=(a/c*n%MOD*(n+1)%MOD*inv2+b/c*(n+1)+x.f)%MOD;
        y.g=(a/c*n%MOD*(n+1)%MOD*(n*2+1)%MOD*inv6+b/c*(n+1)%MOD*n%MOD*inv2+x.g)%MOD;
        y.h=a/c*(a/c)%MOD*n%MOD*(n+1)%MOD*(n*2+1)%MOD*inv6%MOD;
        (y.h+=b/c*(b/c)%MOD*(n+1))%=MOD;
        (y.h+=a/c*(b/c)%MOD*n%MOD*(n+1))%=MOD;
        (y.h+=2LL*(a/c)%MOD*x.g)%=MOD;
        (y.h+=2LL*(b/c)%MOD*x.f)%=MOD;
        y.f=(y.f+MOD)%MOD;y.g=(y.g+MOD)%MOD;y.h=(y.h+MOD)%MOD;
        return y;
    }
    ll m=(a*n+b)/c;
    x=cal(c,c-b-1,a,m-1);
    y.f=(n*m-x.f)%MOD;
    y.g=y.g*inv2%MOD;
    y.h=(n*m%MOD*(m+1)-2LL*x.g-2LL*x.f-y.f)%MOD;
    y.f=(y.f+MOD)%MOD;y.g=(y.g+MOD)%MOD;y.h=(y.h+MOD)%MOD;
    return y;
}
int main()
{
    inv2=pow_mod(2,MOD-2);inv6=pow_mod(6,MOD-2);
    return 0;
}
