#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],f[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=0;i<(1<<n);i++)
		scanf("%d",&a[i]);
	for(int i=0;i<(1<<n);i++)
		f[i]=a[i];
	for(int i=0;i<n;i++) 
	{
		for(int mask=0;mask<(1<<n);mask++)
			if(mask&(1<<i))
				f[mask]+=f[mask^(1<<i)];
	}
	for(int i=0;i<(1<<n);i++)
		printf("%d ",f[i]);
	puts("");
	return 0;
}