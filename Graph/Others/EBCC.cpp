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
struct edge
{
    int u,v;
    edge(int u=0,int v=0):u(u),v(v){}
}E[2*MAXM];
vector<int> G[MAXN],bcc[MAXN];
int st[MAXN],dfn[MAXN],low[MAXN],bccno[MAXN];
bool isbridge[MAXN];
void add_edge(int u,int v)
{
    E[++mcnt]=(edge){u,v};G[u].push_back(mcnt);
    E[++mcnt]=(edge){v,u};G[v].push_back(mcnt);
}
void dfs(int v,int p)
{
    dfn[v]=low[v]=++tot;
    for(auto cnt:G[v])
    {
        int to=E[cnt].v;
        if(!dfn[to])
        {
            dfs(to,v);
            low[v]=min(low[v],low[to]);
            if(low[to]>dfn[v]) isbridge[cnt]
        else if(dfn[to]<dfn[v]&&to!=p) 
        {
            st[t++]=cnt;
            low[v]=min(low[v],dfn[to]);
        }
    }
}
int tarjan()
{
    bcc_cnt=t=tot=0;
    memset(dfn,0,sizeof(dfn));
    memset(iscut,0,sizeof(iscut));
    for(int i=1;i<=n;i++)
        if(!dfn[i]) dfs(i,0);
    return bcc_cnt;
}
int main()
{
    return 0;
}

