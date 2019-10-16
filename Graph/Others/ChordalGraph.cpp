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
int h[MAXN],label[MAXN];
vector<int> st[MAXN];
bool vis[MAXN];
vector<int> peo;
void MCS()
{
    memset(vis,0,sizeof(vis));
    memset(h,0,sizeof(h));
    int cur=0;
    for(int i=1;i<=n;i++) st[0].push_back(i);
    for(int i=n;i>=1;i--)
    {
        while(1)
        {
            while(st[cur].size()==0) cur--;
            int now=st[cur].back();
            st[cur].pop_back();if(vis[now]) continue;
            vis[now]=true;label[now]=i;
            for(auto to:G[now])
            {
                if(vis[to]) continue;
                h[to]++; st[h[to]].push_back(to); cur=max(cur,h[to]);
            }
            break;
        }
    }
    reverse(peo.begin(),peo.end());
}

