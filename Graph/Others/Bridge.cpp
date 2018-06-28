#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
vector<int> G[MAXN];
int fa[MAXN],low[MAXN],dfn[MAXN];
bool is_cut[MAXN];
int tot=0;
void tarjan(int v,int p)
{
    fa[v]=p;
    dfn[v]=low[v]=++tot;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(!dfn[to])
        {
            tarjan(to,v);
            low[v]=min(low[v],low[to]);
        }
        else if(p==to)
        {
            low[i]=min(low[i],dfn[to]);
        }
    }
}
void count()
{
    int rson=0;
    tarjan(1,0);
    for(int i=2;i<=n;i++)
    {
        int v=fa[i];
        if(v==1) rson++;
        else
        {
            if(low[i]>=dfn[v]) is_cut[v]=true;
        }
    }
    if(rson>1) is_cut[1]=true;
    for(int i=1;i<=n;i++)
    {
        int v=fa[i];
        if(v>0&&low[i]>dfn[v])
        {
            ;
        }
    }
}
int main()
{
    return 0;
}

