#include<bits/stdc++.h>
#define MAXN 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct query{int l,r,t,id;};
int n,m,c[MAXN],cnt[100*MAXN],res,cur,ans[MAXN];
query q[MAXN];
int tim[MAXN],pos[MAXN],pre[MAXN],val[MAXN];
int totq,totc,nowl,nowr;
const int blocks=462;
bool cmp(query x,query y)
{
    if(x.l/blocks!=y.l/blocks) return x.l<y.l;
    if(x.r/blocks!=y.r/blocks) return x.r<y.r;
    return x.t<y.t;
}
char ch[5];
void add(int p)
{
    if(!cnt[c[p]]) res++;
    cnt[c[p]]++;
}
void del(int p)
{
    cnt[c[p]]--;
    if(!cnt[c[p]]) res--;
}
void tadd(int cur)
{
    if(pos[cur]>=nowl&&pos[cur]<=nowr)
    {
        cnt[c[pos[cur]]]--;
        if(!cnt[c[pos[cur]]]) res--;
    }
    pre[cur]=c[pos[cur]];
    c[pos[cur]]=val[cur];
    if(pos[cur]>=nowl&&pos[cur]<=nowr)
    {
        if(!cnt[c[pos[cur]]]) res++;
        cnt[c[pos[cur]]]++;
    }
}
void tdel(int cur)
{
    if(pos[cur]>=nowl&&pos[cur]<=nowr)
    {
        cnt[c[pos[cur]]]--;
        if(!cnt[c[pos[cur]]]) res--;
    }
    c[pos[cur]]=pre[cur];
    if(pos[cur]>=nowl&&pos[cur]<=nowr)
    {
        if(!cnt[c[pos[cur]]]) res++;
        cnt[c[pos[cur]]]++;
    }
}
void tupd(int now)
{
    while(cur<totc&&tim[cur+1]<=now) tadd(++cur);
    while(cur>0&&tim[cur]>now) tdel(cur--);
}
void upd(int now,int l,int r)
{
    tupd(now);
    while(nowl>l) add(--nowl);
    while(nowr<r) add(++nowr);
    while(nowl<l) del(nowl++);
    while(nowr>r) del(nowr--);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=1;i<=m;i++)
    {
        scanf("%s",ch);
        if(ch[0]=='Q')
        {
            totq++;q[totq].id=totq;q[totq].t=i;
            scanf("%d%d",&q[totq].l,&q[totq].r);
        }
        else
        {
            totc++;tim[totc]=i;
            scanf("%d%d",&pos[totc],&val[totc]);
        }
    }
    sort(q+1,q+totq+1,cmp);
    nowl=1;nowr=0;cur=0;
    for(int i=1;i<=totq;i++)
    {
        upd(q[i].t,q[i].l,q[i].r);
        ans[q[i].id]=res;
    }
    for(int i=1;i<=totq;i++) printf("%d\n",ans[i]);
    return 0;
}

