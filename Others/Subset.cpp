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
void solve1(int sup)//all subsets
{
    int sub=sup;
    do
    {
        //operation here
        sub=(sub-1)&sup;
    }while(sub!=sup);
}
void solve2(int n,int k) //all subsets of (1<<n) of size k
{
    int comb=(1<<k)-1;
    while(comb<1<<n)
    {
        //operation here
        int x=comb&-comb,y=comb+x;
        comb=((comb&~y)/x>>1)|y;
    }
}
int main()
{
    return 0;
}

