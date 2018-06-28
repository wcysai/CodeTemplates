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
struct Edge
{
    int u,v;
    Edge(int u=0,int v=0):u(u),v(v){}
}e[MAXM];
int n,m,stamp,dfn[MAXN],low[MAXN],bccno[MAXN],bcc_cnt;
vector<int> vec[MAXN],bcc[MAXN];
bool g[MAXN][MAXN],isbridge[MAXM];

void tarjan(int tot,int fa)
{
    int tmp;
    dfn[tot]=low[tot]=++stamp;
    for(int i=0;i<(int)vec[tot].size();i++)
    {
        tmp=e[vec[tot][i]].v;
        if(!dfn[tmp])
        {
            tarjan(tmp,tot);
            low[tot]=min(low[tot],low[tmp]);
            if(low[tmp]>dfn[tot])
                isbridge[vec[tot][i]]=isbridge[vec[tot][i]^1]=1;
        }
        else if(dfn[tmp]<dfn[tot] && tmp!=fa)
        {
            low[tot]=min(low[tot], dfn[tmp]);
        }
    }
}

void dfs(int tot)
{
    dfn[tot]=1;
    bccno[tot]=bcc_cnt;
    for(int i=0;i<(int)vec[tot].size();i++)
    {
        int tmp=vec[tot][i];
        if(isbridge[tmp])
            continue;
        if(!dfn[e[tmp].v])
        {
            dfs(e[tmp].v);
        }
    }
}

void find_ebcc(){
    bcc_cnt=stamp=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(isbridge,0,sizeof(isbridge));
    memset(bccno,0,sizeof(bccno));
    memset(bcc,0,sizeof(bcc));
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i, -1);
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            bcc_cnt++;
            dfs(i);
        }
    }               
}
int main()
{
    return 0;
}
