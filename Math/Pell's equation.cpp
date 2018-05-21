#include<bits/stdc++.h>
#define MAXN 10005
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
P Pell(int N)
{
	int p0=0,p1=1,q0=1,q1=0;
	int a0=(int)sqrt(N),a1=a0,a2=a0;
	if(a0*a0==N) return P(-1,-1);
	int g1=0,h1=1;
	while(true)
	{
		int g2=-g1+a1*h1;
		int h2=(N-g2*g2)/h1;
		a2=(g2+a0)/h2;
		int p2=a1*p1+p0;
		int q2=a1*q1+q0;
		if(p2*p2-N*q2*q2==1) return P(p2,q2);
		a1=a2;g1=g2;h1=h2;p0=p1;p1=p2;q0=q1;q1=q2;
	}
}
int main()
{
	int n;
	while(scanf("%d",&n)==1)
	{
		P p=Pell(n);
		printf("%d %d\n",p.F,p.S);
	}
	return 0;
}