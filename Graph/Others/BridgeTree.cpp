#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,tot,t,bcc_cnt,mcnt;
vector<int> G[MAXN],bcc[MAXN];
int st[MAXN],dfn[MAXN],low[MAXN],bccno[MAXN];
int U[MAXM],V[MAXM];
bool isbridge[MAXM];
vector<int> tree[MAXN];
//bridge tree:
//edge-biconnected components are connected by bridges
void add_edge(int u,int v)
{
    U[++mcnt]=u;V[mcnt]=v;
    G[u].push_back(mcnt);G[v].push_back(mcnt);
}
int adj(int u,int e)
{
    return U[e]==u?V[e]:U[e];
}
void dfs1(int v,int edge)
{
    dfn[v]=low[v]=++tot;
    st[t++]=v;
    for(auto e:G[v])
    {
        if(e==edge) continue;
        int to=adj(v,e);
        if(!dfn[to])
        {
            dfs1(to,e);
            low[v]=min(low[v],low[to]);
        }
        else low[v]=min(low[v],dfn[to]);
    }
    if(low[v]==dfn[v]&&edge!=-1) isbridge[edge]=true;
}
void dfs2(int v)
{
    dfn[v]=1;
    bccno[v]=bcc_cnt;
    bcc[bcc_cnt].push_back(v);
    for(auto e:G[v])
    {
        int to=adj(v,e);
        if(isbridge[e]) continue;
        if(!dfn[to]) dfs2(to);
    }
}
int tarjan()
{
    bcc_cnt=tot=0;
    memset(dfn,0,sizeof(dfn));
    memset(isbridge,false,sizeof(isbridge));
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs1(i,-1);
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            bcc_cnt++;
            dfs2(i);
        }
    }
    return bcc_cnt;
}
void build_bridge_tree()
{
    tarjan();
    for(int i=1;i<=mcnt;i++)
    {
        if(isbridge[i])
        {
            int u=bccno[U[i]],v=bccno[V[i]];
            tree[u].push_back(v);tree[v].push_back(u);
        }
    }
}

