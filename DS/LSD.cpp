#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
int ans[MAXN];
vector<int> G[MAXN];
struct state
{
    vector<int> *a;//reversed depth array
    int sz()
    {
        return a->size();
    }
    void add(int i,int val)
    {
        (*a)[i]+=val;
    }
}s[MAXN];
state pull(state z)
{
    if(z.sz()==0)
    {
        state c;
        c.a=new vector<int> (1,1);
        return c;
    }
    else
    {
        state c;
        c.a=z.a;
        c.a->push_back(0);;
        c.add(c.sz()-1,1);
        return c;
    }
}
state merge(state a,state b)
{
    if(a.sz()<b.sz()) swap(a,b);
    int bs=b.sz();
    int as=a.sz();
    for(int i=0;i<bs;i++) a.add(as-i-1,(*(b.a))[bs-i-1]);
    return a;
}
void dfs(int v,int p)
{
    s[v].a=new vector<int>(0);
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        s[v]=merge(s[v],s[to]);
    }
    s[v]=pull(s[v]);
}
int main()
{
    return 0; 
}

