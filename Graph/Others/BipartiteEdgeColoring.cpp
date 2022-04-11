#include<bits/stdc++.h>
#define MAXN 2005
#define MAXM 100005
#define INF 100000000
#define MOD 100000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int a,b,n,m,d;
int deg[MAXN];
P to[MAXN][MAXN];
int c[MAXM];
P e[MAXM];
void recolor(int u,int c1,int c2)
{
    int v=to[u][c1].F;
    int id=to[u][c1].S;
    to[v][c1]=to[u][c1]=P(0,0);
    c[id]=c2;
    to[u][c2]=P(v,id);
    if(to[v][c2].F==0)
    {
        to[v][c2]=P(u,id);
        return;
    }
    recolor(v,c2,c1);
    to[v][c2]=P(u,id);
}
void color(int id)
{
    int u=e[id].F,v=e[id].S;
    for(int i=1;i<=d;i++)
    {
        if(!to[u][i].F&&!to[v][i].F)
        {
            c[id]=i;
            to[u][i]=P(v,id);
            to[v][i]=P(u,id);
            return;
        }
    }
    int x=-1,y=-1;
    for(int i=1;i<=d;i++)
    {
        if(!to[u][i].F) x=i;
        if(!to[v][i].F) y=i;
    }
    assert(x!=-1&&y!=-1);
    c[id]=x;
    to[u][x]=P(v,id);
    recolor(v,x,y);
    to[v][x]=P(u,id);
}
int main()
{
    scanf("%d%d%d",&a,&b,&m);
    n=a+b;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&e[i].F,&e[i].S);
        e[i].S+=a;
        deg[e[i].F]++; deg[e[i].S]++;
    }
    d=0;
    for(int i=1;i<=n;i++) d=max(d,deg[i]);
    printf("%d\n",d);
    for(int i=1;i<=m;i++) color(i);
    for(int i=1;i<=m;i++) printf("%d ",c[i]);
    puts("");
    return 0;
}