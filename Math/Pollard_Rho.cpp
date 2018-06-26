#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
ll pollard_rho(ll n, int a)
{
    ll x = 2, y = 2, d = 1, k = 0, i = 1;
    while(d == 1)
    {
        ++k;
        x = mul_mod(x, x, n) + a;
        d = __gcd(x >= y ? x - y : y - x, n);
        if(k == i)
        {
            y = x;
            i <<= 1;
        }
    }
    if(d == n) return pollard_rho(n, a + 1);
    return d;
}
int main()
{
    return 0;
}

