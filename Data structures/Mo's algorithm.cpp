#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 100005
using namespace std;
struct query
{
    int l,r,id;
}save[MAXM];
int cnt[MAXN],a[MAXN],out[MAXN];
int n,m,ans,block;
bool cmp(query x,query y)
{
    if(x.l/block!=y.l/block) return x.l/block<y.l/block;
    return x.r<y.r^(x.l/block&1);
}
void add(int pos)
{
    if(cnt[a[pos]]==a[pos]) ans--;
    cnt[a[pos]]++;
    if(cnt[a[pos]]==a[pos]) ans++;
    return;
}
void del(int pos)
{
    if(cnt[a[pos]]==a[pos]) ans--;
    cnt[a[pos]]--;
    if(cnt[a[pos]]==a[pos]) ans++;
    return;
}
void update(int cl,int cr,int l,int r)
{
    while(cl<l)
    {
        del(cl);
        cl++;
    }
    while(cl>l)
    {
        cl--;
        add(cl);
    }
    while(cr>r)
    {
        del(cr);
        cr--;
    }
    while(cr<r)
    {
        cr++;
        add(cr);
    }
    return;
}
int main()
{
    scanf("%d %d",&n,&m);
    block=(int)sqrt(n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]>100000) a[i]=100001;
    }
    for(int i=0;i<m;i++)
    {
        save[i].id=i;
        scanf("%d %d",&save[i].l,&save[i].r);
    }
    sort(save,save+m,cmp);
    memset(cnt,0,sizeof(cnt));
    ans=0;
    for(int i=save[0].l;i<=save[0].r;i++)
    {
        if(cnt[a[i]]==a[i]) ans--;
        cnt[a[i]]++;
        if(cnt[a[i]]==a[i]) ans++;
    }
    out[save[0].id]=ans;
    int cl=save[0].l,cr=save[0].r;
    for(int i=1;i<m;i++)
    {
        update(cl,cr,save[i].l,save[i].r);
        out[save[i].id]=ans;
        cl=save[i].l;
        cr=save[i].r;
    }
    for(int i=0;i<m;i++)
        printf("%d\n",out[i]);
    return 0;
}

