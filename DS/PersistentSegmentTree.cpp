#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 2000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,tot,cnt,a[MAXN],root[MAXN];
int lson[MAXM],rson[MAXM],mx[MAXM];
void merge(int k)
{
    mx[k]=max(mx[lson[k]],mx[rson[k]]);
}
void build(int &k,int l,int r)
{
    k=++tot;
    if(l==r) {mx[k]=a[l]; return;}
    int mid=(l+r)/2;
    build(lson[k],l,mid);build(rson[k],mid+1,r);
    merge(k);
}
void insert(int &k,int last,int l,int r,int p,int v)
{
    k=++tot;
    mx[k]=mx[last];
    if(l==r) {mx[k]=v; return;}
    lson[k]=lson[last];rson[k]=rson[last];
    int mid=(l+r)/2;
    if(p<=mid) insert(lson[k],lson[last],l,mid,p,v);
    else insert(rson[k],rson[last],mid+1,r,p,v);
    merge(k);
}
int query(int &k,int l,int r,int x,int y)
{
    if(!k) return 0;
    if(l>y||r<x) return 0;
    if(l>=x&&r<=y) return mx[k];
    int mid=(l+r)/2;
    return max(query(lson[k],l,mid,x,y),query(rson[k],mid+1,r,x,y));
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    build(root[++cnt],1,n);
    for(int i=1;i<=q;i++)
    {
        int type,k,x,y;
        scanf("%d%d%d%d",&type,&k,&x,&y);
        if(type==1) insert(root[++cnt],root[k],1,n,x,y);
        else printf("%d\n",query(root[k],1,n,x,y));
    }
    return 0;
}



