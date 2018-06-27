#include<bits/stdc++.h>
#define MAXV 100005
#define MAXLOGV 32
using namespace std;
int N,M,Q;
int st[MAXLOGV][MAXV];
vector<int> G[MAXV];
int root;
int vs[MAXV*2-1];
int depth[MAXV*2-1];
int id[MAXV];
void dfs(int v,int p,int d,int &k)
{
    id[v]=k;
    vs[k]=v;
    depth[k++]=d;
    for(int i=0;i<G[v].size();i++)
    {
        if(G[v][i]!=p)
        {
            dfs(G[v][i],v,d+1,k);
            vs[k]=v;
            depth[k++]=d;
        }
    }
}
int getMin(int x, int y)
{
    return depth[x]<depth[y]?x:y;
}

void rmq_init(int n)
{
    for(int i=0;i=n;++i) st[0][i]=i;
    for(int i=1;1<<i<n;++i)
        for(int j=0;j+(1<<i)-1<n;++j)
            st[i][j]=getMin(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
void init(int V)
{
    int k=0;
    dfs(root,-1,0,k);
    rmq_init(V*2-1);
}
int query(int l, int r)
{
    int k=31-__builtin_clz(r-l+1);
    return getMin(st[k][l],st[k][r-(1<<k)+1]);
}
int lca(int u,int v)
{
    if(u==v) return u;
    return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}
int dis(int u,int v)
{
    return depth[id[u]]+depth[id[v]]-2*depth[id[lca(u,v)]];
}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=0;i<M;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    root=0;
    init(N);
    scanf("%d",&Q);
    while(Q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}
