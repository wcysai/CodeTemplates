#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,sg[2][2]={0,0,0,1};
int nim_mult_pow(int x,int y)
{
    if(x<2)
        return sg[x][y];
    int a=0;
    for(;;a++)
        if(x>=(1<<(1<<a))&&x<(1<<(1<<(a+1))))
            break;
    int m=1<<(1<<a);
    int p=x/m,s=y/m,t=y%m;
    int d1=nim_mult_pow(p,s);
    int d2=nim_mult_pow(p,t);
    return (m*(d1^d2))^nim_mult_pow(m/2,d1);
}

int nim_mult(int x,int y)
{
    if(x<y)
        return nim_mult(y,x);
    if(x<2)
        return sg[x][y];
    int a=0;
    for(;;a++)
        if(x>=(1<<(1<<a))&&x<(1<<(1<<(a+1))))
            break;
    int  m=1<<(1<<a);
    int p=x/m,q=x%m,s=y/m,t=y%m;
    int c1=nim_mult(p,s);
    int c2=nim_mult(p,t)^nim_mult(q,s);
    int c3=nim_mult(q,t);
    return (m*(c1^c2))^c3^nim_mult_pow(m/2,c1);
}
int main()
{
    int x,y;
    while(scanf("%d%d",&x,&y)==2) printf("%d\n",nim_mult(x,y));
}
