#include<bits/stdc++.h>
typedef long long ll;
ll mul(ll A,ll B,ll mod)
{
    return (A*B-(ll)((long double)A*B/mod)*mod+mod)%mod;
}
