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
int n,m,tot,root[MAXN];
int lson[MAXM],rson[MAXN],p[MAXM],rk[MAXM];
void build(int &k,int l,int r)
{
    k=++tot;
    if(l==r) {p[k]=l; return;}
    int mid=(l+r)/2;
    build(lson[k],l,mid);build(rson[k],mid+1,r);
}
void insert(int &k,int last,int l,int r,int pos,int val)
{
    k=++tot;
    if(l==r) {p[k]=val; rk[k]=rk[last]; return;}
    lson[k]=lson[last];rson[k]=rson[last];
    int mid=(l+r)/2;
    if(pos<=mid) insert(lson[k],lson[last],l,mid,pos,val);
    else insert(rson[k],rson[last],mid+1,r,pos,val);
}
int query(int k,int l,int r,int pos)
{
    if(l==r) return k;
    int mid=(l+r)/2;
    if(pos<=mid) return query(lson[k],l,mid,pos);
    else return query(rson[k],mid+1,r,pos);
}
void add(int k,int l,int r,int pos)
{
    if(l==r) {rk[k]++; return;}
    int mid=(l+r)/2;
    if(pos<=mid) add(lson[k],l,mid,pos);
    else add(rson[k],mid+1,r,pos);
}
int find(int k,int x)
{
    int q=query(k,1,n,x);
    if(x==p[q]) return q;
    return find(k,p[q]);
}
int main()
{
    return 0;
}

