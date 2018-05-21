#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
using namespace std;
typedef long long ll;
ll a[MAXN];
ll n,k;
ll dp[MAXN][MAXN],knuth[MAXN][MAXN];
int main()
{
    while(scanf("%lld %lld",&n,&k)==2)
    {
        a[0]=0;
        for(ll i=1;i<=k;i++)
            scanf("%lld",&a[i]);
        a[k+1]=n;
        for(ll i=0;i<=k+1;i++)
            for(ll j=0;j<=k+1;j++)
                dp[i][j]=INF;
        for(ll i=0;i<=k;i++)
            dp[i][i+1]=0;
        for(ll l=3;l<=k+2;l++)
            for(ll i=0;i<=k+2-l;i++)
            {
                if(l==3)
                {
                    dp[i][i+l-1]=a[i+l-1]-a[i];
                    knuth[i][i+l-1]=i+1;
                }
                else
                    for(ll j=knuth[i][i+l-2];j<=knuth[i+1][i+l-1];j++)
                        if(dp[i][j]+dp[j][i+l-1]+a[i+l-1]-a[i]<dp[i][i+l-1])
                        {
                            dp[i][i+l-1]=dp[i][j]+dp[j][i+l-1]+a[i+l-1]-a[i];
                            knuth[i][i+l-1]=j;
                        }
            }
        printf("%lld\n",dp[0][k+1]);
    }
    return 0;
}

