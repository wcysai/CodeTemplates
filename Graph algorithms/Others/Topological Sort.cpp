#include<bits/stdc++.h>
#define MAXV 100005
using namespace std;
int V,t;
vector<int> G[MAXV];
int d[MAXV],f[MAXV],p[MAXV],color[MAXV];
deque<int> order;
void dfs_visit(int v)
{
	d[v]=++t;
	color[v]=1;
	for(int i=0;i<G[v].size();i++)
	{
		int to=G[v][i];
		if(color[to]==0)
		{
			p[to]=v;
			dfs_visit(to);
		}
	}
	color[v]=2;
	order.push_front(v);
	f[v]=++t;
}
void toposort()
{
	t=0;
	memset(color,0,sizeof(color));
	memset(p,-1,sizeof(p));
	for(int i=0;i<V;i++)
		if(color[i]==0)
			dfs_visit(i);
}
int main()
{
	return 0;
}
