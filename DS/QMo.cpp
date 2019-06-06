#include<bits/stdc++.h>
#define MAXN 50005
#define MAXM 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int blocks=1200;
int tot,tcnt,qid;
struct query
{
    int l,r,ti,id;
}Q[MAXN];
int n,q,cnt[MAXM],ans,a[MAXN];
P change[MAXN];
int res[MAXN];
bool cmp(query x,query y)
{
    if(x.l/blocks!=y.l/blocks) return x.l/blocks<y.l/blocks;
    if(x.r/blocks!=y.r/blocks) return x.r/blocks<y.r/blocks;
    if(x.r/blocks&1) return x.ti>y.ti; else return x.ti<y.ti;
}
void add(int pos)
{
    if(!cnt[a[pos]]) ans++;
    cnt[a[pos]]++;
}
void del(int pos)
{
    cnt[a[pos]]--;
    if(!cnt[a[pos]]) ans--;
}
void modify(int ti,int num)
{
    if(change[ti].F>=Q[num].l&&change[ti].F<=Q[num].r)
    {
        cnt[a[change[ti].F]]--;
        if(!cnt[a[change[ti].F]]) ans--;
        if(!cnt[change[ti].S]) ans++;
        cnt[change[ti].S]++;
    }
    swap(a[change[ti].F],change[ti].S);
}
char ch[2];
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=q;i++)
    {
        int l,r;
        scanf("%s%d%d",ch,&l,&r);
        if(ch[0]=='Q') Q[++tot]=(query){l,r,tcnt,++qid};
        else change[++tcnt]=P(l,r);
    }
    sort(Q+1,Q+tot+1,cmp);
    int l=1,r=0,ti=0;
    for(int i=1;i<=tot;i++)
    {
        while(l>Q[i].l) add(--l);
        while(l<Q[i].l) del(l++);
        while(r<Q[i].r) add(++r);
        while(r>Q[i].r) del(r--);
        while(ti<Q[i].ti) modify(++ti,i);
        while(ti>Q[i].ti) modify(ti--,i);
        res[Q[i].id]=ans;
    }
    for(int i=1;i<=qid;i++) printf("%d\n",res[i]);
    return 0;
}
