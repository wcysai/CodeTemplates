#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,t,c[MAXN],sz[MAXN],st[MAXN],ed[MAXN],cnt[MAXN],rev[MAXN];
vector<int> G[MAXN];
void dfs(int v,int p)
{
    st[v]=++t;rev[t]=v;
    sz[v]=1;
    for(int i=0;i<(int)G[v].size();i++)
    {
        if(G[v][i]==p) continue;
        dfs(G[v][i],v);
        sz[v]+=sz[G[v][i]];
    }
    ed[v]=t;
    return;
}
void dfs2(int v,int p,bool keep)
{
    int mx=-1,wson=-1;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p) continue;
        if(sz[to]>mx) {mx=sz[to]; wson=to;}
    }
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p||to==wson) continue;
        dfs2(to,v,0);
    }
    if(wson!=-1) dfs2(wson,v,1);
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p||to==wson) continue;
        for(int j=st[to];j<ed[to];j++)
            cnt[c[rev[j]]]++;
    }
    cnt[c[v]]++;
    //answer queries here
    if(!keep) 
    {
        for(int j=st[v]lj<ed[v];j++)
            cnt[c[rev[j]]]--;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1,0);
}
