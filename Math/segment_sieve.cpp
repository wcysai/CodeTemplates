#include<bits/stdc++.h>
#define MAXL 1000005
#define MAXSQRTB 47000
#define INF 1000000000
using namespace std;
typedef long long ll;
bool is_prime_small[MAXSQRTB];
bool is_prime[MAXL];
vector<ll> prime;
void segment_sieve(ll a,ll b)
{
    for(ll i=0;(ll)i*i<=b;i++) is_prime_small[i]=true;
    for(ll i=0;i<b-a;i++) is_prime[i]=true;
    for(ll i=2;(ll)i*i<=b;i++)
    {
        if(is_prime_small[i])
        {
            for(ll j=2*i;(ll)j*j<=b;j+=i) is_prime_small[j]=false;
            for(ll j=max(2LL,(a+i-1)/i)*i;j<b;j+=i) is_prime[j-a]=false;
        }
    }
    for(ll i=0;i<b-a;i++)
        if(is_prime[i]&&a+i!=1) prime.push_back(a+i);
}
