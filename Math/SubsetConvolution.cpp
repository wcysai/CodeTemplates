#include<bits/stdc++.h>
#define MAXN 2000005
#define MAXLOGN 22
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int f[MAXN],g[MAXN];
int fhat[MAXLOGN][MAXN],ghat[MAXLOGN][MAXN],h[MAXLOGN][MAXN];
int fog[MAXN];
int n;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void subset_convolution()
{
    
    for(int mask=0;mask<(1<<n);mask++) 
    {
        fhat[__builtin_popcount(mask)][mask]=f[mask];
        ghat[__builtin_popcount(mask)][mask]=g[mask];
    }
    for(int i=0;i<=n;i++) 
    {
        for(int j=0;j<n;j++) 
        {
            for(int mask=0;mask<(1<<n);mask++) 
            {
                if((mask&(1<<j))!=0) 
                {
                    add(fhat[i][mask],fhat[i][mask^(1<<j)]);
                    add(ghat[i][mask],ghat[i][mask^(1<<j)]);
                }
            }
        }
    }
    for(int mask=0;mask<(1<<n);mask++) 
        for(int i=0;i<=n;i++) 
            for(int j=0;j<=i;j++) 
                add(h[i][mask],1LL*fhat[j][mask]*ghat[i-j][mask]%MOD);
    for(int i=0;i<=n;i++)
        for(int j=0;j<n;j++)
            for(int mask=0;mask<(1<<n);mask++) 
                if((mask&(1<<j))!=0) 
                    dec(h[i][mask],h[i][mask^(1<<j)]);
    for(int mask=0;mask<(1<<n);mask++) fog[mask]=h[__builtin_popcount(mask)][mask];
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<(1<<n);i++) scanf("%d",&f[i]);
    for(int i=0;i<(1<<n);i++) scanf("%d",&g[i]);
    subset_convolution();
    for(int i=0;i<(1<<n);i++) printf("%d ",fog[i]);
    puts("");
    return 0;
}