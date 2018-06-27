#include<bits/stdc++.h>
#define MAXN 1000
using namespace std;
typedef vector<double> vec;
typedef vector<vec> mat;
typedef long long ll;
int n;
mat mul(mat A,mat B)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<A.size();i++)
        for(int k=0;k<B.size();k++)
            for(int j=0;j<B[0].size();j++)
                C[i][j]=(C[i][j]+A[i][k]*B[k][j]);
    return C;
}
mat pow(mat A,ll n)
{
    mat B(A.size(),vec(A.size()));
    for(int i=0;i<A.size();i++)
        B[i][i]=1;
    while(n>0)
    {
        if(n&1) B=mul(B,A);
        A=mul(A,A);
        n>>=1;
    }
    return B;
}
int main()
{
    scanf("%d",&n);
    mat A(n,vec(n));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%lf",&A[i][j]);
    mat L(n,vec(n));
    mat U(n,vec(n));
    for(int i=1;i<n;i++)
        for(int j=0;j<i;j++)
            U[i][j]=0;
    for(int i=0;i<n;i++)
        L[i][i]=1;
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            L[i][j]=0;
    for(int i=0;i<n;i++)
    {
        U[i][i]=A[i][i];
        for(int j=i+1;j<n;j++)
        {
            L[j][i]=A[j][i]/U[i][i];
            U[i][j]=A[i][j];
        }
        for(int j=i+1;j<n;j++)
            for(int k=i+1;k<n;k++)
                A[j][k]=A[j][k]-L[j][i]*U[i][k];
    }
    printf("L=\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            printf("%6lf ",L[i][j]);
        printf("\n");
    }
    printf("U=\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            printf("%6lf ",U[i][j]);
        printf("\n");
    }
}


