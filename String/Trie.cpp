#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int tot=1,n;
int trie[MAXN][26];
bool ed[MAXN];
void insert(char *s,int rt)
{
    for(int i=0;s[i];i++)
    {
        int x=s[i]-'a';
        if(trie[rt][x]==0) trie[rt][x]=++tot;
        rt=trie[rt][x];
    }
    ed[rt]=true;
}
bool find(char *s,int rt)
{
    for(int i=0;s[i];i++)
    {
        int x=s[i]-'a';
        if(trie[rt][x]==0) return false;
        rt=trie[rt][x];
    }
    return ed[rt];
}
int main()
{
    memset(ed,false,sizeof(ed));
    return 0;
}

