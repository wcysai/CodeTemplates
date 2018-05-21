#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#define MAXN 64
using namespace std;
typedef vector<int> vec;
typedef vector<vec> mat;
mat add(mat A,mat B)
{
    mat C(A.size(),vec(A[0].size()));
    for(int i=0;i<A.size();i++)
        for(int j=0;j<A[0].size();j++)
          C[i][j]=A[i][j]+B[i][j];
    return C;
}
mat sub(mat A,mat B)
{
    mat C(A.size(),vec(A[0].size()));
    for(int i=0;i<A.size();i++)
        for(int j=0;j<A[0].size();j++)
          C[i][j]=A[i][j]-B[i][j];
    return C;
}
mat mul(mat A,mat B)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<A.size();i++)
    {
        for(int k=0;k<B.size();k++)
        {
            for(int j=0;j<B[0].size();j++)
            {
                C[i][j]=(C[i][j]+A[i][k]*B[k][j]);
            }
        }
    }
    return C;
}
mat Strassen(mat A,mat B)
{
    if (A.size()==1) return mul(A,B);
    mat C(A.size(),vec(B[0].size()));
    int mid=A.size()/2;
    mat A11(mid,vec(mid));
    mat A12(mid,vec(mid));
    mat A21(mid,vec(mid));
    mat A22(mid,vec(mid));
    mat B11(mid,vec(mid));
    mat B12(mid,vec(mid));
    mat B21(mid,vec(mid));
    mat B22(mid,vec(mid));
    mat P1(mid,vec(mid));
    mat P2(mid,vec(mid));
    mat P3(mid,vec(mid));
    mat P4(mid,vec(mid));
    mat P5(mid,vec(mid));
    mat P6(mid,vec(mid));
    mat P7(mid,vec(mid));
    for(int i=0;i<mid;i++)
    {
        for(int j=0;j<mid;j++)
        {
            A11[i][j]=A[i][j];
            B11[i][j]=B[i][j];
        }
    }
     for(int i=mid;i<A.size();i++)
    {
        for(int j=0;j<mid;j++)
        {
            A12[i-mid][j]=A[i][j];
            B12[i-mid][j]=B[i][j];
        }
    }
     for(int i=0;i<mid;i++)
    {
        for(int j=mid;j<A.size();j++)
        {
            A21[i][j-mid]=A[i][j];
            B21[i][j-mid]=B[i][j];
        }
    }
     for(int i=mid;i<A.size();i++)
    {
        for(int j=mid;j<A.size();j++)
        {
            A22[i-mid][j-mid]=A[i][j];
            B22[i-mid][j-mid]=B[i][j];
        }
    }
    P1=Strassen(A11,sub(B12,B22));
    P2=Strassen(add(A11,A12),B22);
    P3=Strassen(add(A21,A22),B11);
    P4=Strassen(A22,sub(B21,B11));
    P5=Strassen(add(A11,A22),add(B11,B22));
    P6=Strassen(sub(A12,A22),add(B21,B22));
    P7=Strassen(sub(A11,A21),add(B11,B12));
     for(int i=0;i<mid;i++)
    {
        for(int j=0;j<mid;j++)
        {
            C[i][j]=P5[i][j]+P4[i][j]-P2[i][j]+P6[i][j];
        }
    }
     for(int i=mid;i<A.size();i++)
    {
        for(int j=0;j<mid;j++)
        {
            C[i][j]=P1[i-mid][j]+P2[i-mid][j];
        }
    }
     for(int i=0;i<mid;i++)
    {
        for(int j=mid;j<A.size();j++)
        {
            C[i][j]=P3[i][j-mid]+P4[i][j-mid];
        }
    }
     for(int i=mid;i<A.size();i++)
    {
        for(int j=mid;j<A.size();j++)
        {
            C[i][j]=P1[i-mid][j-mid]+P5[i-mid][j-mid]-P3[i-mid][j-mid]-P7[i-mid][j-mid];
        }
    }
    return C;
}
int main()
{
    int n;
    scanf("%d",&n);
    mat A(n,vec(n));
    mat B(n,vec(n));
    mat C(n,vec(n));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
          scanf("%d",&A[i][j]);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
          scanf("%d",&B[i][j]);
    C=Strassen(B,A);
     for(int i=0;i<n;i++)
     {
        for(int j=0;j<n;j++)
          if(j!=n-1) printf("%d ",C[i][j]); else printf("%d",C[i][j]);
        printf("\n");
     }
     C=Strassen(A,B);
     for(int i=0;i<n;i++)
     {
        for(int j=0;j<n;j++)
          if(j!=n-1) printf("%d ",C[i][j]); else printf("%d",C[i][j]);
        if(i!=n-1) printf("\n");
     }
    return 0;
}
