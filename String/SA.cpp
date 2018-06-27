#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;
int n,k;
int r[MAXN+1];
int sa[MAXN],lcp[MAXN];
int c[MAXN],t1[MAXN],t2[MAXN];
string S;
void construct_sa(string S,int *sa) 
{
    int n=S.length()+1;
    int m=130;
    int i,*x=t1,*y=t2;
    for(i=0;i<m;i++) c[i]=0;
    for(i=0;i<n;i++) c[x[i]=S[i]]++;
    for(i=1;i<m;i++) c[i]+=c[i-1];
    for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
    for(int k=1;k<=n;k<<=1) {
        int p=0;
        for(i=n-k;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
        for(i=0;i<m;i++) c[i]=0;
        for(i=0;i<n;i++) c[x[y[i]]]++;
        for(i=0;i<m;i++) c[i]+=c[i-1];
        for(i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1; x[sa[0]]=0;
        for(i=1;i<n;i++) 
            x[sa[i]]=y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]?p-1:p++;
        if(p>=n) break;
        m=p;
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
