//luogu 4719 dynamic maximum weight vertex cover
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
int tot,n,q;
int dp[MAXN][2];
int ldp[MAXN][2];
int pa[MAXN],a[MAXN],dep[MAXN],sz[MAXN],wson[MAXN],top[MAXN],st[MAXN],ed[MAXN],tpos[MAXN],w[MAXN],bot[MAXN];
struct mat 
{
    int v[2][2];
    mat(){v[0][0]=v[0][1]=v[1][0]=v[1][1]=-INF;}
};
mat mul(mat a,mat b)
{
    mat c;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++)
                c.v[i][j]=max(c.v[i][j],a.v[i][k]+b.v[k][j]);
    return c;
}
mat unit;
vector<int> G[MAXN];
void dfs1(int v,int p,int d)
{
    dep[v]=d;pa[v]=p;sz[v]=1;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p) continue;
        dfs1(to,v,d+1);
        if(sz[to]>sz[wson[v]]) wson[v]=to;
        sz[v]+=sz[to];
    }
}
void dfs2(int v,int p,int num)
{
    top[v]=num; bot[num]=v; 
    st[v]=++tot;
    tpos[tot]=v;
    if(wson[v]) dfs2(wson[v],v,num);
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p||to==wson[v]) continue;
        dfs2(to,v,to);
    }
    ed[v]=tot;
}
struct segtree
{
    mat val[4*MAXN];
    void pushup(int k)
    {
        val[k]=mul(val[k*2],val[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            int v=tpos[l];
            val[k].v[0][0]=val[k].v[0][1]=ldp[v][0];
            val[k].v[1][0]=ldp[v][1];
            val[k].v[1][1]=-INF;
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int p,int v1,int v2)
    {
        if(l==r)
        {  
            val[k].v[0][0]=val[k].v[0][1]=v1;
            val[k].v[1][0]=v2;
            val[k].v[1][1]=-INF;
            return;
        }
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p,v1,v2);
        else update(k*2+1,mid+1,r,p,v1,v2);
        pushup(k);
    }
    mat query(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return unit;
        if(l>=x&&r<=y) return val[k];
        int mid=(l+r)/2;
        return mul(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}tree;
void init()
{
    tot=0;
    memset(wson,0,sizeof(wson));//important when multiple test cases!!!
    dfs1(1,0,1);
    dfs2(1,0,1);
    tree.build(1,1,n);
}
void update(int v,int x)
{
    ldp[v][1]+=(x-w[v]); w[v]=x; 
    while(v!=0)
    {
        int l=st[top[v]],r=st[bot[top[v]]];
        //mat tmp1(2,vec(1)),tmp2(2,vec(1));
        //tmp1[0][0]=tmp1[1][0]=tmp2[0][0]=tmp2[1][0]=0;
        mat past=tree.query(1,1,n,l,r);
        tree.update(1,1,n,st[v],ldp[v][0],ldp[v][1]);
        mat now=tree.query(1,1,n,l,r);
        v=pa[top[v]];
        ldp[v][0]+=max(now.v[0][0],now.v[1][0])-max(past.v[0][0],past.v[1][0]);
        ldp[v][1]+=now.v[0][0]-past.v[0][0];
    }
}
int main()
{
    unit.v[0][0]=unit.v[1][1]=0; unit.v[0][1]=unit.v[1][0]=-INF;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    init();
    for(int i=1;i<=n;i++) update(i,a[i]);
    for(int i=0;i<q;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        update(x,y);
        int l=1,r=st[bot[1]];
        mat A=tree.query(1,1,n,l,r);
        printf("%d\n",max(A.v[0][0],A.v[1][0]));
    }
    return 0;
}
