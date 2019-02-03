#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 2000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,sz,tot,root[MAXN],a[MAXN],ans[MAXN];
int cnt[MAXM],lson[MAXM],rson[MAXM];
vector<int> G[MAXN];
vector<int> v;
//ask for how many a[j]<a[i] if j is in the subtree of i for every i from 1..n
//time complexity:O(nlogn)
void pushup(int k)
{
    cnt[k]=cnt[lson[k]]+cnt[rson[k]];
}
void build(int &k,int l,int r,int p)
{
    k=++tot;
    if(l==r)
    {
        cnt[k]=1;
        return;
    }
    int mid=(l+r)/2;
    if(p<=mid) build(lson[k],l,mid,p);
    else build(rson[k],mid+1,r,p);
    pushup(k);
}
int merge(int x,int y,int l,int r)
{
    if(!x) return y;
    if(!y) return x;
    if(l==r) 
    {
        cnt[x]+=cnt[y];
        return x;
    }
    int mid=(l+r)/2;
    lson[x]=merge(lson[x],lson[y],l,mid);
    rson[x]=merge(rson[x],rson[y],mid+1,r);
    pushup(x);
    return x;
}
int query(int k,int l,int r,int x)
{
    if(k==0) return 0;
    if(r<x) return 0;
    if(l>=x) return cnt[k];
    int mid=(l+r)/2;
    return query(lson[k],l,mid,x)+query(rson[k],mid+1,r,x);
}
void dfs(int v,int p)
{
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        root[v]=merge(root[v],root[to],1,sz);
    }
    ans[v]=query(root[v],1,sz,a[v]+1);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=1;i<=n;i++) a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
    sz=(int)v.size();
    for(int i=2;i<=n;i++)
    {
        int p;scanf("%d",&p);
        G[p].push_back(i);G[i].push_back(p);
    }
    for(int i=1;i<=n;i++) build(root[i],1,sz,a[i]);
    dfs(1,0);
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
}

