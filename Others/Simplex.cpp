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
const db eps=1e-8;
//n variables,m constraints
//ith constriant like: \sum_{j=1}^{n} a[i][j] \cdot x[j]\leq a[i][0]
//minimize object function, constraints are \geq
//object function: \sum_{i=1}^{n} a[0][i]\cdot x_{i}
//original: minimize CX constraint AX\geq B
//dual: maximize B^{T}Y constraint A^{T}\leq C^{T}
int n,m,id[MAXN],tp[MAXN];
db a[MAXM][MAXN];
void pivot(int r,int c)
{
    swap(id[r+n],id[c]);
    db t=-a[r][c];
    a[r][c]=-1;
    for(int i=0;i<=n;i++) a[r][i]/=t;
    for(int i=0;i<=m;i++)
    {
        if(a[i][c]&&r!=i)
        {
            t=a[i][c];
            a[i][c]=0;
            for(int j=0;j<=n;j++) a[i][j]+=t*a[r][j];
        }
    }
}
void solve()
{
    db t;
    for(int i=1;i<=n;i++) id[i]=i;
    while(true)
    {
        int i=0,j=0; db w=-eps;
        for(int k=1;k<=m;k++) if(a[k][0]<w) w=a[i=k][0];
        if(!i) break;
        for(int k=1;k<=n;k++) if(a[i][k]>eps) {j=k; break;}
        if(!j) {puts("Infeasible"); return;}
        pivot(i,j);
    }
    while(true)
    {
        int i=0,j=0; db w=eps;
        for(int k=1;k<=n;k++) if(a[0][k]>w) w=a[0][j=k];
        if(!j) break;
        w=INF;
        for(int k=1;k<=m;k++) if(a[k][j]<-eps&&(t=-a[k][0]/a[k][j])<w)
        {
            w=t;
            i=k;
        }
        if(!i) {puts("Unbounded"); return;}
        pivot(i,j);
    }
    printf("%.10f\n",a[0][0]);
    for(int i=n+1;i<=n+m;i++) tp[id[i]]=i-n;
    for(int i=1;i<=n;i++) printf("%.10f",tp[i]?a[tp[i]][0]:0);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lf",&a[0][i]);
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
            scanf("%lf",&a[i][j]),a[i][j]*=-1;
        scanf("%lf",&a[i][0]);
    }
    solve();
    return 0;
}

