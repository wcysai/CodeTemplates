#include<bits/stdc++.h>
#define MAXN 65
#define MAXM 6005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int color[MAXN];
ll val[MAXM];
int n,m,tot,tot2;
struct LinearMatroid
{
    ll basis[62];
    bool test(vector<int> &v)
    {
        memset(basis,0,sizeof(basis));
        for(auto i:v)
        {
            ll x=val[i];
            bool f=false;
            for(int j=60;j>=0;j--)
            {
                if(!(x&(1LL<<j))) continue;
                if(!basis[j])
                {
                    basis[j]=x;
                    f=true;
                    break;
                }
                else x^=basis[j];
            }
            if(!f) return false;
        }
        return true;
    }
};
struct ColorfulMatroid
{
    int cnt[125];
    bool test(vector<int> &v)
    {
        memset(cnt,0,sizeof(cnt));
        for(auto i:v)
        {
            cnt[color[i]]++;
            if(cnt[color[i]]>1) return false;
        }
        return true;
    }
};


template <typename MT1, typename MT2>
struct MatroidIntersection
{
    int n;
    MatroidIntersection(int _n):n(_n){}
    int pre[MAXM];
    bool vis[MAXM],sink[MAXM],has[MAXM];
    queue<int> que;
    void clear_all()
    {
        memset(vis,false,sizeof(vis));
        memset(sink,false,sizeof(sink));
        memset(pre,0,sizeof(pre));
        while(que.size()) que.pop();
    }
    vector<int> getcur()
    {
        vector<int> ret;
        for(int i=1;i<=n;i++) if(has[i]) ret.push_back(i);
        return ret;
    }
    void enqueue(int v,int p)
    {
        vis[v]=true; pre[v]=p;
        que.push(v);
    }
    vector<int> run()
    {
        MT1 mt1;  MT2 mt2;
        memset(has,false,sizeof(has));
        while(true)
        {
            vector<int> cur=getcur();
            clear_all();
            for(int i=1;i<=n;i++)
            {
                if(has[i]) continue;
                vector<int> tmp=cur; tmp.push_back(i);
                if(mt1.test(tmp)) {que.push(i); vis[i]=true;}
            }
            for(int i=1;i<=n;i++)
            {
                if(has[i]) continue;
                vector<int> tmp=cur; tmp.push_back(i);
                if(mt2.test(tmp)) sink[i]=true;
            }
            int last=-1;
            while(que.size())
            {
                int v=que.front(); que.pop();
                if(sink[v]) {last=v; break;}
                for(int i=1;i<=n;i++)
                {
                    if(vis[i]) continue;
                    if(has[i]==has[v]) continue;
                    has[v]^=1; has[i]^=1;
                    vector<int> tmp=getcur();
                    if(!has[v]) { if(mt1.test(tmp)) enqueue(i,v); }
                    else {if(mt2.test(tmp)) enqueue(i,v);}
                    has[v]^=1; has[i]^=1;
                }
            }
            if(last==-1) return cur;
            while(last)
            {
                has[last]^=1;
                last=pre[last];
            }
        }
    }
};
//Pick Your Own Nim
//In real cases, Linear Matroid Need Optimization to Pass
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        ll x;
        scanf("%lld",&x);
        val[++tot]=x; color[tot]=++tot2;
    }
    scanf("%d",&m);
    for(int i=0;i<m;i++)
    {
        int k;
        scanf("%d",&k);
        tot2++;
        for(int j=0;j<k;j++)
        {
            ll x;
            scanf("%lld",&x);
            val[++tot]=x; color[tot]=tot2;
        }
    }
    MatroidIntersection<LinearMatroid,ColorfulMatroid> matint(tot);
    vector<int> res=matint.run();
    if(res.size()<n+m) {puts("-1"); return 0;}
    else
    {
        vector<ll> ans;
        int last=n;
        for(auto x:res)
        {
            if(color[x]>last)
            {
                ans.push_back(val[x]);
                last=color[x];
            }
        }
        for(auto x:ans) printf("%lld\n",x);
    }
    return 0;
}
