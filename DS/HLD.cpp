#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct node
{
    int l,r,maxi,sum;
};
int tot,q,n,k,a[MAXN];
int pa[MAXN],dep[MAXN],sz[MAXN],wson[MAXN],top[MAXN],spos[MAXN],tpos[MAXN];
struct segtree
{
    node seg[4*MAXN];
    int id[MAXN];
    void build(int k,int l,int r)
    {
        seg[k].l=l;seg[k].r=r;
        if(l==r)
        {
            seg[k].maxi=seg[k].sum=a[tpos[l]];
            id[l]=k;
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        seg[k].maxi=max(seg[k*2].maxi,seg[k*2+1].maxi);
        seg[k].sum=seg[k*2].sum+seg[k*2+1].sum;
    }      
    void update(int k,int x)
    {
        k=id[k];
        seg[k].maxi=seg[k].sum=x;
        while(k>1)
        {
            k=k/2;
            seg[k].maxi=max(seg[k*2].maxi,seg[k*2+1].maxi);
            seg[k].sum=seg[k*2].sum+seg[k*2+1].sum;
        }
    }
    int query1(int k,int l,int r)
    {
        if(seg[k].l>r||seg[k].r<l) return -INF;
        if(seg[k].l>=l&&seg[k].r<=r) return seg[k].maxi;
        return max(query1(k*2,l,r),query1(k*2+1,l,r));
    }
    int query2(int k,int l,int r)
    {
        if(seg[k].l>r||seg[k].r<l) return 0;
        if(seg[k].l>=l&&seg[k].r<=r) return seg[k].sum;
        return query2(k*2,l,r)+query2(k*2+1,l,r);
    }
    int query_max(int l,int r) 
    {
        return query1(1,l,r);
    }
    int query_sum(int l,int r)
    {
        return query2(1,l,r);
    }
}tree;
vector<int> G[MAXN];
void dfs1(int v,int p,int d)
{
    dep[v]=d;pa[v]=p;sz[v]=1;
    for(int i=0;i<G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p) continue;
        dfs1(to,v,d+1);
        if(sz[to]>sz[wson[v]]) wson[v]=to;
        sz[v]+=sz[to];
    }
}
void dfs2(int v,int p,int num)
{
    top[v]=num;
    spos[v]=++tot;
    tpos[tot]=v;
    if(wson[v]) dfs2(wson[v],v,num);
    for(int i=0;i<G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p||to==wson[v]) continue;
        dfs2(to,v,to);
    }
}
void init()
{
    tot=0;dfs1(1,1,1);
    dfs2(1,0,1);
    tree.build(1,1,n);
}
void update(int k,int x)
{
    tree.update(spos[k],x);
}
int query_max(int u,int v)
{
    int res=-INF;
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        res=max(res,tree.query_max(spos[top[u]],spos[u]));
        u=pa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    res=max(res,tree.query_max(spos[v],spos[u]));
    return res;
}
int query_sum(int u,int v)
{
    int res=0;
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        res+=tree.query_sum(spos[top[u]],spos[u]);
        u=pa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    res+=tree.query_sum(spos[v],spos[u]);
    return res;
}
char str[10];
int x,y;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
    }
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    init();
    scanf("%d",&q);
    while(q--)
    {
        scanf("%s%d%d",str,&x,&y);
        if(str[1]=='H') update(x,y);
        if(str[1]=='M') printf("%d\n",query_max(x,y));
        if(str[1]=='S') printf("%d\n",query_sum(x,y));
    }
    return 0;
}

