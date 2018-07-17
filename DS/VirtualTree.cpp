#include<bits/stdc++.h>
#define MAXV 100005
#define INF 1000000000
#define MAXLOGV 20
using namespace std;
struct edge
{
    int to,cost;
};
vector<edge> G[MAXV];
vector<int> vt[MAXV];
int parent[MAXLOGV][MAXV];
int depth[MAXV],dfn[MAXV],dis[MAXV],st[MAXV];
int n,q,tot;
void add_edge(int from,int to)
{
    vt[from].push_back(to);
}
bool cmp(int x,int y)
{
    return dfn[x]<dfn[y];
}
void dfs(int v,int p,int d,int minx)
{
    dfn[v]=++tot;
    dis[v]=minx;
    parent[0][v]=p;
    depth[v]=d;
    for(int i=0;i<(int)G[v].size();i++)
        if(G[v][i].to!=p) dfs(G[v][i].to,v,d+1,min(minx,G[v][i].cost));
}
void init(int V)
{
    dfs(1,-1,0,INF);
    for(int k=0;k+1<MAXLOGV;k++)
    {
        for(int v=1;v<=V;v++)
        {
            if(parent[k][v]<0) parent[k+1][v]=-1;
            else parent[k+1][v]=parent[k][parent[k][v]];
        }
    }
}
int lca(int u,int v)
{
    if(depth[u]>depth[v]) swap(u,v);
    for(int k=0;k<MAXLOGV;k++)
    {
        if((depth[v]-depth[u])>>k&1)
            v=parent[k][v];
    }
    if(u==v) return u;
    for(int k=MAXLOGV-1;k>=0;k--)
    {
        if(parent[k][u]!=parent[k][v])
        {
            u=parent[k][u];
            v=parent[k][v];
        }
    }
    return parent[0][u];
}
void build_vtree(vector<int> &a)
{
    sort(a.begin(),a.end(),cmp);
    assert(a.size()>0);
    int t=0;
    st[t=1]=a[0];
    for(int i=1;i<(int)a.size();i++)
    {
        if(t==1) {st[++t]=a[i]; continue;}
        int l=lca(a[i],st[t]);
        if(l==st[t]) continue;
        while(t>1&&dfn[st[t-1]]>=dfn[l]) add_edge(st[t-1],st[t]),t--;
        if(l!=st[t]) add_edge(l,st[t]),st[t]=l;
        st[++t]=a[i];
    }
    while(t>0) add_edge(st[t-1],st[t]),t--;
}
int main()
{
    return 0;
}
