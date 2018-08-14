#include<bits/stdc++.h>
#define MAXV 10000
#define MAXE 1000
#define INF 1000000
using namespace std;
int d[MAXV][MAXV];
int V;
void floyd_warshall()
{
    for(int k=0;k<V;k++)
        for(int i=0;i<V;i++)
          for(int j=0;j<V;j++) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
int main()
{
    return 0;
}
