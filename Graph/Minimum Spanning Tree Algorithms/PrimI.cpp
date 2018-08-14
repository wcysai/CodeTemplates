#include<bits/stdc++.h>
#define MAXV 100005
#define MAXE 300005
#define INF 1000000000
using namespace std;
typedef pair<int,int> P;
int V,E;
struct edge
{
	int to,cost;
};
vector<edge> G[MAXV];// adjacency table
priority_queue<P, vector<P>, greater<P> > pq; //priority queue(defaulted to extract the minimum)
bool used[MAXV];// to judge if some vertex is in the MST
int dis[MAXV];//minimum distance to vertex i
int prim()
{
	int ans=0;
	memset(used,false,sizeof(used));
	fill(dis,dis+V,INF);
	dis[0]=0;
	while(!pq.empty()) pq.pop();
	pq.push(P(0,0));
	while(!pq.empty())
	{
		P p=pq.top();pq.pop();
		int v=p.second;
		if(used[v]||p.first>dis[v]) continue;
		used[v]=true;
		ans+=dis[v];
		for(int i=0;i<G[v].size();i++)
		{
			edge e=G[v][i];
			if(dis[e.to]>e.cost)
			{
				dis[e.to]=e.cost;
				pq.push(P(dis[e.to],e.to));
			}
		}
	}
	return ans;
}
int main()
{
	scanf("%d%d",&V,&E);
	for(int i=0;i<E;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		x--,y--;//convert into 0-based
		G[x].push_back((edge){y,z});
		G[y].push_back((edge){x,z});
	}
	printf("%d\n",prim());
	return 0;
}