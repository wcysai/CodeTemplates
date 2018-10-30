#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
struct edge
{
    int u,v,w;
};
int dmst(int N,vector<edge> &E,int root)
{
    vector<int> cost(N),back(N),label(N),bio(N);
    int ret=0;
    for(;;)
    {
        for(int i=1;i<=N;i++) cost[i]=INF;
        for(auto e:E)
        {
            if(e.u==e.v) continue;
            if(e.w<cost[e.v]) cost[e.v]=e.w,back[e.v]=e.u;
        }
        cost[root]=0;
        for(int i=1;i<=N;i++) if(cost[i]==INF) return -1;
        for(int i=1;i<=N;i++) ret+=cost[i];
        int K=0;
        for(int i=1;i<=N;i++) label[i]=1;
        for(int i=1;i<=N;i++) bio[i]=-1;
        for(int i=1;i<=N;i++)
        {
            int x=i;
            for(;x!=root&&bio[x]==-1;x=back[x]) bio[x]=i;
            if(x!=root&&bio[x]==i)
            {
                for(;label[x]==-1;x=back[x]) label[x]=K;
                ++K;
            }
        }
        if(K==0) break;
        for(int i=1;i<=N;i++) if(label[i]==-1) label[i]=K++;
        for(auto &e:E)
        {
            int uu=label[e.u];
            int vv=label[e.v];
            if(uu!=vv) e.w-=cost[e.v];
            e.u=uu;e.v=vv;
        }
        root=label[root];
        N=K;
    }
    return ret;
}
int main()
{
    return 0;
}

