#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct Edge{
    int u,v;
    Edge(int u=0,int v=0):u(u),v(v){}
}e[MAXM];
int n,m,stamp,dfn[MAXN],low[MAXN],iscut[MAXN],bccno[MAXN];
int scnt,st[MAXM],bcc_cnt;
vector<int> vec[MAXN],bcc[MAXN];

void tarjan(int tot,int fa)
{
    int child=0,tmp;
    dfn[tot]=low[tot]=++stamp;
    for(int i=0;i<vec[tot].size();i++)
    {
        tmp=e[vec[tot][i]].v;
        if(!dfn[tmp])
        {
            st[++scnt]=vec[tot][i],child++;
            tarjan(tmp,tot);
            low[tot]=min(low[tot],low[tmp]);
            if(low[tmp]>=dfn[tot])
            {
                iscut[tot]=1;
                bcc[++bcc_cnt].clear();
                while(1)
                {
                    int num=st[scnt--];
                    if(bccno[e[num].u]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(e[num].u);
                        bccno[e[num].u]=bcc_cnt;
                    }
                    if(bccno[e[num].v]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(e[num].v);
                        bccno[e[num].v]=bcc_cnt;
                    }
                    if(e[num].u==tot && e[num].v==tmp)
                        break;
                }
            }
        }
        else if(dfn[tmp]<dfn[tot] && tmp!=fa)
        {
            st[++scnt]=vec[tot][i];
            low[tot]=min(low[tot], dfn[tmp]);
        }
    }
    if(fa<0 && child==1)
        iscut[tot]=0;
}

void find_bcc()
{
    // 割顶的bccno值无意义 
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    memset(bcc,0,sizeof(bcc));
    stamp=scnt=bcc_cnt=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,-1);
}
int main()
{
    return 0;
}
