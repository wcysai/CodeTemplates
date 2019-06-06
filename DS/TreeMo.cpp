#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXM 200005
#define MAXLOGN 20
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,tot,st[2*MAXN],ed[2*MAXN],loc[2*MAXN],val[MAXN];
vector<int> dis;
vector<int> G[MAXN];
int spt[MAXLOGN+1][4*MAXN];
int vs[MAXN*2],depth[MAXN*2];
int id[MAXN],pos[2*MAXN],cnt[MAXN],now,sum;
bool vis[MAXN];
vector<int> v;
void dfs(int v,int p,int d,int &k)
{
    st[v]=++tot; loc[tot]=v;
    id[v]=k;
    vs[k]=v;
    depth[k++]=d;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v,d+1,k);
        vs[k]=v;
        depth[k++]=d;
    }
    ed[v]=++tot;
    loc[tot]=v;
}
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
int getMin(int x, int y)
{
    return depth[x]<depth[y]?x:y;
}

void rmq_init(int n)
{
    for(int i=1;i<=n;++i) spt[0][i]=i;
    for(int i=1;1<<i<n;++i)
        for(int j=1;j+(1<<i)-1<=n;++j)
            spt[i][j]=getMin(spt[i-1][j],spt[i-1][j+(1<<(i-1))]);
}
void init(int V)
{
    int k=0;
    dfs(1,0,0,k);
    rmq_init(V*2-1);
}
int query(int l, int r)
{
    int k=31-__builtin_clz(r-l+1);
    return getMin(spt[k][l],spt[k][r-(1<<k)+1]);
}
int lca(int u,int v)
{
    if(u==v) return u;
    return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}

struct qry
{
    int u,v;
    int l,r,z,id;
}Q[MAXM];
bool cmp(qry a,qry b)
{
    return pos[a.l]==pos[b.l]?a.r<b.r:pos[a.l]<pos[b.l];
}
void deal(int x)
{
    if(!vis[x])
    {
        if(!cnt[val[x]]) now++;
        cnt[val[x]]++;
        sum++;
    }
    else
    {
        cnt[val[x]]--;
        assert(cnt[val[x]]>=0);
        if(!cnt[val[x]]) now--;
        sum--;
    }
    vis[x]^=1;
}
int ans[MAXM];
const int blocks=200;
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&val[i]);
        dis.push_back(val[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    for(int i=1;i<=n;i++) val[i]=lower_bound(dis.begin(),dis.end(),val[i])-dis.begin();
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
    init(n);
    assert(tot==2*n);
    for(int i=1;i<=tot;i++) pos[i]=i/blocks+1;
    for(int i=1;i<=q;i++)
    {
        Q[i].id=i;
        int u,v;
        scanf("%d%d",&u,&v);
        Q[i].u=u; Q[i].v=v;
        if(st[u]>st[v]) swap(u,v);
        int z=lca(u,v);
        if(z==u) Q[i].l=st[u],Q[i].r=st[v];
        else Q[i].l=ed[u],Q[i].r=st[v],Q[i].z=z;
    }
    sort(Q+1,Q+q+1,cmp);
    int l=1,r=0;
    memset(cnt,0,sizeof(cnt));
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=q;i++)
    {
        if(r<Q[i].r) {for(r++;r<=Q[i].r;r++) deal(loc[r]); r--;}
        if(r>Q[i].r) {for(;r>Q[i].r;r--) deal(loc[r]); }
        if(l<Q[i].l) {for(;l<Q[i].l;l++) deal(loc[l]); }
        if(l>Q[i].l) {for(l--;l>=Q[i].l;l--) deal(loc[l]); l++;}
        if(Q[i].z) deal(Q[i].z);
        ans[Q[i].id]=now;
        if(Q[i].z) deal(Q[i].z);
    }
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);          
    return 0;
}
