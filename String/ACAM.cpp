#include<bits/stdc++.h>
#define MAXN 50020
#define MAXC 26
using namespace std;
struct aho_corasick 
{
    int cnt=0,kmp[MAXN],ch[MAXN][MAXC],nxt[MAXN][MAXC];
    long long dp[MAXN];
 
    void add(string &s,int c) 
    {
        int cur=0;
        for(char &c:s) 
        {
            if(ch[cur][c-'a']==0) ch[cur][c-'a']=++cnt;
            cur=ch[cur][c-'a'];
        }
        dp[cur]+=c;
    }
 
    void BFS() 
    {
        queue<int> q;
        for(q.push(0);!q.empty();q.pop()) 
        {
            int u=q.front();
            dp[u]+=dp[kmp[u]];
            for(int i=0;i<MAXC;i++) 
            {
                if(ch[u][i]>0) 
                {
                    int v=ch[u][i];
                    q.push(v);
                    nxt[u][i]=v;
                    kmp[v]=nxt[kmp[u]][i];
                    if (kmp[v]==v) kmp[v]=0;
                } 
                else nxt[u][i]=nxt[kmp[u]][i];
            }
        }
    }
 
    pair<long long,int> traverse(string s,int st) 
    {
        long long ret=0;
        for (char &c:s) 
        {
            st=nxt[st][c-'a'];
            ret+=dp[st];
        }
        return {ret,st};
    }
} acs;