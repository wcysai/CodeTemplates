#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int fact[MAXN];
int pow_mod(int a,int i)
{
    if(i==0) return 1;
    int s=1;
    while(i>0)
     {
         if(i&1) s=(1LL*s*a)%MOD;
         a=(1LL*a*a)%MOD;
         i>>=1;
     }
     return s;
}
int inv(int x)
{
	return pow_mod(x,MOD-2);
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	fact[0]=1;
	for(int i=1;i<=n;i++)
		fact[i]=1LL*fact[i-1]*i%MOD;
	int ans=0;
	for(int k=0;k<=m;k++)
	{
		int res=((1LL*fact[m]*inv(fact[k])%MOD)*inv(fact[m-k])%MOD)*pow_mod(m-k,n)%MOD;
		if(!(k&1)) ans=(ans+res)%MOD; else ans=(ans+MOD-res)%MOD;
	}
	ans=1LL*ans*(inv(fact[m]))%MOD;
	printf("%d\n",ans);
}