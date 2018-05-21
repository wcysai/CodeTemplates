#include<bits/stdc++.h>
#define MAXV 100005
#define INF 1000000000
using namespace std;
int n;
vector<int> G[MAXV];
int depth[MAXV],pa[MAXV],pre[MAXV];
bool used[MAXV];
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
int solve(int v,int p)
{
	printf("%d ",v+1);
	for(int i=0;i<G[v].size();i++)
	{
		int to=G[v][i];
		if(to==p) continue;
		solve(to,v);
		printf("%d ",v+1);
	}
	
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		G[x-1].push_back(y-1);
		G[y-1].push_back(x-1);
	}
	dfs(0,-1,0);
	int v=0,res=-INF;
	for(int i=0;i<n;i++)
	{
		if(depth[i]>res)
		{
			res=depth[i];
			v=i;
		}
	}
	dfs(v,-1,0);
	int u=0;res=-INF;
	for(int i=0;i<n;i++)
	{
		if(depth[i]>res)
		{
			res=depth[i];
			u=i;
		}
	}
	printf("%d\n",2*n-2-depth[u]);
	memset(used,false,sizeof(used));
	for(int i=u;i!=v;i=pa[i])
	{
		used[i]=true;
		printf("%d ",i+1);
		for(int j=0;j<G[i].size();j++)
		{
			if(used[G[i][j]]||G[i][j]==pa[i]) continue;
			solve(G[i][j],i);
			printf("%d ",i+1);
		}
	}
	printf("%d\n",v+1);
	return 0;
}
