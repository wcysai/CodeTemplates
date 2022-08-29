#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;
int sa[MAXN],rk[MAXN],oldrk[MAXN*2],id[MAXN],px[MAXN],c[MAXN];
string S;
bool cmp(int x,int y,int w)
{
    return oldrk[x]==oldrk[y]&&oldrk[x+w]==oldrk[y+w];
}
void construct_sa(string S) 
{
    int n=S.length();
    int m=130;
    int i,p,w;
    for(i=1;i<=n;i++) c[i]=0;
    for(i=1;i<=n;i++) ++c[rk[i]=S[i-1]];
    for(i=1;i<=m;i++) c[i]+=c[i-1];
    for(i=n;i>=1;i--) sa[c[rk[i]]--]=i;
    for(w=1;;w<<=1,m=p) {
        for(p=0,i=n;i>n-w;i--) id[++p]=i;
        for(i=1;i<=n;i++) if(sa[i]>w) id[++p]=sa[i]-w;
        memset(c,0,sizeof(c));
        for(i=1;i<=n;i++) ++c[px[i]=rk[id[i]]];
        for(i=1;i<=m;i++) c[i]+=c[i-1];
        for(i=n;i>=1;i--) sa[c[px[i]]--]=id[i];
        memcpy(oldrk,rk,sizeof(rk));
        for(p=0,i=1;i<=n;i++)
            rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
        if(p==n){
            for(int i=1;i<=n;i++) rk[i-1]=rk[i]-1;;
            for(int i=0;i<n;i++) sa[rk[i]]=i;
            break;
        }
    }
}
void construct_lcp(string S,int *sa,int *lcp)
{
    int n=S.length();
    for(int i=0;i<=n;i++) r[sa[i]]=i;
    int h=0;
    lcp[0]=0;
    for(int i=0;i<n;i++)
    {
        int j=sa[r[i]-1];
        if(h>0) h--;
        for(;j+h<n&&i+h<n;h++)
        {
            if(S[j+h]!=S[i+h]) break;
        }
        lcp[r[i]-1]=h;
    }
}
int main()
{
    cin>>S;
    n=S.size();
    construct_sa(S,sa);
    construct_lcp(S,sa,lcp);
    int cnt=0;
    return 0;
}
