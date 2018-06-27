#include<bits/stdc++.h>
#define MAXN 500005
#define MOD 998244353
#define INF 1000000000
#define F first
#define S second
using namespace std;  
typedef long long ll;
typedef pair<int,int> P;
const int g=3;
int tot=1;
int dbit(int x)
{
    while((x&-x)!=x) x+=x&-x;
    return x;
}
int two[32];
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
int A[MAXN],B[MAXN],C[10000000];
struct atom
{
    int l,r;
};
atom solve(int l,int r)
{
    if (l>r){ C[++tot]=1; return (atom){tot,tot};}
    if (l==r){ C[++tot]=l; C[++tot]=1; return (atom){tot-1,tot};}
    int mid=(l+r)/2; atom k1=solve(l,mid),k2=solve(mid+1,r);
    int n=max(mid-l+1,r-mid),sz=1;
    while (sz<=(n<<1)) sz*=2;
    for (int i=0;i<sz;i++){A[i]=0; B[i]=0;}
    for (int i=k1.l;i<=k1.r;i++) A[i-k1.l]=C[i]; 
    for (int i=k2.l;i<=k2.r;i++) B[i-k2.l]=C[i];
    ntt(sz,A,1); ntt(sz,B,1);
    for (int i=0;i<sz;i++) A[i]=1LL*A[i]*B[i]%MOD;
    ntt(sz,A,-1);
    atom ans; ans.l=tot+1;
    for (int i=0;i<=r-l+1;i++) C[++tot]=A[i]; 
    ans.r=tot; 
    return ans;
}
int n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=30;i++)
        two[i]=pow_mod(1<<i,MOD-2);
    atom ans=solve(0,n-1); 
    for(int i=ans.l;i<=ans.r;i++)
        printf("%d ",C[i]);
    return 0;  
}
