#include<bits/stdc++.h>
#define MAXV 1000
#define MAXE 10000
#define INF 1000000
using namespace std;
struct edge{int to,cost;};
typedef pair<int,int> P;
int V;
vector<edge> G[MAXV];
int d[MAXV];
bool inque[MAXV];
queue<int> que;
void spfa(int s)
{
    fill(d,d+V,INF);
    fill(inque,inque+V,false);
    d[s]=0;
    while(!que.empty()) que.pop();
    que.push(s);
    inque[s]=true;
    while(!que.empty())
    {
        int u=que.front();
        que.pop();
        for(int i=0;i<G[u].size();i++)
        {
            if(d[u]+G[u][i].cost<d[G[u][i].to])
            {
                d[G[u][i].to]=d[u]+G[u][i].cost;
                if(!inque[G[u][i].to])
                {
                    inque[G[u][i].to]=true;
                    que.push(G[u][i].to);
                }
            }
        }
        inque[u]=false;
    }
}
int main()
{
    return 0;
}
