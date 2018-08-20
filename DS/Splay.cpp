#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int ch[MAXN][2],f[MAXN],size[MAXN],cnt[MAXN],key[MAXN];
int sz,root;
inline void clear(int x)
{
    ch[x][0]=ch[x][1]=f[x]=size[x]=cnt[x]=key[x]=0;
}
inline bool get(int x)
{
    return ch[f[x]][1]==x;
}
inline void pushup(int x)
{
    if (x)
    {
        size[x]=cnt[x];
        if (ch[x][0]) size[x]+=size[ch[x][0]];
        if (ch[x][1]) size[x]+=size[ch[x][1]];
    }
}
inline void rotate(int x)
{
    int old=f[x],oldf=f[old],whichx=get(x);
    ch[old][whichx]=ch[x][whichx^1]; f[ch[old][whichx]]=old;
    ch[x][whichx^1]=old; f[old]=x;
    f[x]=oldf;
    if (oldf) ch[oldf][ch[oldf][1]==old]=x;
    pushup(old); pushup(x);
}
inline void splay(int x,int goal)
{
    for(int fa;(fa=f[x])!=goal;rotate(x))
        if(f[fa]!=goal) rotate((get(x)==get(fa))?fa:x);
    if(goal==0) root=x;
}
inline void insert(int x)
{
    if (root==0){sz++; ch[sz][0]=ch[sz][1]=f[sz]=0; root=sz; size[sz]=cnt[sz]=1; key[sz]=x; return;}
    int now=root,fa=0;
    while(1)
    {
        if (x==key[now])
        {
            cnt[now]++; pushup(now); pushup(fa); splay(now,0); break;
        }
        fa=now;
        now=ch[now][key[now]<x];
        if (now==0)
        {
            sz++;
            ch[sz][0]=ch[sz][1]=0;
            f[sz]=fa;
            size[sz]=cnt[sz]=1;
            ch[fa][key[fa]<x]=sz;
            key[sz]=x;
            pushup(fa);
            splay(sz,0);
            break;
        }
    }
}
inline int find(int x)
{
    int now=root,ans=0;
    while(1)
    {
        if(x<key[now]) now=ch[now][0];
        else
        {
            ans+=(ch[now][0]?size[ch[now][0]]:0);
            if (x==key[now]){splay(now,0); return ans+1;}
            ans+=cnt[now];
            now=ch[now][1];
        }
    }
}
inline int findx(int now,int k)
{
    while(now)
    {
        if(k<=size[ch[now][0]]) now=ch[now][0];
        else if(k<=size[ch[now][0]]+cnt[now]) return key[now];
        else k-=size[ch[now][0]]+cnt[now],now=ch[now][1];
    }
}
inline int pre()
{
    int now=ch[root][0];
    while (ch[now][1]) now=ch[now][1];
    return now;
}
inline int next()
{
    int now=ch[root][1];
    while (ch[now][0]) now=ch[now][0];
    return now;
}
inline void del(int x)
{
    int whatever=find(x);
    if (cnt[root]>1){cnt[root]--; pushup(root); return;}
    if (!ch[root][0]&&!ch[root][1]) {clear(root); root=0; return;}
    if (!ch[root][0])
    { 
        int oldroot=root; root=ch[root][1]; f[root]=0; clear(oldroot); return;
    }
    else if (!ch[root][1])
    {
        int oldroot=root; root=ch[root][0]; f[root]=0; clear(oldroot); return;
    }
    int leftbig=pre(),oldroot=root;
    splay(leftbig,0);
    ch[root][1]=ch[oldroot][1];
    f[ch[oldroot][1]]=root;
    clear(oldroot);
    pushup(root);
}
int main()
{
    int n,opt,x;
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        scanf("%d%d",&opt,&x);
        switch(opt)
        {
            case 1: insert(x); break;
            case 2: del(x); break;
            case 3: printf("%d\n",find(x)); break;
            case 4: printf("%d\n",findx(root,x)); break;
            case 5: insert(x); printf("%d\n",key[pre()]); del(x); break;
            case 6: insert(x); printf("%d\n",key[next()]); del(x); break;
        }
    }
}

