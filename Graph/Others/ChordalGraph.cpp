/*************************************************************************
    > File Name: ChordalGraph.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-31 15:49:59
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
vector<int> G[MAXN];
int h[MAXN];
bool vis[MAXN];
vector<int> peo;
priority_queue<P> pque;
void MCS()
{
    memset(vis,0,sizeof(vis));
    memset(h,0,sizeof(h));
    for(int i=1;i<=n;i++) pque.push(P(0,i));
    for(int i=n;i>=1;i--)
    {
        while(1)
        {
            P p=pque.top();pque.pop();
            if(vis[p.S]) continue;
            peo.push_back(p.S);vis[p.S]=true;
            for(auto to:G[p.S]) 
            {
                if(vis[to]) continue;
                h[to]++;pque.push(P(h[to],to));
            }
            break;
        }
    }
    reverse(peo.begin(),peo.end());
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
    }
    MCS();
    return 0;
}

