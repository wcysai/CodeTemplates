#include<bits/stdc++.h>
#define MAXN 105
#define MAXM 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef double db;
typedef vector<db> vec;
typedef vector<vec> mat;
//usage:
//maximize cx, where x is a vector of length n, with m constraints
//feed in m+1 lines
//first line contains (0,c)
//each of the next lines describe an inequality ax<=b in the form of (b,a)
const db eps=1e-8;
bool eq(db a,db b)
{
    return fabs(a-b)<eps;
}
bool ls(db a,db b)
{
    return a<b&&!eq(a,b);
}
vec simplex(mat a)
{
    int n=(int)a.size()-1;
    int m=(int)a[0].size()-1;
    vec left(n+1),up(m+1);
    iota(up.begin(),up.end(),1);
    iota(left.begin(),left.end(),m+1);
    auto pivot=[&](int x,int y)
    {
        swap(left[x],up[y]);
        db k=a[x][y];
        a[x][y]=1;
        vector<int> vct;
        for(int j=0;j<=m;j++)
        {
            a[x][j]/=k;
            if(!eq(a[x][j],0)) vct.push_back(j);
        }
        for(int i=0;i<=n;i++)
        {
            if(eq(a[i][y],0)||i==x) continue;
            db coef=a[i][y];
            a[i][y]=0;
            for(int j:vct) a[i][j]-=coef*a[x][j];
        }
    };
    while(1)
    {
        int x=-1;
        for(int i=1;i<=n;i++) if(ls(a[i][0],0)&&(x==-1||a[i][0]<a[x][0])) x=i;
        if(x==-1) break;
        int y=-1;
        for(int j=1;j<=m;j++) if(ls(a[x][j],0)&&(y==-1||a[x][j]<a[x][y])) y=j;
        assert(y!=-1);
        pivot(x,y);
    }
    while(1)
    {
        int y=-1;
        for(int j=1;j<=m;j++) if(ls(0,a[0][j])&&(y==-1||a[0][j]>a[0][y])) y=j;
        if(y==-1) break;
        int x=-1;
        for(int i=1;i<=n;i++) if(ls(0,a[i][y])&&(x==-1||a[i][0]/a[i][y]<a[x][0]/a[x][y])) x=i;
        assert(x!=-1);
        pivot(x,y);
    }
    vector<db> ans(m+1);
    for(int i=1;i<=n;i++) if(left[i]<=m) ans[left[i]]=a[i][0];
    ans[0]=-a[0][0];
    return ans;
}
