#include <bits/stdc++.h>
#define MAXN 400005
#define MOD 1000000007
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const double PI=acos(-1.0);
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
struct Complex
{
    double x,y;
    Complex(double _x = 0.0,double _y = 0.0)
    {
        x=_x;
        y=_y;
    }
    Complex operator-(const Complex &b)const
    {
        return Complex(x-b.x,y-b.y);
    }
    Complex operator +(const Complex &b)const
    {
        return Complex(x+b.x,y+b.y);
    }
    Complex operator *(const Complex &b)const
    {
        return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
    }
    Complex conj() 
    {
        return Complex(x,-y);
    }
};
void change(Complex y[],int len)
{
    int i,j,k;
    for(i=1,j=len/2;i<len-1;i++)
    {
       if(i<j)swap(y[i],y[j]);
       k = len/2;
       while(j>=k)
        {
            j-=k;
            k/=2;
        }
        if(j<k) j+=k;
    }
}
Complex roots[MAXN];
void fft(Complex y[],int len,int on)
{
    change(y,len);
    double ang=2*acos(-1)/len*on;
    for(int i=0; i<len/2; i++)
        roots[i]=Complex(cos(ang*i),sin(ang*i));
    for(int h=2;h<=len;h<<=1)
    {
        for(int j=0;j<len;j+=h)
        {
            for(int k=0;k<h/2;k++)
            {
                Complex u=y[j+k];
                Complex t=roots[len/h*k]*y[j+k+h/2];
                y[j+k]=u+t;
                y[j+k+h/2]=u-t;
            }
        }
    }
    if(on==-1)
    for(int i=0;i<len;i++)
        {y[i].x/=len;y[i].y/=len;}
}
int dbit(int x)
{
    while(x!=(x&-x)) x+=(x&-x);
    return x;
}
const int base=1<<15;
int n,k;
int x[MAXN],y[MAXN],ret[MAXN];
Complex A[MAXN],B[MAXN],iA[MAXN],iB[MAXN];
void mult(int x[],int y[],int ret[],int len)
{
    for(int i=0;i<len;i++) A[i]=Complex(x[i]/base,x[i]%base),B[i]=Complex(y[i]/base,y[i]%base);
    fft(A,len,1);fft(B,len,1);
    for(int i=0;i<len;i++) 
    {
        int j=(i?(len-i):i);
        Complex a1=(A[i]+A[j].conj())*Complex(0.5,0);
        Complex a0=(A[i]-A[j].conj())*Complex(0,-0.5);
        Complex b1=(B[i]+B[j].conj())*Complex(0.5,0);
        Complex b0=(B[i]-B[j].conj())*Complex(0,-0.5);
        iA[i]=(a1*b1)+(a1*b0)*Complex(0,1);
        iB[i]=(a0*b1)+(a0*b0)*Complex(0,1);
    }
    fft(iA,len,-1);fft(iB,len,-1);
    for(int i=0;i<len;i++)
    {
        ll av=(ll)round(iA[i].x);ll bv=(ll)round(iA[i].y)+(ll)round(iB[i].x);ll cv=(ll)round(iB[i].y);
        av%=MOD;bv%=MOD;cv%=MOD;
        ret[i]=((av*base*base+bv*base+cv)%MOD+MOD)%MOD;
    }
}
int main()
{
    string str1;
    string str2;
    cin>>str1>>str2;
    for(int i=0;i<str1.size();i++)
        x[str1.size()-1-i]=str1[i]-'0';
    for(int i=0;i<str2.size();i++)
        y[str2.size()-1-i]=str2[i]-'0';
    int len=dbit(str1.size()+str2.size());
    mult(x,y,len);
    for(int i=0;i<len;i++)
        if(ret[i]>=10) {ret[i+1]+=ret[i]/10; ret[i]%=10;}
    bool f=false;
    for(int i=len-1;i>=0;i--)
    {
        if(ret[i]>0) f=true;
        if(f) printf("%d",ret[i]);
    }
    return 0;
}
