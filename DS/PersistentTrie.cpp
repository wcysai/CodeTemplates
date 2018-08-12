#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 2000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN],tot;
int trie[MAXM][2],root[MAXN],sz[MAXM];
int newnode()
{
    ++tot;
    trie[tot][0]=trie[tot][1]=0;
    return tot;
}
void insert(int u,int v,int x)
{
    int now1=root[u]=newnode(),now2=root[v];
    for(int i=18;i>=0;i--)
    {
        int id=(x>>i)&1;
        trie[now1][id]=newnode();
        trie[now1][!id]=trie[now2][!id];
        now1=trie[now1][id];now2=trie[now2][id];
        sz[now1]=sz[now2]+1;
    }
}
int query(int l,int r,int x)
{
    int res=0;
    int now1=root[r+1],now2=root[l];
    for(int i=18;i>=0;i--)
    {
        int id=(x>>i)&1;
        if(sz[trie[now1][!id]]-sz[trie[now2][!id]]>0)
        {
            res+=(1<<i);
            id=!id;
        }
        now1=trie[now1][id];now2=trie[now2][id];
    }
    return res;
}
int main()
{
    return 0;
}

