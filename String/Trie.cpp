#include<bits/stdc++.h>
#define MAXN 50020
using namespace std;
struct trie
{
    trie* next[26];
};
trie* thead;
char str[MAXN][1001];
inline trie*  newnode()
{
    trie* t;
    t=(trie*)malloc(sizeof(trie));
    memset(t,0,sizeof(trie));
    return t;
}
void insert(char x[])
{
    int i;
    trie* s=thead;
    trie* t;
    for(i=0;x[i];i++)
    {
        if(s->next[x[i]-'a']) {s=s->next[x[i]-'a'];}
        else
        {
            t=newnode();
            s->next[x[i]-'a']=t;
            s=t;
        }
    }
    return;
}
bool find(char x[])
{
    trie* s=thead;
    int i;
    for(i=0;x[i];i++)
    {
        if(s->next[x[i]-'a']==NULL) return false;
        s=s->next[x[i]-'a'];
    }
    return true;
}
void deltrie(trie* s)
{
    int i;
    for(i=0;i<26;i++)
    {
        if(s->next[i])
        deltrie(s->next[i]);
    }
    free(s);
    s=NULL;
}
int main()
{
    int i=0;
    thead=newnode();
    while(scanf("%s",str[i])==1)
    {
        if(str[i][0]=='1') break;
        insert(str[i]);
        i++;
    }
    char x[20];
    while(scanf("%s",x)==1)
        printf(find(x)?"yes\n":"no\n");
    deltrie(thead);
    return 0;
}
