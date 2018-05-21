#include<bits/stdc++.h>
#define MAXN 10000
using namespace std;
pair<int,int> linear_congruence(const vector<int>&A, const vector<int>&B, const vector<int>&M)
{
    int x=0,m=1;
    for(int i=0;i<A.size();i++)
    {
        int a=A[i]*m,b=B[i]-A[i]*x,d=gcd(M[i],a);
        if(b%d!=0) return make_pair(0,-1);
        int t=b/d*mod_inverse(a/d,M[i]/d)%(M[i]/d);
        x=x+m*t;
        m*=M[i]/d;
    }
    return make_pair(x%m,m);
}
