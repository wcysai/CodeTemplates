#include<bits/stdc++.h>
#define MAXN 10000005
#define INF 100000000
#define MOD 100000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef __int128 lll;
struct frac
{
    ll x,y;
    frac(ll _x=0,ll _y=0) {x=_x; y=_y;}
    frac operator +(const frac &t) const
    {
        return frac(x+t.x,y+t.y);
    }
}st[MAXN],L,R,M;

int T;
ll n;
bool inR(ll x,ll y) {return x*y<=n;}
double slope(ll x) {return (double)n/x/x;}

inline void write(lll x){
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

inline void writeln(const lll &x){
    write(x);
    putchar('\n');
}

lll solve(ll n)
{
    lll ret=0;
    int t=0,rt=cbrt(n);
    st[++t]=frac(1,0);
    st[++t]=frac(1,1);
    ll m=sqrt(n),x=n/m,y=m+1;
    while(true)
    {
        for(L=st[t--];!inR(x+L.x,y-L.y);x+=L.x,y-=L.y)
            ret+=x*L.y+(L.y+1)*(L.x-1)/2;
        if(y<=rt) break;
        for(R=st[t];inR(x+R.x,y-R.y);R=st[--t]) L=R;
        while(true)
        {
            M=L+R;
            if(!inR(x+M.x,y-M.y)) st[++t]=(R=M);
            else
            {
                if(slope(x+M.x)<=(double)R.y/R.x) break;
                L=M;
            }
        }
    }
    for(int i=1;i<y;i++) ret+=n/i;
    return ret*2-1LL*m*m;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        writeln(solve(n));
    }
    return 0;
}
