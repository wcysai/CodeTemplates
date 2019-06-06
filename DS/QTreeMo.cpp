#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 100005
#define MAXLOGN 20
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,q,tot,ctot,qtot,st[2*MAXN],ed[2*MAXN],loc[2*MAXN],val[MAXN];
int V[MAXN],W[MAXM],C[MAXN];
vector<int> dis;
vector<int> G[MAXN];
int spt[MAXLOGN+1][4*MAXN];
int vs[MAXN*2],depth[MAXN*2];
int id[MAXN],pos[2*MAXN],cnt[MAXN];
P change[MAXN];
ll res;
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
    int l,r,z,ti,id;
}Q[MAXM];
bool cmp(qry a,qry b)
{
    if(pos[a.l]!=pos[b.l]) return pos[a.l]<pos[b.l];
    if(pos[a.r]!=pos[b.r]) return pos[a.r]<pos[b.r];
    if(pos[a.r]&1) return a.ti>b.ti; else return a.ti<b.ti;
}
void deal(int x)
{
    if(!vis[x])
    {
        cnt[C[x]]++;
        res+=1LL*W[cnt[C[x]]]*V[C[x]];
    }
    else
    {
        res-=1LL*W[cnt[C[x]]]*V[C[x]];
        cnt[C[x]]--;
    }
    vis[x]^=1;
}
void modify(int ti)
{
    int x=change[ti].F,y=change[ti].S;
    if(vis[x])
    {
        res-=1LL*W[cnt[C[x]]]*V[C[x]];
        cnt[C[x]]--;
        cnt[y]++;
        res+=1LL*W[cnt[y]]*V[y];
    }
    swap(C[change[ti].F],change[ti].S);
}
ll ans[MAXM];
const int blocks=2000;
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++) scanf("%d",&V[i]);
    for(int i=1;i<=n;i++) scanf("%d",&W[i]);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
    for(int i=1;i<=n;i++) scanf("%d",&C[i]);
    init(n);
    for(int i=1;i<=tot;i++) pos[i]=i/blocks+1;
    for(int i=1;i<=q;i++)
    {
        int type,u,v;
        scanf("%d%d%d",&type,&u,&v);
        if(type==0) change[++ctot]=P(u,v);
        else
        {
            ++qtot;
            Q[qtot].id=qtot;
            Q[qtot].ti=ctot;
            if(st[u]>st[v]) swap(u,v);
            int z=lca(u,v);
            if(z==u) Q[qtot].l=st[u],Q[qtot].r=st[v];
            else Q[qtot].l=ed[u],Q[qtot].r=st[v],Q[qtot].z=z;
        }
    }
    sort(Q+1,Q+qtot+1,cmp);
    int l=1,r=0,ti=0;
    memset(cnt,0,sizeof(cnt));
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=qtot;i++)
    {
        if(r<Q[i].r) {for(r++;r<=Q[i].r;r++) deal(loc[r]); r--;}
        if(r>Q[i].r) {for(;r>Q[i].r;r--) deal(loc[r]); }
        if(l<Q[i].l) {for(;l<Q[i].l;l++) deal(loc[l]); }
        if(l>Q[i].l) {for(l--;l>=Q[i].l;l--) deal(loc[l]); l++;}
        if(Q[i].z) deal(Q[i].z);
        while(ti<Q[i].ti) modify(++ti);
        while(ti>Q[i].ti) modify(ti--);
        ans[Q[i].id]=res;
        if(Q[i].z) deal(Q[i].z);
    }
    for(int i=1;i<=qtot;i++) printf("%lld\n",ans[i]);          
    return 0;
}
