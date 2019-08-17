#include<bits/stdc++.h>
#define MAXV 3005
#define MAXE 50000
#define INF 1000000000
using namespace std;
typedef pair<int,int> P;
typedef long long ll;
struct edge{int to,cap,rev,id;};//id=1 positive edge, id=0 reverse edge
struct edge2{int to,cost;};
struct edge3{int from,to,cap;};
int V,E;
vector<edge> G[MAXV];
vector<edge2> gh[MAXV];
vector<edge3>  edges;
int level[MAXV];
int iter[MAXV];
void add_edge(int from,int to,int cap)
{
    edges.push_back((edge3){from,to,cap});
}
void add_all()
{
    for(auto e:edges)
    {
        G[e.from].push_back((edge){e.to,e.cap,(int)G[e.to].size(),1});
        G[e.to].push_back((edge){e.from,0,(int)G[e.from].size()-1,0});
    }
}
void clear_all()
{
    for(int i=1;i<=V;i++) G[i].clear();
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
//0-based!!!
void build_gomory_hu_tree()
{
    vector<int> p(V+1,1),cap(V+1,0);
    for(int s=2;s<=V;s++)
    {
        add_all();
        int t=p[s];
        cap[s]=max_flow(s,t);
        vector<bool> in_cut(V+1,0);
        queue<int> que({s});
        in_cut[s]=true;
        while(!que.empty())
        {
            int v=que.front();
            que.pop();
            for(auto e:G[v])
            {
                if(e.cap>0&&!in_cut[e.to])
                {
                    in_cut[e.to]=true;
                    que.push(e.to);
                }
            }
        }
        for(int v=1;v<=V;v++)
            if(v!=s&&in_cut[v]&&p[v]==t)
                p[v]=s;
        if(in_cut[p[t]])
        {
            p[s]=p[t];
            p[t]=s;
            swap(cap[s],cap[t]);
        }
        clear_all();
    }
    for(int v=2;v<=V;v++)
    {
        gh[p[v]].push_back((edge2){v,cap[v]});
        gh[v].push_back((edge2){p[v],cap[v]});
    }
}
int main()
{
    scanf("%d%d",&V,&E);
    for(int i=0;i<E;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    build_gomory_hu_tree();
    return 0;
}
