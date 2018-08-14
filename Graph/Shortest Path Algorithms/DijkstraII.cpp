#include<bits/stdc++.h>
#define MAXV 1000
#define MAXE 10000
#define INF 1000000
using namespace std;
int cost[MAXV][MAXV];
int d[MAXV];
bool used[MAXV];
int V;
void dijkstra(int s)
{
    fill(d,d+V,INF);
    fill(used,used+V,false);
    d[s]=0;
    while(true)
    {
        int v=-1;
        for(int u=0;u<V;u++)
            if(!used[u]&&(v==-1||d[u]<d[v])) v=u;
        if(v==-1) break;
        used[v]=true;
        for(int u=0;u<V;u++)
            d[u]=min(d[u],d[v]+cost[v][u]);
    }
}
int main()
{
    return 0;
}
