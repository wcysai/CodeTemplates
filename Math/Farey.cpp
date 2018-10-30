#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll a,b,c,d,t;
P cal(ll a,ll b,ll c,ll d)
{
    //printf("%lld %lld %lld %lld\n",a,b,c,d);
    ll x=a/b+1;if(x*d<c) return P(x,1);
    if(!a) return P(1,d/c+1);
    if(a<=b&&c<=d)
    {
        P t=cal(d,c,b,a);
        swap(t.F,t.S); return t;
    }
    x=a/b;P t=cal(a-b*x,b,c-d*x,d);
    t.F+=t.S*x;return t;
}
int main()
{
    while(~scanf("%lld%lld%lld%lld",&a,&b,&c,&d))
    {
        t=__gcd(a,b),a/=t,b/=t,t=__gcd(c,d),c/=t,d/=t;
        printf("%lld %lld %lld %lld\n",a,b,c,d);
        P p=cal(a,b,c,d);
        printf("%lld/%lld\n",p.F,p.S);
    }
    return 0;
}
