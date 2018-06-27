#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 23;
const double eps = 1e-8;

double a[N][N], ans[N];
int n, m, t, id[N << 1];

void pivot(int l, int e) 
{
    swap(id[e], id[n + l]);
    double r = a[l][e]; a[l][e] = 1;
    for (int j = 0; j <= n; ++j)
        a[l][j] /= r;
    for (int i = 0; i <= m; ++i)
        if (i != l) {
            r = a[i][e]; a[i][e] = 0;
            for (int j = 0; j <= n; ++j)
                a[i][j] -= r * a[l][j];
        }
}

int main() 
{
    scanf("%d%d", &n, &m);
    int i, j, l, e; double k, kk;
    for (j = 1; j <= n; ++j) scanf("%lf", &a[0][j]), id[j] = j;
    for (i = 1; i <= m; ++i) 
    {
        for (j = 1; j <= n; ++j)
            scanf("%lf", &a[i][j]);
        scanf("%lf", &a[i][0]);
    }
    
    while (true) 
    {
        l = e = 0; k = -eps;
        for (i = 1; i <= m; ++i)
            if (a[i][0] < k) {
                k = a[i][0];
                l = i;
            }
        if (!l) break;
        k = -eps;
        for (j = 1; j <= n; ++j)
            if (a[l][j] < k && (!e || (rand() & 1))) {
                k = a[l][j];
                e = j;
            }
        if (!e) {puts("Infeasible"); return 0;}
        pivot(l, e);
    }
    
    while (true) {
        for (j = 1; j <= n; ++j)
            if (a[0][j] > eps)
                break;
        if ((e = j) > n) break;
        k = 1e18; l = 0;
        for (i = 1; i <= m; ++i)
            if (a[i][e] > eps && (kk = (a[i][0] / a[i][e])) < k) {
                k = kk;
                l = i;
            }
        if (!l) {puts("Unbounded"); return 0;}
        pivot(l, e);
    }
    
    printf("%.10lf\n", -a[0][0]);
    for (i = 1; i <= m; ++i) ans[id[n + i]] = a[i][0];
    for (i = 1; i <= n; ++i) printf("%.10lf ", ans[i]);
    return 0;
}