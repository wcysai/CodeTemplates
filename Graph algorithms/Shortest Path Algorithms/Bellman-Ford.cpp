#include<bits/stdc++.h>
#define MAXV 1000
#define MAXE 10000
#define INF 1000000
using namespace std;
struct edge{int from,to,cost;};
edge es[MAXE];
int d[MAXV];
int V,E;
void shortest_path(int s)
{
    for(int i=0;i<V;i++) d[i]=INF;
    d[s]=0;
    while(true)
    {
        bool update=false;
        for(int i=0;i<E;i++)
        {
            edge e=es[i];
            if(d[e.from]!=INF&&d[e.to]>d[e.from]+e.cost)
            {
                d[e.to]=d[e.from]+e.cost;
                update=true;
            }
        }
        if(!update) break;
    }
}
int main()
{
    return 0;
}
