#include<bits/stdc++.h>
#define MAXN 150005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,a[MAXN];
int Lmin[MAXN],Rmin[MAXN],Lmax[MAXN],Rmax[MAXN];
int st[MAXN];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int t=0;
	for(int i=1;i<=n;i++)
	{
		while(t>0&&a[st[t-1]]>=a[i]) t--;
		Lmin[i]=t==0?0:st[t-1];
		st[t++]=i;
	}
	t=0;
	for(int i=n;i>=1;i--)
	{
		while(t>0&&a[st[t-1]]>a[i]) t--;
		Rmin[i]=t==0?n+1:st[t-1];
		st[t++]=i;
	}
    t=0;
	for(int i=1;i<=n;i++)
	{
		while(t>0&&a[st[t-1]]<=a[i]) t--;
		Lmax[i]=t==0?0:st[t-1];
		st[t++]=i;
	}
	t=0;
	for(int i=n;i>=1;i--)
	{
		while(t>0&&a[st[t-1]]<a[i]) t--;
		Rmax[i]=t==0?n+1:st[t-1];
		st[t++]=i;
	}
    for(int i=1;i<=n;i++) printf("%d %d %d %d\n",Lmin[i],Lmax[i],Rmin[i],Rmax[i]);
    return 0;
}