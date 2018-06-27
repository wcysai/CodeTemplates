#include<bits/stdc++.h>
#define MAXN 10000
using namespace std;
void manacher(char str[],int len[],int n)
{
    len[0]=1;
    for(int i=1,j=0;i<(n<<1)-1;++i)
    {
        int p=i>>1,q=i-p,r=((j+1)>>1)+len[j]-1;
        len[i]=r<q?0:min(r-q+1,len[(j<<1)-i]);
        while(p>len[i]-1&&q+len[i]<n&&str[p-len[i]]==str[q+len[i]])
            ++len[i];
        if(q+len[i]-1>r)
            j=i;
    }
}
int a[MAXN];
char str[MAXN];
int main()
{
    scanf("%s",str);
    int x=strlen(str);
    manacher(str,a,strlen(str));
    for(int i=0;i<2*x-1;i++)
      printf("%d ",a[i]);
}
