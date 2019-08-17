#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll N,tot,t,now;
P st[MAXN];
void add(ll u,ll v)
{
    P p=P(u,v);
    while(t-now>1&&(st[t-1].F-st[t-2].F)*(p.S-st[t-1].S)<=(st[t-1].F-p.F)*(st[t-2].S-st[t-1].S)) t--;
    st[t++]=p;
}
bool cmp(P x,P y)
{
    if(x.S!=y.S) return x.S<y.S;
    return x.F<y.F;
}
ll query(ll x)
{
    ll l=-1,r=t-1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(st[mid].F*x+st[mid].S<=st[mid+1].F*x+st[mid+1].S) l=mid;
        else r=mid;
    }
    return st[r].F*x+st[r].S;
}
int main()
{
}
