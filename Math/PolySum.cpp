#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
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
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
namespace polysum
{
    const int D=100005;
    int a[D],f[D],g[D],p[D],p1[D],p2[D],b[D],h[D][2],C[D];
    int calcn(int d,int *a,int n)
    {
        if(n<=d) return a[n];
        p1[0]=p2[0]=1;
        for(int i=0;i<=d;i++)
        {
            int t=(n-i+MOD)%MOD;
            p1[i+1]=1LL*p1[i]*t%MOD;
        }
        for(int i=0;i<=d;i++)
        {
            int t=(n-d+i+MOD)%MOD;
            p2[i+1]=1LL*p2[i]*t%MOD;
        }
        ll ans=0;
        for(int i=0;i<=d;i++)
        {
            int t=1LL*g[i]*g[d-i]%MOD*p1[i]%MOD*p2[d-i]%MOD*a[i]%MOD;
            if((d-i)&1) ans=(ans-t+MOD)%MOD;
            else ans=(ans+t)%MOD;
        }
        return ans;
    }
    void init(int M)
    {
        f[0]=f[1]=g[0]=g[1]=1;
        for(int i=2;i<=M+4;i++) f[i]=1LL*f[i-1]*i%MOD;
        g[M+4]=pow_mod(f[M+4],MOD-2);
        for(int i=M+3;i>=1;i--) g[i]=1LL*g[i+1]*(i+1)%MOD;
    }
    int polysum(int n,int *a,int m) //a[0]..a[m] \sum_{i=0}^{n-1} a[i]
    {
        a[m+1]=calcn(m,a,m+1);
        for(int i=1;i<=m+1;i++) a[i]=(a[i-1]+a[i])%MOD;
        return calcn(m+1,a,n-1);
    }
    int qpolysum(int R,int n,int *a,int m) //a[0]..a[m] \sum_{i=0}^{n-1} a[i]*R^i
    {
        if(R==1) return polysum(n,a,m);
        a[m+1]=calcn(m,a,m+1);
        int r=pow_mod(R,MOD-2),p3=0,p4=0,c,ans;
        h[0][0]=0;h[0][1]=1;
        for(int i=1;i<=m+1;i++)
        {
            h[i][0]=1LL*(h[i-1][0]+a[i-1])*r%MOD;
            h[i][1]=1LL*h[i-1][1]*r%MOD;
        }
        for(int i=0;i<=m+1;i++)
        {
            int t=1LL*g[i]*g[m+1-i]%MOD;
            if(i&1) p3=((p3-1LL*h[i][0]*t)%MOD+MOD)%MOD,p4=((p4-1LL*h[i][1]*t)%MOD+MOD)%MOD;
            else p3=(p3+1LL*h[i][0]*t)%MOD,p4=(p4+1LL*h[i][1]*t)%MOD;
        }
        c=1LL*pow_mod(p4,MOD-2)*(MOD-p3)%MOD;
        for(int i=0;i<=m+1;i++) h[i][0]=(h[i][0]+1LL*h[i][1]*c)%MOD;
        for(int i=0;i<=m+1;i++) C[i]=h[i][0];
        ans=(1LL*calcn(m,C,n)*pow_mod(R,n)-c)%MOD;
        if(ans<0) ans+=MOD;
        return ans;
    }
}
ll a[MAXN];
int main()
{
    a[0]=1;a[1]=100;a[2]=0;
    polysum::init(1000);
    printf("%lld\n",polysum::qpolysum(2,4,a,1));
    return 0;
}
