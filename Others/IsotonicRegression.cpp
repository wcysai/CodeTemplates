#include<bits/stdc++.h>
#define MAXN 1005
#define MAXV 500005
#define MAXE 1000005
#define INF 1000000000
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int n,m,sz,a[MAXN],ans[MAXN];
vector<int> g[MAXN];
vector<int> dis;
struct edge{int to,cap,rev;};
int V;
vector<edge> G[MAXN];
bool valid[MAXN],good[MAXN],vis[MAXN];
int level[MAXN];
int iter[MAXN];
void add_edge(int from,int to,int cap)
{
    G[from].push_back((edge){to,cap,(int)G[to].size()});
    G[to].push_back((edge){from,0,(int)G[from].size()-1});
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s]=0;
    que.push(s);
    while(!que.empty())
    {
        int v=que.front(); que.pop();
        for(int i=0;i<(int)G[v].size();i++)
        {
            edge &e=G[v][i];
            if(e.cap>0&&level[e.to]<0)
            {
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v,int t,int f)
{
    if(v==t) return f;
    for(int &i=iter[v];i<(int)G[v].size();i++)
    {
        edge &e=G[v][i];
        if(level[v]<level[e.to]&&e.cap>0)
        {
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0)
            {
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
int max_flow(int s,int t)
{
    int flow=0;
    for(;;)
    {
        bfs(s);
        if(level[t]<0) return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while((f=dfs(s,t,INF))>0)
          flow+=f;
    }
}
void dfs2(int v)
{
    vis[v]=true;
    if(v!=n+1||v!=n+2) good[v]=true;
    for(auto e:G[v])
    {
        if(e.cap==0) continue;
        if(!vis[e.to]) dfs2(e.to);
    }
}
void solve(int l,int r,vector<int> &v)
{
    if(!v.size()) return;
    if(l==r) 
    {
        for(auto x:v) ans[x]=dis[l];
        return;
    }
    int mid=(l+r)/2;
    for(auto x:v) G[x].clear(),valid[x]=true,good[x]=false,vis[x]=false;
    int s=n+1,t=n+2;
    G[s].clear(); G[t].clear();
    for(auto x:v)
    {
        int cost;
        if(a[x]>=dis[mid+1]) cost=1; else cost=-1;
        if(cost>=0) add_edge(s,x,1); else add_edge(x,t,1);
        for(auto to:g[x]) if(valid[to]) add_edge(x,to,INF);
    } 
    vector<int> lhs,rhs;
    max_flow(s,t);
    dfs2(s);
    for(auto x:v) if(good[x]) rhs.push_back(x); else lhs.push_back(x);
    for(auto x:v) valid[x]=false;
    solve(l,mid,lhs); solve(mid+1,r,rhs);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        dis.push_back(a[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
    }
    sz=(int)dis.size();
    vector<int> v;
    for(int i=1;i<=n;i++) v.push_back(i);
    solve(0,sz-1,v);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
