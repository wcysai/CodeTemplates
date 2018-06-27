#include<bits/stdc++.h>
#define MAXN 500030
using namespace std;
int n,m,h[MAXN],c[MAXN];
struct node
{
    int l,r,left,right,lazy;
}seg[4*MAXN];
bool cmp(int x,int y)
{
    return x>y;
}
void build(int k,int l,int r)
{
    seg[k].l=l;
    seg[k].r=r;
    seg[k].lazy=0;
    if(l==r)
    {
        seg[k].left=seg[k].right=h[l];
        return;
    }
    int mid=(l+r)/2;
    build(k*2,l,mid);
    build(k*2+1,mid+1,r);
    seg[k].left=seg[k*2].left;
    seg[k].right=seg[k*2+1].right;
}
void Lazy(int k)
{
    if(seg[k].l==seg[k].r)
    {
        seg[k].lazy=0;
        return;
    }
    seg[k*2].left-=seg[k].lazy;
    seg[k*2].right-=seg[k].lazy;
    seg[k*2+1].left-=seg[k].lazy;
    seg[k*2+1].right-=seg[k].lazy;
    seg[k*2].lazy+=seg[k].lazy;
    seg[k*2+1].lazy+=seg[k].lazy;
    seg[k].lazy=0;
}
bool update(int k,int l,int r)
{
    if(r<l) return true;
    if(seg[k].l>r||seg[k].r<l) return true;
    if(seg[k].l>=l&&seg[k].r<=r)
    {
        seg[k].lazy++;
        seg[k].left--;
        seg[k].right--;
        return (seg[k].left>=0&&seg[k].right>=0);
    }
    if(seg[k].lazy) Lazy(k);
    bool f1=update(k*2,l,r);
    bool f2=update(k*2+1,l,r);
    seg[k].left=seg[k*2].left;
    seg[k].right=seg[k*2+1].right;
    return(f1&&f2);
}
int findval(int k,int l,int r,int x)
{
    if(seg[k].lazy) Lazy(k);
    if(l==r) return seg[k].left;
    int mid=(l+r)/2;
    if(x>mid) return findval(k*2+1,mid+1,r,x);
    return findval(k*2,l,mid,x);
}
int findleft(int k,int l,int r,int x)
{
    if(seg[k].lazy) Lazy(k);
    if(l==r) return l;
    int mid=(l+r)/2;
    if(seg[k*2].right<=x) return findleft(k*2,l,mid,x);
    return findleft(k*2+1,mid+1,r,x);
}
int findright(int k,int l,int r,int x)
{
    if(seg[k].lazy) Lazy(k);
    if(l==r) return r;
    int mid=(l+r)/2;
    if(seg[k*2].lazy) Lazy(k*2);
    if(seg[k*2+1].lazy) Lazy(k*2+1);
    if(seg[k*2+1].left>=x) return findright(k*2+1,mid+1,r,x);
    return findright(k*2,l,mid,x);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&h[i]);
    sort(h+1,h+n+1,cmp);
    for(int i=0;i<m;i++)
        scanf("%d",&c[i]);
    build(1,1,n);
    int cnt=0;
    while(true)
    {
        if(c[cnt]>n) break;
        int x=findval(1,1,n,c[cnt]);
        int a=findleft(1,1,n,x);
        int b=findright(1,1,n,x);
        bool f1=update(1,1,a-1),f2=update(1,b-c[cnt]+a,b);
        if(!(f1&&f2)) break;
        cnt++;
        if(cnt>=m) break;
    }
    printf("%d\n",cnt);
    return 0;
}
