#include<bits/stdc++.h>
using namespace std;
typedef __int64 ll;
ll extgcd(ll a,ll b,ll &x,ll &y)
{
    ll d=a;
    if(b!=0)
    {
        d=extgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else
    {
        x=1;
        y=0;
    }
    return d;
}
ll a,b,x,y;
int main()
{
    while(scanf("%I64d%I64d",&a,&b)==2)
    {
        if(extgcd(a,b,x,y)==1)
        {
            while(x<0)
            {
                x+=b;
                y-=a;
            }
        printf("%I64d %I64d\n",x,y);
        }
        else puts("sorry");
    }
    return 0;
}
