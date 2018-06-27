#include<bits/stdc++.h>
#define MAXN 101
using namespace std;
double x[MAXN],y[MAXN];
int n;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%lf %lf",&x[i],&y[i]);
    double a;
    while(scanf("%lf",&a)==1)
    {
        double s=0;
        for(int i=0;i<n;i++)
        {
            double res=1;
            for(int j=0;j<n;j++)
                if(j!=i) res=res*(a-x[j]);
            for(int j=0;j<n;j++)
                if(j!=i) res=res/(x[i]-x[j]);
            res=res*y[i];
            s+=res;
        }
        printf("%lf\n",s);
    }
    return 0;
}
