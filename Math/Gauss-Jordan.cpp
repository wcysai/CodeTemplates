#include<bits/stdc++.h>
#define MAXN 105
using namespace std;
const double eps=1e-8;
typedef vector<double> vec;
typedef vector<vec> mat;
int sz;
vec gauss_jordan(const mat& A, const vec& b)
{
    int n=A.size();
    mat B(n,vec(n+1));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            B[i][j]=A[i][j];

    for(int i=0;i<n;i++) B[i][n]=b[i];
    for(int i=0;i<n;i++)
    {
        int pivot=i;
        for(int j=i;j<n;j++)
            if(abs(B[j][i])>abs(B[pivot][i])) pivot=j;
        swap(B[i],B[pivot]);
        if(abs(B[i][i])<eps) return vec();
        for(int j=i+1;j<=n;j++) B[i][j]/=B[i][i];
        for(int j=0;j<n;j++)
        {
            if(i!=j)
            {
                for(int k=i+1;k<=n;k++)
                    B[j][k]-=B[j][i]*B[i][k];
            }
        }
    }
    vec x(n);
    for(int i=0;i<n;i++)
        x[i]=B[i][n];
    return x;
}
int main()
{
    scanf("%d",&sz);
    mat A(sz,vec(sz));
    vec b(sz);
    for(int i=0;i<sz;i++)
        for(int j=0;j<sz;j++)
            A[i][j]=0;
    for(int i=0;i<sz;i++)
    {
        double x;
        int cnt=0;
        while(scanf("%lf",&x)==1)
        {
            if(x==-1) break;
            A[x-1][i]=1.0;
        }
    }
    for(int i=0;i<sz;i++)
        b[i]=1.0;
    vec res=gauss_jordan(A,b);
    if(res==vec()) printf("No solution\n");
    else
    {
        for(int i=0;i<sz;i++)
            if(res[i]>0) printf("%d ",i+1);
        printf("\n");
    }
    return 0;
}
