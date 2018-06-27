#include<bits/stdc++.h>
#define MAXN 100000
using namespace std;
int N,Q;
int a[MAXN];
int st[MAXN][32];
int pre[MAXN];
void init(int n,int *arr)
{
    pre[1]=0;
    for(int i=2;i<=n;i++)
    {
        pre[i]=pre[i-1];
        if ((1<<pre[i]+1)==i) ++pre[i];
    }
    for(int i=n-1;i>=0;--i)
    {
        st[i][0]=arr[i];
        for(int j=1;(i+(1<<j)-1)<n;++j)
            st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
    }
}
int query(int l,int r)
{
    int len=r-l+1,k=pre[len];
    return min(st[l][k],st[r-(1<<k)+1][k]);
}
int main()
{
    scanf("%d",&N);
    for(int i=0;i<N;i++)
        scanf("%d",&a[i]);
    init(N,a);
    scanf("%d",&Q);
    while(Q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",query(x,y));
    }
    return 0;
}
