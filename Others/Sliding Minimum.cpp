#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
int n,k;
int a[MAXN];
int b[MAXN];
int deq[MAXN];
void solve()
{
	int s=0,t=0;
	for(int i=0;i<n;i++)
	{
		while(s<t&&a[deq[t-1]]>=a[i]) t--;
		deq[t++]=i;
		if(i-k+1>=0)
		{
			b[i-k+1]=a[deq[s]];
			if(deq[s]==i-k+1)
			{
				s++;
			}
		}
	}
	for(int i=0;i<=n-k;i++)
	{
		printf("%d%c",b[i],i==n-k?'\n':' ');
	}
}
int main()
{
    scanf("%d %d",&n,&k);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    solve();
    return 0;
}
