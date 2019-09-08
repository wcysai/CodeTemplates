#include<bits/stdc++.h>
#define MAXN 100005
#define MOD 998244353
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int g=3;
int two[32];
int dbit(int x)
{
    while((x&-x)!=x) x+=x&-x;
    return x;
}
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
int rev(int x,int r)
{
    int ans=0;
    for(int i=0;i<r;i++)
        if(x&(1<<i)) ans+=1<<(r-i-1);
    return ans;
}
void ntt(int n,int A[],int on)
{
    int r=0,cnt=0,t=n;
    while(t>1) {cnt++; t/=2;}
    for(;;r++) if((1<<r)==n)  break;
    for(int i=0;i<n;i++)
    {
        int tmp=rev(i,r);
        if(i<tmp) swap(A[i],A[tmp]);
    }
    for(int s=1;s<=r;s++)
    {
        int m=1<<s;
        int wn=pow_mod(g,(MOD-1)/m);
        for(int k=0;k<n;k+=m)
        {
            int w=1;
            for(int j=0;j<m/2;j++)
            {
                int t,u;
                t=1LL*w*A[k+j+m/2]%MOD;
                u=A[k+j];
                A[k+j]=(u+t);
                if(A[k+j]>=MOD) A[k+j]-=MOD;
                A[k+j+m/2]=u+MOD-t;
                if(A[k+j+m/2]>=MOD) A[k+j+m/2]-=MOD;
                w=1LL*w*wn%MOD;
            }
        }
    }
    if(on==-1)
    {
        for(int i=1;i<n/2;i++)
            swap(A[i],A[n-i]);
        for(int i=0;i<n;i++)
            A[i]=1LL*A[i]*two[cnt]%MOD;
    }
}
int fact[MAXN],inv[MAXN],A[MAXN],B[MAXN];
int main()
{
    int n;
    for(int i=1;i<=30;i++)
        two[i]=pow_mod(1<<i,MOD-2);
    scanf("%d",&n);
    fact[0]=1,inv[0]=1;
    for(int i=1;i<=n;i++)
    {
        fact[i]=1LL*fact[i-1]*i%MOD;
        inv[i]=pow_mod(fact[i],MOD-2);
    }
    int sz=dbit(n)*2;
    //printf("%d\n",sz);
    memset(A,0,sizeof(A));
    memset(B,0,sizeof(B));
    for(int i=0;i<=n;i++)
    {
        if(i&1) A[i]=MOD-inv[i]; else A[i]=inv[i];
        B[i]=1LL*inv[i]*pow_mod(i,n)%MOD;
        printf("%d %d\n",A[i],B[i]);
    }
    ntt(sz,A,1);ntt(sz,B,1);
    for(int i=0;i<sz;i++)
        A[i]=1LL*A[i]*B[i]%MOD;
    ntt(sz,A,-1);
    for(int i=0;i<=n;i++)
        printf("%d ",A[i]);
    return 0;
}
