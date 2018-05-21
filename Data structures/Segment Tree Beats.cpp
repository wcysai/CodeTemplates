#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct node
{
	ll l,r,sum,maxx,secx,maxnum,lazy;
}seg[4*MAXN];
ll t,n,m,a[MAXN];
void Lazy(ll k)
{
	if(seg[k].l==seg[k].r||seg[k].lazy==INT_MAX) return;
	if(seg[k*2].lazy>=seg[k].lazy&&seg[k*2].maxx>seg[k].lazy)
	{
		seg[k*2].sum-=(seg[k*2].maxx-seg[k].lazy)*seg[k*2].maxnum;
		seg[k*2].maxx=seg[k].lazy;
		seg[k*2].lazy=seg[k].lazy;
	}
	if(seg[k*2+1].lazy>=seg[k].lazy&&seg[k*2+1].maxx>seg[k].lazy)
	{
		seg[k*2+1].sum-=(seg[k*2+1].maxx-seg[k].lazy)*seg[k*2+1].maxnum;
		seg[k*2+1].maxx=seg[k].lazy;
		seg[k*2+1].lazy=seg[k].lazy;
	}
	seg[k].lazy=INT_MAX;
	return;
}
void merge(ll k)
{
	seg[k].sum=seg[k*2].sum+seg[k*2+1].sum;
	seg[k].maxx=max(seg[k*2].maxx,seg[k*2+1].maxx);
	ll res=0,ans=-1;
	if(seg[k*2].maxx==seg[k].maxx) res+=seg[k*2].maxnum;
	if(seg[k*2+1].maxx==seg[k].maxx) res+=seg[k*2+1].maxnum;
	seg[k].maxnum=res;
	if(seg[k*2].maxx!=seg[k].maxx) ans=max(ans,seg[k*2].maxx);
	if(seg[k*2].secx!=seg[k].maxx) ans=max(ans,seg[k*2].secx);
	if(seg[k*2+1].maxx!=seg[k].maxx) ans=max(ans,seg[k*2+1].maxx);
	if(seg[k*2+1].secx!=seg[k].maxx) ans=max(ans,seg[k*2+1].secx);
	seg[k].secx=ans;
	//printf("l=%lld r=%lld maxx=%lld secx=%lld maxnum=%lld sum=%lld lazy=%lld\n",seg[k].l,seg[k].r,seg[k].maxx,seg[k].secx,seg[k].maxnum,seg[k].sum,seg[k].lazy);
}
void build(ll k,ll l,ll r)
{
	seg[k].l=l;seg[k].r=r;seg[k].lazy=INT_MAX;
	if(l==r)
	{
		seg[k].maxx=seg[k].sum=a[l];
		seg[k].maxnum=1;
		seg[k].secx=-1;
		return;
	}
	ll mid=(l+r)/2;
	build(k*2,l,mid);build(k*2+1,mid+1,r);
	merge(k);
}
void update(ll k,ll l,ll r,ll x)
{
	if(seg[k].l>r||seg[k].r<l||seg[k].maxx<=x) return;
	if(seg[k].l>=l&&seg[k].r<=r&&seg[k].secx<x)
	{
		seg[k].sum-=(seg[k].maxx-x)*seg[k].maxnum;
		seg[k].maxx=x;
		seg[k].lazy=x;
		return;
	}
	Lazy(k);
	update(k*2,l,r,x);update(k*2+1,l,r,x);
	merge(k);
}
ll query1(ll k,ll l,ll r)
{
	if(seg[k].l>r||seg[k].r<l) return 0;
	if(seg[k].l>=l&&seg[k].r<=r) return seg[k].maxx;
	Lazy(k);
	return max(query1(k*2,l,r),query1(k*2+1,l,r));
}
ll query2(ll k,ll l,ll r)
{
	if(seg[k].l>r||seg[k].r<l) return 0;
	if(seg[k].l>=l&&seg[k].r<=r) return seg[k].sum;
	Lazy(k);
	return query2(k*2,l,r)+query2(k*2+1,l,r);
}
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&m);
		for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
		build(1,1,n);
		for(ll i=1;i<=m;i++)
		{
			ll type,x,y,z;
			scanf("%lld",&type);
			if(type==0)
			{
				scanf("%lld%lld%lld",&x,&y,&z);
				update(1,x,y,z);
			}
			else if(type==1)
			{
				scanf("%lld%lld",&x,&y);
				printf("%lld\n",query1(1,x,y));
			}
			else
			{
				scanf("%lld%lld",&x,&y);
				printf("%lld\n",query2(1,x,y));
			}
		}
	}
	return 0;
}