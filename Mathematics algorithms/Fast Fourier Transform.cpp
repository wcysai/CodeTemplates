#include <bits/stdc++.h>
#define MAXN 400005
using namespace std;
const double PI=acos(-1.0);
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
void fft(Complex y[],int len,int on)
{
    change(y,len);
    for(int h=2;h<=len;h<<=1)
    {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j=0;j<len;j+=h)
        {
            Complex w(1,0);
            for(int k=j;k<j+h/2;k++)
            {
                Complex u=y[k];
                Complex t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
    for(int i=0;i<len;i++)
        {y[i].x/=len;y[i].y/=len;}
}
Complex x1[MAXN],x2[MAXN],x3[MAXN];
int a[MAXN],res1[MAXN],res2[MAXN],res3[MAXN];
int n,s;
int main()
{
    scanf("%d",&n);
    memset(a,0,sizeof(a));
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        a[x+20000]++;
    }
    int len=1;
    while(len<40000*4)
        len<<=1;
    for(int i=0;i<len;i++)
        x1[i]=x2[i]=x3[i]=Complex((double)a[i],0);
    fft(x1,len,1);
    for(int i=0;i<len;i++)
        x1[i]=x1[i]*x1[i]*x1[i];
    fft(x1,len,-1);
    for(int i=0;i<len-60000;i++)
        res1[i]=(int)(x1[i+60000].x+0.5);
    for(int i=0;i<len;i++)
        if(i&1) x1[i]=Complex(0,0); else x1[i]=x2[i/2];
    fft(x1,len,1);
    fft(x2,len,1);
    for(int i=0;i<len;i++)
        x1[i]=x1[i]*x2[i];
    fft(x1,len,-1);
    for(int i=0;i<len-60000;i++)
        res2[i]=(int)(x1[i+60000].x+0.5);
    for(int i=0;i<len;i++)
        if(i%3!=0) x1[i]=Complex(0,0); else x1[i]=x3[i/3];
    for(int i=0;i<len-60000;i++)
        res3[i]=(int)(x1[i+60000].x+0.5);
    for(int i=0;i<=10;i++)
        printf("%d %d %d %d\n",res1[i],res2[i],res3[i],(res1[i]-3*res2[i]+2*res3[i])/6);
    return 0;
}
