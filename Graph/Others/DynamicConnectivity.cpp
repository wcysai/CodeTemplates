#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,k,x,y;
char str[2];
vector<P> edges[4*MAXN];
bool ask[MAXN];
int p[MAXN],r[MAXN],sz[MAXN];
int ans[MAXN];
int num;
struct update
{
    int x,y;
    bool addrk;
};
update st[MAXN];
int t;
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        r[i]=0;
    }
}
int find(int x)
{
   while(p[x]!=x) x=p[x];
   return x;
}
bool unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return false;
    num--;
    if(r[x]<r[y]) 
    {
        p[x]=y; 
        st[t++]=(update){x,y,false};
    }
    else
    {
        p[y]=x;
        st[t++]=(update){y,x,r[x]==r[y]};
        if(r[x]==r[y]) r[x]++;
    }
    return true;
}
void undo()
{
    assert(t);
    int x=st[t-1].x,y=st[t-1].y;
    //printf("undo %d %d %d\n",x,y,st[t-1].addrk);
    p[x]=x;p[y]=y;
    if(st[t-1].addrk) r[y]--;
    t--;num++;
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
void add_edge(int k,int l,int r,int x,int y,int u,int v)
{
    if(x>r||l>y) return;
    if(l>=x&&r<=y)
    {
        edges[k].push_back(P(u,v));
        return;
    }
    int mid=(l+r)/2;
    add_edge(k*2,l,mid,x,y,u,v);add_edge(k*2+1,mid+1,r,x,y,u,v);
}
void solve(int k,int l,int r)
{
    if(l>r) return;
    int cnt=0;
    for(auto e:edges[k]) if(unite(e.F,e.S)) cnt++;  
    if(l==r)
    {
        if(ask[l]) ans[l]=num;
        for(int i=0;i<cnt;i++) undo();
        return;
    }
    int mid=(l+r)/2;
    solve(k*2,l,mid);solve(k*2+1,mid+1,r);
    //printf("cnt %d %d %d\n",l,r,cnt);
    for(int i=0;i<cnt;i++) undo();
}
map<P,int> mp;
int main()
{
    freopen("connect.in","r",stdin);
    freopen("connect.out","w",stdout);
    scanf("%d%d",&n,&k);num=n;init(n);
    memset(ask,false,sizeof(ask));
    for(int i=1;i<=k;i++)
    {
        scanf("%s",str);
        if(str[0]=='?')
        {
            ask[i]=true;
            continue;
        }
        scanf("%d%d",&x,&y);
        if(x>y) swap(x,y);
        if(str[0]=='+') mp[P(x,y)]=i;
        else
        {
            add_edge(1,1,k,mp[P(x,y)],i-1,x,y);
            mp[P(x,y)]=-1;
        }
    }
    for(auto p:mp) if(p.S!=-1) add_edge(1,1,k,p.S,k,p.F.F,p.F.S);
    solve(1,1,k);
    for(int i=1;i<=k;i++) if(ask[i]) printf("%d\n",ans[i]);
    return 0;
}

