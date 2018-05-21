#include<bits/stdc++.h>
#define MAXN 50020
using namespace std;
struct trie
{
    trie* next[26];
    trie* fail;
    bool mark;
};
trie* thead;
char str[MAXN][1001];
inline trie*  newnode()
{
    trie* t;
    t=(trie*)malloc(sizeof(trie));
    t->fail=NULL;
    t->mark=false;
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
    s->mark=true;
    return;
}
trie* g(trie* s, char x)
{
    if(s->next[x-'a']) return s->next[x-'a'];
    else if(s==thead) return thead;
    else return NULL;
}

void bfs()
{
    trie* s=thead;
    queue<trie*> que;
    for(int i=0;i<26;i++)
        if(s->next[i]){s->next[i]->fail=thead; que.push(s->next[i]);}
    while(!que.empty())
    {
        trie* t=que.front();
        que.pop();
        for(int i=0;i<26;i++)
            if(g(t,(char)('a'+i))!=NULL)
            {
                que.push(t->next[i]);
                trie* v=t->fail;
                while(g(v,(char)('a'+i))==NULL) v=v->fail;
                t->next[i]->fail=g(v,(char)('a'+i));
            }
    }
    return;
}
int match(char x[])
{
    trie* s=thead;
    int cnt=0;
    for(int i=0;x[i];i++)
    {
        while(g(s,x[i])==NULL)
        {
            s=s->fail;
            if(s->mark) cnt++;
        }
        s=g(s,x[i]);
        if(s->mark) cnt++;
    }
     while(s->fail!=thead)
     {
        s=s->fail;
        if(s->mark) cnt++;
     }
    return cnt;
}
bool find(char x[])
{
    trie* s=thead;
    for(int i=0;x[i];i++)
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
    bfs();
    char p[100];
    scanf("%s",p);
    printf("%d\n",match(p));
    deltrie(thead);
    return 0;
}
