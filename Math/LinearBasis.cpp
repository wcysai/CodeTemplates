#include<bits/stdc++.h>
#define MAXN 1000
using namespace std;
int a[MAXN],bas[62];
int n;
int main()
{
    for(int i=1;i<=n;i++)
    {
        int x=a[i];
        for(int j=60;j>=0;j--)
        {
            if(x&(1ll<<j))
            {
                if(!bas[j])
                {
                    bas[j]=x;
                    break;
                }
                x^=bas[j];
            }
        }
    }
}
