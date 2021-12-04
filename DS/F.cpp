#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
pair<ll,int> a[MAXN];
int h[MAXN];
int Lmin[MAXN],Rmin[MAXN],Lmax[MAXN],Rmax[MAXN];
int st[MAXN];
	
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {scanf("%lld",&a[i].F); a[i].S=i;}
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
		while(t>0&&a[st[t-1]]>=a[i]) t--;
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
		while(t>0&&a[st[t-1]]<=a[i]) t--;
		Rmax[i]=t==0?n+1:st[t-1];
		st[t++]=i;
	}
    for(int i=1;i<=n;i++) printf("%d %d %d %d\n",Lmin[i],Rmin[i],Lmax[i],Rmax[i]);
    return 0;
}