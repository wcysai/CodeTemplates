#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int g=3; 
int two[31];
int dbit(int x)
{
    while(x!=(x&-x)) x+=(x&-x);
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
int n,A[MAXN],B[MAXN],C[MAXN],D[MAXN];
void find_inverse(int A[],int n)
{
	if(n==1) {B[0]=pow_mod(A[0],MOD-2); return;}
	find_inverse(A,(n+1)/2);
	int len=dbit(n);
	for(int i=0;i<n;i++)
		C[i]=A[i];
	for(int i=n;i<len;i++) C[i]=0;
	ntt(len,C,1);ntt(len,B,1);
	for(int i=0;i<len;i++)
		C[i]=1LL*B[i]*B[i]%MOD*C[i]%MOD;
	ntt(len,C,-1);ntt(len,B,-1);
	for(int i=0;i<n;i++)
		B[i]=((2*B[i]-C[i])%MOD+MOD)%MOD;
}
void find_sqr(int A[],int n)
{
    if(n==1) 
    { 
        D[0]=A[0]; 
        return;
    }
    find_sqr(A,(n+1)/2);
    memset(B,0,sizeof(B));
    find_inverse(D,(n+1)/2);
    for(int i=0;i<(n+1)/2;i++)
        B[i]=1LL*B[i]*((MOD+1)/2)%MOD;
    int len=dbit(n)*2;
    ntt(len,D,1);
    for(int i=0;i<len;i++)
        D[i]=1LL*D[i]*D[i]%MOD;
    ntt(len,D,-1);
    for(int i=0;i<n;i++)
        D[i]=(D[i]+A[i])%MOD;
    ntt(len,D,1);ntt(len,B,1);
    for(int i=0;i<len;i++)
        D[i]=1LL*D[i]*B[i]%MOD;
    ntt(len,D,-1);
    for(int i=n;i<2*n;i++) D[i]=0;
}
int main()
{
	for(int i=1;i<=30;i++)
        two[i]=pow_mod(1<<i,MOD-2);
    A[0]=1;
    A[1]=MOD-2;
    A[2]=1;
    find_sqr(A,4);
    for(int i=0;i<4;i++) printf("%d ",D[i]);
    return 0;
}