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
int st[MAXN],dfn[MAXN],low[MAXN];
bool art[MAXN];
void dfs(int v,int p,int &tot)
{
    dfn[v]=low[v]=++tot;
    st[t++]=v;
    for(auto to:G[v])
    {
        if(!dfn[to])
        {
            dfs(to,v,tot);
            low[v]=min(low[v],low[to]);
            if(low[to]>=dfn[v])
            {
                art[to]=(dfn[v]>1||dfn[to]>2);
                bcc_cnt++;
                bcc[bcc_cnt].push_back(v);
                while(bcc[bcc_cnt].back()!=v)
                    bcc[bcc_cnt].push_back(st[t-1]),t--;
            }
        }
        else low[v]=min(low[v],dfn[to]);
    }
}
int tarjan()
{
    bcc_cnt=tot=0;
    memset(dfn,0,sizeof(dfn));
    memset(art,false,sizeof(art));
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i,-1,t=0);
}
int main()
{
    return 0;
}

