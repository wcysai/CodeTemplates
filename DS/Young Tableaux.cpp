#include<bits/stdc++.h>
#define MAXN 5005
#define MAXM 305
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
int t[MAXN];
int young[MAXM][MAXM];
void ins(int v)
{
    for(int i=1;;i++)
    {
        if(t[i]==0||v>=young[i][t[i]])
        {
            young[i][++t[i]]=v;
            break;
        }
        int pos=upper_bound(young[i]+1,young[i]+t[i]+1,v)-young[i];
        swap(young[i][pos],v);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        ins(a[i]);
    }
    int x=0;
    for(int i=1;;i++)
    {
        x+=t[i];
        printf("%d\n",x);
        if(x==n) break;
    }
    return 0;
}
