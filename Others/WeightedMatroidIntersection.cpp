#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 85
#define MAXM 205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int c[MAXN],k[MAXN],color[MAXM],u[MAXM],v[MAXM],w[MAXM],cost[MAXM];
ll val[MAXM];
int T,n,m,tot,tot2;
struct LinearMatroid
{
    ll basis[62];
    void clear()
    {
        memset(basis,0,sizeof(basis));
    }
    void add(ll x)
    {
        for(int j=60;j>=0;j--)
        {
            if(!(x&(1LL<<j))) continue;
            if(!basis[j])
            {
                basis[j]=x;
                return;
            }
            else x^=basis[j];
        }
    }
    bool test(ll x)
    {
        for(int j=60;j>=0;j--)
        {
            if(!(x&(1LL<<j))) continue;
            if(!basis[j]) return true; else x^=basis[j];
        }
        return false;
    }
};
struct ColorfulMatroid
{
    int cnt[125];
    void clear()
    {
        memset(cnt,0,sizeof(cnt));
    }
    void add(int x)
    {
        cnt[x]++;
    }
    bool test(int x)
    {
        return (cnt[x]==0);
    }
};

struct GraphMatroid
{
    vector<int> G[MAXN];
    bool vis[MAXN];
    bool exist[MAXN];
    void dfs(int v)
    {
        vis[v]=true;
        for(auto to:G[v]) if(!vis[to]) dfs(to);
    }
    bool test(vector<int> &vec)
    {
        for(int i=1;i<=n+1;i++) G[i].clear();
        memset(vis,false,sizeof(vis));
        memset(exist,true,sizeof(exist));
        for(auto x:vec) exist[x]=false;
        for(int i=1;i<=tot;i++)
        {
            if(exist[i])
            {
                G[u[i]].push_back(v[i]);
                G[v[i]].push_back(u[i]);
            }
        }
        dfs(1);
        for(int i=1;i<=n+1;i++) if(!vis[i]) return false;
        return true;
    }
};

struct PartitionMatroid
{
    int cnt[125];
    bool test(vector<int> &vec)
    {
        memset(cnt,0,sizeof(cnt));
        for(auto x:vec) cnt[color[x]]++;
        for(int i=1;i<=m;i++) if(cnt[i]>c[i]-k[i]) return false;
        return true;
    }
};


template <typename MT1, typename MT2>
struct MatroidIntersection
{
    int n,S,T;
    MatroidIntersection(int _n):n(_n){}
    int pre[MAXM],id[MAXM],d[MAXM];
    bool inque[MAXM],sink[MAXM],has[MAXM];
    vector<int> g[MAXN];
    queue<int> que;
    void clear_all()
    {
        for(int i=1;i<=n+2;i++)
        {
            inque[i]=false;
            sink[i]=false;
            pre[i]=0;
            d[i]=-INF;
            if(has[i]) cost[i]=w[i]; else cost[i]=-w[i];
            g[i].clear();
        }
        while(que.size()) que.pop();
    }
    void add_edge(int u,int v)
    {
        g[u].push_back(v);
    }
    vector<int> getcur()
    {
        vector<int> ret;
        for(int i=1;i<=n;i++) if(has[i]) ret.push_back(i);
        return ret;
    }
    void enqueue(int v,int p)
    {
        pre[v]=p;
        if(!inque[v])
        {
            inque[v]=true;
            que.push(v);
        }
    }
    pair<vector<int>,ll> run()
    {
        ll ans=0;
        MT1 mt1;  MT2 mt2;
        memset(has,false,sizeof(has));
        S=n+1; T=n+2;
        while(true)
        {
            clear_all();
            for(int i=1;i<=n;i++)
            {
                if(!has[i])
                {
                    cost[i]=w[i];
                    has[i]^=1;
                    vector<int> tmp=getcur();
                    if(mt1.test(tmp)) add_edge(S,i);
                    if(mt2.test(tmp)) add_edge(i,T);
                    has[i]^=1;
                }
                else cost[i]=-w[i];
            }
            for(int i=1;i<=n;i++)
            {
                if(!has[i])
                {
                    for(int j=1;j<=n;j++)
                    {
                        if(has[j])
                        {
                            has[i]^=1; has[j]^=1;
                            vector<int> tmp=getcur();
                            if(mt1.test(tmp)) add_edge(j,i);
                            if(mt2.test(tmp)) add_edge(i,j);
                            has[i]^=1; has[j]^=1;
                        }
                    }
                }
            }
            d[S]=0; que.push(S); inque[S]=true;
            cost[S]=cost[T]=0;
            int counter=0;
            while(que.size())
            {
                counter++;
                int u=que.front(); que.pop();
                for(auto to:g[u])
                    if(d[to]<d[u]+cost[to])
                    {
                        d[to]=d[u]+cost[to];
                        enqueue(to,u);
                    }
                inque[u]=false;
            }
            if(!pre[T]) return make_pair(getcur(),ans);
            ans+=d[T];
            int last=pre[T];
            while(last!=S)
            {
                has[last]^=1;
                last=pre[last];
            }
        }
    }
};
//hdu 6636 Milk Candy
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        tot=0;
        scanf("%d%d",&n,&m);
        int sum=0;
        ll ans=0;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&c[i],&k[i]);
            sum+=c[i]-k[i];
            for(int j=1;j<=c[i];j++)
            {
                int l,r,cost;
                scanf("%d%d%d",&l,&r,&cost);
                color[++tot]=i; u[tot]=l; v[tot]=r+1; w[tot]=cost;
                ans+=cost;
            }
        }
        MatroidIntersection<GraphMatroid,PartitionMatroid> matint(tot);
        auto res=matint.run();
        GraphMatroid gm; PartitionMatroid pm;
        if((int)res.F.size()!=sum||!gm.test(res.F)||!pm.test(res.F)) puts("-1"); else printf("%lld\n",ans-res.S);
    }
    return 0;
}

