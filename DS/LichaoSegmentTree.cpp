#include<bits/stdc++.h>
#define MAXN 80005
#define MAXM 10000005
#define MAXT 1000000001
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
int n,q,tot,lson[MAXM],rson[MAXM];
bool has[MAXM];
P ans[MAXM];
ll f(P p,int x)
{
    return 1LL*p.F*x+p.S;
}
void insert(int &k,int l,int r,int x,int y,P p)
{
    if(l>y||x>r) return;
    if(!k) k=++tot;
    has[k]=false;
    if(l>=x&&r<=y)
    {
        if(!has[k])
        {
            has[k]=true;
            ans[k]=p;
            return;
        }
        ll trl=f(ans[k],l),trr=f(ans[k],r);
        ll vl=f(p,l),vr=f(p,r);
        if(trl<=vl&&trr<=vr) return;
        if(trl>=vl&&trr>=vr) {ans[k]=p; return;}
        int mid=(l+r)/2;
        if(trl>=vl) swap(ans[k],p);
        if(f(ans[k],mid)<=f(p,mid)) insert(rson[k],mid+1,r,x,y,p);
        else swap(ans[k],p),insert(lson[k],l,mid,x,y,p);
        return;
    }
    int mid=(l+r)/2;
    insert(lson[k],l,mid,x,y,p); insert(rson[k],mid+1,r,x,y,p);
}
ll query(int &k,int l,int r,int x)
{
    if(!k) return INF;
    ll res=(!has[k]?INF:f(ans[k],x));
    if(l==r) return res;
    int mid=(l+r)/2;
    if(x<=mid) return min(res,query(lson[k],l,mid,x));
    else return min(res,query(rson[k],mid+1,r,x));
}
