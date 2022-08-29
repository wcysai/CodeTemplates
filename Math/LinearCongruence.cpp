#include<bits/stdc++.h>
#define MAXN 10000
using namespace std;
//A_ix = B_i mod M_i
ll extgcd(ll a,ll b,ll &x,ll &y)//ax+by=gcd(a,b)
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
int mod_inverse(int a,int m)//ax+km=1
{
    int x,y;
    extgcd(a,m,x,y);
    return (m+x%m)%m;
}
pair<int,int> linear_congruence(const vector<int>&A, const vector<int>&B, const vector<int>&M)
{
    int x=0,m=1;//sol=x mod m
    for(int i=0;i<A.size();i++)
    {
        int a=A[i]*m,b=B[i]-A[i]*x,d=gcd(M[i],a);
        if(b%d!=0) return make_pair(0,-1);
        int t=b/d*mod_inverse(a/d,M[i]/d)%(M[i]/d);
        x=x+m*t; m*=M[i]/d;
    }
    return make_pair(x%m,m);
}
